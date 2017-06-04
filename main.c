#include "list.h"
#include "hash_table.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return -1;
	}

	FILE *file = fopen(argv[1], "r");
	if (!file) {
		perror("fopen");
		return -1;
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0;

	struct list_node *list = NULL;
	size_t n = 0;

	while ((nread = getline(&line, &len, file)) != -1) {
		line[nread - 1] = '\0';
		struct list_node *new_node = list_append(list, line);
		if (!new_node) {
			perror("list_append");
			fclose(file);
			free(line);
			list_free(list);
			return -1;
		}
		list = new_node;
		line = NULL;
		++n;
	}


	fclose(file);
	struct hash_table *table;
	if (hash_table_build(&table, n, list) != 0) {
		perror("hash_table_build");
		list_free(list);
		free(line);
		return -1;
	}

	list_free(list);

	while ((nread = getline(&line, &len, stdin)) != -1) {
		line[nread - 1] = '\0';
		if (!strcmp(line, "exit"))
			break;
		puts(hash_table_query(table, line) ? "YES" : "NO");
	}

	free(line);
	hash_table_free(table);

	return 0;
}
