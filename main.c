
#include "interface.c"
#include "terminal.c"
#include <locale.h>

void processing() {
    system("cls");
    char pBuf[512] = {0};
    size_t len = sizeof(pBuf);
    char * ptr = pBuf;
    GetModuleFileName(NULL, pBuf, len);
    remove_last_file(pBuf);
    Folder *fd = init_folder(pBuf);
    print_directory(fd);
    int index = 0;
    char c;
    int flag = 1;
    while (flag) {
        print_brackets(fd, index);
        c = getch();
        remove_brackets(fd, index);
        switch (c) {
            case 27: {
                flag--; break;
            }
            case 'W': case 'w': {
                if (index > 0) index--; break;
            }
            case 'S': case 's': {
                if (index + 1 < ((fd->superuser == 1) ? fd->su_files_counter : fd->loh_files_counter)) index++;
                break;
            }
            case 13: {
                if ((fd->files + index)->type == FOLDER) fd = reopen(fd, &index);
                else if ((fd->files + index)->type == C_FILE) {
                    add_file_to_path(fd->path, (fd->files + index)->name, (fd->files + index)->name_length);
                    execute((fd->files + index)->type, fd->path);
                    remove_last_file(fd->path);
                    system("cls");
                    print_directory(fd);
                    index = 0;
                } 
                break;
            }
        }
    }
    system("cls");
    destroy_folder(fd);
}


int main() {
    setlocale(LC_ALL, "");
    processing();
    printf("Fufayka\n");
}