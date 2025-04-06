#include "FastaReader.h"
#include"sequence.h"
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

vector<sequence> FastaReader::FastaReadALL(const string& filepath)
{
	vector<sequence> sequences;
	ifstream file(filepath);
	//�ļ������쳣�Ĵ���(AI)
	if (!file.is_open())
	{
		throw runtime_error("�޷���FASTA�ļ���" + filepath);
	}

	sequence Current;//��ǰָ���ȡ��DNA���У�����header �� DNA
	string line;//FASTA�ļ���ĳһ���ַ���

	while (getline(file, line))
	{
		if (line.empty())continue;
		if (line[0] == '>')
		{
			//���֮ǰ�������ȱ��棨AI��
			if (!Current.Getheader().empty())//��Current��header�жϣ����header����֤�������кϷ������ж�ȡ���ж�����Ϸ��ԣ�
			{
				sequences.push_back(Current);
			}
			Current = sequence(line.substr(1));//string::substr(&������&��ȡ�ִ�����),ʡ���ִ�����ʱ�Զ���ȡ��stringĩβ����ʼ��Current
		}
		else//û��header��ȡDNA
		{
			Current.AddDNA(line);
		}
	}

	if (!Current.Getheader().empty())//�ص�����������ȡ�ʹ���FASTA�еĶ�����У�CurrentΪ��ʱ��ֵ����Ҫ��η��ؼ��뵽Current��
		//���һ�ж�ȡ�����һ������û�б���������ѭ���ⲿ����Ҫ�������α���
	{
		sequences.push_back(Current);//Vector�����.push_back(��������/ָ�룩,��vector�ද̬���Ԫ�ز���ֵ�ĺ�����
		//Vector�����.insert(����.begin()+n ��Ҫ�����ֵ ��������vector����ָ��λ�ò������
		// ���磺sequences.insert(sequences.begin() + 2,Current);
	}
			
	return sequences;
}

/*�汾1�з��ص�ǰ��ȡ���еĳ�ʼλ��ָ��ķ�ʽ����.seekg(-offset, std::ios_base::cur);
streamoff offset = line.size() + 1;
//-size_t�ᴥ���������������streamoff����ר�ű�ʾƫ������ǿ��ת����������<ios>���У�
file.seekg(-offset, std::ios_base::cur);
ԭ���롮file.seekg(-line.size() - 1, std::ios_base::cur);������һԪ����������޷�������
*/

//����һ��д���ǹ��췵��ָ��Ķ�̬vector������̬�����ڴ棬�������Ҫ�ǵ�delete.û�д�ֵ��ô���㡣
/*
vector<sequence>* FastaReader::CreateSequences(sequence& Current)
{
	auto* A = new vector<sequence>;
	A->push_back(Current);
	return A;
}
*/


