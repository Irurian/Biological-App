#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;
/*
��û����ɵ�����
1.'N'����ıȶ������û����� 
2.������ݵķ�ʽ����Ҫ�����ļ���ת��ΪJSON��ʽ�ȡ�
3.���ֽ������ĸ���
4.NW�㷨�߼��Ż�
5.�Զ�������ֱ�׼
*/

class NeedlemanWunsch {   
public:
    // ���캯��
    NeedlemanWunsch(string seq_a, string seq_b, int gap = -2);

    // ��ʼ�ȶԼ��㻹��������
    void Align();  //�ȶԴ����
    void PrintResults() const;  //������
    void Analyze();

    //�������ݳ�Ա
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
   //�����߼����ֱ�Ϊ���㷣�ֵ��߼����л��ݵ��߼���
    int GetSubstitutionScore(char a, char b) const;  //��ȡ����ĳλ�õĵ÷�
    void Traceback(); //����������ѱȶ������ַ���

    // �ȶԽ�����������DNA���з�ʽ���
    string aligned_a;
    string aligned_b;
    string match_symbols;
    int total_length;
    int matches;
    int gaps;
    int alignment_score;
    double match_percentage;
    double gap_percentage;
    
    // ԭʼ���кͲ���
    const string seq_a;
    const string seq_b;
    const int gap_penalty;  //��λ����
  
    // ��̬�滮����
    vector<vector<int>> score_matrix;

    // ���ж������������ַ�ʽ�����м���߼�
    static const map<char, int> dna_index;      // ���ӳ���
    static const vector<vector<int>> sub_mat;  // �滻����
};