
#include "ft_fdf.h"

char *reverse(char *str)
{
    char *rev;
    int i;

    i = 0;
    rev = ft_strdup("123456");
    while (i < 6)
    {
        rev[i] = str[5 - i];
        i++;
    }
    return (rev);
}

int    get_hexpos(char *hex, char c)
{
    int pos;

    pos = 0;
    while(hex[pos])
    {
        if (hex[pos] == c)
            return (pos);
        pos++;
    }
    return (-1);
}

int convert_hex(char *color)
{
    unsigned int val;
    char *hex;
    int i;

    val = 0;
    i = 0;
    hex = reverse(color);
    while (hex[i])
    {
        val += get_hexpos(BASE16,hex[i]) * pow(16,i);
        i++;
    }
    free(hex);
    return (val);
}

char *gethex(char *line,size_t *i)
{
    line += 2;
    *i += 2;
    return (ft_substr((const char *)line,0,6));
}