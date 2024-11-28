#ifndef INTERFACE_H
#define INTERFACE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define NUM_FILES 100

typedef enum {
    TXT, FOLDER, OTHER
} FileType;

typedef struct {
    char * name;
    int name_length;
    FileType type;
} File;

typedef struct {
    int su_files_counter;
    int loh_files_counter;
    File *files;
    int max_files;
    int superuser;
    char* path;
    int path_len;
} Folder;

FileType check_extension(Folder * fd, File * f);
Folder * init_folder(char * path);
void destroy_folder(Folder * fd);
void print_directory(Folder * fd);
void remove_last_file(char * path);
Folder * reopen(Folder * fd, int * index);
void add_file_to_path(char * path, char * name, int name_len);
#endif