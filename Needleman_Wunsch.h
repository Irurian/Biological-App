#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

class NeedlemanWunsch {
public:
    // ���캯��
    NeedlemanWunsch(string seq_a, string seq_b, int gap = -2);

    // ��ʼ�ȶԼ��㻹��������
    void Align();  //�ȶԴ����
    void PrintResults() const;  //������

private:
   //�����߼����ֱ�Ϊ���㷣�ֵ��߼����л��ݵ��߼���
    int GetSubstitutionScore(char a, char b) const;  //��ȡ����ĳλ�õĵ÷�
    void Traceback(); //����������ѱȶ������ַ���

    // �ȶԽ�����������DNA���з�ʽ���
    string aligned_a;
    string aligned_b;
    string match_symbols;

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