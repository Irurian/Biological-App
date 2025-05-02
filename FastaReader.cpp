#include "FastaReader.h"
#include"Sequence.h"
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

bool FastaReader::WordJudge(char &i)
{
	i = toupper(i);//��Сд����
	return (i == 'A' || i == 'T' || i == 'C' || i == 'G' || i == 'N' || i == '>');
}

vector<sequence> FastaReader::FastaReadALL(const string& filepath)
{
	string cleanedPath = filepath;
	vector<sequence> sequences;
	ifstream file(cleanedPath);

	FastaReader p1;
	//�ļ������쳣�Ĵ���(AI)
	if (!file.is_open())
	{
		throw runtime_error("�޷���FASTA�ļ���" + cleanedPath);
	}
	
	sequence Current;//��ǰָ���ȡ��DNA���У�����header �� DNA
	string line;//FASTA�ļ���ĳһ���ַ���
	/*size_t line_number = 0;*/
	bool isHeader = false;

	while (getline(file, line)) 
	{//�Ƴ�����β�Ŀհף���Щ�����ʽ�ǳ���Ҫ����ȻӰ������ͳ�������
		line.erase(0, line.find_first_not_of("\t\r\n"));
		line.erase(line.find_last_not_of(" \t\r\n") + 1);

		if (line.empty()) continue;

		if (line[0] == '>') 
		{   
			// ����ǰһ������
			if (!Current.GetHeader().empty()) 
			{
				sequences.push_back(Current);
			}
			Current.Clear();

			// ������header��ȥ��>����β�հף�erase()����������
			string header = line.substr(1);
			header.erase(0, header.find_first_not_of(" \t"));
			header.erase(header.find_last_not_of(" \t") + 1);
			Current.AddHeader(header);
			bool isHeader = true;
		}
		else if(isHeader == false)
		{
			// ����DNA��
			for (char c : line)
			{
				if (p1.WordJudge(c))
				{
					Current.AddDNA(c);
				}
			}
			
		}
	}

	if (!Current.GetHeader().empty())//�ص�����������ȡ�ʹ���FASTA�еĶ�����У�CurrentΪ��ʱ��ֵ����Ҫ��η��ؼ��뵽Current��
		//���һ�ж�ȡ�����һ������û�б���������ѭ���ⲿ����Ҫ�������α���
	{
		sequences.push_back(Current);
	}
	// ����DataManagement
	DataManager& dm = DataManager::GetInstance();
		dm.AddSequences(sequences);
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


