#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include "fasta.h"
#include"sequence.h"
using namespace std;

int main()
{
	string filepath;
	sequence p1;
	cout << "准备读取文件" << endl;
	getline(cin, filepath);
	vector<sequence>sequences = fasta::FastaReadALL(filepath);
	cout << "序列读取完毕" << endl;
	for ( auto& sequence : sequences)
	{
		cout << "Header:" << endl;
		sequence.OutpDNA(sequence);

		cout << "DNA" <<endl;
		sequence.OutpDNA(sequence);
	}
	cout << "最后一部";
	return 0;
}