#include"header.h"
#include"lexical.h"
extern int automation_table[][129];

string KT[] = { "break", "char", "const", "continue", "do", "double", "else", "float", "for", "if", "int", "return", "void", "while" };//¹Ø¼ü×Ö
string PT[] = { "+", "-", "*", "/", "<", ">", "=", ",", ";", "[", "]", "{", "}", "(", ")", "!", "&&", "||", "<=", ">=", "==", "!=" };//½ç·û

int lexical::openfile(string filename)
{
	file.open(filename, ios::in);
	if (!file)
	{
		return 0;
	}
	return 1;
}

vector<token> lexical::gettoken()
{
	if (!file)
	{
		cout << "You haven't input a file yet" << endl;
		exit(0);
	}
	lexical_anylize();
	return token_list;
}

void lexical::lexical_anylize()
{
	int cur_state = 1;
	int control_get = 0;
	string str = "";
	char ch = ' ';
	while (!file.eof())
	{
		if (!control_get)
		{
			file.get(c);
		}
		if (file.eof())
		{
			c = 0;
		}
		control_get = 0;
		int next_state = state_check(cur_state, c);
		if (next_state == 0)
		{
			token cur_token;
			int str_pos;
			int it_pos;
			switch (cur_state)
			{
			case 2:
				cur_token.num = CT.size();
				CT.push_back(str);
				cur_token.tablename = "CT";
				cur_token.symbol_pointer = -1;
				token_list.push_back(cur_token);
				break;
			case 6:
				cur_token.num = CT.size();
				CT.push_back(str);
				cur_token.tablename = "CT";
				cur_token.symbol_pointer = -1;
				token_list.push_back(cur_token);
				break;
			case 7:
				str_pos = check_str_type(str);
				if (str_pos == -1)
				{
					cur_token.tablename = "IT";
					it_pos = check_it_pos(str);
					if (it_pos == -1)
					{
						cur_token.num = IT.size();
						IT.push_back(str);
						symbol tmp;
						cur_token.symbol_pointer = symbol_list.size();
						tmp.name = cur_token;
						tmp.type = -1;
						//cout<< tmp.name.num;
						symbol_list.push_back(tmp);
					}
					else
					{
						cur_token.num = it_pos;
						int i = 0;
						for(auto str : symbol_list)
                        {
                            if(str.name.num == cur_token.num)
                            {
                                cur_token.symbol_pointer = i;
                            }
                            i++;
                        }
					}

				}
				else
				{
					cur_token.tablename = "KT";
					cur_token.num = str_pos;
					cur_token.symbol_pointer = -1;
				}
				token_list.push_back(cur_token);
				break;
			case 10:
				cur_token.num = CHT.size();
				cur_token.symbol_pointer = -1;
				ch = str[1];
				ch = str[1];
				CHT.push_back(ch);
				cur_token.tablename = "CHT";
				token_list.push_back(cur_token);
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 22:
			case 24:
			case 27:
			case 28:
			case 29:
			case 30:
				cur_token.num = check_pt_pos(str);
				cur_token.symbol_pointer = -1;
				cur_token.tablename = "PT";
				token_list.push_back(cur_token);
				break;
			case 25:
				cur_token.num = CT.size();
				cur_token.symbol_pointer = -1;
				cur_token.tablename = "CT";
				token_list.push_back(cur_token);
				CT.push_back(str);
				break;
			}
			//cout << str << endl;
			if (file.eof())
			{
				break;
			}
			if (c != ' '&&c != '\n'&&c != '\t'&&c != '\r')
			{
				control_get = 1;
			}
			if (cur_state == 1 && next_state == 0 && control_get == 1)
			{
				cout << "There are something wrong with your code on char ' " << c << " ' with ansii code " << (int)c << endl;
				exit(0);
			}
			str = "";
			cur_state = 1;
			continue;
		}
		else
		{
			str += c;
			cur_state = next_state;
		}

	}
}

int lexical::state_check(int cur_state, int cur_char)
{
	return automation_table[cur_state][cur_char];
}

int lexical::check_str_type(string str)
{
	int i = 0;
	for (auto s : KT)
	{
		if (s == str)
		{
			return i;
		}
		i++;
	}
	return -1;
}

int lexical::check_pt_pos(string pt)
{
	int i = 0;
	for (auto s : PT)
	{
		if (pt == s)
		{
			return i;
		}
		i++;
	}
	return -1;
}

int lexical::check_it_pos(string it)
{
	int i = 0;
	for (auto s : IT)
	{
		if (s == it)
		{
			return i;
		}
		i++;
	}
	return -1;
}

lexical::lexical()
{
	IT.clear();
	CT.clear();
	CHT.clear();
	token_list.clear();
}

lexical::~lexical()
{
	file.close();
}
