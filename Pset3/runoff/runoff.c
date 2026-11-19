#include <cs50.h>
#include <stdio.h>
#include <string.h>

// 最大投票人数和候选人数
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 第i个投票者的第j票
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// 候选人的名字，票数，淘汰状态
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// 候选人数组
candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

// 要实现的函数
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

/*
    这里我放一个总体的思路，更具体的细节就不在后面赘述了
    相信到这里了你可以用自己的方式做出来的

    runoff的算法是这样的，题目假设每位选民都会按自己意愿给每位候选人投票，
    然后比较第一票，如果有人得到的票数超过总票数的50%，直接获胜
    如果没有的话，找到第一票的最少票数，如果剩余的人平票了，那就都获胜
    没有平票，就淘汰掉票数最低的人（们）
    这样不断淘汰直到找到胜利者或平票
    

    接下来是更细节的实现，建议没有思路再看

    获得候选人名单 -> 检查 -> 初始化候选人数组candidate：名字，票数为0，未淘汰

    获得选民人数 -> 检查 -> 向第i位选民询问第j位的投票
    -> vote()函数遍历候选人名字，有相同的，向preference[i][j]记录该候选人编号(0，1，2...)

    接下来的while循环

    tabulate()统计该轮没淘汰的候选人的票数
    每一轮都有voter_count张票，对于第i张票，如果这个票的第j个对应的候选人没有被淘汰，该候选人票数++
    如果这个候选人被淘汰了，检查这张票的下一个排名，直到票数++了或者候选人遍历完了

    然后print_winner()遍历候选人的票数，如果有人的票数超过50%，
    那么获胜，打印出名字，并返回true，意味着程序可以结束了
    没人获胜呢，返回false，程序继续执行

    find_min()函数找出当前未淘汰的候选人的最小票数 min
    可能只有一个最小，可能有多个人票数最小，也可能所有票数一样

    is_tie()用于判断是不是剩下的所有人票数都一样，也就是是不是都等于最小票数

    那么如果这一步没有平票的话，继续执行程序
    eliminate()函数把票数最小的人都淘汰掉，也就是candidates[].eliminated = true

    最后将票数清0，保留淘汰状态

    然后继续执行这个while循环，最终找到胜利者
*/

int main(int argc, string argv[])
{
    // 检查参数数量
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // 初始化候选人数组
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // 一次循环询问一位选民
    for (int i = 0; i < voter_count; i++)
    {
        // 一次循环询问一个排名
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // 记录投票，如果投票有效
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // 持续比较直到出现胜者
    while (true)
    {
        // 给未被淘汰的候选人统计票数
        tabulate();

        // 检查是否已有人获胜
        bool won = print_winner();
        if (won)
        {
            break;
        }

        int min = find_min();    // 找到最低票数
        bool tie = is_tie(min);

        // 如果剩下的人票数一样，都获胜
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
    
        eliminate(min);      // 淘汰所有票数最低的人

        // 将候选人票数重置为0
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;
}

// 记录选民的投票
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    
    return false;
}

// 为没被淘汰的候选人统计票数
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }

    return;
}

// 如果有胜利者，打印出来
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (double) voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// 找到剩余候选人的最低票数
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (!candidates[j].eliminated && candidates[j].votes < min)
            {
                min = candidates[j].votes;
            }
        }
    }
    
    return min;
}

// Return true 如果剩下所有人票数相同
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes > min)
            {
                return false;
            }
        }
    }
    return true;
}

// 淘汰票数最低的候选人（们）
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
