#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 候选人最大数量
#define MAX 9

// 候选人的名字和票数
typedef struct
{
    string name;
    int votes;
} candidate;

// 存候选人信息的数组
candidate candidates[MAX];

// 候选人人数
int candidate_count;

// 要完成的函数
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // 检查有没有命令行输入
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // 填入候选人信息
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // 遍历每一个投票者
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // 检查是不是有效名
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // 输出票数最多的人
    print_winner();

    return 0;
}

// 根据投的票更新候选人的票数
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// 输出胜利者
void print_winner(void)
{
    // 找出最大票数
    int max_vote = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++)
    {
        if (max_vote < candidates[i].votes)
        {
            max_vote = candidates[i].votes;
        }
    }

    // 跟最大票数相等就输出名字
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}