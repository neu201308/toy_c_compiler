#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<stack>

using namespace std;
struct token{
	string tablename;
	int num;
	int symbol_pointer;
};

struct ttable{
	int num;
	string name;
};

struct symbol{
	token name;
	int type;
	string category;
	int address;
};

struct tapel{
	string tval;
	int tpoint;
};

struct token_all{	//四元式中项的类型
	int num;
	int kind;
	token_all(){}
	token_all(int kind1, int num1)
	{
		num = num1;
		kind = kind1;
	}
};

struct quad{
	string op;
	token_all arg1, arg2, result;
};
