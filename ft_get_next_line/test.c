



#include <stdio.h>
#include <stdlib.h>

char * modify(char **str)
{
    char *line;


    return line;
}
int main()
{
    int i = 0;
    char *txt = "hello there \nayoub";
    while(txt[i])
        i++;
    char *str = malloc(i);
    int j = 0;
    while (j < i)
    {
        str[j] = txt[j];
        j++;
    }
    str[j] = '\0';
    char **cpy = &str;

    printf("%s\n",*cpy);
    return (1);
}