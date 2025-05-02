#include "DataManager.h"

/*注意这里的static要去掉，相关知识点：
1.static定义类内静态成员，说明该成员属于类而非对象——共享使用，形成所谓单例化
2.类外static定义的函数（在.cpp中使用）——该函数只在当前.cpp有效
*/
DataManager& DataManager::GetInstance() //这里的函数已经由DataManager::限制了作用域，加上static会改变函数”链接性。
{
	DataManager Instance;
	return Instance;
}
//使用的时候靠引用调用：DataManagement& dm = DataManagement::GetInstance();

void DataManager::AddSequences(const vector<sequence>& seq)
{
	for (auto& current : seq)
		my_sequences.push_back(current);
}

/*
下面三个传对象的函数都带有两个不能删去的const：第一个const不能去掉，因为后面const定义这为const成员函数
，去掉const违背了const成员函数的承诺（"不修改对象状态"），编译器会直接拒绝。
*/
const vector<sequence>& DataManager::GetAllSequences()const
{
	return my_sequences;
}

const sequence* DataManager::ReturnSequence(sequence& seq)const
{
	return &seq;
}

const sequence* DataManager::GetSequenceByHeader(const string& header)const
{
	for (auto& current_sequence : this->GetAllSequences())
	{
		if (current_sequence.GetHeader() == header)
			return  &current_sequence;
	}
	return nullptr;
}


//分析结果管理   
void DataManager::AddAnalysisResult(const string& header, const AnalysisResult& result)
{
	my_analysis_results[header] = result;
}


void DataManager::AddNWResult(const NeedlemanWunsch& current, map<int, NeedlemanWunschResult>& my_NW_result)
{
	//输出string
	my_NW_result[NW_order].aligned_a = current.Return_A();
	my_NW_result[NW_order].aligned_b = current.Return_B();
	my_NW_result[NW_order].match_symbols = current.Return_MatchSymbols();
	//计算出来的数据
	my_NW_result[NW_order].total_length = current.Return_TotalLength();
	my_NW_result[NW_order].matches = current.Return_Matches();
	my_NW_result[NW_order].gaps = current.Return_Gaps();
	my_NW_result[NW_order].alignment_score = current.Return_AlignmentScore();
	my_NW_result[NW_order].match_percentage = current.Return_MatchPercentage();
	my_NW_result[NW_order].gap_percentage = current.Return_GapPercentage();
	++NW_order;
}

//由于AnalysisResult是DataManager内部的数据成员，因此要有两个作用域
const DataManager::AnalysisResult* DataManager::GetAnalysisResult(const string& header)const
{
	auto current = my_analysis_results.find(header);
	return(current != my_analysis_results.end())? &current->second : nullptr;
	/*
	返回这个结构体对象，如果找到：返回迭代器指向的 AnalysisResult 的地址（& current->second）。
		
		current->second 是map中存储的 AnalysisResult 对象。

		通过& 取地址，返回指针。

		未找到：返回 nullptr，表示无结果。
	*/
}

DataManager::AnalysisResult DataManager::Analyze(const sequence& seq) {
	DataManager::AnalysisResult result;
	const string& dna = seq.GetDNA();
	result.total_length = static_cast<int>(dna.length());
	for (char base : dna) {
		switch (base) {
		case 'A': result.A++; break;
		case 'T': result.T++; break;
		case 'C': result.C++; break;
		case 'G': result.G++; break;
		default: result.N++; break;
		}
	}
	result.gc_count = result.G + result.C;
	result.gc_content = (result.total_length > 0) ? static_cast<double>(result.gc_count) / result.total_length : 0.0;
	return result;
}


void DataManager::PrintAnalysis(const DataManager::AnalysisResult& result)
{
	cout << fixed << setprecision(2);  // 固定小数位数
	cout << "DNA总长度为：" << result.total_length << endl;
	cout << "DNA的GC含量为：" << result.gc_content * 100 << "%" << endl;  // 显示为百分比

	const int col_width = 15;
	cout << left;  // 左对齐
	cout << setw(col_width) << "A:" << result.A << endl;
	cout << setw(col_width) << "T:" << result.T << endl;
	cout << setw(col_width) << "C:" << result.C << endl;
	cout << setw(col_width) << "G:" << result.G << endl;
	cout << setw(col_width) << "N:" << result.N << endl;
}