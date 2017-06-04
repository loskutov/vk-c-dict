#include "hash_table.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_table {
	char **data;
	size_t size; /* guaranteed to be power of two */
};

static uint64_t to_power_of_2(uint64_t n) {
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	return n;
}

static uint64_t hash(const char *s)
{
	uint64_t ans = 0;
	while (*s) {
		ans *= 31;
		ans += *s;
		++s;
	}
	return ans;
}

static void hash_table_insert(struct hash_table *table, char *s)
{
	size_t h = hash(s);
	for (size_t i = 0; i < table->size; ++i) {
		size_t index = (i + h) & (table->size - 1);
		if (!table->data[index]) {
			table->data[index] = s;
			return;
		} else if (!strcmp(table->data[index], s)) {
			return;
		}
	}
	assert(0);
}

int hash_table_build(struct hash_table **res, size_t n, struct list_node *list)
{
	struct hash_table *table = malloc(sizeof(struct hash_table));
	if (!table)
		return -1;
	*res = table;
	table->size = (size_t) to_power_of_2(n) * 2; /* ensures load factor <= 0.5 */
	table->data = calloc(table->size, sizeof(char*));
	if (!table->data)
		return -1;
	while (list) {
		hash_table_insert(table, list->value);
		list = list->next;
	}
	return 0;
}

bool hash_table_query(const struct hash_table *table, const char *s)
{
	size_t h = hash(s);
	for (size_t i = 0; i < table->size; ++i) {
		size_t index = (i + h) & (table->size - 1);
		if (!table->data[index])
			return false;
		else if (!strcmp(table->data[index], s))
			return true;
	}
	assert(0);
}

void hash_table_free(struct hash_table *table)
{
	for (size_t i = 0; i < table->size; ++i)
		free(table->data[i]);
	free(table->data);
	free(table);
}
