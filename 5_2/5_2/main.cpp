#include<iostream>
using namespace std;
struct node
{
	int n;
	node* next;
	node(int nn)
	{
		n = nn;
		next = NULL;
	}
};
void get_input(int &num_event, int *&cost, node **&rely, bool *&is_relied);
int calculate(int index,int num_event,int *cost,node **rely, int *earliest);
void remove(node *head);
int main()
{
	cout << "I have read the rules about plagiarism punishment" << endl;
	
	//num of events
	int num_event = 0;
	//cost of each event
	int *cost = NULL;
	//rely[i] is a list to save index of events that event[i] relied on
	node **rely = NULL;
	//is_relied[i]==false if event[i] doesn't be relied by anyone
	bool *is_relied = NULL;
	get_input(num_event, cost, rely, is_relied);

	//the earliest time that the event can start
	int *earliest = new int[num_event];
	for (int i = 0; i < num_event; i++)
	{
		earliest[i] = -1;
	}

	for (int i = 0; i < num_event; i++)
	{
		if (is_relied[i] == false)
		{
			earliest[i] = calculate(i,num_event,cost,rely,earliest);
		}
	}

	int max = 0;
	for (int i = 0; i < num_event; i++)
	{
		int temp = earliest[i] + cost[i];
		max = (max > temp ? max : temp);
	}
	cout << max << endl;
	delete[]cost;
	delete[]is_relied;
	for (int i = 0; i < num_event; i++)
	{
		remove(rely[i]);
	}
	delete[]rely;
	return 0;

}

void get_input(int &num_event, int *&cost, node **&rely, bool *&is_relied)
{
	cin >> num_event;
	cost = new int[num_event] {};
	rely = new node*[num_event]{};
	is_relied = new bool[num_event] {};

	int index_of_event = 0;
	for (int i = 0; i < num_event; i++)
	{
		cin >> index_of_event;

		//different begin of index,0 or 1
		index_of_event--;

		cin >> cost[index_of_event];
	}
	int to_rely = 0, be_relied = 0;
	//for(int i=0;i<12;i++)
	while (cin >> to_rely >> be_relied)
	{
		//cin >> to_rely >> be_relied;
		//different begin of index,0 or 1
		to_rely--;
		be_relied--;

		is_relied[be_relied] = true;
		node *p = new node(be_relied);
		if (rely[to_rely] == NULL)
		{
			rely[to_rely] = p;
		}
		else
		{
			node *head = rely[to_rely];
			while (head->next != NULL)
			{
				head = head->next;
			}
			head->next = p;
		}
	}
}

int calculate(int index, int num_event, int *cost, node **rely, int *earliest)
{
	//had got
	if (earliest[index] >= 0)
		return earliest[index];

	//condition rely[index]==NULL is considered
	int max = 0;
	node *head = rely[index];
	while (head != NULL)
	{
		int temp = calculate(head->n, num_event, cost, rely, earliest) + cost[head->n];
		if (temp > max)
		{
			max = temp;
		}
		head = head->next;
	}
	earliest[index] = max;
	return earliest[index];
}

void remove(node *head)
{
	node *temp = head;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}