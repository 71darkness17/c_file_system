#include"file_func.h"
#include<stdio.h>
#include<stdlib.h>



TEXT_FILE open_as_text(char * path) {
    FILE* file = fopen(path,"w+");
    char* str = malloc(2*sizeof(char));
    char c;
    int i = 0,len = 2;
    while((c = getc(file)) != EOF){
        *(str+i) = c;
        if(i+1>=len){
            str = (char*) realloc(str,(len+10)*sizeof(char));
            len+=10;
        }
        i++;
    }
    TEXT_FILE tfile;
    tfile.text.str = str;
    tfile.pointer = file;
    tfile.text.len = i+1;
    tfile.text.space = len;
    return tfile;
}

STRING add_text(STRING text, int pos){
    STRING temp;
    temp.str = (char*) malloc(2*sizeof(char));
    temp.len = 0;
    temp.space = 2;
    char c;
    while((c = getchar()) != '\n'){
        *(temp.str+temp.len) = c;
        if(temp.len+1>=temp.space){
            temp.str = (char*) realloc(temp.str,(temp.space+10)*sizeof(char));
            temp.space+=10;
        }
        temp.len++;
    }
    if (temp.len+text.len >= text.space) {
        text.space = temp.len+text.len+10;
        text.str = (char*) realloc(text.str,text.space*sizeof(char));
    }
    
    for(int j = 0;j<temp.len;j++){
        char copy = ' ',paste;
        for(int i = pos+j;i<text.len;i++){
            paste = copy;
            copy = *(text.str + i);
            *(text.str + i) = paste; 
        }
    }
    for(int i = 0;i<temp.len;i++){
            *(text.str + i+pos) = *(temp.str + i);
        }
    return text;
}

TEXT_FILE edit_file(TEXT_FILE file, int mode) {
    
    return file;
}




