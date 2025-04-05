#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include "fasta.h"

using namespace std;

class sequence
{
	friend class fasta;
private:
	string header;
	string DNA;

public:
	static sequence Getheader(string& line,sequence &A);
    static sequence GetDNA(string& line,  sequence& A);
	static sequence FastaSequenceLoad(ifstream& file);
    string ReturnHeader(sequence& A);
	string ReturnDNA(sequence& A);
	void OutpHeader(sequence& A);
	void OutpDNA(sequence& A);

	
};

