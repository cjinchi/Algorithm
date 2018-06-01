#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
using namespace std;
class bigraph
{
private:
	vector<vector<short>> graph;
	vector<short> zero_side;
	vector<bool> visited;
private:
	void get_data();
	void output();
	void bfs(short index, int depth);
public:
	void start();
};
int main()
{
	bigraph problem;
	problem.start();
	return 0;
}
void bigraph::start()
{
	get_data();
	visited[0] = true;
	bfs(0, 0);
	output();
}
void bigraph::get_data()
{
	string line="";
	//for(int xxx=0;xxx<5;xxx++)
	while (getline(cin, line))
	{
		//getline(cin, line);
		stringstream xs;
		xs.clear();
		vector<short> aline;
		xs << line;
		short temp;
		xs >> temp;
		while (!xs.eof())
		{
			xs >> temp;
			aline.push_back(temp);
		}
		//the last one will be pushed twice, so pop to fix it
		aline.pop_back();
		graph.push_back(aline);
	}

	visited.resize(graph.size(), false);
}
void bigraph::output()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	sort(zero_side.begin(), zero_side.end());
	int len_result = (int)(zero_side.size());
	for (int i = 0; i < len_result; i++)
	{
		cout << zero_side[i] << endl;
	}
}
void bigraph::bfs(short index, int depth)
{
	if (depth % 2 == 0)
	{
		zero_side.push_back(index);
	}
	int nei_num = (int)(graph[index].size());
	for (int i = 0; i < nei_num; i++)
	{
		if (visited[graph[index][i]])
		{
			continue;
		}
		else
		{
			visited[graph[index][i]] = true;
			bfs(graph[index][i], depth + 1);
		}
	}
}