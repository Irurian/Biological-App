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
	cout << "׼����ȡ�ļ�" << endl;
	getline(cin, filepath);
	vector<sequence>sequences = fasta::FastaReadALL(filepath);
	cout << "���ж�ȡ���" << endl;
	for ( auto& sequence : sequences)
	{
		cout << "Header:" << endl;
		sequence.OutpDNA(sequence);

		cout << "DNA" <<endl;
		sequence.OutpDNA(sequence);
	}
	cout << "���һ��";
	return 0;
}