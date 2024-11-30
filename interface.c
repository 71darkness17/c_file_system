#include "interface.h"
#include "terminal.h"

FileType check_extension(Folder * fd, File * f) {
    int end = f->name_length - 1;
    if (end >= 3 && f->name[end] == 't' &&
        f->name[end - 1] == 'x' && f->name[end - 2] == 't' && f->name[end - 3] == '.') return TXT_FILE;
    else if (end == 1 && f->name[end] == '.' && f->name[end - 1] == '.') return FOLDER;
    else if (end == 0 && f->name[end] == '.') return FOLDER; 
    else if (f->name[end] == 'c' && f->name[end - 1] == '.') return C_FILE;
    else if (f->name_length >= 4 && f->name[end] == 'e' && f->name[end - 1] == 'x' &&
             f->name[end - 2] == 'e' && f->name[end - 3] == '.') return EXE_FILE;
    else if (f->name_length >= 3 && f->name[end] == 'y' 
             && f->name[end - 1] == 'p' && f->name[end - 2] == '.') return PY_FILE;
    add_file_to_path(fd->path, f->name, f->name_length);
    DIR * dr = opendir(fd->path);
    remove_last_file(fd->path);
    if (dr) return FOLDER;
    closedir(dr);

    return OTHER;
}

Folder * init_folder(char * path) {
    Folder * fd = (Folder *) malloc (sizeof(Folder));
    fd->loh_files_counter = 0;
    fd->su_files_counter = 0;
    fd->max_files = NUM_FILES;
    fd->superuser = 1;
    fd->path = path;
    int len = 0;
    for ( ; path[len] != '\0'; ++len);
    fd->path_len = len;
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
        (fd->files + fd->su_files_counter)->type = check_extension(fd, fd->files + fd->su_files_counter);
        //printf("%s\n", (fd->files + fd->su_files_counter)->name);
        fd->su_files_counter++;
    }
    return fd;
}

Folder * reopen(Folder * fd, int * index) {
    //char * path = (fd->files + *index)->name;
    add_file_to_path(fd->path, (fd->files + *index)->name, (fd->files + *index)->name_length);
    Folder * new_fd = init_folder(fd->path);
    destroy_folder(fd);
    system("cls");
    print_directory(new_fd);
    *index = 0;
    //print_brackets(fd, *index);
    return new_fd;
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
        switch ((fd->files + i)->type) {
            case FOLDER: {
                set_console_color(BLUE);
                break;
            }
            case TXT_FILE: {
                set_console_color(GREEN);
                break;
            }
            case C_FILE: {
                set_console_color(RED); break;
            }
            case PY_FILE: {
                set_console_color(YELLOW); break;
            }
            case EXE_FILE: {
                set_console_color(VIOLET); break;
            }
        }
        printf(" %s", (fd->files + i)->name);
        // if ((fd->files + i)->type == TXT) printf(" TXT FILEEEEEEEE");
        // else if ((fd->files + i)->type == FOLDER) printf(" FOLDEEEER");
        printf("\n");
        set_console_color(WHITE);
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

void add_file_to_path(char * path, char * name, int name_len) {
    int index = 0;
    if (name_len == 2 && name[0] == '.' && name[1] == '.') {
        remove_last_file(path);
        return;
    }
    else if (name_len == 1 && name[0] == '.') return;
    while (path[index] != '\0') index++;
    path[index] = '\\'; index++;
    for (int i = 0; i != name_len; ++i, ++index) {
        path[index] = name[i];
    }
    //printf("\nadded - %s\n", path);
}

void execute(FileType type, char  * path) {
    system("cls");
    switch (type) {
        case C_FILE: {
            execute_c(path); break;
        }
        case PY_FILE: {
            execute_py(path); break;
        }
    }
    set_console_color(CYAN);
    printf("\nPress any key to quit\n");
    getch();
}

void execute_c(char * path) {
    char * command = (char *) malloc (512 * sizeof(char));
    for (int i = 0; i != 512; ++i) {
        command[i] = '\0';
    }
    char first_part[] = "gcc ";
    int index = 0;
    for ( ; index != 4; ++index) {
        command[index] = first_part[index];
    }
    for ( ;path[index - 4] != '\0'; ++index) {
        command[index] = path[index - 4];
    }
    char second_part[] = " -o tmp.exe";
    for (int i = 0; i != 11; ++i) {
        command[index] = second_part[i];
        index++;
    }
    system(command);
    free(command);
    system("tmp.exe");
    system("del tmp.exe");
}

void execute_py(char * path) {
    char * command = (char *) malloc (512 * sizeof(char));
    for (int i = 0; i != 512; ++i) {
        command[i] = '\0';
    }
    char first_part[] = "python ";
    int index = 0;
    for ( ; index != 7; ++index) {
        command[index] = first_part[index];
    }

    for ( ;path[index - 7] != '\0'; ++index) {
        command[index] = path[index - 7];
    }
    system(command);
    free(command);
}
