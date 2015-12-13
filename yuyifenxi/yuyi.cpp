#include"header.h"
#include"lexical.h"

int compare_sign=0;
int t=0;
int quad_num = 0;
vector<token> token_list;
extern string KT[];
extern string PT[];

vector<quad> quad_list;

vector<ttable> t_list;

stack<token_all> sem_stack;

vector<tapel> tapel_list;

string tapel_type;

lexical lexical_analyzer;

void FactorA();
void DEF_TermA();
void DEF_TermB();
void DEF_TermC();
void Condition();
void Expression();
void GramaTerm();
void IF_TermA();
void IF_TermB();
void GramaTermB();
void GramaTermA();
void Assign();
token_all Create_stack_member(int kind, int num);
void Quat(string op);
void id_key_type();
void Quat_compare(int k);
void Quat_left(string op);
void Quat_else(string op);
string find_type(token_all tmp);

void read(){
    cout<<t<<endl;
    t++;

    }

void GramaTermA(){
     GramaTerm();
     GramaTermB();
}

void GramaTermB(){
    if(token_list[t].tablename=="IT"){
       GramaTermA();
     }
     else if(token_list[t].tablename=="KT" && ((token_list[t].num==10)  || (token_list[t].num==1) ||(token_list[t].num==7) )) {       // int char float
            GramaTermA();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==9) ){                // if
          GramaTermA();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==13)) {          //while
           GramaTermA();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==4)) {         //do
          GramaTermA();
     }
 }


void Term(){
     if(token_list[t].tablename=="PT" && (token_list[t].num==11)){  //{
        read();
        GramaTermA();
        if(token_list[t].tablename=="PT" && (token_list[t].num==12)){   //}
            read();
        }
        else
            cout<<"error:没有'}'！"<<endl;
     }
     else
     cout<<"error:没有'{'！"<<endl;
}

void DEF_TermC(){
     if(token_list[t].tablename=="PT" && (token_list[t].num==6)){  //=
        sem_stack.push(Create_stack_member(1, t-1));
        read();
        Expression();
        Assign();
     }
}

void DEF_TermB(){
     if(token_list[t].tablename=="IT"){
		 id_key_type();
        read();
        DEF_TermC();
     }
     else
        cout<<"error:标识符定义错误"<<endl;
}

void DEF_TermA(){
     DEF_TermB();
     loop3:
         if(token_list[t].tablename=="PT" && (token_list[t].num==7)){//,
            read();
            DEF_TermB();
            goto loop3;
         }
}

void DEF_Term(){
	if (token_list[t].tablename == "KT" && ((token_list[t].num == 10) || (token_list[t].num == 1) || (token_list[t].num == 7)))
	{
		tapel_type = KT[token_list[t].num];
		read();
		DEF_TermA();
		if (token_list[t].tablename == "PT" && (token_list[t].num == 8)){    //;
			read();
		}
		else
			cout << "error:没有;" << endl;
	}
}

void id_key_type()        //识别标识符类型填入符号总表
{
	lexical_analyzer.symbol_list[token_list[t].symbol_pointer].type = tapel_list.size();
	lexical_analyzer.symbol_list[token_list[t].symbol_pointer].category = "v";
	tapel tmp;
	tmp.tval = tapel_type;
	tmp.tpoint = 0;
	tapel_list.push_back(tmp);
}

void EVA_Term(){
    if(token_list[t].tablename=="IT"){
		sem_stack.push(Create_stack_member(1, t));
		read();
    if(token_list[t].tablename=="PT" && (token_list[t].num==6)) {    //=
        read();
        Expression();
		Assign();
        if(token_list[t].tablename=="PT" && (token_list[t].num==8)){  //;
            read();
        }
        else
            cout<<"error:没有';'!"<<endl;
    }
    else
        cout<<"error:赋值语句错误"<<endl;
}
}

void Assign()	//"="四元式
{
	quad tmp;
	tmp.op = "=";
	tmp.arg1 = sem_stack.top();
	tmp.arg2 = Create_stack_member(0,0);
	sem_stack.pop();
	tmp.result = sem_stack.top();
	sem_stack.pop();
	quad_num++;
	quad_list.push_back(tmp);
}

string find_type(token_all tmp)		//寻找类型

{
    if(token_list[tmp.num].tablename=="IT")
    {
        if(lexical_analyzer.symbol_list[token_list[tmp.num].symbol_pointer].type == -1)
    {
        cout<<"error: 变量"<<lexical_analyzer.IT[token_list[tmp.num].num]<<"未定义！";
        exit(0);
    }
	else return tapel_list[lexical_analyzer.symbol_list[token_list[tmp.num].symbol_pointer].type].tval;
    }
    else return "float";

}

void Quat(string op)
{
	ttable ttmp;
	token t_type;
	symbol stmp;

	char a[100];
	sprintf(a, "%d", t_list.size());
	string s = a;
	ttmp.name = "#t"+s;
	ttmp.num = quad_num;					//临时变量表的临时变量名以及临时变量所指向四元式下标

	t_type.tablename = "TT";
	t_type.num = t_list.size();
	t_type.symbol_pointer = lexical_analyzer.symbol_list.size();//临时变量token生成

	stmp.name = t_type;        //临时变量的符号表生成

	t_list.push_back(ttmp);

	quad tmp;
	tmp.op = op;
	tmp.arg2 = sem_stack.top();
	sem_stack.pop();
	tmp.arg1 = sem_stack.top();
	sem_stack.pop();

	string type1 = find_type(tmp.arg1);//判断临时变量类型开始
	string type2 = find_type(tmp.arg2);

	stmp.type = tapel_list.size();
	stmp.category = "vt";
	if (type1 == "int"&&type2 == "int")
	{
		tapel tmp;
		tmp.tval = "int";
		tmp.tpoint = 0;
		tapel_list.push_back(tmp);

	}
	else
	{
		tapel tmp;
		tmp.tval = "float";
		tmp.tpoint = 0;
		tapel_list.push_back(tmp);
	}

	lexical_analyzer.symbol_list.push_back(stmp);//临时变量符号表添加

	tmp.result = Create_stack_member(2, t_list.size()-1);
	quad_num++;
	quad_list.push_back(tmp);
	sem_stack.push(tmp.result);


}

void Factor(){
     if(token_list[t].tablename=="IT"){
		 sem_stack.push(Create_stack_member(1, t));
        read();
     }
     else if(token_list[t].tablename=="CT"){
		 sem_stack.push(Create_stack_member(1, t));
        read();
     }
     else if(token_list[t].tablename=="CHT"){   //'
		 sem_stack.push(Create_stack_member(1, t));
        read();
     }
     else if(token_list[t].tablename=="PT" && (token_list[t].num==13)){   //(
          read();
          Expression();
          if(token_list[t].tablename=="PT" && (token_list[t].num==14)){   //)
            read();
          }
          else
            cout<<"error:没有')'"<<endl;
     }
     else
        cout<<"error:表达式错误"<<endl;
}

void Iterm(){
    Factor();
    loop1:
        if(token_list[t].tablename=="PT" &&( (token_list[t].num==2)||(token_list[t].num==3 ))){   //* /
			string op;
			if (token_list[t].num == 2)
				op = "*";
			else op = "/";
            read();
            Factor();
			Quat(op);
            goto loop1;
        }
}

void Expression(){
    Iterm();
    loop2:
        if(token_list[t].tablename=="PT" && ( (token_list[t].num==0)||(token_list[t].num==1 ))){   //+ -
			string op;
			if (token_list[t].num == 0)
				op = "+";
			else op = "-";
            read();
            Iterm();
			Quat(op);
            goto loop2;
             }
}

void IF_Term(){
    if(token_list[t].tablename=="KT" && (token_list[t].num==9) ){//if
            read();
     if(token_list[t].tablename=="PT" && (token_list[t].num==13)){       //(
       read();
       Condition();
       if(token_list[t].tablename=="PT" && (token_list[t].num==14)){    //)
        Quat_left("if");
        read();
        Term();
        IF_TermA();
        Quat_else("if_end");
       }
       else
        cout<<"error: if()"<<endl;
     }
     else
        cout<<"error: if()"<<endl;
        }

}

void Quat_left(string op)
{
	quad tmp;
	tmp.op = op;
    tmp.arg1 = sem_stack.top();
    sem_stack.pop();
    tmp.arg2= Create_stack_member(0,0);
    tmp.result = Create_stack_member(0,0);
    quad_num++;
    quad_list.push_back(tmp);
}


void IF_TermA(){

      if((token_list[t].tablename=="KT") && (token_list[t].num==6)){  //else
        Quat_else("else");
        read();
        IF_TermB();
      }
}

void Quat_else(string op)
{
	quad tmp;
	tmp.op = op;
    tmp.arg1 = Create_stack_member(0,0);
    tmp.arg2= Create_stack_member(0,0);
    tmp.result = Create_stack_member(0,0);
    quad_num++;
    quad_list.push_back(tmp);
}

void IF_TermB(){
      if(token_list[t].tablename=="KT" && (token_list[t].num==9)){ //if


          IF_Term();
      }
      else if(token_list[t].tablename=="PT" && (token_list[t].num==11)){//{

          Term();
      }
      else
        cout<<"error:if语句错误"<<endl;
}

void Condition(){
     if((token_list[t].tablename=="IT")||(token_list[t].tablename=="CT")||(token_list[t].tablename=="CHT")||(token_list[t].tablename=="PT" && (token_list[t].num==13))){
        Factor();
        FactorA();
     }
     else
        cout<<"error:条件错误"<<endl;
}

void FactorA(){
    if(token_list[t].tablename=="PT" && ((token_list[t].num==4) || (token_list[t].num==5)||(token_list[t].num==18) ||(token_list[t].num==19) ||(token_list[t].num==20) ||(token_list[t].num==21))){
        int i=t;
        read();
        Factor();
        Quat_compare(token_list[i].num);
     }
     else
        Quat_compare(0);
}
void Quat_compare(int k)
{
	tapel typetmp;
	ttable ttmp;
	token t_type;
	symbol stmp;
	char a[100];
	sprintf(a, "%d", t_list.size());
	string s = a;
	ttmp.name = "#t"+s;
	ttmp.num = quad_num;					//临时变量表的临时变量名以及临时变量所指向四元式下标

	t_type.tablename = "TT";
	t_type.num = t_list.size();
	t_type.symbol_pointer = lexical_analyzer.symbol_list.size();//为临时变量建立一个nametoken
	stmp.name = t_type;        //临时变量的符号表生成
	stmp.type = tapel_list.size();
	stmp.category = "vt";
	t_list.push_back(ttmp);    //临时变量表添加
	typetmp.tval = "int";
    typetmp.tpoint = 0;         //临时变量种类添加
    tapel_list.push_back(typetmp);
	lexical_analyzer.symbol_list.push_back(stmp);//临时变量符号表添加

    quad tmp;
	if(k!=0)
    {
        tmp.op = PT[k];
        tmp.arg2 = sem_stack.top();
        sem_stack.pop();
        tmp.arg1 = sem_stack.top();
        sem_stack.pop();
        tmp.result = Create_stack_member(2, t_list.size()-1);
        quad_num++;
        quad_list.push_back(tmp);
        sem_stack.push(tmp.result);
    }
	else if(k==0)
    {
        tmp.op = "_";
        tmp.arg1 = sem_stack.top();
        sem_stack.pop();
        tmp.arg2 = Create_stack_member(0,0);
        tmp.result = Create_stack_member(2, t_list.size()-1);
        quad_num++;
        quad_list.push_back(tmp);
        sem_stack.push(tmp.result);
    }
}


void WHILE_Term(){
      Quat_else("while");
     if(token_list[t].tablename=="PT" && (token_list[t].num==13)){   //(
        read();
        Condition();
        if(token_list[t].tablename=="PT" && (token_list[t].num==14)){  //)
          Quat_left("do");
          read();
          Term();
          Quat_else("whilend");
        }
        else
            cout<<"error:没有')'"<<endl;
     }
     else
        cout<<"error:没有'('"<<endl;
}

void DW_Term(){
     Term();
     if(token_list[t].tablename=="KT" && (token_list[t].num==13)){
        Quat_else("do");
        read();
        if(token_list[t].tablename=="PT" && (token_list[t].num==13)){   //(
            read();
            Condition();
            if(token_list[t].tablename=="PT" && (token_list[t].num==14)){  //)
                Quat_left("dowhile");
                read();
                }
            else
            cout<<"error:没有')'"<<endl;
     }
     else
        cout<<"error:没有'('"<<endl;
     }
     else
        cout<<"error:do while"<<endl;
}

void GramaTerm(){
     if(token_list[t].tablename=="IT"){

        EVA_Term();
     }
     else if(token_list[t].tablename=="KT" && ((token_list[t].num==10)  || (token_list[t].num==1) ||(token_list[t].num==7) )) {       // int char float

           DEF_Term();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==9) ){                // if

          IF_Term();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==13)) {          //while
          read();
          WHILE_Term();
     }
     else if(token_list[t].tablename=="KT" && (token_list[t].num==4)) {         //do
         read();
         DW_Term();
     }
     else
        cout<<"error:不知道写的啥！"<<endl;
        system("pause");
 }

token_all Create_stack_member(int kind, int num)
{
	token_all tmp(kind,num);
	return tmp;
}

string print_token_all(token_all tmp)
{
	if (tmp.kind == 1)
	{
		if (token_list[tmp.num].tablename == "CT")
			return lexical_analyzer.CT[token_list[tmp.num].num];
		else
			return lexical_analyzer.IT[token_list[tmp.num].num];

	}
	else if (tmp.kind == 2)
	{
		char a[100];
		sprintf(a, "%d", tmp.num);
		string s = a;
		return "#t"+s;
	}
	else
	{
		return "_";
	}
}



int main(){
    int i = 0;
	lexical_analyzer.openfile("a.txt");
	token_list = lexical_analyzer.gettoken();
	for (auto str : token_list)
	{
		cout << str.tablename << " " << str.num << endl;
	}
    token temp;
    temp.num=0;
    temp.tablename=" ";
    token_list.push_back(temp);
    while(t!=((int)token_list.size()-1)){
     GramaTerm();
     }
   if(t==((int)token_list.size()-1)){
    cout<<"编译通过"<<endl;
   }
   for (auto tmp : quad_list)
   {
	   cout << "(" << tmp.op << "," << print_token_all(tmp.arg1) << "," << print_token_all(tmp.arg2) << "," << print_token_all(tmp.result) << ")" << endl;
   }
   i = 0;
   for (auto tmp : lexical_analyzer.symbol_list)
   {
	   if (tmp.category == "v")
	   cout << lexical_analyzer.IT[tmp.name.num] << " " << tmp.type << " " << tmp.category <<" "<< tapel_list[i].tval<<endl;
	   else if(tmp.category == "vt")
		cout << t_list[tmp.name.num].name << " " << tmp.type << " " << tmp.category << " "<< tapel_list[i].tval<<endl;
        i++;
   }
  /* for (auto tmp : tapel_list)
   {
	   cout << tmp.tval << endl;
   }*/
}
