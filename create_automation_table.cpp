#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int table[21][129];
void settable(int line, int row, int value)
{
	table[line][row] = value;
}
int main()
{
	memset(table, 0, sizeof(table));
	string biaoshifu = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string shuzi = "0123456789";
	string jiefu = "{}<>[];+-*/),";
	string Ee = "Ee";
	string jiajian = "+-";
	for (auto i : biaoshifu)
	{
		settable(1, i, 7);
		settable(7, i, 7);
	}
	for (auto i : shuzi)
	{
		settable(1, i, 2);
		settable(2, i, 2);
		settable(3, i, 3);
		settable(4, i, 6);
		settable(5, i, 6);
		settable(6, i, 6);
		settable(12, i, 2);
	}
	for (auto i : Ee)
	{
		settable(2, i, 4);
		settable(3, i, 4);
	}
	for (auto i : jiajian)
	{
		settable(4, i, 5);
		settable(13, i, 12);
		settable(11, i, 12);
	}
	for (auto i : jiefu)
	{
		settable(1, i, 20);
	}
	for (int i = 1; i <= 128; i++)
	{
			settable(8, i, 9);
	}
	settable(1, '\'', 8);
	settable(9, '\'', 10);
	settable(2, '.', 3);
	settable(1, '(', 13);
	settable(1, '=', 11);
	settable(11, '=', 12);
	settable(1, '>', 14);
	settable(14, '=', 15);
	settable(1, '<', 16);
	settable(16, '=', 17);
	settable(1, '!', 18);
	settable(18, '=', 19);

	ofstream outfile("automation.cpp");
	outfile << "int automation_table[][129] = { " << endl;
	for (int i = 1; i <= 20; i++)
	{
		outfile << "	{";
		for (int j = 1; j <= 128; j++)
		{
			outfile << table[i][j];
			if (j != 128)
			{
				outfile << ',';
			}
		}
		if (i != 20)
		{
			outfile << "}," << endl;
		}
		else
		{
			outfile << "}" << endl;
		}
	}
	outfile << "};" << endl;
}