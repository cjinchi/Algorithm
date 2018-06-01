#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<string>
using namespace std;
class problem
{
private:
	vector<vector<short>> graph;
	vector<vector<short>> tgraph;
	vector<short> stack;
	vector<bool> visited;
	vector<vector<short>> scc;
	vector<short> vertex_to_scc;
	vector<short> scc_impact;
private:
	void first_round_dfs(short index);
	void second_round_dfs(short index);
	void get_t_graph();
	void get_one_scc_impact(short scc_index);
	short impact_dfs(short index);
public:
	problem();
	void get_data();
	void get_scc();
	void get_all_scc_impact();
	void output();
};

problem::problem()
{
}

void problem::get_data()
{
	string s_line = "";
	short temp = 0;
	while (getline(cin, s_line))
	{
		stringstream ss;
		ss.clear();
		ss << s_line;
		vector<short> v_line;
		while (!ss.eof())
		{
			ss >> temp;
			v_line.push_back(temp);
		}
		graph.push_back(v_line);
	}
	visited.resize(graph.size(), false);
}

void problem::get_t_graph()
{
	tgraph.resize(graph.size());
	for (short i = 0; i < (short)graph.size(); i++)
	{
		for (short j = 0; j < (short)graph[i].size(); j++)
		{
			short dest = graph[i][j];
			tgraph[dest].push_back(i);
		}
	}
}

void problem::get_scc()
{
	//first round dfs
	fill(visited.begin(), visited.end(),false);
	for (short i = 0; i < (short)graph.size(); i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			first_round_dfs(i);
			stack.push_back(i);
		}
	}

	//get t_graph
	get_t_graph();

	//second round dfs
	vertex_to_scc.resize(graph.size(),-1);
	fill(visited.begin(), visited.end(), false);
	while (stack.size() > 0)
	{
		short vertex_index = stack[stack.size() - 1];
		stack.pop_back();

		if (!visited[vertex_index])
		{
			visited[vertex_index] = true;

			vector<short> one_scc;
			one_scc.push_back(vertex_index);
			scc.push_back(one_scc);
			vertex_to_scc[vertex_index] = (short)(scc.size() - 1);

			second_round_dfs(vertex_index);
		}
	}


}


void problem::first_round_dfs(short index)
{
	for (short i = 0; i < (short)graph[index].size(); i++)
	{
		short nei_index = graph[index][i];
		if (!visited[nei_index])
		{
			visited[nei_index] = true;
			first_round_dfs(nei_index);
			stack.push_back(nei_index);
		}
	}
}

void problem::second_round_dfs(short index)
{
	for (short i = 0; i < (short)tgraph[index].size(); i++)
	{
		short nei_index = tgraph[index][i];
		if (!visited[nei_index])
		{
			visited[nei_index] = true;
			scc[scc.size() - 1].push_back(nei_index);
			vertex_to_scc[nei_index] = (short)(scc.size() - 1);
			second_round_dfs(nei_index);
		}
	}
}

void problem::get_all_scc_impact()
{
	scc_impact.resize(scc.size(), -1);
	for (short i = 0; i < (short)scc.size(); i++)
	{
		get_one_scc_impact(i);
	}
}
void problem::get_one_scc_impact(short scc_index)
{
	if (scc_impact[scc_index] >= 0)
	{
		return;
	}
	else
	{
		fill(visited.begin(), visited.end(), false);
		visited[scc[scc_index][0]] = true;
		scc_impact[scc_index]=impact_dfs(scc[scc_index][0])-1;
	}
}
short problem::impact_dfs(short index)
{
	short result = 1;//myself
	for (short i = 0; i < (short)graph[index].size(); i++)
	{
		short nei_index = graph[index][i];
		if (!visited[nei_index])
		{
			visited[nei_index] = true;
			if (vertex_to_scc[index] == vertex_to_scc[nei_index])
			{
				result += impact_dfs(nei_index);
			}
			else
			{
				get_one_scc_impact(vertex_to_scc[nei_index]);
				result += (scc_impact[vertex_to_scc[nei_index]] + 1);
			}
		}
	}
	return result;
}
void problem::output()
{
	cout << "I have read the rules about plagiarism punishment" << endl;
	short max_impact = 0, max_index = 0;
	for (short i = 0; i < (short)scc_impact.size(); i++)
	{
		if (scc_impact[i] > max_impact)
		{
			max_impact = scc_impact[i];
			max_index = i;
		}
	}
	cout << max_impact << endl;
	sort(scc[max_index].begin(), scc[max_index].end());
	for (short i = 0; i < (short)scc[max_index].size(); i++)
	{
		cout << scc[max_index][i] << " ";
	}
}
int main()
{
	problem x;
	x.get_data();
	x.get_scc();
	x.get_all_scc_impact();
	x.output();
	return 0;
}