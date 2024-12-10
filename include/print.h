#ifndef PRINT_H
#define PRINT_H

#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include "tree.h"

/* File type colors based on LS_COLORS */
#define COLOR_RESET     "\033[0m"
#define COLOR_DIR       "\033[1;36m"   // Directory (bold cyan)
#define COLOR_LINK      "\033[35m"     // Symbolic link (magenta)
#define COLOR_SOCKET    "\033[32m"     // Socket (green) 
#define COLOR_PIPE      "\033[33m"     // Named pipe (yellow)
#define COLOR_EXEC      "\033[31m"     // Executable (green)
#define COLOR_BLOCK     "\033[34;46m"  // Block device (blue on cyan)
#define COLOR_CHAR      "\033[34;43m"  // Character device (blue on yellow)
#define COLOR_SETUID    "\033[30;41m"  // setuid (black on red) 
#define COLOR_SETGID    "\033[30;46m"  // setgid (black on cyan)
#define COLOR_STICKY_OW "\033[30;42m"  // Sticky other-writable (black on green)
#define COLOR_OW        "\033[30;43m"  // Other-writable (black on yellow)

void print_file_info(const struct stat *st);
void print_entry_name(const char *name, const char *path, mode_t mode);
void print_entry_prefix(const char *prefix, int is_last);

#endif
