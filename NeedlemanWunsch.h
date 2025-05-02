#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;
/*
还没有完成的需求：
1.'N'碱基的比对情况还没有设计 
2.输出数据的方式——要存入文件，转化为JSON格式等。
3.部分借鉴代码的复现
4.NW算法逻辑优化
5.自定义的评分标准
*/

class NeedlemanWunsch {   
public:
    // 构造函数
    NeedlemanWunsch(string seq_a, string seq_b, int gap = -2);

    // 开始比对计算还有输出结果
    void Align();  //比对大程序
    void PrintResults() const;  //输出结果
    void Analyze();

    //返回数据成员
    string Return_A()const { return aligned_a; }
    string Return_B()const { return aligned_b; }
    string Return_MatchSymbols()const { return match_symbols; }
    int Return_TotalLength()const { return total_length; }
    int Return_Matches()const { return matches; }
    int Return_Gaps()const { return gaps;}
    int Return_AlignmentScore()const { return alignment_score; }
    double Return_MatchPercentage()const { return match_percentage; }
    double Return_GapPercentage()const { return gap_percentage; }
    
private:
   //计算逻辑，分别为计算罚分的逻辑还有回溯的逻辑。
    int GetSubstitutionScore(char a, char b) const;  //获取矩阵某位置的得分
    void Traceback(); //回溯生成最佳比对数列字符串

    // 比对结果——输出的DNA序列方式配对
    string aligned_a;
    string aligned_b;
    string match_symbols;
    int total_length;
    int matches;
    int gaps;
    int alignment_score;
    double match_percentage;
    double gap_percentage;
    
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