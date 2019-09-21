#pragma once
#include "common.h"

/* 最大公共子序列 longest common subsequence */

using namespace std;
template <typename T>
class LCS
{
public:
	//构造函数
	LCS(T s1, T s2) : len1(s1.length()), len2(s2.length())
	{
		//dp初始化
		dp = new int *[len1 + 1];
		flag = new int *[len1 + 1];
		for (int i = 0; i <= len1; i++)
		{
			dp[i] = new int[len2 + 1];
			flag[i] = new int[len2 + 1];
		}
		for (int i = 0; i < len1 + 1; i++)
		{
			for (int j = 0; j < len2 + 1; j++)
			{
				dp[i][j] = 0;
			}
		}
		computeLength(s1, s2);
		cout << "the lcs string is:  ";
		printLCS(s1, s2, len1, len2);
	}
	//计算长度
	void computeLength(T s1, T s2)
	{
		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
					flag[i][j] = 1;

				}
				else
				{
					if (dp[i - 1][j] >= dp[i][j - 1])
					{
						flag[i][j] = 2;
						dp[i][j] = dp[i - 1][j];
					}
					else
					{
						flag[i][j] = 3;
						dp[i][j] = dp[i][j - 1];
					}
				}
			}
		}
		cout << "the max length is: " << dp[len1][len2] << endl;
	}
	//打印lcs
	void printLCS(T s1, T s2, int i, int j)
	{
		if (i == 0 || j == 0)
		{
			return;
		}
		if (flag[i][j] == 1)
		{
			printLCS(s1, s2, i - 1, j - 1);
			cout << s1[i - 1] << " ";
		}
		else if (flag[i][j] == 2)
		{
			printLCS(s1, s2, i - 1, j);
		}
		else
		{
			printLCS(s1, s2, i, j - 1);
		}
	}
	//析构函数
	~LCS() 
	{
		for (int i = 0; i <= len1; i++)
		{
			delete[] dp[i];
			delete[] flag[i];
		}
		delete[] dp;
		delete[] flag;
	}
private:
	int **dp;
	int len1;
	int len2;
	int **flag;
};

