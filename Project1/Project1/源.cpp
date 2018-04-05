#include<iostream>
using namespace std;
#define NUM 5
int a[NUM] = {};

void f(int p)
{
	if (p == NUM)
	{
		for (int i = 0; i<NUM; i++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i<NUM; i++)
		{
			bool exist = false;
			for (int j = 0; j<p; j++)
			{
				if (a[j] == i)
				{
					exist = true;

				}
			}
			if (!exist)
			{
				a[p] = i;
				f(p + 1);
			}
		}
	}
}

int main()
{

	f(0);
	return 0;

}

