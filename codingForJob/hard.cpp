#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <queue>
#include <set>
#include <bitset>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverseList(ListNode* head, ListNode* trail) //trailΪ�����ڱ�,�����뷴ת
{
	if (!head || !head->next)
	{
		return head;
	}
	ListNode* pre = trail;
	while (head != trail)
	{
		ListNode* tmp = head->next;
		head->next = pre;
		pre = head;
		head = tmp;
	}
	return pre;
}
ListNode* reverseKGroup(ListNode* head, int k)
{
	if (k == 1 || !head || !head->next)
	{
		return head;
	}
	ListNode* t = head;
	ListNode* pret = new ListNode(0);  //��¼��ת֮ǰ�Ѿ���ת���˵����һ��Ԫ��
	pret->next = head;
	ListNode* result = pret;
	while (head)
	{
		for (int i = 0; i < k - 1; ++i)  //��Ϊ��תʱ������ʼ��head�����ֻ��Ҫ�ж�head֮��k-1��next��Ϊnull�����������ʼ��head��������k��
		{
			head = head->next;
			if (!head)
			{
				return result->next;
			}
		}
		head = head->next;  //��Ϊǰ���for�������head�����ǵ�k��������ת�����ǰ�������ģ������Ҫǰ��һλ��Ϊ�ڱ�
		t = reverseList(t, head);
		pret->next = t;
		for (int i = 0; i < k; ++i)
		{
			t = t->next;
			pret = pret->next;
		}
	}
	return result->next;
}

vector<int> maxSlidingWindow_1(vector<int>& nums, int k)  //�����������ֵ--deque��¼ֵ
{
	deque<int> d;
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		if (i < k - 1)
		{
			while (!d.empty() && d.back() < nums.at(i))
			{
				d.pop_back();
			}
			d.push_back(nums.at(i));
		}
		else
		{
			while (!d.empty() && d.back() < nums.at(i))
			{
				d.pop_back();
			}
			d.push_back(nums.at(i));
			result.push_back(d.front());
			if (!d.empty() && d.front() == nums.at(i - k + 1))
			{
				d.pop_front();
			}
		}
	}
	return result;
}

vector<int> maxSlidingWindow_2(vector<int>& nums, int k)  //�����������ֵ--deque��¼�±�,�ü�¼�±�ķ����������Ǹ���
{
	if (nums.size() == 0)
	{
		return{};
	}
	deque<int> d; //��¼���ֵ���±�
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		if (i >= k && d.front() <= i - k)
		{
			d.pop_front();
		}
		while (!d.empty() && nums.at(i) > nums.at(d.back()))
		{
			d.pop_back();
		}
		d.push_back(i);
		if (i >= k - 1)
		{
			result.push_back(nums.at(d.front()));
		}
	}
	return result;
}

vector< vector<string> > result;
unordered_set<int> columns, pie, na;
void solveNQueens_dfs(int n, int row, vector<int> pos)  
{
	if (row >= n)  //row��0��ʼ��n�еĻ��ǵ�n-1�����Ե�n�Ļ����˳��ݹ�
	{
		vector<string> tmp;
		for (int i=0; i<n; ++i)
		{
			string s = "";
			for (int j=0; j<n; ++j)
			{
				if (j == pos.at(i))
				{
					s += "Q";
				}
				else
				{
					s += ".";
				}
			}
			tmp.push_back(s);
		}
		result.push_back(tmp);
		return;
	}
	for (int col=0; col < n; ++col)
	{
		if (columns.count(col) || pie.count(row - col) || na.count(row + col))
		{
			continue;
		}
		columns.insert(col);
		pie.insert(row - col);
		na.insert(row + col);
		//�ѽ���ŵ���ǰ��pos��
		pos.at(row) = col;
		solveNQueens_dfs(n, row + 1, pos);  //�ݹ鵽��һ��
		//�����һ�ֿ��ܵõ��Ľ��,�ٿ���ǰ����û�л������ܳ���
		columns.erase(col);
		pie.erase(row - col);
		na.erase(row + col);
	}
}
vector<vector<string>> solveNQueens(int n)  //N�ʺ�
{
	if (n == 0)
	{
		return {};
	}
	vector<int> pos(n, -1); //�±�����к�
	solveNQueens_dfs(n, 0, pos);
	return result;
}

void totalNQueens_dfs(int n, int row, int &result)
{
	if (row >= n)
	{
		result++;
		return;
	}
	for (int col=0; col<n; ++col)
	{
		if (columns.count(col) || pie.count(row - col) || na.count(row + col))
		{
			continue;
		}
		columns.insert(col);
		pie.insert(row - col);
		na.insert(row + col);
		totalNQueens_dfs(n, row + 1, result);
		//ɾ����ǰcol�Ľ��
		columns.erase(col);
		pie.erase(row - col);
		na.erase(row + col);
	}
}
int totalNQueens(int n)
{
	if (n == 0)
	{
		return 0;
	}
	int result = 0;
	totalNQueens_dfs(n, 0, result);
	return result;
}

bool check_solveSudoku_dfs(vector<vector<char>>& board, int i, int j, char c)
{
	for (int l=0; l<9; ++l)
	{
		if (board.at(i).at(l) != '.' && board.at(i).at(l) == c)
		{
			return false;
		}
		if (board.at(l).at(j) != '.' && board.at(l).at(j) == c)
		{
			return false;
		}
		int blocki = (i / 3) * 3 + l / 3, blockj = (j / 3) * 3 + l % 3;
		if (board.at(blocki).at(blockj) != '.' && board.at(blocki).at(blockj) == c)
		{
			return false;
		}
	}
	return true;
}
bool solveSudoku_dfs(vector<vector<char>>& board)
{
	for (int i=0; i<9; ++i)
	{
		for (int j=0; j<9; ++j)
		{
			if (board.at(i).at(j) == '.')
			{
				for (char c = '1'; c <= '9'; c++)
				{
					if (check_solveSudoku_dfs(board, i, j, c))
					{
						board.at(i).at(j) = c;
						if (solveSudoku_dfs(board))
						{
							return true;  //�����ǰԪ�ص���c�󣬽��еݹ�ɹ��Ļ����ͷ���true
						}
						else
						{
							board.at(i).at(j) = '.';  //����ݹ鲻�ɹ����ͻ�ԭ��ǰԪ��
						}
					}
				}
				return false;  //��ǰԪ�ص��ڡ�.��������δ���ҵ��ɹ���c������false
			}
		}
	}
	return true;   //����Ԫ�������ϣ�����δ����false�Ļ������ǳɹ���
}
void solveSudoku(vector<vector<char>>& board)  //������
{
	if (board.size() == 0 || board.at(0).size() == 0)
	{
		return;
	}
	solveSudoku_dfs(board);
}

struct TrieNode   //���������ֵ���
{
	char val;
	bool isEndOfWord = false;
	vector<TrieNode*> children;
	TrieNode(char value)
	{
		this->val = value;
		for (int i = 0; i < 26; i++)
		{
			children.push_back(nullptr);
		}
	}
};
TrieNode* root = new TrieNode(NULL);
int direction[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
set<string> res;
void findWords_dfs(vector<vector<char>>& board, int row, int column, TrieNode* tmp, string s)
{
	if (!tmp)
	{
		return;
	}
	char t = board.at(row).at(column);
	board.at(row).at(column) = '*';
	s += tmp->val;
	if (tmp->isEndOfWord)
	{
		board.at(row).at(column) = t;  //Ҫ�ѵ�ǰ��ֵ�ָ�����Ϊ����һ���ַ�����ƥ��
		res.insert(s);
		//�����ʱ���к��ӣ���˵����words��������Ե�ǰ�ɹ�ƥ����ַ���Ϊǰ׺���ַ����������Ҫ������ȥ
		for (int i=0; i<26; ++i)
		{
			if (tmp->children.at(i))
			{
				break;
			}
			else if (i == 25)
			{
				return;
			}
		}
	}
	for (int i=0; i<4; ++i)
	{
		if (row + direction[i][0] < 0 || row + direction[i][0] >= board.size() || column + direction[i][1] < 0 || column + direction[i][1] >= board.at(row).size())
		{
			continue;
		}
		else
		{
			if (board.at(row + direction[i][0]).at(column + direction[i][1]) == '*')
			{
				continue;
			}
			int index = board.at(row + direction[i][0]).at(column + direction[i][1]) - 'a';
			char c = board.at(row + direction[i][0]).at(column + direction[i][1]);
			board.at(row + direction[i][0]).at(column + direction[i][1]) = '*';
			if (tmp->children.at(index))
			{
				findWords_dfs(board, row + direction[i][0], column + direction[i][1], tmp->children.at(index), s);
			}
			board.at(row + direction[i][0]).at(column + direction[i][1]) = c;  //ִ����ݹ��Ҫ�ѵ�ǰ��ֵ�ָ�����Ϊ�п��ܵݹ鲻�ɹ���Ҳ��Ϊ����һ���ַ�����ƥ��
		}
	}
	board.at(row).at(column) = t;  //Ҫ�ѵ�ǰ��ֵ�ָ�����Ϊ�п��ܵݹ鲻�ɹ���Ҳ��Ϊ����һ���ַ�����ƥ��
}
vector<string> findWords(vector<vector<char>>& board, vector<string>& words)  //�������� II
{
	if (board.size() == 0 || words.size() == 0)
	{
		return {};
	}
	//�����ֵ���
	TrieNode* tmp = root;
	for (int i=0; i<words.size(); ++i)
	{
		for (int j=0; j<words.at(i).size(); ++j)
		{
			if (!tmp->children.at(words.at(i).at(j) - 'a'))
			{
				tmp->children.at(words.at(i).at(j) - 'a') = new TrieNode(words.at(i).at(j));
			}
			tmp = tmp->children.at(words.at(i).at(j) - 'a');
		}
		tmp->isEndOfWord = true;
		tmp = root;
	}
	for (int i=0; i<board.size(); ++i)
	{
		for (int j=0; j<board.at(i).size(); ++j)
		{
			int index = board.at(i).at(j) - 'a';
			if (root->children.at(index))
			{
				findWords_dfs(board, i, j, root->children.at(index), "");
			}
		}
	}
	vector<string> result;
	result.resize(res.size());
	result.assign(res.begin(), res.end());
	return result;
}

int maxProfit_iii(vector<int>& prices)  //������Ʊ�����ʱ�� III
{
	if (prices.size() == 0)
	{
		return 0;
	}
	vector< vector< vector<int> > > dp(prices.size(), vector< vector<int> >(3, vector<int>(2)));  //��һ��3��ʾ��ǰ���׵Ĵ���(��Ϊ�������),�ڶ���2���Ƿ�ӵ�й�Ʊ��dp��ʾ��ǰ����������״����µ��������
	for (int i=0; i<prices.size(); ++i)
	{
		for (int k = 2; k >= 1; k--)
		{
			if (i - 1 == -1)
			{
				dp[i][k][0] = 0;
				dp[i][k][1] = -prices.at(i);
				continue;
			}
			dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices.at(i));
			dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices.at(i));
		}
	}
	return dp[prices.size() - 1][2][0];
}

int maxProfit_iv(int k, vector<int>& prices)
{
	if (prices.size() == 0)
	{
		return 0;
	}
	if (k > prices.size() / 2)  //�����ƴ���
	{
		vector< vector<int> > dp(prices.size(), vector<int>(2));
		for (int i=0; i<prices.size(); ++i)
		{
			if (i - 1 == -1)
			{
				dp[i][0] = 0;
				dp[i][1] = -prices.at(0);
				continue;
			}
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices.at(i));
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices.at(i));
		}
		return dp[prices.size() - 1][0];
	}
	else
	{
		vector< vector< vector<int> > > dp(prices.size(), vector< vector<int> >(k + 1, vector<int>(2)));
		for (int i = 0; i < prices.size(); ++i)
		{
			for (int j = k; j >= 1; --j)
			{
				if (i - 1 == -1)
				{
					dp[i][j][0] = 0;
					dp[i][j][1] = -prices.at(i);
					continue;
				}
				dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices.at(i));
				dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices.at(i));
			}
		}
		return dp[prices.size() - 1][k][0];
	}
}

int minDistance(string word1, string word2)  //�༭����
{
	if (word1.size() == 0)
	{
		return word2.size();
	}
	else if (word2.size() == 0)
	{
		return word1.size();
	}
	vector< vector<int> > dp(word1.size() + 1, vector<int>(word2.size() + 1));
	for (int i=0; i<=word1.size(); ++i)
	{
		dp[i][0] = i;
	}
	for (int j=0; j<=word2.size(); ++j)
	{
		dp[0][j] = j;
	}
	for (int i=1; i<=word1.size(); ++i)
	{
		for (int j=1; j<=word2.size(); ++j)
		{
			if (word1[i - 1] == word2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
				dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i][j]);
			}
		}
	}
	return dp[word1.size()][word2.size()];
}

int main
{
	//K ��һ�鷭ת����
	//reverseKGroup

	//�����������ֵ
	//maxSlidingWindow

	//N�ʺ�
	//solveNQueens

	//N�ʺ� II
	//totalNQueens

	//������
	//solveSudoku

	//�������� II
	//findWords

	//������Ʊ�����ʱ�� III
	//maxProfit_iii

	//������Ʊ�����ʱ�� IV
	//maxProfit_iv

	//�༭����
	//minDistance
}