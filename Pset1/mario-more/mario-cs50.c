#include <stdio.h>

int get_height(void);
void build(int height);

int main(void)
{
    int height = get_height();
    build(height);

    return 0;
}

//这个函数获取输入，限定范围为1～8
int get_height(void)
{
    //获取输入,cs50库让你只需要检查数字范围
    int height;
    do
    {
        height = scanf("Enter the height(1 ~ 8): ");
    } while (height < 1 || height > 8);

    return height;
}

//这个函数打印砖块
void build(int height)
{
    for (int i = 0; i < height; i++)
    {
        //打印左半部的空格
        for (int j = 1; j < height - i; j++)
        {
            printf(" ");
        }
        //打印左半部的 #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //打印中间的空格
        printf("  ");
        //打印右半部的 #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return;
}