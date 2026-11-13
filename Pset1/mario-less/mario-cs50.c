#include <cs50.h>
#include <stdio.h>

int get_height(void);
void build(int height);

int main(void)
{
    int height = get_height();
    build(height);

    return 0;
}

//获取高度的函数
int get_height(void)
{
    //不合格的输入(如字符)cs50的函数会自动处理，只要判断数字是否合格
    int h;
    do
    {
        h = get_int("Height: ");
    } while (h < 1);
    //返回高度
    return h;
}

//打印输出砖块的函数
void build(int height)
{
    //需要打印 height 行
    for (int i = 0; i < height; i++)
    {
        //打印空格，因为最底下没有空格，j 初始化为 1 使得第一行打印 height-1 次，height - i 使得下一行减少一次
        for (int j = 1; j < height - i; j++)
        {
            printf(" ");
        }
        //打印 #，第一行 1 个，第二行 2 个，可以有多种初始化和判断条件，这里演示一种
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return;
}
