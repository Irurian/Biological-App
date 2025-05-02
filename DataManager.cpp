#include "DataManager.h"

/*ע�������staticҪȥ�������֪ʶ�㣺
1.static�������ھ�̬��Ա��˵���ó�Ա��������Ƕ��󡪡�����ʹ�ã��γ���ν������
2.����static����ĺ�������.cpp��ʹ�ã������ú���ֻ�ڵ�ǰ.cpp��Ч
*/
DataManager& DataManager::GetInstance() //����ĺ����Ѿ���DataManager::�����������򣬼���static��ı亯���������ԡ�
{
	DataManager Instance;
	return Instance;
}
//ʹ�õ�ʱ�����õ��ã�DataManagement& dm = DataManagement::GetInstance();

void DataManager::AddSequences(const vector<sequence>& seq)
{
	for (auto& current : seq)
		my_sequences.push_back(current);
}

/*
��������������ĺ�����������������ɾȥ��const����һ��const����ȥ������Ϊ����const������Ϊconst��Ա����
��ȥ��constΥ����const��Ա�����ĳ�ŵ��"���޸Ķ���״̬"������������ֱ�Ӿܾ���
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


//�����������   
void DataManager::AddAnalysisResult(const string& header, const AnalysisResult& result)
{
	my_analysis_results[header] = result;
}


void DataManager::AddNWResult(const NeedlemanWunsch& current, map<int, NeedlemanWunschResult>& my_NW_result)
{
	//���string
	my_NW_result[NW_order].aligned_a = current.Return_A();
	my_NW_result[NW_order].aligned_b = current.Return_B();
	my_NW_result[NW_order].match_symbols = current.Return_MatchSymbols();
	//�������������
	my_NW_result[NW_order].total_length = current.Return_TotalLength();
	my_NW_result[NW_order].matches = current.Return_Matches();
	my_NW_result[NW_order].gaps = current.Return_Gaps();
	my_NW_result[NW_order].alignment_score = current.Return_AlignmentScore();
	my_NW_result[NW_order].match_percentage = current.Return_MatchPercentage();
	my_NW_result[NW_order].gap_percentage = current.Return_GapPercentage();
	++NW_order;
}

//����AnalysisResult��DataManager�ڲ������ݳ�Ա�����Ҫ������������
const DataManager::AnalysisResult* DataManager::GetAnalysisResult(const string& header)const
{
	auto current = my_analysis_results.find(header);
	return(current != my_analysis_results.end())? &current->second : nullptr;
	/*
	��������ṹ���������ҵ������ص�����ָ��� AnalysisResult �ĵ�ַ��& current->second����
		
		current->second ��map�д洢�� AnalysisResult ����

		ͨ��& ȡ��ַ������ָ�롣

		δ�ҵ������� nullptr����ʾ�޽����
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
	cout << fixed << setprecision(2);  // �̶�С��λ��
	cout << "DNA�ܳ���Ϊ��" << result.total_length << endl;
	cout << "DNA��GC����Ϊ��" << result.gc_content * 100 << "%" << endl;  // ��ʾΪ�ٷֱ�

	const int col_width = 15;
	cout << left;  // �����
	cout << setw(col_width) << "A:" << result.A << endl;
	cout << setw(col_width) << "T:" << result.T << endl;
	cout << setw(col_width) << "C:" << result.C << endl;
	cout << setw(col_width) << "G:" << result.G << endl;
	cout << setw(col_width) << "N:" << result.N << endl;
}