/* DESCRIPTION
 * That 'free' realization can work only with last pointer, what 'alloc' gave;
 */

#include <stdio.h>
#define ALLOCSIZE 10000

struct heap {
	char allocbuf[ALLOCSIZE];
	size_t size;
	size_t capacity;
	char *allocp;
};

struct heap Heap;

void init_heap(size_t size, size_t capacity, char *allocptr)
{
	Heap.size = size;
	Heap.capacity = capacity;
	Heap.allocp = allocptr;
}

void print_heap(struct heap *head)
{
	printf("Heap Data\n");
	printf("size: %zu\n", Heap.size);
	printf("capacity: %zu\n", Heap.capacity);
	printf("ptr: %p\n", Heap.allocp);
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (Heap.allocbuf + ALLOCSIZE - Heap.allocp >= n) {
		Heap.allocp += n;
		Heap.size += n;
		return Heap.allocp - n;
	} else
		return 0;
}

void afree(char *p)
{
	if (p >= Heap.allocbuf && p < Heap.allocbuf + ALLOCSIZE) {
		Heap.allocp = p;
		Heap.size = p - Heap.allocbuf;
	}
}

int main(void)
{
	char *name;
	char *sex;
	char *age;
	char *scream;
	char *voice;
	init_heap(0, ALLOCSIZE, Heap.allocbuf);
	print_heap(&Heap);
	name = alloc(5);
	print_heap(&Heap);
	sex = alloc(10);
	print_heap(&Heap);
	age = alloc(17);
	print_heap(&Heap);
	afree(age);
	afree(sex);
	printf("Truth: 5\n");
	print_heap(&Heap);
	afree(name);
	printf("Truth: 0");
	print_heap(&Heap);
	return 0;
}
