#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Sequence.h"
#include"DataManager.h"

using namespace std;
class FastaReader  //fasta��һ�ִ��ı���ʽ�������ṹΪ������һ����>Ϊ��ͷ��������е�ID�����������ڶ��п�ʼ��DNA������Ϣ�����Ժ����С�һ��FASTA�ı����Դ洢������С�
{
public:
	static vector<sequence> FastaReadALL(const string& filepath);
	/*��һ����ָ�봫ֵ�ķ�����Ҫdeleteû����ô�ã�vector<sequence>* CreateSequences(sequence& Current);*/ 
	bool WordJudge(char &i);//�Զ����ַ��Ϸ��Խ����ж�(�Ѳ���)
};