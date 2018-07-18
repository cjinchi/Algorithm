#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<vector<int>> tree;
vector<int> dp;				//physics index, 0 is root
vector<int> map;			//from logic to physics, as I'm not sure whether input-data is ordered 

void get_data();
int get_dp(int index);

int main()
{
	//input and init
	get_data();
	map.resize(tree.size());
	for (int i = 0; i < (int)tree.size(); i++)
	{
		int node_id = tree[i][tree[i].size() - 1];
		tree[i].pop_back();
		map[node_id] = i;
	}
	dp.resize(tree.size(),-1);
	
	//dp
	for (int index = ((int)dp.size()) - 1; index>=0; index--)
	{
		dp[index] = get_dp(index);
	}
	
	//output
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << dp[0] << endl;
	return 0;
}

void get_data()
{
	string line = "";
	while (getline(cin, line))
	{
		stringstream x;
		x.clear();
		x << line;
		vector<int> node;
		int num,temp;
		x >> num;
		while (x >> temp)
		{
			node.push_back(temp);
		}
		node.push_back(num);
		tree.push_back(node);
	}
}

int get_dp(int index)
{
	if (dp[index] >= 0)
	{
		return dp[index];
	}
	//if is a leaf
	if (tree[index].size() == 0)
	{
		dp[index] = 0;
		return 0;
	}

	//case node.index inside MVC
	int ret1 = 1;
	for (int i = 0; i < (int)tree[index].size(); i++)
	{
		int child_index = map[tree[index][i]];
		ret1 += get_dp(child_index);
	}

	//case node.index outside MVC
	int ret2 = (int)tree[index].size();	   //num of its children
	for (int i = 0; i < (int)tree[index].size(); i++)
	{
		int child_index = map[tree[index][i]];
		//No error even when child is a leaf
		for (int j = 0; j < (int)tree[child_index].size(); j++)
		{
			int grandchild_index = map[tree[child_index][j]];
			ret2 += get_dp(grandchild_index);
		}
	}
	dp[index] = min(ret1, ret2);
	return dp[index];
}