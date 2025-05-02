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
    cout << "请输入FASTA文件路径(或拖入文件): ";
    string filepath;
    getline(cin, filepath);

    FastaReader reader;
    try {
        auto sequences = reader.FastaReadALL(filepath);
        if (sequences.empty()) {
            cout << "警告: 文件未包含有效FASTA数据" << endl;
        }
        else {
            for (const auto& seq : sequences) {
                cout << "\n> " << seq.Getheader() << "\n";
                cout << seq.GetDNA() << endl;
            }
            cout << "\n解析完成，共找到 " << sequences.size() << " 条序列" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}


