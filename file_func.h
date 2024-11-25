#ifndef FILE_FUNC_H
#define FILE_FUNC_H
#define TEXT_FILE struct TextFile
#define STRING struct String
struct String {
    int len;
    char * str;
    int space;
};
struct TextFile {
    FILE* pointer;
    struct String text;
};

char * open_as_text(char * path);
#endif