#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
#define BIGNUM 2147483647

struct node
{
	int index;
	int length;
	bool operator < (node& x)
	{
		return this->length < x.length;
	}

	bool operator > (node& x)
	{
		return this->length > x.length;
	}
};

vector<vector<node>> graph;
vector<node> fringe;				//Fresh ==> Fringe ==> Finished		
vector<int> place;
vector<bool> is_in;
int src = 0, dst = 0, fringe_num = 0;

//input
void get_data();

//heap
void make_min_heap(vector<node>::iterator beg, vector<node>::iterator end);
void sift_down(int p, vector<node>::iterator beg, vector<node>::iterator end);
void pop_min_heap(vector<node>::iterator beg, vector<node>::iterator end);

int main()
{	
	//input and init
	get_data();
	fringe.resize(graph.size() - 1);
	int number = 0, fringe_ptr = 0;
	while (fringe_ptr < (int)graph.size() - 1)
	{
		if (number != src)
		{
			node temp_node;
			temp_node.index = number;
			temp_node.length = BIGNUM;
			fringe[fringe_ptr] = temp_node;
			place[number] = fringe_ptr;
			fringe_ptr++;
			
		}
		number++;
	}
	fringe_num = (int)graph.size() - 1;
	is_in[src] = false;
	for (int i = 0; i < fringe_num; i++)
	{
		for (int j = 0; j < (int)graph[src].size(); j++)
		{
			if (fringe[i].index == graph[src][j].index)
			{
				fringe[i].length = graph[src][j].length;
			}
		}
	}
	make_min_heap(fringe.begin(), fringe.begin() + fringe_num);
	
	//alg begin
	while (1)
	{
		if (fringe[0].index == dst)				//fringe[0] is min of heap
		{
			cout << "I have read the rules about plagiarism punishment" << endl;
			cout << fringe[0].length << endl;
			break;
		}

		int top = fringe[0].index;
		int top_length = fringe[0].length;
		is_in[top] = false;
		pop_min_heap(fringe.begin(), fringe.begin() + fringe_num);
		fringe_num--;

		for (int j = 0; j < (int)graph[top].size(); j++)
		{
			if (!is_in[graph[top][j].index])
			{
				continue;
			}
			int i = place[graph[top][j].index];
			int new_length = max(graph[top][j].length, top_length);
			fringe[i].length = min(fringe[i].length, new_length);
			//sift up
			node temp_node = fringe[i];
			while (i != 0 && temp_node.length < fringe[(i - 1) / 2].length)
			{
				fringe[i] = fringe[(i - 1) / 2];
				place[fringe[i].index] = i;
				i = (i - 1) / 2;
			}
			fringe[i] = temp_node;
			place[fringe[i].index] = i;
		}
	}
	return 0;
}
void get_data()
{
	int num = 0;
	
	cin >> num >> src >> dst;
	//scanf("%d %d %d", &num, &src, &dst);
	graph.resize(num);
	place.resize(num);
	is_in.resize(num, true);
	int city1 = 0, city2 = 0, length = 0;
	while (cin >> length >> city1 >> city2)
	//while(scanf("%d %d %d", &length, &city1, &city2)>0)
	{
		node temp_node;
		temp_node.length = length;
		temp_node.index = city1;
		graph[city2].push_back(temp_node);
		temp_node.index = city2;
		graph[city1].push_back(temp_node);
	}
}

void make_min_heap(vector<node>::iterator beg,vector<node>::iterator end)
{
	int p = ((int)(end-beg) - 2) / 2;
	while (p >= 0)
	{
		sift_down(p, beg, end);
		p--;
	}
}
void sift_down(int p, vector<node>::iterator beg, vector<node>::iterator end)
{
	node temp = *(beg+p);		//save root
	int size = end - beg;
	while (1)
	{
		//Step 1:get min child
		int min_child = ((2 * p + 2 < size) && (*(beg+2 * p + 1) > *(beg+2 * p + 2))) ?
			2 * p + 2 : 2 * p + 1;
		//Step 2:exchange if necessary
		if (min_child < size&&temp > *(beg+min_child))	//necessary
		{
			*(beg+p) = *(beg+min_child);
			place[(beg + p)->index] = p;
			p = min_child;
		}
		else											//unnecessary,so p is the place to save temp
		{
			break;
		}
	}

	*(beg + p) = temp;
	place[(beg + p)->index] = p;
}

void pop_min_heap(vector<node>::iterator beg, vector<node>::iterator end)
{
	node temp = *(end - 1);
	*(end - 1) = *beg;
	*beg = temp;
	place[beg->index] = 0;
	place[(end - 1)->index] = end - beg - 1;
	sift_down(0, beg, end - 1);
}