#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"sequence.h"
using namespace std;
class FastaReader  //fasta��һ�ִ��ı���ʽ�������ṹΪ������һ����>Ϊ��ͷ��������е�ID�����������ڶ��п�ʼ��DNA������Ϣ�����Ժ����С�һ��FASTA�ı����Դ洢������С�
{
	
public:
	static vector<sequence>FastaReadALL(const string& filepath);

};

