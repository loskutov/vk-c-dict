#ifndef VK_TEST_LIST
#define VK_TEST_LIST

/**
 * A non-owning list of strings
 */
struct list_node {
	char *value;
	struct list_node *next;
};

struct list_node *list_append(struct list_node *list, char *s);
/**
 * Frees the list structure, but not the data stored inside as it's non-owning
 */
void list_free(struct list_node *list);

#endif /* !defined(VK_TEST_LIST) */
