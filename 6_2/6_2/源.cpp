#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
using namespace std;
class problem
{
private:
	vector<vector<int>> graph;
	vector<bool> visited;
	vector<int> max_impact_index;
	int max_impact;
private:
	void get_data();
	void output();
	void dfs_begin();
	int dfs(int index);
public:
	problem();
	void start();
};

int main()
{
	problem x;
	x.start();
	return 0;
}

problem::problem()
{
	max_impact = 0;
}

void problem::get_data()
{
	string s_line = "";
	int temp = 0;
	while (getline(cin, s_line))
	{
		stringstream ss;
		ss.clear();
		ss << s_line;
		vector<int> v_line;
		while (!ss.eof())
		{
			ss >> temp;
			v_line.push_back(temp);
		}
		graph.push_back(v_line);
	}
	visited.resize(graph.size(), false);
}

void problem::start()
{
	get_data(); 
	dfs_begin();
	output();
}

void problem::output()
{
	sort(max_impact_index.begin(), max_impact_index.end());
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << max_impact << endl;
	for (int i = 0; i < (int)max_impact_index.size(); i++)
	{
		cout << max_impact_index[i] << " ";
	}
}
void problem::dfs_begin()
{
	for (int i = 0; i < (int)graph.size(); i++)
	{
		fill(visited.begin(), visited.end(), false);
		visited[i] = true;
		int impact = dfs(i)-1;        //delete myself
		if (max_impact_index.size() == 0)
		{
			max_impact_index.push_back(i);
			max_impact = impact;
		}
		else if (impact == max_impact)
		{
			max_impact_index.push_back(i);
		}
		else if (impact > max_impact)
		{
			max_impact_index.clear();
			max_impact_index.push_back(i);
			max_impact = impact;
		}
	}
}

int problem::dfs(int index)
{
	int result = 1;//myself
	for (int i = 0; i < (int)graph[index].size(); i++)
	{
		int nei_index = graph[index][i];
		if (!visited[nei_index])
		{
			visited[nei_index] = true;
			result += dfs(nei_index);
		}
	}
	return result;
}