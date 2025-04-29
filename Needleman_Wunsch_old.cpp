#include "Needleman_Wunsch_old.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void Needleman_Wunsch_old::Print_NW_Result()const
{
	cout << dna_A << endl << dna_B << endl << dna_A_solved << " " << dna_B_solved;

}
/*
void Needleman_Wunsch_old::NW_Method()
{
	int a, b;
	Needleman_Wunsch_old p1;
	cout << "��ѡ��Ҫ���бȶԵ��������У�" << endl;
	cin >> a >> b;
	p1.dna_A = my_data.ReturnSequence(a).GetDNA();
	p1.dna_B = my_data.ReturnSequence(b).GetDNA();
	CreateScoreMatrix(p1.score_matrix, p1.dna_A, p1.dna_B);
	p1.TraceBack();
	p1.GetMethod(p1.match_method);
	p1.Print_NW_Result();

}
*/


//����

void Needleman_Wunsch_old::TraceBack()
{
	int i = static_cast<int>(dna_A.size());
	int j = static_cast<int>(dna_B.size()); //�����������һ��Ԫ������Ϊ���г��ȣ���������ʱ��+1��Ϊ�˳�ʼ����gap��0�ȳ�ʼ������
	int n = 0;
	
	//ADD:max()����ֻ��������������Ҫ�Ƚ����Ӧ����ôд  max({ Align, Insert, Delete })
	while (i > 0 || j > 0)
	{
		if (i > 0 && j > 0 &&
			score_matrix[i][j] == score_matrix[i - 1][j - 1] +(dna_A[i - 1] == dna_B[j - 1] ? match_score : mismatch_score))
			//��������ԶԽ�����ʱ��������Ԫ�ضԽ�����ʱ��˵����ʱʹ�õ���Align
		{
			match_method[n] = "Align";//match
			++number_of_Align;
			++match;
			--i;
			--j;
		}
		if (i>0 && score_matrix[i][j]== score_matrix[i-1][j]+ gap_penalty)
		{
			match_method[n] = "Delete";//mismatch
			++number_of_Delete;
			++mismatch;
			--i;
		}
		if(j>0 && score_matrix[i][j] == score_matrix[i][j-1] + gap_penalty)
		{
			match_method[n] = "Insert";//gap
			++number_of_Insert;
			++gaps;
			--j;
		}
		++n;
	}
	reverse(match_method.begin(), match_method.end());
}

int Needleman_Wunsch_old::CalculateScore(int& x, int& y)
{
	return 0;
}

void Needleman_Wunsch_old::GetMethod(vector<string>& match_method)
{
	int n = 0;
	for (string i : match_method)
	{
		if (i == "Align")
		{
			dna_A_solved = dna_A[n] + dna_A_solved;
			dna_B_solved = dna_B[n] + dna_B_solved;
		}
		else if (i == "Delete")
		{
			dna_A_solved = dna_A[n] + dna_A_solved;
			dna_B_solved = "-" + dna_B_solved;
		}
		else if (i == "Insert")
		{
			dna_A_solved = "-" + dna_A_solved;
			dna_B_solved = dna_B[n] + dna_B_solved;
		}
		++n;
	}
}

void Needleman_Wunsch_old::CreateScoreMatrix(vector<vector<int>>& score_matrix, string& dna_A, string& dna_B)
{
	int x = static_cast<int>(dna_A.size()) + 1;
	int y = static_cast<int>(dna_B.size()) + 1;
	 
	score_matrix.resize(x, vector<int>(y, 0));

	//��Ҫ����ʼ���߽���������ʼ������x y ��ѭ���ݹ�Ļ�����������������ʼ�������޷�������������ֵ���㣻
	for (int i = 1; i < x; ++i)
		score_matrix[i][0] = i * gap_penalty;
	for (int j = 1; j < y; ++j)
		score_matrix[0][j] = j * gap_penalty;

	int Align = 0, Insert = 0, Delete = 0;
	for (int i=1;i<x;++i)
	{
		for (int j = 1; j < y; ++j)
		{
			if (dna_A[i -1] == dna_B[j-1])
				Align = score_matrix[i - 1][j - 1] + match_score;
			else
				Align = score_matrix[i - 1][j - 1] + mismatch_score;
			Insert = score_matrix[i][j - 1] + gap_penalty;
		    Delete = score_matrix[i - 1][j] + gap_penalty;

			score_matrix[x][y] = max({ Align, Insert, Delete });
		}
	}
}