#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

void calculate(string text, double *pL, double *pS);

/*
    题目给了输入计算的标准，不用考虑太多复杂情况
    有明确的计数规则，也有可以直接采用的输入假设
    官方题面把这些细节放在advice里
    字母	只数英文字母 A–Z 和 a–z。比如 You're 含 5 个字母，撇号不计
    单词	按空格分隔。`sister-in-law` 算 1 个单词，连字符不拆词
    句子	把 .、`!`、`?` 当作句子结束标记。这题可以按标点计数，无需识别 Mr. 这样的缩写
    可以假设输入至少有一个单词，首尾没有空格，单词之间没有连续空格
    按题意，空字符串和多余空格都可以暂时不处理
*/

int main(void)
{
    //程序默认输入正确，无需处理，cs50的这个函数直接能读取所有输入
    //题目给了输入计算的标准，不用考虑太多复杂情况
    string text = get_string("Text: ");

    double L;
    double S;
    calculate(text, &L, &S);

    //题目提供的公式
    double index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        //round函数四舍五入，具体用法自行查阅
        printf("Grade %d\n", (int)round(index));
    }

    return 0;
}

/*
    这个函数计算字母，单词和句子数量
    有很多计算方法，演示一种
    我这里顺手就用了指针传递参数
    如果没学可以不用函数，或者用函数返回值来计算，就不要全放一个函数了
    题目给了输入计算的标准，不用考虑太多复杂情况
*/
void calculate(string text, double *pL, double *pS)
{
    //GPT跟我说计数用int，最后计算的时候再转化成浮点数更好
    double count_letter = 0;
    double count_word = 0;
    double count_sentence = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            //是字母就记 字母数 +1
            count_letter++;
        }
        else if (text[i] == ' ')
        {
            //遇到空格记 单词数+1
            count_word++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            //遇到这些标点，可视为句子 +1
            count_sentence++;
        }
    }
    
    //最后一个单词不会被计数，因此当输入不是空白时加上
    if (count_letter != 0)
    {
        count_word++;
    }

    *pL = ((count_letter / count_word) * 100);
    *pS = ((count_sentence / count_word) * 100);
    return;
}


