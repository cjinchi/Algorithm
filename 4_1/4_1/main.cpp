#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
//sort sp by moving its index in arr
void sort_string_arr(string sp[], int arr[], int left, int right);
//sort char in str
void sort_string(string &str);

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;

	int n = 0;
	cin >> n;
	string *p = new string[n];		//init arr
	string *sp = new string[n];		//sorted arr
	int *arr = new int[n];			//save index

	//input and init
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
		sp[i] = p[i];
		sort_string(sp[i]);
	}
	for (int i = 0; i < n; i++)
		arr[i] = i;
	sort_string_arr(sp, arr, 0, n - 1);

	//find
	vector<string> result;
	result.clear();
	for (int i = 0; i < n - 1;)
	{
		if (sp[arr[i]] == sp[arr[i + 1]])  //find a pair
		{
			if (p[arr[i]] < p[arr[i + 1]])
				result.push_back(p[arr[i]]);
			else
				result.push_back(p[arr[i + 1]]);
			int current = arr[i];
			i += 2;

			while (i < n && sp[current] == sp[arr[i]])
			{
				if (p[arr[i]] < result[result.size() - 1])
					result[result.size() - 1] = p[arr[i]];
				i++;
			}
		}
		else
			i++;
	}
	sort(result.begin(), result.end());

	//output
	cout << result.size() << endl;
	for (unsigned int i = 0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}
	delete[]p;
	delete[]sp;
	delete[]arr;
	return 0;
}

void sort_string_arr(string sp[],int arr[],int left,int right)
{
	if (left >= right)
	{
		return;
	}

	int index = left + 1;
	for (int i = left + 1; i <= right; i++)
	{
		if (sp[arr[i]] < sp[arr[left]])
		{
			if (i != index)
			{
				int temp = arr[i];
				arr[i] = arr[index];
				arr[index] = temp;
			}
			index++;
		}
	}

	if (index - 1 != left)
	{
		int temp = arr[left];
		arr[left] = arr[index - 1];
		arr[index - 1] = temp;
	}

	sort_string_arr(sp, arr, left, index - 2);
	sort_string_arr(sp, arr, index, right);
}

void sort_string(string &str)
{
	int len = str.length();
	for (int i = 0; i < len - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (str[j] < str[min])
				min = j;
		}
		if (min != i)
		{
			char temp = str[i];
			str[i] = str[min];
			str[min] = temp;
		}
	}
}
