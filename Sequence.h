#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

//����������������ͣ�����������FASTA�洢��ʽ���������͸�ʽ��

class sequence
{
private:
	string header;
	string DNA;

public://���������е�header,DNA,���г��ȵ���ȡ���д�ӡ��
	//AI����Ĺ��캯��
	sequence(const string&h="",const string&d=""):header(h),DNA(d){}
	void Clear() { header.clear(); DNA.clear(); }

	string GetHeader()const { return header; }
	string GetDNA()const { return DNA; }
	size_t length()const { return DNA.length(); }
	void PrintHeader() { cout << header; }
	void PrintDNA() { cout << DNA; }
	void AddHeader(const string& line) { header = line; }
	void AddDNA(const string& line) { DNA += line; }
	void AddHeader(const char& i) { header += i; }
	void AddDNA(const char& i) { DNA += i; }
};

