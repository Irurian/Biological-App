#pragma once
#include<iostream>
#include<vector>
#include<string>


using namespace std;

class Needleman_Wunsch_old
{
	
private:
	vector<vector<int>>score_matrix;
	vector<string>match_method;
	
	int number_of_Align;
	int number_of_Insert;
	int number_of_Delete;

	int mismatch;
	int gaps;
	int match;

	string dna_A;
	string dna_B;

	string dna_A_solved;
	string dna_B_solved;

    const int gap_penalty=-1;
	const int match_score=+1;
	const int mismatch_score=-1;

public:
	//输出模块

	void Print_NW_Result()const;
	void NW_Method()
	{
		;
	}

	//部件

	void TraceBack();
	int CalculateScore(int&x,int&y);
	void CreateScoreMatrix(vector<vector<int>>& score_matrix, string &dna_A,string &dna_B);
	void GetMethod(vector<string>& match_method);
	
};

