// calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<string>
#include <iostream>
#include"stack.h"
#define pi 3.14159265 
#define exp 2.718281
using namespace std;

int check_for_correct_input(string str, bool check_for_bracekts)
{
	check_for_bracekts = 1;
	int posL, posR;
	string str_check_for_brackets = str;
	string Lbracket = "(";
	string Rbracket = ")";
	while (check_for_bracekts)
	{
		posL = str_check_for_brackets.find(Lbracket);
		posR = str_check_for_brackets.find(Rbracket);
		if ((posL != -1) && (posR != -1) && (posL < posR))
		{
			str_check_for_brackets.erase(posL, 1);
			check_for_bracekts = 1;
			str_check_for_brackets.erase(posR - 1, 1);
		}
		else
			check_for_bracekts = 0;
	}

	if (posL == posR) { check_for_bracekts = 1; }
	return check_for_bracekts;
};
int stack_brackets_check(string str, bool check)
{
	Stack<char> stck;
	for (int i = 0; i < str.length(); i++) 
	{
		if (str[i] == '(') { stck.push(str[i]); } 
		if (str[i] == ')') { stck.pop(); }
	}
	if (stck.empty() == 0) { check = 1; }
	return check;
};
void transform_inf_to_stack(Stack<string> *stck, string str)
{
	stck->push(")");
	string tmp_str;
	int pos,j;
	for (int i = 0; i < str.length(); i++)
	{
	if (str[i] == '(') { stck->push(")");}else
	if (str[i] == ')') { stck->push("(");}else
	//sqrt,sgn,sin,cos,log,ln,tg,ctg
	if (str[i] == 's'&& str[i + 1] == 'q') 
	{pos = str.find(")", i); tmp_str.assign(str, i, pos - i+1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//sqrt
	else
	if (str[i] == 's'&& str[i + 1] == 'g') 
	{ pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//sgn
	else
	if (str[i] == 's'&& str[i + 1] == 'g')	
	{pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//sgn
	else
	if (str[i] == 's'&& str[i + 1] == 'i')
	{pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//sin
	else
	if (str[i] == 'c'&& str[i + 1] == 'o')
	{		pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;}//cos
	else
	if (str[i] == 't'&& str[i + 1] == 'g')
	{		pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;}//tg
	else
	if (str[i] == 'c'&& str[i + 1] == 't')
	{pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//ctg
	else
	if (str[i] == 'l'&& str[i + 1] == 'o')
	{pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0"; i = pos;		}//log
	else
	if (str[i] == 'l'&& str[i + 1] == 'n')
	{pos = str.find(")", i); tmp_str.assign(str, i, pos -i +1); stck->push(tmp_str); tmp_str = "\0";	i = pos;	}//ln
	else
																													 //double
	if (str[i] >= 48 && str[i] <= 57) 
	{
		j = i; while (str[i] == 46 || (str[i] >= 48 && str[i] <= 57)){i++;} 
		tmp_str.assign(str, j, i - j); stck->push(tmp_str); tmp_str = "\0"; i--;
	}
	else
	// + * - / ^ 
	if (str[i] == '+') { stck->push("+"); }
	else
	if (str[i] == '*') { stck->push("*"); }
	else
	if (str[i] == '-') { stck->push("-"); }
	else
	if (str[i] == '/') { stck->push("/"); }
	else
	if (str[i] == '^') { stck->push("^"); }
	else
	//pi and exp
	if (str[i] == 'p'&&str[i] == 'i') { stck->push("pi"); i++; 		}
	else
	if (str[i] == 'e'&&str[i] == 'p') { stck->push("exp"); i += 2; 	}

	}

	stck->push("(");
};
int priority(string c)
{	
	if (c == "^")					{		return 3;	}
	else if (c == "*" || c == "/")	{		return 2;	}
	else if (c == "+" || c == "-")	{		return 1;	}
	else							{		return 0;	}
}
void prefix_notation_isnt_my_oreintation(Stack<string> *prefix, Stack<string> str)
{
	/*
	stack string| stack operators |stack prefix
	*/
	Stack<string> operators;
	string tmp;
	while (!str.empty())
	{
		tmp = str.top();
		
			if (tmp == "(") { operators.push(tmp); str.pop(); }
			if (tmp == ")") { while (tmp != "(") { tmp = operators.top(); if (tmp != "(") { prefix->push(tmp); }operators.pop(); } }
//			if (tmp == "*" || tmp == "+" || tmp == "-" || tmp == "/" || tmp == "^")
			if (tmp == "*") { if (priority(tmp) <= priority(operators.top()))  {/*} if (operators.top == "*" || operators.top == "/" || operators.top == "^") {  */prefix->push(operators.top()); operators.pop();} }
			if (tmp == "+") { if (priority(tmp) <= priority(operators.top())) {/*} if (operators.top == "*" || operators.top == "/" || operators.top == "^") {  */prefix->push(operators.top()); operators.pop(); } }
			if (tmp == "-") { if (priority(tmp) <= priority(operators.top())) {/*} if (operators.top == "*" || operators.top == "/" || operators.top == "^") {  */prefix->push(operators.top()); operators.pop(); } }
			if (tmp == "/") { if (priority(tmp) <= priority(operators.top())) {/*} if (operators.top == "*" || operators.top == "/" || operators.top == "^") {  */prefix->push(operators.top()); operators.pop(); } }
			if (tmp == "^") { if (priority(tmp) <= priority(operators.top())) {/*} if (operators.top == "*" || operators.top == "/" || operators.top == "^") {  */prefix->push(operators.top()); operators.pop(); } }
			if (tmp != "*" && tmp != "+" && tmp != "-" && tmp != "/" && tmp != "^" && tmp != "(" && tmp != ")")
			{prefix->push(tmp); str.pop();}
	}
};
/*
1) Create empty stack for saving operators
2)check calculation from right to left
if token is operant- add him to the ioutput list
if token is left bracket take out from stack all symbols to right bracket and add them to the output list
if token is operator- delete all operators from stack ( while will see operator with lower proirity)
and add them to the output list if only operators proirity on top of stack >= prority of current operator(token)
then add token in stack 
otherway add token in stack firstly 
3) if after searching all elements some operators left in stack-> add to output 

*/
int main()
{
	Stack<string> prefix_stack;
	Stack<string> from_str;
	string str = "((2.2+1.1*4.4*1.0)*5.5)/6.6+(cos(0.123891298)*2.0+sin(0.0))^2.0+sgn(-5.0)+log(exp)+log(1.0)";
	bool check_for_bracekts = 0;
	cout << "our txt is :" << str << endl;

	check_for_bracekts = check_for_correct_input(str, check_for_bracekts);
	cout << "check=" << check_for_bracekts<<endl;
	
	check_for_bracekts = stack_brackets_check(str, check_for_bracekts);
	cout << "check=" << check_for_bracekts<<endl;


	//prefix_isnt_my_oreintation()
	transform_inf_to_stack(&from_str, str);
	while (!from_str.empty()) { cout << from_str.top(); from_str.pop(); }
	prefix_notation_isnt_my_oreintation(&prefix_stack, from_str);
	while (!prefix_stack.empty()) { cout << prefix_stack.top(); prefix_stack.pop(); }
}
