#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>
#include <stdbool.h>
#include "errors.h"

typedef struct {
    bool show_hidden;    /* -a */
    bool dirs_only;      /* -d */
    bool show_perms;     /* -p */
    bool show_user;      /* -u */
    bool show_group;     /* -g */
    bool show_size;      /* -s */
    bool sort_by_mtime;  /* -t */
    bool sort_by_ctime;  /* -c */
    bool reverse_sort;   /* -r */
    bool no_sort;        /* -U */
} options_t;

extern options_t opts;

int parse_options(int argc, char *argv[]);
void print_help(void);

#endif
