#pragma once
class lexical
{
public:
	lexical();
	~lexical();

	int openfile(string filename);
	vector<token> gettoken();

	vector<string> IT;//��ʶ��
	vector<string> CT;//����
	vector<char> CHT;//�ַ�
	vector<token> token_list;
private:
	char c;
	fstream file;
	void lexical_anylize();
	int state_check(int cur_state, int cur_char);
	int check_str_type(string str);
	int check_pt_pos(string pt);
	int check_it_pos(string it);
};

