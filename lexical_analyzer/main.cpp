#include "header.h"
#include "lexical.h"
int main()
{
	lexical lexical_analyzer;
	lexical_analyzer.openfile("a.txt");
	vector<token> token_list = lexical_analyzer.gettoken();
	for (auto str : lexical_analyzer.token_list)
	{
		cout << str.tablename << " " << str.num << endl;
	}
	return 0;
}