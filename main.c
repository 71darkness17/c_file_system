#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <Windows.h>

#define EXT ".c"
#define ELEN 2

enum User {
    superuser, loh
};

int main() {
    system("cls");
    DIR * dp = opendir(".");
    if ( ! dp ) {
        fprintf(stderr, "Can't open current directory!\n");
        return 1;
    }
    struct dirent * de;
    de->d_reclen
    while ( ( de = readdir(dp) ) ) {
        if(de->d_name[0] == '.') continue;
        // size_t nlen = strlen(de->d_name);
        // if ( nlen > ELEN && strcmp((de->d_name) + nlen - ELEN, ".") != 0 )
        printf("%s\n", de->d_name);
    }
    closedir(dp);
}