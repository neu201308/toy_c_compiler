#pragma once
class lexical
{
public:
	lexical();
	~lexical();

	int openfile(string filename);
	vector<token> gettoken();

	vector<string> IT;//标识符
	vector<string> CT;//常量
	vector<char> CHT;//字符
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

