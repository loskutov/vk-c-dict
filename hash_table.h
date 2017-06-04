#ifndef VK_TEST_HASH_TABLE
#define VK_TEST_HASH_TABLE

#include <stdbool.h>
#include <stddef.h>

#include "list.h"

/**
 * A static owning set of strings. Supports building from a list of strings,
 * checking if a string is contained inside it, and freeing, releasing
 * all the memory (included the contained strings) to the OS
 */
struct hash_table;

/**
 * Builds a hash table
 * @table: a pointer where the hash table will be stored
 * @n:     number of strings in @list
 * @list:  a list of strings, each located on heap
 *
 * Returns 0 on success and -1 otherwise
 */
int hash_table_build(struct hash_table **table, size_t n, struct list_node *list);

/**
 * Checks whether a string is stored in the hash table
 * @table: a pointer to the hash table, acquired from @hash_table_build
 * @s:     a string to query
 */
bool hash_table_query(const struct hash_table *table, const char *s);

/**
 * Releases all the resources back to the OS, including the strings stored
 * @table: a pointer to a hash table, acquired from @hash_table_build
 */
void hash_table_free(struct hash_table *table);

#endif /* !defined VK_TEST_HASH_TABLE */
