#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

//更多种类的数据类型？更多样化的FASTA存储格式，其他类型格式？

class sequence
{
private:
	string header;
	string DNA;

public://包含了序列的header,DNA,序列长度的提取还有打印。
	//AI提议的构造函数
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

