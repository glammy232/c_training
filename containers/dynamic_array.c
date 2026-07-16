#include <stdio.h>
#include <stdlib.h>
#define VECTOR_INIT_SIZE 8
#define VECTOR_TYPE(T) \
	typedef struct { \
		size_t size; \
		size_t capacity; \
		T *data; \
	} T ## _vector_t; \
	\
	void T ## _vector_init(T ## _vector_t *v, size_t capacity); \
	void T ## _vector_insert(T ## _vector_t *v, T value); \
	void T ## _vector_destroy(T ## _vector_t *v);

#define VECTOR_IMPLEMENT(T) \
	void T ## _vector_init(T ## _vector_t *v, size_t capacity) \
	{ \
		v->size = 0; \
		v->capacity = capacity; \
		v->data = malloc(capacity * sizeof(T)); \
		if (!(v->data)) { \
			perror("T ## _vector_init failed: malloc failed.\n"); \
		} \
	} \
	void T ## _vector_insert(T ## _vector_t *v, T value) \
	{ \
		if (v->size >= v->capacity) \
			v->data = realloc(v->data, v->capacity * sizeof(T) * 2); \
		if (!(v->data)) \
			perror("T ## _vector_insert failed: realloc failed.\n"); \
		v->data[v->size] = value; \
		v->size++; \
	}

VECTOR_TYPE(int)
VECTOR_IMPLEMENT(int)
int main(void)
{
	int_vector_t arr;
	printf("init\n");
	int_vector_init(&arr, VECTOR_INIT_SIZE);
	printf("size: %zu\n", arr.size);
	printf("insert\n");
	int_vector_insert(&arr, 1);
	printf("size: %zu\n", arr.size);
	printf("val[0]: %d\n", arr.data[0]);
	printf("insert\n");
	int_vector_insert(&arr, 2);
	printf("val[1]: %d\n", arr.data[1]);
	return 0;
}
