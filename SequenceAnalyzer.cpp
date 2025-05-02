#include "SequenceAnalyzer.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include<cctype>
#include<iomanip>
using namespace std;

//可以加上DNA长度为0的检测
void SequenceAnalyzer::SaveData(const sequence& seq)
{
	string DNA = seq.GetDNA();
	for (auto& A : DNA)
	{
		A = toupper(A);//兼容大小写输入
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

	this->gc_content = static_cast<double>(gc_count) / total_length;//最高精度的输入格式：内存中的double类型本身具有约15-17位十进制精度，您不需要（也无法）在数据输入时限制其存储精度
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
		cout << "序列" << i << endl;
		cout << "=============" << endl;
		A.PrintAnalyze();
		++i;
	}
	cout << "=============" << endl;
}

void SequenceAnalyzer::PrintAnalyze() const 
{  
	cout << fixed << setprecision(2);  // 固定小数位数
	cout << "DNA总长度为：" << total_length << endl;
	cout << "DNA的GC含量为：" << gc_content * 100 << "%" << endl;  // 显示为百分比
	PrintBaseCounts();
}

void SequenceAnalyzer::PrintBaseCounts() const 
{
	const int col_width = 15;
	cout << left;  // 左对齐
	cout << setw(col_width) << "A:" << A << endl;
	cout << setw(col_width) << "T:" << T << endl;
	cout << setw(col_width) << "C:" << C << endl;
	cout << setw(col_width) << "G:" << G << endl;
	cout << setw(col_width) << "N:" << N << endl;
}

/*自己写的最初模板
void SequenceAnalyzer::PrintBaseCounts() 
{
	cout << "DNA中A碱基数量为：" << this->A<<endl;
	cout << "DNA中T碱基数量为：" << this->T << endl;
	cout << "DNA中C碱基数量为：" << this->C << endl;
	cout << "DNA中G碱基数量为：" << this->G << endl;
	cout << "DNA中N碱基数量为：" << this->N << endl;
}

void SequenceAnalyzer::PrintAnalyze( ) 
{
	cout <<"DNA总长度为："<< this->total_length<<endl;
	cout << "DNA的GC含量为：" << this->gc_content << endl;
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
}//AI 建议的JSON格式输出
