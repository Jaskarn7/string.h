#include <stdio.h>
#include "string.h"
#include <string.h>

int main(void)
{

    printf("\n\t\t\t-------------------Testing-------------------\n\n\n");

    /* Testing str_len function to return length of passed string */
    printf("\tLength of string: :%d:%d:\n\n", strlen("Hello, World!"), str_len("Hello, World!"));

     /**
      * Testing str_cmp to check if two strings are equal or not
      * The results here will be a bit different as str_cmp return 1 if strings are equal and strcmp return 0 on it.
      **/ 

    printf("\tString compare: :%d:%d:\n", strcmp("hello", "hello"), str_cmp("hello", "hello"));
    printf("\tString compare: :%d:%d:\n\n", strcmp("hello", "world"), str_cmp("hello", "world"));

    /* Testing str_cpy function which replaces the second passed string with the first */
    char *s = "hello";
    char *p = "world";
    str_cpy(s, p);
    printf("\tString copy: :%s:%s:\n\n", strcpy("hello", "world"), s);

    /* Testing str_cat which concatenates second passed string to first */
    char *str1 = "hello ";
    char *str2 = "world";
    printf("\tString concatenates: :%s:%s:\n\n", strcat(str1, str2), str_cat("hello ", "world"));

    /* Testing str_chr function which returns the pointer to first location of character in the string */
    printf("\tString character: :%s:%s:\n\n", strchr("Hello", 'l'), str_chr("hello", 'l'));

    return 0;
}