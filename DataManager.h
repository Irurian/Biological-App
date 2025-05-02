#pragma once
#include<vector>
#include<map>
#include<string>
#include"Sequence.h"
#include"SequenceAnalyzer.h"
#include"NeedlemanWunsch.h"
#include<algorithm>
#include<iomanip>
using namespace std;

//使用单例模式，确保所有数据只有一个实例存在，共用数据
class DataManager
{
public:
	//DNA相关数据的存储方式--struct相当于一个打包和封装，在下面的 vector 和 map 中可以同时包含所需的数据成员，然后 访问方式？？？
	struct AnalysisResult
	{
		int total_length = 0;
		int gc_count = 0;
		double gc_content = 0;
		int A = 0, T = 0, C = 0, G = 0, N = 0;
	};

	struct NeedlemanWunschResult
	{
		//输出string
		string aligned_a;
		string aligned_b;
		string match_symbols;
		//计算出来的数据
		int total_length=0;
		int matches=0;
		int gaps=0;
		int alignment_score=0;
		double match_percentage=0;
		double gap_percentage=0;
	};
	
	//单例访问：确保程序只有唯一的数据存储点(传固定static对象）
	static DataManager& GetInstance();


	//禁止拷贝和赋值
	DataManager(const DataManager&) = delete; //禁止调用拷贝构造函数
	DataManager& operator=(const DataManager&) = delete; //禁止赋值

	
	//序列管理
	void AddSequences(const vector<sequence>& seq);
    const vector<sequence>& GetAllSequences()const; //不加&会怎么样
	const sequence* GetSequenceByHeader(const string& header)const;//header作为访问对象的关键字
	const sequence* ReturnSequence(sequence& seq)const;

	//分析结果管理   
	void AddAnalysisResult(const string& header, const AnalysisResult& result);
	const AnalysisResult* GetAnalysisResult(const string& header)const;
	void AddNWResult(const NeedlemanWunsch& current , map<int, NeedlemanWunschResult>& my_NW_result);

	//输出函数
	static AnalysisResult Analyze(const sequence& seq);
	static void PrintAnalysis(const DataManager::AnalysisResult& result);
	//静态函数调用：SequenceAnalyzer::PrintAnalysis(*analysis)—— 类名::静态函数（）
private:
	//1.构造函数
	DataManager() = default;
	//2.存储数据的vector和map
	vector<sequence>my_sequences;
	map<int, NeedlemanWunschResult>my_NW_result;
	map<string, AnalysisResult>my_analysis_results;
};

static int NW_order = 1;
/*ADD:
在C++中，返回对象的引用（&）而不是直接返回对象本身，主要基于以下几个关键原因：

1. 避免不必要的拷贝
直接返回对象（无&）会触发拷贝构造：
vector<sequence> GetAllSequences() const;  // 返回时拷贝整个vector
如果vector很大，拷贝会带来显著的性能开销。

返回引用（带&）零拷贝：
const vector<sequence>& GetAllSequences() const;  // 仅返回引用
无论容器多大，都只传递一个指针大小的地址。
*/