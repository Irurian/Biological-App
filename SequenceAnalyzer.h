#pragma once
#include <iostream>
#include <vector>
#include<sstream>
#include "Sequence.h"  
#include"DataManager.h"
using namespace std;
/*
还没有完成的需求：
1.更多类型文件的读取程序，整合成数据读取类
2.与数据库的交互
3.
*/

class SequenceAnalyzer {
public:
    // 输出流：统计给定sequence对象的数据  ADD:输出流函数末尾最好加const保护输出对象,只读函数不写入/或者形参表上对象前加const
    
    //默认加const原则：只要函数不修改成员变量，一律声明为const
    void PrintAnalyzes(vector<SequenceAnalyzer>Analyzers)const;
    void PrintAnalyze()const;
    void PrintBaseCounts()const;  // 返回碱基计数（A/T/C/G）
    //文件输出方法之JASON格式：(待整合)
    string ToJSON()const;

    void SaveData(const sequence& seq);//把碱基信息传入类成员
    vector<SequenceAnalyzer>& UpdateAnalyzers(const SequenceAnalyzer& Ana, vector<SequenceAnalyzer>Analyzers);

    // 获取统计结果
    int Get_total_length()const;
    int Get_gc_count()const;
    double Get_gc_content()const;
    
private:

     // 存储碱基频率
   
    int total_length=0;            // 总序列长度
    int gc_count=0;                // G+C的总数
    double gc_content=0.0;              //GC含量

    int A = 0;
    int T = 0;
    int C = 0;
    int G = 0;
    int N = 0;//N表示未知碱基
    // 内部方法：统计碱基并更新gc_count_
};

