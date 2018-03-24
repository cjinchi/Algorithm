#include<iostream>
#include<string>
using namespace std;

//return num in [left,right]
long long divide_and_conquer(string *arr, int *p, int left, int right, int *buf);

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;

	int len = 0;
	cin >> len;

	string *arr = new string[len];
	int *p = new int[len];
	int *buf = new int[len];

	for (int i = 0; i < len; i++)
	{
		cin >> arr[i];
		p[i] = i;
		buf[i] = 0;
	}
	cout << divide_and_conquer(arr, p, 0, len - 1, buf) << endl;

	delete[]arr;
	delete[]p;
	delete[]buf;
	return 0;
}
long long divide_and_conquer(string *arr, int *p, int left, int right, int *buf)
{
	if (left >= right)
	{
		return 0;
	}

	long long result = 0;
	int mid = (left + right) / 2;
	result += divide_and_conquer(arr, p, left, mid, buf);
	result += divide_and_conquer(arr, p, mid + 1, right, buf);

	int index = left, il = left, ir = mid + 1;
	while (il <= mid && ir <= right)
	{
		if (arr[p[il]] <= arr[p[ir]])
		{
			buf[index] = p[il];
			il++;
		}
		else
		{
			result += (mid - il + 1);
			buf[index] = p[ir];
			ir++;
		}
		index++;
	}
	while (il <= mid)
	{
		buf[index] = p[il];
		index++;
		il++;
	}
	while (ir <= right)
	{
		buf[index] = p[ir];
		index++;
		ir++;
	}
	for (int i = left; i <= right; i++)
	{
		p[i] = buf[i];
	}
	return result;
}