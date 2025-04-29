#include "Needleman_Wunsch.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
// ��ʼ����̬��Ա,dna_index��sub_mat��github��Դ����������������������������ai�������
/*
1. dna_index�����������������ӳ���
����
�����ַ�����ֵ��ӳ�䣺��DNA����ַ���A/T/C/G��ת��Ϊ�滻�����е���/��������0-3�������ڿ��ٲ��ҵ÷֡�

ͳһ��Сд����ͬʱ֧�ִ�д��Сд������� a �� A ��ӳ�䵽����0����
*/
const map<char, int> NeedlemanWunsch::dna_index = 
{
    {'A',0}, {'T',1}, {'C',2}, {'G',3},
    {'a',0}, {'t',1}, {'c',2}, {'g',3}
};


//2.DNA�滻����A-T-C-G˳�򣩣�ԭ���õ�����ͨ�Ĵ���-1��ƥ��+1������ai�����и���רҵ��ƥ����ϵ��Ȼ������㷨�����ַ�ʽ��ʵ�ܶ���������ԭ����ͬ
/*
ͨ�� sub_mat ����ʵ�ֲ�ͬ����ԵĲ��컯���֣������ڿ�λ���֣���λ������һ�ֶ���ķ�ʽ����

A - T���䣺 - 1

C - G���䣺 - 1

�����ʹ��䣨��A - C���� - 2

ƥ�䣺 + 1
*/
const vector<vector<int>> NeedlemanWunsch::sub_mat = 
{
    // A   T   C   G
    { 1, -1, -2, -2 },  // A
    {-1,  1, -2, -2 },  // T
    {-2, -2,  1, -1 },  // C
    {-2, -2, -1,  1 }   // G
};

// ���캯��
NeedlemanWunsch::NeedlemanWunsch(string a, string b, int gap)
    : seq_a(move(a)), seq_b(move(b)), gap_penalty(gap)//��λ����Ĭ��Ϊ-2������ȡ����ֵ
{
    // ��ʼ����̬�滮����
    size_t m = seq_a.length() + 1;
    size_t n = seq_b.length() + 1;
    score_matrix.resize(m, vector<int>(n, 0));

    // ��ʼ���߽�����
    for (size_t i = 0; i < m; ++i)
        score_matrix[i][0] = static_cast<int>(i) * gap_penalty;
    for (size_t j = 0; j < n; ++j)
        score_matrix[0][j] = static_cast<int>(j) * gap_penalty;
}

// ���ıȶ��㷨
void NeedlemanWunsch::Align() 
{
    size_t m = seq_a.length();
    size_t n = seq_b.length();

    for (size_t i = 1; i <= m; ++i)
    {
        for (size_t j = 1; j <= n; ++j) 
        {
            // ʹ���滻�����ȡʵ�ʵ÷�
            int match = score_matrix[i - 1][j - 1] + GetSubstitutionScore(seq_a[i - 1], seq_b[j - 1]);
            int del = score_matrix[i - 1][j] + gap_penalty;
            int insert = score_matrix[i][j - 1] + gap_penalty;

            score_matrix[i][j] = max({ match, del, insert }); 
        }
    }
    Traceback();//���ݻ�ȡ����������Ž��������
}

// ��ȡ�滻��������������ÿ��λ�ô���һ���滻��ʽ�����ַ�ʽ�ĵ÷�
int NeedlemanWunsch::GetSubstitutionScore(char a, char b) const 
{
        int idx_a = dna_index.at(a);  // ʵ��ʹ������ֵ
        int idx_b = dna_index.at(b);
        return sub_mat[idx_a][idx_b];  // ���ؾ����еľ���ֵ
}

// ����·������ȡ�����Է�ʽ����������ѧר�÷��ŵõ�����������ż����Է�ʽ��
void NeedlemanWunsch::Traceback()
{
    size_t i = seq_a.length();
    size_t j = seq_b.length();

    while (i > 0 || j > 0)//�Ӿ���ĩβ��ʼ�����ζ��ϣ��󣬶Խǵĵ÷ֽ����жϣ�����ѡ��ԽǷ�ʽ����ߵķ�
    {
        if (i > 0 && j > 0 && score_matrix[i][j] == score_matrix[i - 1][j - 1] + GetSubstitutionScore(seq_a[i - 1], seq_b[j - 1])) 
        {    // ��ǰ�÷� = ���Ͻǵ÷� + �滻���������ȱ������ܵ�ͬԴλ��
            aligned_a = seq_a[--i] + aligned_a;
            aligned_b = seq_b[--j] + aligned_b;
            match_symbols = (seq_a[i] == seq_b[j] ? '|' : ':') + match_symbols;
        }
        else if (i > 0 && score_matrix[i][j] == score_matrix[i - 1][j] + gap_penalty)
        {    // ��ǰ�÷� = �Ϸ��÷� + ��λ����
            aligned_a = seq_a[--i] + aligned_a;
            aligned_b = '-' + aligned_b;
            match_symbols = ' ' + match_symbols;
        }
        else 
        {    //��ǰ�÷� = ���÷� + ��λ����
            aligned_a = '-' + aligned_a;
            aligned_b = seq_b[--j] + aligned_b;
            match_symbols = ' ' + match_symbols;
        }
    }
}

// ������
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