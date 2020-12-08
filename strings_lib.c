#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "strings_lib.h"

char* string_duplicate(char* original){
    return strdup(original);
}

char* string_new(){
    return string_duplicate("");
}

char* string_itoa(int number){
    char* number_as_string = string_new();
    sprintf(number_as_string, "%d", number);
    return number_as_string;
}

void string_append(char** original, char* string_to_add){
    *original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
    strcat(*original, string_to_add);
}

char* string_substring(char* text, int start, int length){
    char* new_string = calloc(1, length + 1);
    strncpy(new_string, text + start, length);
    return new_string;
}

char* string_substring_from(char *text, int start){
    return string_substring(text, start, strlen(text) - start);
}