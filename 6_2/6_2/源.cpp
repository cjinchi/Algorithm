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
	vector<bool> impact_visited;
	vector<short> impact;
	short max_impact;
	vector<short> max_impact_indexs;
private:
	void first_round_dfs(short index);
	void get_t_graph();
	short impact_dfs(short index);
	void tag_visited_dfs(short vertex_index, bool add_to_maximpact);
public:
	problem();
	void get_data();
	void get_scc();
	void output();
};

problem::problem()
{
	max_impact = 0;
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
		while (ss >> temp)
		{
			v_line.push_back(temp);
		}
		graph.push_back(v_line);
	}
	visited.resize(graph.size(), false);
	impact_visited.resize(graph.size(), false);
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
	fill(visited.begin(), visited.end(), false);
	while (stack.size() > 0)
	{
		short vertex_index = stack[stack.size() - 1];
		stack.pop_back();

		if (!visited[vertex_index])
		{
			fill(impact_visited.begin(), impact_visited.end(), false);
			impact_visited[vertex_index] = true;
			short temp_impact = impact_dfs(vertex_index)-1;
			
			if (temp_impact > max_impact)
			{
				max_impact_indexs.clear();
				max_impact = temp_impact;
				tag_visited_dfs(vertex_index,true);
			}
			else if (temp_impact==max_impact)
			{
				tag_visited_dfs(vertex_index,true);
			}
			else
			{
				tag_visited_dfs(vertex_index, false);
			}
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
short problem::impact_dfs(short index)
{
	short result = 1;//myself
	for (short i = 0; i < (short)graph[index].size(); i++)
	{
		short nei_index = graph[index][i];
		if (!impact_visited[nei_index])
		{
			impact_visited[nei_index] = true;
			result += impact_dfs(nei_index);
		}
	}
	return result;
}
void problem::output()
{
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << max_impact << endl;
	sort(max_impact_indexs.begin(), max_impact_indexs.end());
	for (int i = 0; i < (int)max_impact_indexs.size(); i++)
	{
		cout << max_impact_indexs[i] << " ";
	}
}

void problem::tag_visited_dfs(short vertex_index, bool add_to_maximpact)
{
	visited[vertex_index] = true;
	if (add_to_maximpact)
	{
		max_impact_indexs.push_back(vertex_index);
	}
	for (short i = 0; i < (short)tgraph[vertex_index].size(); i++)
	{
		short nei_index = tgraph[vertex_index][i];
		if (!visited[nei_index])
		{
			tag_visited_dfs(nei_index,add_to_maximpact);
		}
	}
}
int main()
{
	problem x;
	x.get_data();
	x.get_scc();
	x.output();
	return 0;
}