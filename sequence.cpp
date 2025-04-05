#include "fasta.h"
#include"sequence.h"
#include<iostream>
#include<vector>
using namespace std;
sequence sequence::Getheader(string& line,sequence& A)
{
	A.header = line.substr(1);//string::substr(&索引，&提取字串长度),省略字串长度时自动提取到string末尾。
	return A;
}
sequence sequence::GetDNA(string& line, sequence& A)
{
	for (int i = 0; i <= line.size() - 1; ++i)
		A.DNA += line[i];
	return A;
}
sequence sequence::FastaSequenceLoad(ifstream& file)
{
	sequence A;
	string line;
	while (getline(file, line))
	{
		if (line.empty())continue;
		if (line[0] == '>')
		{
			A.Getheader(line, A);
			break;
		}
	}

	while (getline(file, line))
	{
		if (line.empty())continue;
		if (line[0] == '>')
		{
			streamoff offset = line.size() + 1;//-size_t会触发整数溢出报错，用streamoff类型专门表示偏移量（强制转换，定义在<ios>库中）
			file.seekg(-offset, std::ios_base::cur);//返回改行位置初始位置指针，下次循环Load里面使用
			//原代码‘file.seekg(-line.size() - 1, std::ios_base::cur);’报错一元运算符用于无符号类型
			break;
		}
		else
			A.GetDNA(line, A);
	}
	return A;
}

string sequence::ReturnHeader(sequence& A)
{
	return A.header;
}

string sequence::ReturnDNA(sequence& A)
{
	return A.DNA;
}

void sequence::OutpHeader(sequence& A)
{
	cout << A.header;
}
void sequence::OutpDNA(sequence& A)
{
	cout << A.DNA;
}
