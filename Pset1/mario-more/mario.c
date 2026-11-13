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
    //获取输入,当输入不是 数字、超过范围，重新询问
    int height;
    int n;
    do
    {
        int ch;
        printf("Enter the height(1 ~ 8): ");
        n = scanf("%d", &height);

        //scanf()获取输入失败时，没读取的字符会留在缓冲区，需要清空，否则无限循环下去内存爆炸！！！
        while ((ch = getchar()) != '\n')
        {

        }
    } while (n != 1 || height < 1 || height > 8);

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