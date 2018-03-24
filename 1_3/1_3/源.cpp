#include<iostream>
using namespace std;

int main()
{
	int arr[1000] = {};
	int len = 0, c = 0;

	while (cin >> len)
	{
		//Get data
		for (int i = 0; i < len; i++)
		{
			cin >> arr[i];
		}
		cin >> c;

		//Enumeration
		for (int i = 0; i < len - 1; i++)
		{
			for (int j = i + 1; j < len; j++)
			{
				if (arr[i] + arr[j] == c)
				{
					cout << arr[i] << " " << arr[j] << endl;
				}
			}
		}
	}
	return 0;
}