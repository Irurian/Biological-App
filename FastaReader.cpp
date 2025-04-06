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
	//文件输入异常的处理(AI)
	if (!file.is_open())
	{
		throw runtime_error("无法打开FASTA文件：" + filepath);
	}

	sequence Current;//当前指针读取的DNA序列，含有header 和 DNA
	string line;//FASTA文件的某一行字符串

	while (getline(file, line))
	{
		if (line.empty())continue;
		if (line[0] == '>')
		{
			//如果之前有序列先保存（AI）
			if (!Current.Getheader().empty())//对Current的header判断，如果header存在证明该序列合法，进行读取（判断输入合法性）
			{
				sequences.push_back(Current);
			}
			Current = sequence(line.substr(1));//string::substr(&索引，&提取字串长度),省略字串长度时自动提取到string末尾。初始化Current
		}
		else//没有header读取DNA
		{
			Current.AddDNA(line);
		}
	}

	if (!Current.Getheader().empty())//重点在于连续读取和储存FASTA中的多个序列，Current为临时的值，需要多次返回加入到Current中
		//最后一行读取完后还有一个序列没有保存所以在循环外部还需要再来依次保存
	{
		sequences.push_back(Current);//Vector类对象.push_back(返回容器/指针）,是vector类动态添加元素并赋值的函数。
		//Vector类对象.insert(对象.begin()+n ，要插入的值 ）用于向vector类中指定位置插入对象。
		// 例如：sequences.insert(sequences.begin() + 2,Current);
	}
			
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


