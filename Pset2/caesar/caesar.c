#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

/*
    接收一个命令行参数，要求一个非负数字，检查输入
    提示用户输入明文
    处理，输出密文
*/
void swap(const string ptext, string ctext, int len, int key);

int main(int argc, string argv[])
{
    //检查是否只有一个参数
    if (argc != 2)
    {
        printf("Please enter only a number.\n");
        return 1;
    }

    //检查该参数的字符是不是只有 数字，命令行参数把输入当作字符串处理
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //把获取的输入转化，atoi函数负责把数字字符串char转化为int数字
    int key = atoi(argv[1]) % 26;

    //获取明文
    string ptext = get_string("plaintext:  ");
    int len = strlen(ptext);

    //声明存储密文的字符数组
    char ctext[len + 1];

    swap(ptext, ctext, len, key);
    printf("ciphertext: %s\n", ctext);

    return 0;
}

//接收明文和key，转化的结果存进ctext数组
void swap(const string ptext, string ctext, int len, int key)
{
    for (int i = 0; ptext[i] != '\0'; i++)
    {
        if (ptext[i] >= 'A' && ptext[i] <= 'Z')
        {
            //对大写字母的处理
            ctext[i] = ((ptext[i] - 'A' + key) % 26 + 'A');
        }
        else if (ptext[i] >= 'a' && ptext[i] <= 'z')
        {
            //对小写字母的处理
            ctext[i] = ((ptext[i] - 'a' + key) % 26 + 'a');
        }
        else
        {
            ctext[i] = ptext[i];
        }
    }

    //字符串末尾加 '\0'，因为前面声明的是字符数组，这样才会被正确当字符串处理
    ctext[len] = '\0';

    return;
}