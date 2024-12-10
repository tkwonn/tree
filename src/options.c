#include "options.h"

options_t opts = {0};

static struct option long_options[] = {
    {"help", no_argument, NULL, 1},
    {0, 0, 0, 0}
};

void print_help(void) {
    printf("Usage: tree [-adpugstcrU] [--help] [directory ...]\n"
            "\n------- Listing options -------\n"
            "  -a    All files are listed.\n"
            "  -d    List directories only.\n"
            "\n------- File options -------\n"
            "  -p    Print the protection for each file.\n"
            "  -u    Print file owner or UID number.\n"
            "  -g    Print file group owner or GID number.\n"
            "  -s    Print the size in bytes of each file.\n"
            "\n------- Sorting options -------\n"
            "  -t    Sort files by last modification time.\n"
            "  -c    Sort files by last status change time.\n"
            "  -r    Sort in reverse order.\n"
            "  -U    Leave files unsorted.\n"
            "\n------- Miscellaneous options -------\n"
            "  --help    Print this help message.\n");
    exit(EXIT_SUCCESS);
}

int parse_options(int argc, char *argv[]) {
    int opt;
    
    while ((opt = getopt_long(argc, argv, "adpugstcrU", long_options, NULL)) != -1) {
        switch (opt) {
            case 1:   print_help(); break;
            case 'a': opts.show_hidden = true; break;
            case 'd': opts.dirs_only = true; break;
            case 'p': opts.show_perms = true; break;
            case 'u': opts.show_user = true; break;
            case 'g': opts.show_group = true; break;
            case 's': opts.show_size = true; break;
            case 't': 
            case 'c': 
                opts.sort_by_mtime = (opt == 't');
                opts.sort_by_ctime = (opt == 'c');
                opts.no_sort = false;
                break;
            case 'r': opts.reverse_sort = true; break;
            case 'U': 
                opts.no_sort = true;
                opts.sort_by_mtime = false;
                opts.sort_by_ctime = false;
                break;
            default: usageErr("tree [-adpugstcrU] [--help] [directory ...]\n");
        }
    }
    
    return optind;
}
