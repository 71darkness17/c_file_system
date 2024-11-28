#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

#include "interface.c"
#include "terminal.c"






int main(int args, char * argv) {
    system("cls");
    char pBuf[512] = {0};
    size_t len = sizeof(pBuf);
    char * ptr = pBuf;
    GetModuleFileName(NULL, pBuf, len);
    remove_last_file(pBuf);
    Folder *fd = init_folder(pBuf);
    print_directory(fd);
    destroy_folder(fd);
    printf("Fufayka\n");
}