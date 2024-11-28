#include "interface.h"

FileType check_extension(File * f) {
    int end = f->name_length - 1;
    if (end >= 2 && f->name[end] == 't' &&
     f->name[end - 1] == 'x' && f->name[end - 2] == 't') return TXT;
    return OTHER;
}

Folder * init_folder(char * path) {
    Folder * fd = (Folder *) malloc (sizeof(Folder));
    fd->loh_files_counter = 0;
    fd->su_files_counter = 0;
    fd->max_files = NUM_FILES;
    fd->superuser = 1;
    fd->path = path;
    fd->files = (File *) malloc (fd->max_files * sizeof(File *));
    DIR * dp = opendir(fd->path);
    struct dirent * de;
    while ((de = readdir(dp))) {
        if (de->d_name[0] != '.') {
            fd->loh_files_counter++;
        }
        (fd->files + fd->su_files_counter)->name = (char *) malloc (100 * sizeof(char));
        for (int i = 0; i != 100; ++i) {
            (fd->files + fd->su_files_counter)->name[i] = '\0';
        }
        for (int i = 0; i != de->d_namlen; ++i) {
            (fd->files + fd->su_files_counter)->name[i] = de->d_name[i];
        }
        (fd->files + fd->su_files_counter)->name_length = de->d_namlen;
        (fd->files + fd->su_files_counter)->type = check_extension(fd->files + fd->su_files_counter);
        //printf("%s\n", (fd->files + fd->su_files_counter)->name);
        fd->su_files_counter++;
    }
    return fd;
}

void destroy_folder(Folder * fd) {
    for (int i = 0; i != fd->su_files_counter; ++i) {
        free((fd->files + i)->name);
    }
    free(fd->files);
    free(fd);
}
void print_directory(Folder * fd) {
    for (int i = 0; i != fd->su_files_counter; ++i) {
        if ((fd->files + i)->name[0] == '.' && fd->superuser == 0) continue;
        printf(" %s", (fd->files + i)->name);
        if ((fd->files + i)->type == TXT) printf(" TXT FILEEEEEEEE");
        printf("\n");
    }
}

void remove_last_file(char * path) {
    int began = 0;
    for (int i = 512 - 1; i != -1; --i) {
        if (path[i] != 0 && began == 0) {
            began = 1;
        }
        if (path[i] == '\\' && began == 1) {
            path[i] = 0;
            break;
        }
        path[i] = 0;
    }
}
