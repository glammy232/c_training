#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Размер линии кэша большинства современных процессоров (x86/ARM)
#define CACHE_LINE_SIZE 64

// Выравнивание структуры для предотвращения False Sharing между потоками
typedef struct {
  uint8_t *buffer;
  size_t capacity; // Должна быть степенью двойки!
  size_t mask;

  // Разделяем индексы чтения и записи по разным линиям кэша,
  // чтобы Producer и Consumer не инвалидировали кэш друг другу.
  _Alignas(CACHE_LINE_SIZE) _Atomic size_t head; // Индекс для чтения
  _Alignas(CACHE_LINE_SIZE) _Atomic size_t tail; // Индекс для записи
} ring_buffer_t;

/**
 * Инициализация буфера.
 * Размер буфера (ОБЯЗАТЕЛЬНО степень двойки, например 1024, 4096)
 */
static inline bool ring_buffer_init(ring_buffer_t *rb, uint8_t *buffer_mem,
                                    size_t capacity) {
  if (!rb || !buffer_mem || (capacity & (capacity - 1)) != 0) {
    return false; // Размер не степень двойки или неверные указатели
  }
  rb->buffer = buffer_mem;
  rb->capacity = capacity;
  rb->mask = capacity - 1;
  atomic_init(&rb->head, 0);
  atomic_init(&rb->tail, 0);
  return true;
}

/**
 * Запись в буфер
 * Использует memory_order_release, чтобы данные гарантированно записались
 * в память до того, как обновится индекс tail.
 */
static inline bool ring_buffer_push(ring_buffer_t *rb, uint8_t data) {
  // Получаем текущие индексы без строгой синхронизации там, где это можно
  size_t current_tail = atomic_load_explicit(&rb->tail, memory_order_relaxed);
  size_t current_head = atomic_load_explicit(&rb->head, memory_order_acquire);

  // Проверка на переполнение буфера
  if ((current_tail - current_head) >= rb->capacity) {
    return false; // Буфер полон
  }

  // Быстрая маска за счет степени двойки (заменяет дорогое деление по модулю)
  rb->buffer[current_tail & rb->mask] = data;

  // Атомарно увеличиваем tail с барьером release
  atomic_store_explicit(&rb->tail, current_tail + 1, memory_order_release);
  return true;
}

/**
 * Чтение из буфера
 * Использует memory_order_acquire, чтобы чтение данных происходило
 * строго после того, как мы увидели обновленный tail.
 */
static inline bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *value) {
  size_t current_head = atomic_load_explicit(&rb->head, memory_order_relaxed);
  size_t current_tail = atomic_load_explicit(&rb->tail, memory_order_acquire);

  if (current_head == current_tail) {
    return false;
  }

  *value = rb->buffer[current_head & rb->mask];

  // Атомарно увеличиваем head с барьером release
  atomic_store_explicit(&rb->head, current_head + 1, memory_order_release);
  return true;
}
