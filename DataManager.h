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

//ʹ�õ���ģʽ��ȷ����������ֻ��һ��ʵ�����ڣ���������
class DataManager
{
public:
	//DNA������ݵĴ洢��ʽ--struct�൱��һ������ͷ�װ��������� vector �� map �п���ͬʱ������������ݳ�Ա��Ȼ�� ���ʷ�ʽ������
	struct AnalysisResult
	{
		int total_length = 0;
		int gc_count = 0;
		double gc_content = 0;
		int A = 0, T = 0, C = 0, G = 0, N = 0;
	};

	struct NeedlemanWunschResult
	{
		//���string
		string aligned_a;
		string aligned_b;
		string match_symbols;
		//�������������
		int total_length=0;
		int matches=0;
		int gaps=0;
		int alignment_score=0;
		double match_percentage=0;
		double gap_percentage=0;
	};
	
	//�������ʣ�ȷ������ֻ��Ψһ�����ݴ洢��(���̶�static����
	static DataManager& GetInstance();


	//��ֹ�����͸�ֵ
	DataManager(const DataManager&) = delete; //��ֹ���ÿ������캯��
	DataManager& operator=(const DataManager&) = delete; //��ֹ��ֵ

	
	//���й���
	void AddSequences(const vector<sequence>& seq);
    const vector<sequence>& GetAllSequences()const; //����&����ô��
	const sequence* GetSequenceByHeader(const string& header)const;//header��Ϊ���ʶ���Ĺؼ���
	const sequence* ReturnSequence(sequence& seq)const;

	//�����������   
	void AddAnalysisResult(const string& header, const AnalysisResult& result);
	const AnalysisResult* GetAnalysisResult(const string& header)const;
	void AddNWResult(const NeedlemanWunsch& current , map<int, NeedlemanWunschResult>& my_NW_result);

	//�������
	static AnalysisResult Analyze(const sequence& seq);
	static void PrintAnalysis(const DataManager::AnalysisResult& result);
	//��̬�������ã�SequenceAnalyzer::PrintAnalysis(*analysis)���� ����::��̬��������
private:
	//1.���캯��
	DataManager() = default;
	//2.�洢���ݵ�vector��map
	vector<sequence>my_sequences;
	map<int, NeedlemanWunschResult>my_NW_result;
	map<string, AnalysisResult>my_analysis_results;
};

static int NW_order = 1;
/*ADD:
��C++�У����ض�������ã�&��������ֱ�ӷ��ض�������Ҫ�������¼����ؼ�ԭ��

1. ���ⲻ��Ҫ�Ŀ���
ֱ�ӷ��ض�����&���ᴥ���������죺
vector<sequence> GetAllSequences() const;  // ����ʱ��������vector
���vector�ܴ󣬿�����������������ܿ�����

�������ã���&���㿽����
const vector<sequence>& GetAllSequences() const;  // ����������
����������󣬶�ֻ����һ��ָ���С�ĵ�ַ��
*/