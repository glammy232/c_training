#include <stdio.h>
#include <stdlib.h>
#define VECTOR_INIT_CAPACITY 8
#define VECTOR_TYPE(T, N) \
	struct N { \
		size_t size; \
		size_t capacity; \
		T *data; \
	};\
	\
	void N ## _create(struct N *v, size_t capacity); \
	void N ## _push(struct N *v, T value); \
	void N ## _pop(struct N *v, T *result); \
	void N ## _insert(struct N *v, size_t index, T value); \
	void N ## _remove(struct N *v, size_t index); \
	void N ## _reserve(struct N *v, size_t index); \
	void N ## _shrink_to_fit(struct N *v, size_t capacity); \
	void N ## _destroy(struct N *v);

#define VECTOR_IMPLEMENT(T, N) \
	void N ## _create(struct N *v, size_t capacity) \
	{ \
		v->size = 0; \
		v->capacity = capacity; \
		v->data = malloc(capacity * sizeof(T)); \
		if (!(v->data)) { \
			fprintf(stderr, "data is null.\n"); \
			exit(EXIT_FAILURE); \
		} \
	} \
	void N ## _push(struct N *v, T value) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
		if (v->size >= v->capacity) { \
			struct N *tmp = realloc(v->data, v->capacity * sizeof(T) * 2); \
			if (!tmp) { \
				fprintf(stderr, "failed to realloc.\n"); \
				exit(EXIT_FAILURE); \
			} \
			v = tmp; \
		} \
		if (!(v->data)) { \
			fprintf(stderr, "data is null.\n"); \
			exit(EXIT_FAILURE); \
		} \
		v->data[v->size] = value; \
		v->size++; \
	} \
	void N ## _pop(struct N *v, T *result) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
		if (v->size <= 0) { \
			fprintf(stderr, "incorrect array size.\n"); \
			exit(EXIT_FAILURE); \
		} \
		if (!(v->data)) { \
			fprintf(stderr, "data is null.\n"); \
			exit(EXIT_FAILURE); \
		} \
		*result = v->data[v->size - 1]; \
		v->data[v->size - 1] = 0; \
	} \
	void N ## _insert(struct N *v, size_t index, T value) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
		if (!(v->data)) { \
			fprintf(stderr, "data is null.\n"); \
			exit(EXIT_FAILURE); \
		} \
		if (index >= v->capacity) { \
			fprintf(stderr, "incorrect index of insert.\n"); \
			exit(EXIT_FAILURE); \
		} \
		int steps = v->size - index - 1; \
		if (v->size - 1 + steps >= v->capacity) { \
			fprintf(stderr, "capacity is too low.\n"); \
			exit(EXIT_FAILURE); \
		} \
		size_t i, k; \
		if (steps > 0) { \
			for (i = v->size - 1; i > index; i--) { \
				v->data[i + steps] = v->data[i]; \
			} \
			v->data[index] = value; \
		} else { \
			v->data[index] = value; \
		} \
	} \
	void N ## _remove(struct N *v, size_t index) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
		T temp = v->data[index]; \
		v->data[index] = 0; \
	} \
	void N ## _reserve(struct N *v, size_t index) \
	{ \
	} \
	void N ## _shrink_to_fit(struct N *v, size_t capacity) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
	} \
	void N ## _destroy(struct N *v) \
	{ \
		if (!v) { \
			fprintf(stderr, "incorrect pointer.\n"); \
			exit(EXIT_FAILURE); \
		} \
		free(v); \
	} 

VECTOR_TYPE(int, ivec)
VECTOR_IMPLEMENT(int, ivec)

int main(void)
{
	struct ivec arr;
	int n;
	ivec_create(&arr, VECTOR_INIT_CAPACITY);
	ivec_push(&arr, 1);
	ivec_pop(&arr, &n);
	ivec_insert(&arr, 1, n);
	return 0;
}
