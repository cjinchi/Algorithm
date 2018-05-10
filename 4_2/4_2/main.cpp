#include<iostream>
using namespace std;

//quick sort
void sort(int arr[], int left, int right);
//decrease to two num
int find_two(int arr[], int ignore, int sum,int n);

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	int n = 0, sum = 0;
	cin >> n >> sum;
	int *p = new int[n];
	for (int i = 0; i < n; i++)
		cin >> p[i];
	sort(p, 0, n - 1);
	
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		//ignore p[i] when find two
		result += find_two(p, i, sum - p[i], n);
	}

	cout << result / 3 << endl;
	
	delete[]p;
	return 0;
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

int find_two(int arr[], int ignore, int sum, int n)
{
	int left = 0, right = n - 1;
	if (left == ignore) left++;
	if (right == ignore) right--;

	int result = 0;
	while (left < right)
	{
		if (arr[left] + arr[right] == sum)
		{
			result++;

			left++;
			right--;
			if (left == ignore) left++;
			if (right == ignore) right--;
		}
		else if (arr[left] + arr[right] > sum)
		{
			right--;
			if (right == ignore) right--;
		}
		else
		{
			left++;
			if (left == ignore) left++;
		}
	}
	return result;
}