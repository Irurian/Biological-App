#include <iostream>
#include "FastaReader.h"
#include "Sequence.h"
#include "SequenceAnalyzer.h"
#include "NeedlemanWunsch.h"
#include "DataManager.h"  // 头文件名称和类名一致
using namespace std;

int main() {
    // 读取序列并存储
    cout << "请输入FASTA文件路径(或拖入文件): ";
    string filepath;
    getline(cin, filepath);
    vector<sequence>sequences;

    FastaReader reader;
    try {
        sequences = reader.FastaReadALL(filepath);
        if (sequences.empty()) {
            cout << "警告: 文件未包含有效FASTA数据" << endl;
        }
        else {
            for (const auto& seq : sequences) {
                cout << "\n> " << seq.GetHeader() << "\n";
                cout << seq.GetDNA() << endl;
            }
            cout << "\n解析完成，共找到 " << sequences.size() << " 条序列" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    // 分析序列并保存结果
    DataManager& dm = DataManager::GetInstance();

    for(auto& current:sequences)
    {
        auto result = DataManager::Analyze(current);
        dm.AddAnalysisResult(current.GetHeader(), result);
    }

    // 获取并使用数据
    const auto* analysis = dm.GetAnalysisResult(sequences[0].GetHeader());
    if (analysis) {
        DataManager::PrintAnalysis(*analysis);
    }

    return 0;
}