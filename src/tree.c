#include "tree.h"
#include "print.h"
#include "options.h"

int entry_compare(const entry_t *a, const entry_t *b) {
    if (opts.no_sort)
        return 1; // always append to the end
    
    int result;

    if (opts.sort_by_mtime || opts.sort_by_ctime) {
        time_t time_a = opts.sort_by_mtime ? a->st.st_mtime : a->st.st_ctime;
        time_t time_b = opts.sort_by_mtime ? b->st.st_mtime : b->st.st_ctime;
        
        if (time_a != time_b) {
            result = (time_a < time_b) ? 1 : -1;  // Newer files first
        } else {
            result = strcmp(a->name, b->name);  // If times are equal, sort by name
        }
    } else {
        result = strcmp(a->name, b->name);  // Default: sort by name
    }

    return opts.reverse_sort ? -result : result;
}

entry_t *insert_entry(entry_t *head, entry_t *entry) {
    entry_t *current, *prev = NULL;
    
    // List is empty or entry should be inserted at the beginning
    if (!head || entry_compare(entry, head) <= 0) {
        entry->next = head;
        return entry;
    }
    
    // Find the correct position to insert the entry
    for (current = head; 
        current && entry_compare(entry, current) > 0; 
        prev = current, current = current->next);
    
    prev->next = entry;
    entry->next = current;
    
    return head;
}

int walk(const char *directory, const char *prefix, counter_t *counter) {
    DIR *dir_handle;
    struct dirent *file_dirent;
    entry_t *head = NULL, *current;
    char *full_path, *new_prefix;
    struct stat st;
    
    dir_handle = opendir(directory);
    if (!dir_handle) {
        errMsg("Failed to open directory \"%s\"", directory);
        return -1;
    }
    
    counter->dirs++;
    
    while ((file_dirent = readdir(dir_handle)) != NULL) {
        if (strcmp(file_dirent->d_name, ".") == 0 || strcmp(file_dirent->d_name, "..") == 0)
            continue;
        
        if (!opts.show_hidden && file_dirent->d_name[0] == '.')
            continue;
        
        full_path = malloc(strlen(directory) + strlen(file_dirent->d_name) + 2); // +2 for '/' and '\0'
        if (!full_path) 
            errExit("malloc");

        snprintf(full_path, PATH_MAX, "%s/%s", directory, file_dirent->d_name);
        
        if (lstat(full_path, &st) == -1) {
            free(full_path);
            continue; // skip this file if we can't stat it
        }
        
        if (opts.dirs_only && !S_ISDIR(st.st_mode)) {
            free(full_path);
            continue;
        }
        
        current = malloc(sizeof(entry_t));
        if (!current)
            errExit("malloc");
        
        current->name = strdup(file_dirent->d_name);
        if (!current->name)
            errExit("strdup");
        
        current->path = full_path;
        current->st = st;
        current->is_dir = S_ISDIR(st.st_mode);
        current->next = NULL;
        
        head = insert_entry(head, current);
    }
    
    if (closedir(dir_handle) == -1)
        errExit("closedir");
    
    for (current = head; current;) {
        entry_t *next = current->next;
        int is_last = (next == NULL);
        
        print_entry_prefix(prefix, is_last);

        if (opts.show_perms || opts.show_user || opts.show_group || opts.show_size) 
            print_file_info(&current->st);
        
        print_entry_name(current->name, current->path, current->st.st_mode);
        
        if (current->is_dir) {
            size_t new_prefix_size = strlen(prefix) + 5 + 1; // +5 for "│   " or "    "(since | is a multibyte letter), +1 for '\0'
            new_prefix = malloc(new_prefix_size);
            if (!new_prefix)
                errExit("malloc");
            
            snprintf(new_prefix, new_prefix_size, "%s%s", prefix, is_last ? "    " : "│   ");
            
            walk(current->path, new_prefix, counter);
            free(new_prefix);
        } else {
            counter->files++;
        }
        
        free(current->name);
        free(current->path);
        free(current);
        current = next;
    }
    
    return 0;
    
    return 0;
}

int main(int argc, char *argv[]) {
    counter_t counter = {0, 0};
    struct stat root_st;
    int optind = parse_options(argc, argv);
    
    // If no directory is specified, use the current directory
    if (optind >= argc) {
        if (stat(".", &root_st) == -1)
            errExit("stat");
        
        if (opts.show_perms || opts.show_user || opts.show_group || opts.show_size) 
            print_file_info(&root_st);
        print_entry_name(".", NULL, root_st.st_mode);
        walk(".", "", &counter);
    } else {
        for (int i = optind; i < argc; i++) {
            if (stat(argv[i], &root_st) == -1)
                errExit("stat");
            if (!S_ISDIR(root_st.st_mode)) {
                errMsg("'%s' is not a directory", argv[i]);
            }
            
            if (opts.show_perms || opts.show_user || opts.show_group || opts.show_size) 
                print_file_info(&root_st);
            print_entry_name(argv[i], NULL, root_st.st_mode);
            walk(argv[i], "", &counter);
        }
    }
    
    printf("\n%zu directories", counter.dirs);
    if (!opts.dirs_only)
        printf(", %zu files", counter.files);
    printf("\n");
    
    return EXIT_SUCCESS;
}
