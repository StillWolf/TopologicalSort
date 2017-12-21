// TopologicalSort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;
int tot, numberOfterm[10], head[1000], numberOfvertex;
bool visit[100];
int StrToInt(string s)
{
	int ans = 0;
	for (int i = 0; i < s.size(); i++)
		ans = ans * 10 + s[i] - 48;
	return ans;
}
struct edge
{
	int to, next;
}e[1000];
class vertex
{
public:
	int number, hours, term, degree;
	string name;
	vertex(string number,string hours,string term,string name)
	{
		string newnumber = "";
		for (int i = 1; i < number.size(); i++)
			newnumber += number[i];
		this->name = name;
		this->number = StrToInt(newnumber);
		this->hours = StrToInt(hours);
		this->term = StrToInt(term);
		this->degree = 0;
	}
	vertex(){}
	void IncDegree()
	{
		degree++;
	}
	void output()
	{
		cout << name << " " << number << " " << hours << " " << endl;
	}
};
vertex Nodes[100];
int index;
string nextString(string s)
{
	while (s[index] == ' ' || s[index] == '\t' && index < s.size())
		index++;
	if (s[index] == '\n' || index >= s.size())
		return "";
	string ans = "";
	while (s[index] != ' ' && s[index] != '\t' && index < s.size())
	{
		ans += s[index];
		index++;
	}
	return ans;
}
void addedge(int a, int b)
{
	tot++;
	Nodes[b].IncDegree();
	e[tot].to = b;
	e[tot].next = head[a];
	head[a] = tot;
}
void init()
{
	string Line="",FileName="E:/course_inf.txt";
	ifstream infoFile;
	infoFile.open(FileName.data(), ios::in);
	vector <string> info;
	char c = 1;
	while (c != EOF)
	{
		c = infoFile.get();
		if (c == '\n')
		{
			if (Line == "")
				continue;
			if (Line[0] == Line[1] && Line[0] == '/')
			{
				Line = "";
				continue;
			}
			info.push_back(Line);
			Line = "";
			continue;
		}
		Line += c;
	}
	int jl = 0;
	for (int i = 0; i < info[0].size(); i++)
	{
		if (info[0][i] < '0' || info[0][i] > '9')
			continue;
		int sum = 0;
		while (info[0][i] >= '0'&&info[0][i] <= '9'&&i < info[0].size())
		{
			sum = sum * 10 + info[0][i] - 48;
			i++;
		}
		numberOfterm[++jl] = sum;
		numberOfvertex += sum;
	}
	for (int i = 1; i <= numberOfvertex; i++)
	{
		index = 0;
		vector <string> Lineinfo;
		for (int j = 1; j <= 4; j++)
			Lineinfo.push_back(nextString(info[i]));
		vertex node(Lineinfo[0], Lineinfo[2], Lineinfo[3], Lineinfo[1]);
		Nodes[i] = node;
		while (index < info[i].size())
		{
			string From = nextString(info[i]), newFrom = "";
			if (From == "")
				break;
			for (int it = 1; it < From.size(); it++)
				newFrom += From[it];
			int from = StrToInt(newFrom);
			addedge(from, i);
		}
	}
	infoFile.close();
}
vector<int> ans[10];
int Remain()
{
	for (int i = 1; i <= numberOfvertex; i++) 
	{
		if (visit[i])
			continue;
		if (Nodes[i].degree != 0)
			continue;
		return i;
	}
	return 0;
}
void TopSort()
{
	for (int i = 1; i <= numberOfvertex; i++)
		if (Nodes[i].term != 0)
		{
			ans[Nodes[i].term].push_back(i);
			visit[i] = 1;
			numberOfterm[Nodes[i].term]--;
			continue;
		}
	int nowNode, nowTerm;
	for (int i = 1; i <= 8; i++)
		if (numberOfterm[i] > 0)
		{
			nowTerm = i;
			break;
		}
	while (Remain())
	{
		nowNode = Remain();
		visit[nowNode] = 1;
		ans[nowTerm].push_back(nowNode);
		for (int i = head[nowNode]; i; i = e[i].next)
			Nodes[e[i].to].degree--;
		numberOfterm[nowTerm]--;
		if (numberOfterm[nowTerm] == 0)
			nowTerm++;
		if (nowTerm > 8)
		{
			cout << "Wrong!" << endl;
			return;
		}
	}
	for (int i = 1; i <= 8; i++)
	{
		cout << "��" << i << "ѧ�ڣ�" << endl;
		for (int j = 0; j < ans[i].size(); j++)
		{
			cout << "\t";
			Nodes[ans[i][j]].output();
		}
	}
}
int main()
{
	init();
	TopSort();
	while (1);
    return 0;
}