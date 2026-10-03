#include <stdio.h>
#include <stdlib.h>

struct Node {
	char v;
	struct Node *next;
};

struct Node *add(struct Node *tail, char c)
{
	struct Node *n = malloc(sizeof(struct Node));
	n->v = c;
	n->next = NULL;
	tail->next = n;
	return n;
}

void free_list(struct Node *head)
{
	while (head) {
		struct Node *next = head->next;
		free(head);
		head = next;
	}
}

void pda(struct Node *list)
{
	while (list) {
		printf("%c", list->v);
		list = list->next;
	}
	printf("\n");
}

int lengthOfLongestSubstring(char *s)
{
	if (s == NULL || s[0] == '\0')
		return 0;

	struct Node dummy = { 0, NULL };
	struct Node *tail = &dummy;

	int max_length = 0;
	int cur_length = 0;

	for (char *p = s; *p; p++) {
		struct Node *cur = dummy.next;
		struct Node *found = NULL;
		while (cur) {
			if (cur->v == *p) {
				found = cur;
				break;
			}
			cur = cur->next;
		}

		if (found) {
			while (dummy.next != found) {
				struct Node *old = dummy.next;
				dummy.next = old->next;
				free(old);
				cur_length--;
			}
			struct Node *old = dummy.next;
			dummy.next = old->next;
			free(old);
			cur_length--;
		}

		tail = add(tail, *p);
		cur_length++;

		if (cur_length > max_length)
			max_length = cur_length;
	}

	free_list(dummy.next);
	return max_length;
}

int main(void)
{
	char *tests[] = { "abcabcbb", "bbbbb", "pwwkew", "" };
	int expected[] = { 3, 1, 3, 0 };

	for (int i = 0; i < 4; i++) {
		int r = lengthOfLongestSubstring(tests[i]);
		printf("\"%s\" -> %d (expected %d) %s\n",
			   tests[i], r, expected[i],
			   r == expected[i] ? "OK" : "FAIL");
	}
	return 0;
}
