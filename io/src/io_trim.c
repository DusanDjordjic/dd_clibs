#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

long int io_trim_str(char** str)
{
    long int n = 0, buf;
    if((buf = io_trim_str_right(str)) == -1) return -1;
    n += buf;
    if((buf = io_trim_str_left(str)) == -1) return -1;
    n += buf;
    return n;
}

long int io_trim_str_right(char** str)
{
    char* out_str = NULL;
    unsigned long int len = strlen(*str);
    unsigned long int i = len - 1; // -1 to skip '\0'
    unsigned long int n = 0;

    while((*str)[i] == ' ' || (*str)[i] == '\n')
    {
        i--;
        n++;
    }

    // str: "dusan  \0" -> len 7
    // i: 2
    // out: "dusan." len - i = 5
    // memcpy: to out, from str + i ('d'), size 5
    // out[len - i] = '\0': "dusan\0"
    if (n > 0)
    {
        out_str = malloc(sizeof(**str) * (len - n + 1));
        if(out_str == NULL) return -1;
        memcpy(out_str, *str, len - n);
        out_str[len - n] = '\0';
    }
    else
    {
        return 0;
    }

    free(*str);
    *str = out_str;
    return n;
}

long int io_trim_str_left(char** str)
{
    char* out_str = NULL;
    unsigned long int len = strlen(*str);
    unsigned long int i = 0;

    while((*str)[i] == ' ' || (*str)[i] == '\n') i++;

    // str: "  dusan\0" -> len 7
    // i: 2
    // out: "dusan\0" len - i + 1 = 6
    // memcpy: to out, from str + i ('d'), size 6
    if (i > 0)
    {
        out_str = malloc(sizeof(**str) * (len - i + 1));
        if(out_str == NULL) return -1;
        memcpy(out_str, *str + i, len - i + 1);
    }
    else
    {
        return 0;
    }

    free(*str);
    *str = out_str;
    return i;
}
