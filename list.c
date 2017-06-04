#include "list.h"

#include <assert.h>
#include <stdlib.h>

void list_free(struct list_node *list)
{
	while (list) {
		struct list_node *next_list = list->next;
		free(list);
		list = next_list;
	}
}

struct list_node *list_append(struct list_node *list, char *s)
{
	struct list_node *new_node = malloc(sizeof(struct list_node));
	if (new_node) {
		new_node->next = list;
		new_node->value = s;
	}
	return new_node;
}
