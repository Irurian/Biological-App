#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include "FastaReader.h"

using namespace std;

class sequence
{
private:
	string header;
	string DNA;

public://���������е�header,DNA,���г��ȵ���ȡ���д�ӡ��
	//AI����Ĺ��캯��
	sequence(const string&h="",const string&d=""):header(h),DNA(d){}

	string Getheader()const { return header; }
	string GetDNA()const { return DNA; }
	size_t length()const { return DNA.length(); }
	string PrintHeader() { cout << header; }
	string PrintDNA() { cout << DNA; }
};

