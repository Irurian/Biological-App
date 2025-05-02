#include <iostream>
#include "FastaReader.h"
#include "Sequence.h"
#include "SequenceAnalyzer.h"
#include "NeedlemanWunsch.h"
#include "DataManager.h"  // ͷ�ļ����ƺ�����һ��
using namespace std;

int main() {
    // ��ȡ���в��洢
    cout << "������FASTA�ļ�·��(�������ļ�): ";
    string filepath;
    getline(cin, filepath);
    vector<sequence>sequences;

    FastaReader reader;
    try {
        sequences = reader.FastaReadALL(filepath);
        if (sequences.empty()) {
            cout << "����: �ļ�δ������ЧFASTA����" << endl;
        }
        else {
            for (const auto& seq : sequences) {
                cout << "\n> " << seq.GetHeader() << "\n";
                cout << seq.GetDNA() << endl;
            }
            cout << "\n������ɣ����ҵ� " << sequences.size() << " ������" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "����: " << e.what() << endl;
        return 1;
    }

    // �������в�������
    DataManager& dm = DataManager::GetInstance();

    for(auto& current:sequences)
    {
        auto result = DataManager::Analyze(current);
        dm.AddAnalysisResult(current.GetHeader(), result);
    }

    // ��ȡ��ʹ������
    const auto* analysis = dm.GetAnalysisResult(sequences[0].GetHeader());
    if (analysis) {
        DataManager::PrintAnalysis(*analysis);
    }

    return 0;
}