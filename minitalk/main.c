
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

    char c = 'b';
    int bit = 4;
    char mask = 0x01 << bit; 
    if ('a' & mask)
    {

    }
    printf("mask = %d\n", mask);
    getbits(c);
    return (0);
}