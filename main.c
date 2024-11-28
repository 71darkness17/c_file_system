#include "interface.c"
#include "terminal.c"

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
        printf("\ncurrent path - %s\n", fd->path);
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
                else if ((fd->files + index)->type == TXT); // Вова, я жду... 
                break;
            }
        }
    }
    system("cls");
    destroy_folder(fd);
}


int main() {
    processing();
    printf("Fufayka\n");
}