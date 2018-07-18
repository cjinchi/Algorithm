#pragma warning(disable:4996)

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
using namespace std;

#define MAX_LEN 10000
short len = 0;
vector<vector<short>> dp;

void get_dp(char str[],short beg, short end);
int main()
{
	//get data
	char str[MAX_LEN] = {};
	char temp = '\0';
	while(cin>>temp)
	{
			str[len] = temp;
			len++;
	}
	dp.resize(len);
	for (short i = 0; i < len; i++)
	{
		dp[i].resize(len,0);
	}

	//dp
	for (short i = len-1; i >=0; i--)
	{
		for (short j = i; j < len; j++)
		{
			get_dp(str,i,j);
		}
	}

	//output 
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << dp[0][len - 1] << endl;
	return 0;
}

void get_dp(char str[], short beg, short end)
{
	if (beg == end)
	{
		dp[beg][end] = 1;
	}
	else if (beg + 1 == end)
	{
		if (str[beg] == str[end])
			dp[beg][end] = 2;
		else
			dp[beg][end] = 1;
	}
	else
	{
		if (str[beg] == str[end])
			dp[beg][end] = 2 + dp[beg + 1][end - 1];
		else
			dp[beg][end] = max(dp[beg][end - 1], dp[beg + 1][end]);
	}
}