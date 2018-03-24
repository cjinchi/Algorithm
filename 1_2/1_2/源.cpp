#include<iostream>
#define ARRAY_LEN 5000000
using namespace std;

//quick sort,ascending
void sort(int arr[], int left, int right);

//print 2*k+1 num in arr[] ,from beg to beg+2*k
void print(int arr[], int beg, int k);

int main()
{
	int arr[ARRAY_LEN] = {};
	int k = 0, len = 0;
	while (cin >> k >> len)
	{
		//Get
		for (int i = 0; i < len; i++)
		{
			cin >> arr[i];
		}

		//Sort
		sort(arr, 0, len - 1);

		//Print
		int beg = (len - (2 * k + 1)) / 2;
		print(arr, beg, k);
	}
	return 0;
}

void print(int arr[], int beg, int k)
{
	for (int i = beg; i < beg + 2 * k; i++)
	{
		cout << arr[i] << " ";
	}
	cout << arr[beg + 2 * k] << endl;
}

void sort(int arr[], int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int index = left + 1;
	for (int i = left + 1; i <= right; i++)
	{
		if (arr[i] < arr[left])
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

	sort(arr, left, index - 2);
	sort(arr, index, right);
}