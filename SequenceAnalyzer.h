#pragma once
#include <iostream>
#include <vector>
#include<sstream>
#include "Sequence.h"  
#include"FastaReader.h"
using namespace std;

class SequenceAnalyzer {
public:
    // �������ͳ�Ƹ���sequence���������  ADD:���������ĩβ��ü�const�����������,ֻ��������д�롣
    //Ĭ�ϼ�constԭ��ֻҪ�������޸ĳ�Ա������һ������Ϊconst

    void PrintAnalyzes(vector<SequenceAnalyzer>Analyzers)const;
    void PrintAnalyze()const;
    void PrintBaseCounts()const;  // ���ؼ��������A/T/C/G��
    //�ļ��������֮JASON��ʽ��
    string ToJSON()const;


    void SaveData(const sequence& seq);//�Ѽ����Ϣ�������Ա
    vector<SequenceAnalyzer>UpdateAnalyzers(const SequenceAnalyzer& Ana, vector<SequenceAnalyzer>Analyzers);

    // ��ȡͳ�ƽ��
    int Get_total_length()const;
    int Get_gc_count()const;
    double Get_gc_content()const;
    
private:

    static vector<SequenceAnalyzer>Analyzers;//���������,ֻҪǰ����� static �Ϳ��Թ�����
     // �洢���Ƶ��
   
    int total_length=0;            // �����г���
    int gc_count=0;                // G+C������
    double gc_content=0.0;              //GC����

    int A = 0;
    int T = 0;
    int C = 0;
    int G = 0;
    int N = 0;//N��ʾδ֪���
    // �ڲ�������ͳ�Ƽ��������gc_count_
};

