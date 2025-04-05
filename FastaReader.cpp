#include "FastaReader.h"
#include"sequence.h"
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

vector<sequence> FastaReader::FastaReadALL(const string& filepath)
{
	ifstream file(filepath);
	//�ļ������쳣�Ĵ���(AI)
	if (!file.is_open())
	{
		throw runtime_error("�޷���FASTA�ļ���" + filepath);
	}

	vector<sequence>sequences;//DNA������
	sequence Current;//��ǰָ���ȡ��DNA���У�����header �� DNA
	string line;//FASTA�ļ���ĳһ���ַ���

	while (getline(file, line))
	{
		if (line.empty())continue;
		if (line[0] == '>')
		{
			//���֮ǰ�������ȱ��棨AI��
			if (Current.Getheader().size()!=0)//��Current��header�жϣ����header����֤�������кϷ������ж�ȡ���ж�����Ϸ��ԣ�
			{
				sequences.push_back(Current);
			}
			Current = sequence(line.substr(1));//string::substr(&������&��ȡ�ִ�����),ʡ���ִ�����ʱ�Զ���ȡ��stringĩβ��
		}
	}

	if (Current.Getheader().size() != 0)//�ص�����������ȡ�ʹ���FASTA�еĶ�����У�CurrentΪ��ʱ��ֵ����Ҫ��η��ؼ��뵽Current��
		//���һ�ж�ȡ�����һ������û�б���������ѭ���ⲿ����Ҫ�������α���
	{
		sequences.push_back(Current);
	}
			
	return sequences;
			/*�汾1�з��ص�ǰ��ȡ���еĳ�ʼλ��ָ��ķ�ʽ����.seekg(-offset, std::ios_base::cur);
			streamoff offset = line.size() + 1;
			//-size_t�ᴥ���������������streamoff����ר�ű�ʾƫ������ǿ��ת����������<ios>���У�
			file.seekg(-offset, std::ios_base::cur);
			ԭ���롮file.seekg(-line.size() - 1, std::ios_base::cur);������һԪ����������޷�������
			*/
}





