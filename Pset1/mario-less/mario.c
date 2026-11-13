#include <stdio.h>

int main(void)
{
    int num;
    while (1)
    {
        printf("Height: ");
        int n = scanf("%d", &num);
        if (num <= 0 || n != 1)
        {
            continue;
        }
        
        for (int i = 0; i < num; i++)
        {
            for (int j = 1; j < num - i; j++)
            {
                printf(" ");
            }
            for (int l = 0; l <= i; l++)
            {
                printf("#");
            }
            printf("\n");
        }

        break;
    }

    return 0;
}