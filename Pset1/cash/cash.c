#include <cs50.h>
#include <stdio.h>

int get_change(void);
int count_coins(int left);

/*
    题目不局限于这一个做法
    这个题目比较短，可以不用函数
    也可以用四个函数分别处理25，10，5，1
    %= 这种符号也可以换成更直观的形式
    比如官方的做法循环一个一个减，减一次记硬币数量加一次
*/

int main(void)
{
    int change = get_change();
    printf("%d\n", count_coins(change));

    return 0;
}


//这个函数用于获取输入，如果输入不大于0需要重新输入，输入不是数字或数字字符混合已经被cs50处理
int get_change(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change <= 0);
    
    return change;
}


//这个函数用于计算最少需要找几个硬币
//贪心算法就是要先把最大的用完，再小一点的，再更小一点的，就能得到最少需要的硬币数
int count_coins(int left)
{
    int coins = 0;

    coins += left / 25;  //先算面值25的硬币数量
    left %= 25;          //剩下的要找的金额

    coins += left / 10;  //再算面值10的硬币数量
    left %= 10;          //剩下的要找的金额

    coins += left / 5;   //最后算面值5的硬币数量
    left %= 5;           //剩下的

    //返回硬币数,不算面值为1的是因为最后剩下几块钱就应该用几个1块的硬币
    return (left + coins);
}

