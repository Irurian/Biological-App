#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"sequence.h"
using namespace std;
class fasta  //fasta��һ�ִ��ı���ʽ�������ṹΪ������һ����>Ϊ��ͷ��������е�ID�����������ڶ��п�ʼ��DNA������Ϣ�����Ժ����С�һ��FASTA�ı����Դ洢������С�
{
	 friend class sequence;
public:
	static vector<sequence>FastaReadALL(string& filepath);

};

