#include "SequenceAnalyzer.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include<cctype>
#include<iomanip>
using namespace std;

//���Լ���DNA����Ϊ0�ļ��
void SequenceAnalyzer::SaveData(const sequence& seq)
{
	string DNA = seq.GetDNA();
	for (auto& A : DNA)
	{
		A = toupper(A);//���ݴ�Сд����
		switch (A) 
		{
		case'A':this->A += 1; break;
		case'T':this->T += 1; break;
		case'C':this->C += 1; break;
		case'G':this->G += 1; break;
		case'N':this->N += 1; break;
		}
	}
	this->total_length = A + T + C + G + N;
	this->gc_count = C + G;

	this->gc_content = static_cast<double>(gc_count) / total_length;//��߾��ȵ������ʽ���ڴ��е�double���ͱ������Լ15-17λʮ���ƾ��ȣ�������Ҫ��Ҳ�޷�������������ʱ������洢����
}

vector<SequenceAnalyzer>& SequenceAnalyzer::UpdateAnalyzers(const SequenceAnalyzer& Ana, vector<SequenceAnalyzer>Analyzers)
{
	Analyzers.push_back(Ana);
	return Analyzers;
}


void SequenceAnalyzer::PrintAnalyzes(vector<SequenceAnalyzer>Analyzers)const 
{
	int i = 1;
	for (auto& A : Analyzers) 
	{
		cout << "����" << i << endl;
		cout << "=============" << endl;
		A.PrintAnalyze();
		++i;
	}
	cout << "=============" << endl;
}

void SequenceAnalyzer::PrintAnalyze() const 
{  
	cout << fixed << setprecision(2);  // �̶�С��λ��
	cout << "DNA�ܳ���Ϊ��" << total_length << endl;
	cout << "DNA��GC����Ϊ��" << gc_content * 100 << "%" << endl;  // ��ʾΪ�ٷֱ�
	PrintBaseCounts();
}

void SequenceAnalyzer::PrintBaseCounts() const 
{
	const int col_width = 15;
	cout << left;  // �����
	cout << setw(col_width) << "A:" << A << endl;
	cout << setw(col_width) << "T:" << T << endl;
	cout << setw(col_width) << "C:" << C << endl;
	cout << setw(col_width) << "G:" << G << endl;
	cout << setw(col_width) << "N:" << N << endl;
}

/*�Լ�д�����ģ��
void SequenceAnalyzer::PrintBaseCounts() 
{
	cout << "DNA��A�������Ϊ��" << this->A<<endl;
	cout << "DNA��T�������Ϊ��" << this->T << endl;
	cout << "DNA��C�������Ϊ��" << this->C << endl;
	cout << "DNA��G�������Ϊ��" << this->G << endl;
	cout << "DNA��N�������Ϊ��" << this->N << endl;
}

void SequenceAnalyzer::PrintAnalyze( ) 
{
	cout <<"DNA�ܳ���Ϊ��"<< this->total_length<<endl;
	cout << "DNA��GC����Ϊ��" << this->gc_content << endl;
	this->PrintBaseCounts();
}
*/


int SequenceAnalyzer::Get_total_length()const 
{
	return total_length;
}

int SequenceAnalyzer::Get_gc_count() const
{
	return gc_count;
}

double SequenceAnalyzer::Get_gc_content()const 
{
	return gc_content;
}

string SequenceAnalyzer::ToJSON()const
{
	std::ostringstream oss;
	oss << "{"
		<< "\"A\":" << A << ","
		<< "\"T\":" << T << ","
		<< "\"C\":" << C << ","
		<< "\"G\":" << G << ","
		<< "\"N\":" << N << ","
		<< "\"gc_content\":" << gc_content << ","
		<< "\"length\":" << total_length
		<< "}";
	return oss.str();
}//AI �����JSON��ʽ���
