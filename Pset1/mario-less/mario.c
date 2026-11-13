#include <stdio.h>

/*
    这个不包括cs50库，只是一种方法的示例
    你可以改变循环的用法，比如只用一个循环进行输入验证

    要了解一下scanf()怎么获取输入的，缓冲区等概念学一下
    或者把两个功能像另一个版本一样都用函数封装，很简洁
*/

int main(void)
{
    int height;
    while (1)
    {
        //获取输入
        printf("Height: ");
        int n = scanf("%d", &height);
        if (height <= 0 || n != 1)
        {
            continue;
        }
        
        //外层循环表示打印 height 层
        for (int i = 0; i < height; i++)
        {
            //打印空格
            for (int j = 1; j < height - i; j++)
            {
                printf(" ");
            }
            //打印 #
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