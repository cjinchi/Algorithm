#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct line
{
	short a;
	short b;
	void set(short aa, short bb)
	{
		if (aa < bb)
		{
			a = aa;
			b = bb;
		}
		else
		{
			a = bb;
			b = aa;
		}
	}
	bool operator < (const line &m)const
	{
		if (a < m.a || (a == m.a&&b < m.b))
			return true;
		else
			return false;
	}
};
enum color_t { WHITE, GRAY,BLACK };

#define DFS_BEGIN 0
#define MAX_NUM_OF_INT 2147483647

short num_vertex = 0;		
vector<vector<short>> nei;
vector<color_t> color;
vector<bool> is_cp;
vector<short> depth;
vector<line> bridge;

void get_data();
int dfs(short index,bool &is_bridge);
#define min(a,b) (a<b?a:b)

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	
	get_data();

	//DFS begin here
	int child_of_root = 0;
	color[DFS_BEGIN] = GRAY;
	depth[DFS_BEGIN] = 0;
	int num_of_nei = nei[DFS_BEGIN].size();
	for(int i=0;i<num_of_nei;i++)
	{
		short nei_index = nei[DFS_BEGIN][i];
		if (color[nei_index] == WHITE)
		{
			child_of_root++;
			color[nei_index] = GRAY;
			depth[nei_index] = depth[DFS_BEGIN] + 1;
			bool is_bridge = true;
			dfs(nei_index, is_bridge);
			if (is_bridge)
			{
				line bridge_line;
				bridge_line.set(DFS_BEGIN, nei_index);
				bridge.push_back(bridge_line);
			}
			color[nei_index] = BLACK;
		}
	}
	color[DFS_BEGIN] = BLACK;
	//judge whether root is cut point or not
	if (child_of_root <= 1)
	{
		is_cp[DFS_BEGIN] = false;
	}
	else
	{
		is_cp[DFS_BEGIN] = true;
	}
	//sort bridge
	sort(bridge.begin(), bridge.end());
	
	//output begin here
	for (int i = 0; i < num_vertex; i++)
	{
		if (is_cp[i])
			cout << i << endl;
	}
	
	int num_of_bridge = bridge.size();
	for (int i = 0; i < num_of_bridge; i++)
	{
		cout << bridge[i].a << " " << bridge[i].b << endl;
	}
	return 0;
}

void get_data()
{
	cin >> num_vertex;
	nei.resize(num_vertex);
	color.resize(num_vertex,WHITE);
	is_cp.resize(num_vertex,false);
	depth.resize(num_vertex,0);

	int a = 0, b = 0;
	
	while (cin >> a >> b)
	{
		nei[a].push_back(b);
		nei[b].push_back(a);
	}
}

int dfs(short index,bool &is_bridge)
{
	is_bridge = true;
	int num_of_nei = nei[index].size();
	//the smallest index of point[index]'s neighbor
	int self_smallest_gray = MAX_NUM_OF_INT;
	//the smallest index of point[index]'s chilidren's neighbor
	int child_smallest_gray = MAX_NUM_OF_INT;

	//for all neighbors
	for(int i=0;i<num_of_nei;i++)
	{
		short nei_index = nei[index][i];
		if (color[nei_index] == WHITE)
		{
			color[nei_index] = GRAY;
			depth[nei_index] = depth[index] + 1;
			int ret = 0;
			bool is_bridge2 = true;
			ret = dfs(nei_index,is_bridge2);
			
			if (is_bridge2)	//judge whether line(index,nei_index) is bridge
			{
				line line_bridge;
				line_bridge.set(index, nei_index);
				bridge.push_back(line_bridge);
			}
			if (ret < child_smallest_gray)
			{
				child_smallest_gray = ret;
			}
			if (ret >= depth[index])
			{
				is_cp[index] = true;
			}
			if (ret < depth[index])	//judge whether line(index,index's dad) is bridge
			{
				is_bridge = false;
			}
			color[nei_index] = BLACK;
		}
		else
		{
			if (color[nei_index] == GRAY && depth[nei_index] < self_smallest_gray)
			{
				self_smallest_gray = depth[nei_index];
				if (depth[nei_index] < depth[index] - 1)
				{
					is_bridge = false;
				}
			}
		}
	}
	return min(self_smallest_gray, child_smallest_gray);
}