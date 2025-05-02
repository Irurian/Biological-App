#include "FastaReader.h"
#include"Sequence.h"
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

bool FastaReader::WordJudge(char &i)
{
	i = toupper(i);//大小写兼容
	return (i == 'A' || i == 'T' || i == 'C' || i == 'G' || i == 'N' || i == '>');
}

vector<sequence> FastaReader::FastaReadALL(const string& filepath)
{
	string cleanedPath = filepath;
	vector<sequence> sequences;
	ifstream file(cleanedPath);

	FastaReader p1;
	//文件输入异常的处理(AI)
	if (!file.is_open())
	{
		throw runtime_error("无法打开FASTA文件：" + cleanedPath);
	}
	
	sequence Current;//当前指针读取的DNA序列，含有header 和 DNA
	string line;//FASTA文件的某一行字符串
	/*size_t line_number = 0;*/
	bool isHeader = false;

	while (getline(file, line)) 
	{//移除行首尾的空白，这些处理格式非常重要，不然影响输出和程序韧性
		line.erase(0, line.find_first_not_of("\t\r\n"));
		line.erase(line.find_last_not_of(" \t\r\n") + 1);

		if (line.empty()) continue;

		if (line[0] == '>') 
		{   
			// 保存前一个序列
			if (!Current.GetHeader().empty()) 
			{
				sequences.push_back(Current);
			}
			Current.Clear();

			// 设置新header（去掉>和首尾空白）erase()函数的运用
			string header = line.substr(1);
			header.erase(0, header.find_first_not_of(" \t"));
			header.erase(header.find_last_not_of(" \t") + 1);
			Current.AddHeader(header);
			bool isHeader = true;
		}
		else if(isHeader == false)
		{
			// 处理DNA行
			for (char c : line)
			{
				if (p1.WordJudge(c))
				{
					Current.AddDNA(c);
				}
			}
			
		}
	}

	if (!Current.GetHeader().empty())//重点在于连续读取和储存FASTA中的多个序列，Current为临时的值，需要多次返回加入到Current中
		//最后一行读取完后还有一个序列没有保存所以在循环外部还需要再来依次保存
	{
		sequences.push_back(Current);
	}
	// 存入DataManagement
	DataManager& dm = DataManager::GetInstance();
		dm.AddSequences(sequences);
	return sequences;
}
	

/*版本1中返回当前读取完行的初始位置指针的方式——.seekg(-offset, std::ios_base::cur);
streamoff offset = line.size() + 1;
//-size_t会触发整数溢出报错，用streamoff类型专门表示偏移量（强制转换，定义在<ios>库中）
file.seekg(-offset, std::ios_base::cur);
原代码‘file.seekg(-line.size() - 1, std::ios_base::cur);’报错一元运算符用于无符号类型
*/

//还有一种写法是构造返回指针的动态vector类来动态分配内存，但是最后要记得delete.没有传值这么方便。
/*
vector<sequence>* FastaReader::CreateSequences(sequence& Current)
{
	auto* A = new vector<sequence>;
	A->push_back(Current);
	return A;
}
*/


