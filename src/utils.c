#include "utils.h"

char *trim_str(char *str)
{
    char *start = str;
    size_t str_len = strlen(str);
    char *end = str + str_len - 1;
    const char end_line = '\0';

    if (!str || !*str) return str;

    while (isspace((unsigned char) *start)) start++;
    while (end != start && isspace((unsigned char) *end)) end--;

    if (start == end && start != str) *str = end_line;
    else if (end != str + str_len - 1)*(end + 1) = end_line;

    end = str;
    if( start != str )
    {
            while( *start ) *end++ = *start++; 
            *end = '\0';
    }

    return str;
}