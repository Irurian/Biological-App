#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"sequence.h"
using namespace std;
class FastaReader  //fasta是一种纯文本格式，基本结构为：“第一行以>为开头，后跟序列的ID和描述”，第二行开始是DNA序列信息，可以横跨多行。一个FASTA文本可以存储多个序列。
{
	
public:
	static vector<sequence>FastaReadALL(const string& filepath);

};

