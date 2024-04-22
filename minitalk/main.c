
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void	getbits(char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)))
            printf("1");
		else
            printf("0");
        usleep(100);
		bit++;
	}
}

// void getbits(char c)
// {
//     short bit = 0;
//     char res = 'a';
//     char mask;
//     while (bit < 8)
//     {
//         mask = 1 << bit;
//         if ((c & (mask)) != 0)
//             printf("1");
//         else
//             printf("0");
//         bit++;
//     }
//     printf("%c\n",res);
// }


int main()
{

    char * str = "hello";
    int i = 0;
    while (str[i])
    {
        printf("char i(%d)is %c\n",i , str[i]); 
        i++;
    }
    return (0);
}