#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

// 得到密钥 -> 处理 -> 得到明文 -> 处理 -> 输出
/*
    我的思路是从命令行得到输入后，先检查是不是只有这一个字符串
    然后检查长度，再检查是不是都是字母，同时统一转化成大写，并且存到另一个char数组里
    然后再遍历一次，检查有没有重复

    之后得到输入
    如果不是字母，不动
    如果是字母，用key转化
    输出的到的新密文
*/


void encode(const string ptext, string ctext, int len, const char* key);

int main(int argc, string argv[])
{
    // 检查是不是只有一个参数
    if (argc != 2)
    {
        printf("Enter one key without space.\n");
        return 1;
    }

    int len = strlen(argv[1]);
    char key[len]; // 另一个数组存 key

    if (len != 26)
    {
        printf("The length is 26.\n");
        return 1;
    }

    // 检查是不是字母且转化成统一的大小写
    for (int i = 0; i < len; i++)
    {
        if (isalpha(argv[1][i]))
        {
            key[i] = toupper(argv[1][i]);
        }
        else
        {
            printf("The key only remains alpha.\n");
            return 1;
        }
    }

    // 遍历检查有无重复的字母
    for (int i = 0; i < len; i++)
    {
        char temp = key[i];
        for (int j = i + 1; j < len; j++)
        {
            if (temp == key[j])
            {
                printf("No duplicate characters.\n");
                return 1;
            }
        }
    }

    
    string ptext = get_string("plaintext:  ");
    int len_t = strlen(ptext);
    char ctext[len_t + 1];    // 存密文的字符串

    encode(ptext, ctext, len_t, key);
    printf("ciphertext: %s\n", ctext);

    return 0;
}

void encode(const string ptext, string ctext, int len, const char* key)
{
    // 和 Caesar 的形式差不多，密钥的使用有一点区别
    for (int i = 0; i < len; i++)
    {
        if (isalpha(ptext[i]))
        {
            char temp = ptext[i];
            if (temp >= 'A' && temp <= 'Z')
            {
                ctext[i] = key[temp - 'A'];
            }
            else if (temp >= 'a' && temp <= 'z')
            {
                ctext[i] = tolower(key[temp - 'a']);
            }
        }
        else
        {
            ctext[i] = ptext[i]; 
        }
    }

    ctext[len] = '\0';
    return;
}