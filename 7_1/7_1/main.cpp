#pragma warning(disable:4996)

#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
using namespace std;

struct edge
{
	int index;
	int power;
	edge(int i, int p) { index = i; power = p; }
};

vector<vector<edge>> graph;
vector<int> dis;
vector<int> point_to;

#define max(a,b) (a>b?a:b)
void get_data();
int get_dis(int index);
void output();

int main()
{
	get_data();
	for (int i = 0; i < (int)point_to.size(); i++)
	{
		if (point_to[i] == 0)
		{
			dis[i]=get_dis(i);
		}
	}
	output();
	return 0;
}

void get_data()
{
	int num = 0;
	cin >> num;
	graph.resize(num);
	dis.resize(num,-1);
	dis[0] = 0;
	point_to.resize(num,0);
	int src = 0;
	int dst = 0;
	int power = 0;
	//while (cin>>src>>dst>>power)
	while(scanf("%d %d %d",&src,&dst,&power)>0)
	{
		edge temp_edge(src, power);
		graph[dst].push_back(temp_edge);
		point_to[src]++;
	}
}

void output()
{
	cout << "I have read the rules about plagiarism punishment" << endl;
	for (int i = 1; i < (int)dis.size(); i++)
	{
		cout << dis[i] << " ";
	}
	cout <<endl;

}

int get_dis(int index)
{
	if (dis[index] > 0)
	{
		return dis[index];
	}
	for (int i = 0; i < (int)graph[index].size(); i++)
	{
		int new_dis = get_dis(graph[index][i].index) + graph[index][i].power;
		dis[index] = max(dis[index], new_dis);
	}
	return dis[index];
}
