#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

class NeedlemanWunsch {
public:
    // 构造函数
    NeedlemanWunsch(string seq_a, string seq_b, int gap = -2);

    // 开始比对计算还有输出结果
    void Align();  //比对大程序
    void PrintResults() const;  //输出结果

private:
   //计算逻辑，分别为计算罚分的逻辑还有回溯的逻辑。
    int GetSubstitutionScore(char a, char b) const;  //获取矩阵某位置的得分
    void Traceback(); //回溯生成最佳比对数列字符串

    // 比对结果——输出的DNA序列方式配对
    string aligned_a;
    string aligned_b;
    string match_symbols;

    // 原始序列和参数
    const string seq_a;
    const string seq_b;
    const int gap_penalty;  //空位罚分
  
    // 动态规划矩阵
    vector<vector<int>> score_matrix;

    // 所有对象共享，包括罚分方式，还有碱基逻辑
    static const map<char, int> dna_index;      // 碱基映射表
    static const vector<vector<int>> sub_mat;  // 替换矩阵
};