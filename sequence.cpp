#include "fasta.h"
#include"sequence.h"
#include<iostream>
#include<vector>
using namespace std;
sequence sequence::Getheader(string& line,sequence& A)
{
	A.header = line.substr(1);//string::substr(&������&��ȡ�ִ�����),ʡ���ִ�����ʱ�Զ���ȡ��stringĩβ��
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
			streamoff offset = line.size() + 1;//-size_t�ᴥ���������������streamoff����ר�ű�ʾƫ������ǿ��ת����������<ios>���У�
			file.seekg(-offset, std::ios_base::cur);//���ظ���λ�ó�ʼλ��ָ�룬�´�ѭ��Load����ʹ��
			//ԭ���롮file.seekg(-line.size() - 1, std::ios_base::cur);������һԪ����������޷�������
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
