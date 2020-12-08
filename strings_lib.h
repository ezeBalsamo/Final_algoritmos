#ifndef FINALAYED_VONWEBER_STRINGS_LIB_H
#define FINALAYED_VONWEBER_STRINGS_LIB_H

char* string_duplicate(char* original);
char* string_new();
char* string_itoa(int number);

void string_append(char** original, char* string_to_add);

char* string_substring(char* text, int start, int length);
char* string_substring_from(char *text, int start);

#endif //FINALAYED_VONWEBER_STRINGS_LIB_H
