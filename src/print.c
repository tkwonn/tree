#include "print.h"

void print_file_info(const struct stat *st) {
    char info[128] = {0};
    int pos = 0;

   // Permissions
    if (opts.show_perms) {
        char perms[] = "----------";

       // File type
        switch (st->st_mode & S_IFMT) {
            case S_IFREG:  perms[0] = '-'; break;
            case S_IFDIR:  perms[0] = 'd'; break;
            case S_IFLNK:  perms[0] = 'l'; break;
            case S_IFCHR:  perms[0] = 'c'; break;
            case S_IFBLK:  perms[0] = 'b'; break;
            case S_IFSOCK: perms[0] = 's'; break;
            case S_IFIFO:  perms[0] = 'p'; break;
            default:       perms[0] = '?'; break;
        }

        perms[1] = (st->st_mode & S_IRUSR) ? 'r' : '-';
        perms[2] = (st->st_mode & S_IWUSR) ? 'w' : '-';
        perms[3] = (st->st_mode & S_IXUSR) ? ((st->st_mode & S_ISUID) ? 's' : 'x') : ((st->st_mode & S_ISUID) ? 'S' : '-');
        perms[4] = (st->st_mode & S_IRGRP) ? 'r' : '-';
        perms[5] = (st->st_mode & S_IWGRP) ? 'w' : '-';
        perms[6] = (st->st_mode & S_IXGRP) ? ((st->st_mode & S_ISGID) ? 's' : 'x') : ((st->st_mode & S_ISGID) ? 'S' : '-');
        perms[7] = (st->st_mode & S_IROTH) ? 'r' : '-';
        perms[8] = (st->st_mode & S_IWOTH) ? 'w' : '-';
        perms[9] = (st->st_mode & S_IXOTH) ? ((st->st_mode & S_ISVTX) ? 't' : 'x') : ((st->st_mode & S_ISVTX) ? 'T' : '-');

        pos += snprintf(info + pos, sizeof(info) - pos, "%s", perms);
    }
    
    // User name
    if (opts.show_user) {
       struct passwd *pwd = getpwuid(st->st_uid);
        pos += snprintf(info + pos, sizeof(info) - pos, " %-8s", pwd ? pwd->pw_name : "???");
        while (pos < 8) info[pos++] = ' ';
    }
    
    // Group name
    if (opts.show_group) {
        struct group *grp = getgrgid(st->st_gid);
        if (pos > 0) info[pos++] = ' ';
        pos += snprintf(info + pos, sizeof(info) - pos, " %-8s", grp ? grp->gr_name : "???");
        while (pos < (opts.show_user ? 17 : 8)) info[pos++] = ' ';
    }
    
    // Size
    if (opts.show_size) {
        if (pos > 0) info[pos++] = ' ';
        pos += snprintf(info + pos, sizeof(info) - pos, " %7ld", (long)st->st_size);
    }
    
    if (pos > 0) {
        printf("[%s]  ", info);
    }
}

void print_entry_name(const char *name, const char *path, mode_t mode) {
    if (S_ISDIR(mode)) {
        if ((mode & S_ISVTX) && (mode & S_IWOTH)) {
            printf("%s%s%s\n", COLOR_STICKY_OW, name, COLOR_RESET);
        } else if (mode & S_IWOTH) {
            printf("%s%s%s\n", COLOR_OW, name, COLOR_RESET);
        } else {
            printf("%s%s%s\n", COLOR_DIR, name, COLOR_RESET);
        }
    }
    else if (S_ISLNK(mode)) {
        if (path) {
            char link_target[PATH_MAX];
            ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
            if (len != -1) {
                link_target[len] = '\0';
                printf("%s%s%s -> %s\n", COLOR_LINK, name, COLOR_RESET, link_target);
            } else {
                printf("%s%s%s\n", COLOR_LINK, name, COLOR_RESET);
            }
        }
    }
    else if (S_ISSOCK(mode)) {
        printf("%s%s%s\n", COLOR_SOCKET, name, COLOR_RESET);
    }
    else if (S_ISFIFO(mode)) {
        printf("%s%s%s\n", COLOR_PIPE, name, COLOR_RESET);
    }
    else if (S_ISBLK(mode)) {
        printf("%s%s%s\n", COLOR_BLOCK, name, COLOR_RESET);
    }
    else if (S_ISCHR(mode)) {
        printf("%s%s%s\n", COLOR_CHAR, name, COLOR_RESET);
    }
    else if (mode & S_ISUID) {
        printf("%s%s%s\n", COLOR_SETUID, name, COLOR_RESET);
    }
    else if (mode & S_ISGID) {
        printf("%s%s%s\n", COLOR_SETGID, name, COLOR_RESET);
    }
    else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
        printf("%s%s%s\n", COLOR_EXEC, name, COLOR_RESET);
    }
    else {
        printf("%s\n", name);
    }
}

void print_entry_prefix(const char *prefix, int is_last) {
    printf("%s%s", prefix, is_last ? "└── " : "├── ");
}
