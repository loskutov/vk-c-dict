#ifndef VK_TEST_HASH_TABLE
#define VK_TEST_HASH_TABLE

#include <stdbool.h>
#include <stddef.h>

#include "list.h"

struct hash_table;

int hash_table_build(struct hash_table **table, size_t n, struct list_node *list);
bool hash_table_query(const struct hash_table *table, const char *s);
void hash_table_free(struct hash_table *table);

#endif /* !defined VK_TEST_HASH_TABLE */
