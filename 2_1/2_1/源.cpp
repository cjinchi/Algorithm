#include<iostream>
#include<sstream>
#include<string>
using namespace std;
//get data from cin
void get_data(int* &arr, int &len);
//return max sum
int max_sub_arr_sum(int arr[], int len);

int main()
{
	int *arr = NULL, len = 0;
	get_data(arr, len);
	cout << max_sub_arr_sum(arr, len) << endl;

	delete[]arr;
	return 0;
}


void get_data(int* &arr, int &len)
{
	string buf = "";
	getline(cin, buf);
	len = 0;
	for (int i = 0; i < int(buf.length()); i++)
	{
		if (buf[i] == ' ')
		{
			len++;
		}
	}

	stringstream stream;
	stream.clear();
	stream << buf;
	arr = new int[len];
	for (int i = 0; i < len; i++)
	{
		stream >> arr[i];
	}
}
int max_sub_arr_sum(int arr[], int len)
{
	int max = arr[0], sum = 0;
	for (int i = 0; i < len; i++)
	{
		if (sum < 0)
		{
			sum = arr[i];
		}
		else
		{
			sum += arr[i];

		}
		if (sum > max)
		{
			max = sum;
		}
	}
	return max;
}
