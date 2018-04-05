#include<iostream>
using namespace std;

#define max(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

//pre[]:Preorder Traversal, range [preL,preR]
//in[]:Inorder Traversal, range [inL,inR]
//maxDistance:the diameter of tree
//return value:the height of tree
int f(int *pre, int *in, int preL, int preR, int inL, int inR, int &maxDistance);

int main()
{
	cout << "I have read the rules about plagiarism punishment" << endl;
	int n = 0;
	cin >> n;
	int *pre = new int[n];
	int *in = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> pre[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> in[i];
	}

	int maxDistance = 0;
	int height = f(pre, in, 0, n - 1, 0, n - 1, maxDistance);
	cout << height << endl << maxDistance << endl;
	delete[]pre;
	delete[]in;
	return 0;
}

int f(int *pre, int *in, int preL, int preR, int inL, int inR, int &maxDistance)
{
	if (inL > inR)
	{
		maxDistance = 0;
		return -1;
	}
	else if (inL==inR)
	{
		maxDistance = 0;
		return 0;
	}
	else
	{
		int index = 0;
		for (index = inL; index <= inR; index++)
		{
			if (in[index] == pre[preL])
			{
				break;
			}
		}
		int maxDis1 = 0, maxDis2 = 0;
		int height1 = f(pre, in, preL + 1, preL + index - inL, inL, index - 1, maxDis1);
		int height2 = f(pre, in, preL + index - inL + 1, preL - inL + inR, index + 1, inR, maxDis2);
		maxDistance = max(height1 + height2 + 2, maxDis1, maxDis2);
		return (height1 > height2 ? height1 + 1 : height2 + 1);
	}
}