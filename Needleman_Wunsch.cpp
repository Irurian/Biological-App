#include "Needleman_Wunsch.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
// 初始化静态成员,dna_index和sub_mat是github开源代码里面的升级操作，这里借助了ai进行理解
/*
1. dna_index：碱基到矩阵索引的映射表
作用
建立字符到数值的映射：将DNA碱基字符（A/T/C/G）转换为替换矩阵中的行/列索引（0-3），便于快速查找得分。

统一大小写处理：同时支持大写和小写碱基（如 a 和 A 均映射到索引0）。
*/
const map<char, int> NeedlemanWunsch::dna_index = 
{
    {'A',0}, {'T',1}, {'C',2}, {'G',3},
    {'a',0}, {'t',1}, {'c',2}, {'g',3}
};


//2.DNA替换矩阵（A-T-C-G顺序），原版用的是普通的错配-1和匹配+1，后来ai发现有更多专业的匹配联系，然后这个算法的评分方式其实很多样，但是原理相同
/*
通过 sub_mat 矩阵实现不同碱基对的差异化评分（区别于空位罚分，空位罚分是一种额外的方式）：

A - T错配： - 1

C - G错配： - 1

跨类型错配（如A - C）： - 2

匹配： + 1
*/
const vector<vector<int>> NeedlemanWunsch::sub_mat = 
{
    // A   T   C   G
    { 1, -1, -2, -2 },  // A
    {-1,  1, -2, -2 },  // T
    {-2, -2,  1, -1 },  // C
    {-2, -2, -1,  1 }   // G
};

// 构造函数
NeedlemanWunsch::NeedlemanWunsch(string a, string b, int gap)
    : seq_a(move(a)), seq_b(move(b)), gap_penalty(gap)//空位罚分默认为-2，可以取其他值
{
    // 初始化动态规划矩阵
    size_t m = seq_a.length() + 1;
    size_t n = seq_b.length() + 1;
    score_matrix.resize(m, vector<int>(n, 0));

    // 初始化边界条件
    for (size_t i = 0; i < m; ++i)
        score_matrix[i][0] = static_cast<int>(i) * gap_penalty;
    for (size_t j = 0; j < n; ++j)
        score_matrix[0][j] = static_cast<int>(j) * gap_penalty;
}

// 核心比对算法
void NeedlemanWunsch::Align() 
{
    size_t m = seq_a.length();
    size_t n = seq_b.length();

    for (size_t i = 1; i <= m; ++i)
    {
        for (size_t j = 1; j <= n; ++j) 
        {
            // 使用替换矩阵获取实际得分
            int match = score_matrix[i - 1][j - 1] + GetSubstitutionScore(seq_a[i - 1], seq_b[j - 1]);
            int del = score_matrix[i - 1][j] + gap_penalty;
            int insert = score_matrix[i][j - 1] + gap_penalty;

            score_matrix[i][j] = max({ match, del, insert }); 
        }
    }
    Traceback();//回溯获取处理过的最优解矩阵数据
}

// 获取替换分数——矩阵中每个位置代表一种替换方式，这种方式的得分
int NeedlemanWunsch::GetSubstitutionScore(char a, char b) const 
{
        int idx_a = dna_index.at(a);  // 实际使用索引值
        int idx_b = dna_index.at(b);
        return sub_mat[idx_a][idx_b];  // 返回矩阵中的具体值
}

// 回溯路径，获取碱基配对方式，并用生物学专用符号得到处理过的最优碱基配对方式。
void NeedlemanWunsch::Traceback()
{
    size_t i = seq_a.length();
    size_t j = seq_b.length();

    while (i > 0 || j > 0)//从矩阵末尾开始，依次对上，左，对角的得分进行判断，优先选择对角方式的最高的分
    {
        if (i > 0 && j > 0 && score_matrix[i][j] == score_matrix[i - 1][j - 1] + GetSubstitutionScore(seq_a[i - 1], seq_b[j - 1])) 
        {    // 当前得分 = 左上角得分 + 替换分数，优先保留可能的同源位点
            aligned_a = seq_a[--i] + aligned_a;
            aligned_b = seq_b[--j] + aligned_b;
            match_symbols = (seq_a[i] == seq_b[j] ? '|' : ':') + match_symbols;
        }
        else if (i > 0 && score_matrix[i][j] == score_matrix[i - 1][j] + gap_penalty)
        {    // 当前得分 = 上方得分 + 空位罚分
            aligned_a = seq_a[--i] + aligned_a;
            aligned_b = '-' + aligned_b;
            match_symbols = ' ' + match_symbols;
        }
        else 
        {    //当前得分 = 左侧得分 + 空位罚分
            aligned_a = '-' + aligned_a;
            aligned_b = seq_b[--j] + aligned_b;
            match_symbols = ' ' + match_symbols;
        }
    }
}

// 结果输出
void NeedlemanWunsch::PrintResults() const 
{
   cout << "\nAligned Sequences:\n"
        << aligned_a << "\n"
        << match_symbols << "\n"
        << aligned_b << "\n";

    int total_length = static_cast<int>(aligned_a.length());
    int matches = static_cast<int>(count(match_symbols.begin(), match_symbols.end(), '|'));
    int gaps = static_cast<int>( count(aligned_a.begin(), aligned_a.end(), '-') + count(aligned_b.begin(), aligned_b.end(), '-'));

   cout << "Alignment Score: " << score_matrix.back().back() << "\n"
        << "Match Percentage: " << 100.0 * matches / total_length << "%\n"
        << "Gap Percentage: " << 100.0 * gaps / total_length << "%\n";
}