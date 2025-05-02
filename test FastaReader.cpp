#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include "FastaReader.h"
#include"Sequence.h"
#include"SequenceAnalyzer.h"
using namespace std;

int main()
{
    cout << "������FASTA�ļ�·��(�������ļ�): ";
    string filepath;
    getline(cin, filepath);

    FastaReader reader;
    try {
        auto sequences = reader.FastaReadALL(filepath);
        if (sequences.empty()) {
            cout << "����: �ļ�δ������ЧFASTA����" << endl;
        }
        else {
            for (const auto& seq : sequences) {
                cout << "\n> " << seq.Getheader() << "\n";
                cout << seq.GetDNA() << endl;
            }
            cout << "\n������ɣ����ҵ� " << sequences.size() << " ������" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "����: " << e.what() << endl;
        return 1;
    }

    return 0;
}


