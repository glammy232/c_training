#include <stdio.h>
#include <stdlib.h>

char *input0 = "abcabcbb";	/* "abc", "bca", "cab" are correct, output = 3 */
char *input1 = "bbbbb";		/* "b" is correct, output = 1 */
char *input2 = "pwwkew";	/* "wke", "kew" are correct, output = 3 */

/*int lengthOfLongestSubstring(char* s) {
	int i;
	char first_element;
	char last_element;
	for (i = 1; s[i] != '\0'; i++) {
		int j = i;
		first_element = s[i - 1];
		while (first_element != s[j] && s[j] != '\0')
			j++;
		last_element = s[j];
		printf("i = %d, j = %d\n s = %c, e = %c\n r = %d\n",
				i - 1, j, first_element, last_element, j - i);
	}
	return -1; 
}*/

struct Node {
	char v;
	struct Node *next;
};

void add(struct Node *list, char c) {
	struct Node *p = list;

	while (p->next)
		p = p->next;

	p->next = malloc(sizeof(struct Node));
	p->next->v = c;
	p->next->next = NULL;
}

void pd(struct Node *list, int index)
{
	struct Node *p = list;
	int i;
	for (i = 0; i < index; i++) {
		i++;
	}
	printf("%c\n", p->v);
}

void pda(struct Node *list)
{
	struct Node *p = list;
	while (p) {
		printf("%c\n", p->v);
		p = p->next;
	}
}

int lengthOfLongestSubstring(char *s)
{
	int max_length;
	struct Node first = { s[0], NULL };
	first.next = NULL;

	char *p = s;
	p++;

	while (*p) {
		struct Node temp = first;
		while (temp.v) {
			if (temp.v != *p)
				break;
			temp = *temp.next;
		}
		add(&first, *p);
		p++;
	}

	pda(&first);

	return 1;
}

int main(void)
{
	int result = lengthOfLongestSubstring(input0);
	int complete = result == 3;
	printf("%d \n", result);
	
	if (complete)
		printf("TRUE\n");
	else
		printf("FAlSE\n");

	result = lengthOfLongestSubstring(input1);
	printf("%d \n", result);

	complete = result == 1;

	if (complete)
		printf("TRUE\n");
	else
		printf("FAlSE\n");

	result = lengthOfLongestSubstring(input2);
	printf("%d \n", result);

	complete = result == 3;

	if (complete)
		printf("TRUE\n");
	else
		printf("FAlSE\n");

	return 0;
}
