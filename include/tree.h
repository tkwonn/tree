#ifndef TREE_H
#define TREE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "options.h"

typedef struct {
    size_t dirs;
    size_t files;
} counter_t;

typedef struct entry {
    char *name;
    char *path;
    struct stat st;
    int is_dir;
    struct entry *next;
} entry_t;


entry_t *insert_entry(entry_t *head, entry_t *entry);
int entry_compare(const entry_t *a, const entry_t *b);
int walk(const char *directory, const char *prefix, counter_t *counter);

#endif
