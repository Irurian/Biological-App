#include "fasta.h"
#include"sequence.h"
#include<iostream>
#include<vector>
#include"fasta.h"
#include<fstream>
using namespace std;

vector<sequence>fasta::FastaReadALL(string& filepath)
{
	ifstream file(filepath);
	vector<sequence>sequences;
	while (file.peek() != EOF)
	{
		int i = 0;
		sequences[i]=sequence::FastaSequenceLoad(file);
	}
	return sequences;
}





