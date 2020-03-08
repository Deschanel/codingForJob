#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <deque>
using namespace std;

int findRepeatNumber_1(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//原地算法,用sort排序后，查找当前与后一个相同的数字
	if (nums.size() <= 1)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());  //时间O(nlogn)
	for (int i=0; i<nums.size() - 1; ++i)
	{
		if (nums.at(i)  == nums.at(i + 1))
		{
			return nums.at(i);
			break;
		}
	}
	return -1;
}

int findRepeatNumber_2(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//使用unorder_set，看看之前是否已经有了，空间O(n)，时间O(n)
	if (nums.size() <= 1)
	{
		return 0;
	}
	unordered_set<int> us;
	for (auto i : nums)
	{
		if (us.count(i))
		{
			return i;
			break;
		}
		else
		{
			us.insert(i);
		}
	}
	return -1;
}

int findRepeatNumber_3(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//如果要是没有重复的话，下标与值应该相等
	//下标为i的值为m，如m==i，则跳过，如果不等的话，我们就去找下标为m的数k，如果k=m的话，重复了返回
	//如果不等的话，将m和k交换，也就是m放到下标为m的位置，k放到下标为i的位置，再去看下标为k的数n，继续以上操作
	if (nums.size() <= 1)
	{
		return -1;
	}
	for (int i : nums)
	{
		if (i < 0 || i > nums.size() - 1)
		{
			return -1;
		}
	}
	for (int i=0; i<nums.size(); ++i)
	{
		while (nums[i] != i)
		{
			if (nums[i] == nums[nums[i]])
			{
				return nums[i];
			}
			swap(nums[i], nums[nums[i]]);
		}
	}
	return -1;
}

bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
{
	//看剩余矩阵右上角那个数m，如果等于直接返回，
	//如果m大于target，那么m所在一列剔除，也就是此时应该看与m同行的左侧的数，
	//如果小于，则m所在行比剔除，此时要看与m同列的下面的数
	//循环这样执行下去
	if (matrix.size() == 0 || matrix.at(0).size() == 0)
	{
		return false;
	}
	int n = matrix.size() - 1, m = matrix.at(0).size() - 1;
	if (matrix[0][0] > target || matrix[n][m] < target)
	{
		return false;
	}
	int i = 0;
	while (i <= n && m >= 0)
	{
		if (matrix[i][m] == target)
		{
			return true;
		}
		else if (matrix[i][m] > target)
		{
			--m;
		}
		else
		{
			++i;
		}
	}
	return false;
}

string replaceSpace_1(string s)  //面试题05. 替换空格
{
	//原地算法，将s扩容，然后一个指针p1从原先未扩容的字符串的最后一个字符往前，一个指针p2从扩容后的字符最后一个位置往前
	//如果p1指向的值不为空格，那么就把这个值赋值给p2指向的位置，
	//如果等于空格，那么p2往前分别加上02%后，然后两者再往前走,直到p1出了第0个字符
	//由于把空格转换为%20，1个变为三个，也就是说一个空格就要额外加上2个字符的长度，共有count个空格，就要额外加上2*count个长度
	if (s.size() == 0)
	{
		return "";
	}
	int count = 0;
	for (char c : s)
	{
		if (c == ' ')
		{
			++count;
		}
	}
	int p1 = s.size() - 1;
	s.resize(s.size() + 2 * count);
	int p2 = s.size() - 1;
	for (; p1 >=0 && p2 >= 0; --p1)
	{
		if (s[p1] != ' ')
		{
			s[p2] = s[p1];
		}
		else
		{
			s[p2] = '0';
			--p2;
			s[p2] = '2';
			--p2;
			s[p2] = '%';
		}
		--p2;
	}
	return s;
}

string replaceSpace_2(string s)  //面试题05. 替换空格
{
	//非原地算法
	if (s.size() == 0)
	{
		return "";
	}
	string result;
	for (char c : s)
	{
		if (c != ' ')
		{
			result += c;
		}
		else
		{
			result += "%20";
		}
	}
	return result;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

vector<int> reversePrint_1(ListNode* head)  //面试题06. 从尾到头打印链表
{
	//记录链表的长度，然后开辟一个此长度的数组，然后链表从头遍历，值在数组中从后往前写
	if (!head)
	{
		return {};
	}
	ListNode* p = head;
	int i = 0;
	while (p)
	{
		++i;
		p = p->next;
	}
	vector<int> result(i, 0);
	while (head && i >= 1)
	{
		result[i - 1] = head->val;
		head = head->next;
		--i;
	}
	return result;
}

vector<int> reversePrint_2(ListNode* head)  //面试题06. 从尾到头打印链表
{
	//用栈
	if (!head)
	{
		return {};
	}
	stack<int> s;
	while (head)
	{
		s.push(head->val);
		head = head->next;
	}
	vector<int> result;
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}

vector<int> reversePrint_3(ListNode* head)  //面试题06. 从尾到头打印链表
{
	//反转链表
	if (!head)
	{
		return {};
	}
	ListNode* p = nullptr;
	while (head)
	{
		ListNode* tmp = head->next;
		head->next = p;
		p = head;  //当tmp为nullptr时，下一个循环就进不去了，head为nullptr了，而p是此时的头元素
		head = tmp;
	}
	vector<int> result;
	while (p)
	{
		result.push_back(p->val);
		p = p->next;
	}
	return result;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)  //面试题07. 重建二叉树
{
	if (preorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(preorder[0]);
	int index = -1;
	for (int i=0; i<inorder.size(); ++i)
	{
		if (inorder[i] == preorder[0])
		{
			index = i;
			break;
		}
	}
	vector<int> inorder_left, inorder_right;
	inorder_left.assign(inorder.begin(), inorder.begin() + index);
	inorder_right.assign(inorder.begin() + index + 1, inorder.end());
	vector<int> preorder_left, preorder_right;
	preorder_left.assign(preorder.begin() + 1, preorder.begin() + 1 + index);
	preorder_right.assign(preorder.begin() + 1 + index, preorder.end());
	root->left = buildTree(preorder_left, inorder_left);
	root->right = buildTree(preorder_right, inorder_right);
	return root;
}

struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

	}
};
TreeLinkNode* GetNext(TreeLinkNode* pNode)  //二叉树的下一个结点---在牛客上
{
	//这里的pNode并不是根节点，而是二叉树里面的任意一个节点，因此用中序遍历不行
	if (!pNode)
	{
		return nullptr;
	}
	TreeLinkNode* p = nullptr;
	if (pNode->right)   //如果有右子树，那么下一个节点就是右子树中最左边的节点
	{
		p = pNode->right;
		while (p->left)
		{
			p = p->left;
		}
	}
	else if (pNode->next)  //如果右子树不存在，且父节点存在
	{
		p = pNode->next;  //指向父节点
		//如果父节点的左节点是pNode，那么下一个节点就是就是父节点
		//如果父节点的右节点是pNode，那么就向上找，直到向上找到的某个节点i是i的父节点的左节点，那么下一个节点就是i的父节点
		while (p && pNode == p->right)
		{
			pNode = p;
			p = p->next;
		}
	}
	return p;
}

class CQueue_1 {       //面试题09. 用两个栈实现队列
//删除时候，先用一个临时栈逆序保存s中的元素，那么临时栈的顶部就是要删除的元素，删除之后，再把元素返回到s中
public:
	stack<int> s;
	CQueue_1() {

	}

	void appendTail(int value) {
		s.push(value);
	}

	int deleteHead() {
		if (s.empty())
		{
			return -1;
		}
		stack<int> tmp;
		while (!s.empty())
		{
			tmp.push(s.top());
			s.pop();
		}
		int result = tmp.top();
		tmp.pop();
		while (!tmp.empty())
		{
			s.push(tmp.top());
			tmp.pop();
		}
		return result;
	}
};

class CQueue_2 {       //面试题09. 用两个栈实现队列
//两个栈，一个管插入，一个管删除
public:
	stack<int> s1, s2;
	CQueue_2() {

	}

	void appendTail(int value) {
		s1.push(value);
	}

	int deleteHead() {
		int result = -1;
		if (!s2.empty())
		{
			result = s2.top();
			s2.pop();
		}
		else if (!s1.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			result = s2.top();
			s2.pop();
		}
		return result;
	}
};

class MyStack_1 {   //用队列实现栈--09的引申题
//插入时候直接插入，删除时候用临时队列
public:
	queue<int> q;
	MyStack_1() {

	}

	void push(int x) {
		q.push(x);
	}

	int pop() {
		if (q.empty())
		{
			return -1;
		}
		queue<int> tmp;
		int result = -1;
		while (!q.empty())
		{
			result = q.front();
			q.pop();
			if (!q.empty())
			{
				tmp.push(result);
			}
		}
		while (!tmp.empty())
		{
			q.push(tmp.front());
			tmp.pop();
		}
		return result;
	}

	int top() {
		if (q.empty())
		{
			return -1;
		}
		queue<int> tmp;
		int result = -1;
		while (!q.empty())
		{
			result = q.front();
			q.pop();
			tmp.push(result);
		}
		while (!tmp.empty())
		{
			q.push(tmp.front());
			tmp.pop();
		}
		return result;
	}

	bool empty() {
		return q.empty();
	}
};

class MyStack_2 {   //用队列实现栈--09的引申题
//哪个不为空就插入到哪个后面
//这样在pop删除时候，可以循环放入到另一个为空的，循环到最后一个元素时候不放了
public:
	queue<int> q1, q2;
	MyStack_2() {

	}

	void push(int x) {
		if (q2.empty())
		{
			q1.push(x);
		}
		else
		{
			q2.push(x);
		}
	}

	int pop() {
		if (q1.empty() && q2.empty())
		{
			return -1;
		}
		int result = -1;
		if (q2.empty())
		{
			while (!q1.empty())
			{
				result = q1.front();
				q1.pop();
				if (!q1.empty())
				{
					q2.push(result);
				}
			}
		}
		else
		{
			while (!q2.empty())
			{
				result = q2.front();
				q2.pop();
				if (!q2.empty())
				{
					q1.push(result);
				}
			}
		}
		return result;
	}

	int top() {
		if (q1.empty() && q2.empty())
		{
			return -1;
		}
		int result = -1;
		if (q2.empty())
		{
			while (!q1.empty())
			{
				result = q1.front();
				q1.pop();
				q2.push(result);
			}
		}
		else
		{
			while (!q2.empty())
			{
				result = q2.front();
				q2.pop();
				q1.push(result);
			}
		}
		return result;
	}

	bool empty() {
		return q1.empty() && q2.empty();
	}
};

int fib(int n)   //面试题10- I. 斐波那契数列
{
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}
	int p = 0, cur = 1;
	for (int i=2; i<=n; ++i)
	{
		if (p > 1000000007 - cur)   //题目要求答案需要取模 1e9+7（1000000007）
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int numWays(int n)  //面试题10- II. 青蛙跳台阶问题
{
	if (n <= 1)
	{
		return 1;
	}
	int p = 1, cur = 1;
	for (int i=2; i<=n; ++i)
	{
		if (p > 1000000007 - cur) //题目要求答案需要取模 1e9+7（1000000007）
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int minArray(vector<int>& numbers)  //面试题11. 旋转数组的最小数字
{
	if (numbers.size() == 0)
	{
		return -1;
	}
	if (numbers.size() == 1)
	{
		return numbers[0];
	}
	int result = INT_MAX;
	int l = 0, r = numbers.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (numbers[l] < numbers[mid])  //如果严格小于，说明l到mid递增，那么result赋值后，看看后面的是否还有更小的
		{
			result = min(result, numbers[l]);
			l = mid + 1;
		}
		else if(numbers[l] == numbers[mid])  //相等的话,赋值当前的l，然后跳过他，看看后面的数组的最小值
		{
			result = min(result, numbers[l]);
			++l;
		}
		else  //后边有序
		{
			result = min(result, numbers[mid]);
			r = mid - 1;
		}
	}
	return result;
}

int exist_direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
set< pair<int, int> > exist_s; //存储用过的行列, 这里也可以定义一个与board相同大小的bool值矩阵，表示第i行第j个是否呗使用了
bool exist_dfs(vector<vector<char>>& board, string word, int n, int row, int column)
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	if (n == word.size())
	{
		return true;
	}
	if (row == -1 || column == -1)  //第一个数字还没开始找
	{
		for (int i=0; i < board.size(); ++i)
		{
			for (int j=0; j < board.at(i).size(); ++j)
			{
				if (board[i][j] == word[n])
				{
					pair<int, int> p(i, j);
					exist_s.insert(p);   //第一个字符直接放进去就可以
					bool flag = exist_dfs(board, word, n + 1, i, j);
					if (flag)
					{
						return true;
					}
					exist_s.erase(p);  //弹出当前用过的，再从下一个字符开始作为开头看看
				}
			}
		}
	}
	else  //后面的数字
	{
		for (int i=0; i<4; ++i)
		{
			int x = row + exist_direction[i][0], y = column + exist_direction[i][1];
			if (x >= 0 && x < board.size() && y >= 0 && y < board.at(0).size())
			{
				if (board[x][y] == word[n])
				{
					pair<int, int> p(x, y);
					set< pair<int, int> >::iterator ifind = exist_s.find(p);
					if (ifind != exist_s.end())  //如果当前字符用过了
					{
						continue;
					}
					exist_s.insert(p);
					bool flag = exist_dfs(board, word, n + 1, x, y);
					if (flag)
					{
						return true;
					}
					exist_s.erase(p);  //弹出当前方向的字符，再从剩余方向进行，因为这个字符可能后面用到
				}
			}
		}
	}
	return false;
}
bool exist(vector<vector<char>>& board, string word)   //面试题12. 矩阵中的路径
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	return exist_dfs(board, word, 0, -1, -1);
}
vector< vector<bool> > exist_1_visited;  //定义一个与board相同大小的bool值矩阵，表示第i行第j个是否使用了
bool exist_1_dfs(vector<vector<char>>& board, string word, int n, int row, int column)
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	if (n == word.size())
	{
		return true;
	}
	if (row == -1 || column == -1)  //第一个数字还没开始找
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board.at(i).size(); ++j)
			{
				if (board[i][j] == word[n] && !exist_1_visited[i][j])
				{
					exist_1_visited[i][j] = true;
					bool flag = exist_dfs(board, word, n + 1, i, j);
					if (flag)
					{
						return true;
					}
					exist_1_visited[i][j] = false;  //弹出当前用过的，再从下一个字符开始作为开头看看
				}
			}
		}
	}
	else  //后面的数字
	{
		for (int i = 0; i < 4; ++i)
		{
			int x = row + exist_direction[i][0], y = column + exist_direction[i][1];
			if (x >= 0 && x < board.size() && y >= 0 && y < board.at(0).size())
			{
				if (board[x][y] == word[n] && !exist_1_visited[x][y])
				{
					exist_1_visited[x][y] = true;
					bool flag = exist_dfs(board, word, n + 1, x, y);
					if (flag)
					{
						return true;
					}
					exist_1_visited[x][y] = false;  //弹出当前方向的字符，再从剩余方向进行，因为这个字符可能后面用到
				}
			}
		}
	}
	return false;
}
bool exist_1(vector<vector<char>>& board, string word)   //面试题12. 矩阵中的路径
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	for (int i = 0; i < board.size(); ++i)
	{
		vector<bool> tmp;
		for (int j = 0; j < board.at(i).size(); ++j)
		{
			tmp.push_back(false);
		}
		exist_1_visited.push_back(tmp);
	}
	return exist_1_dfs(board, word, 0, -1, -1);
}

int movingCount_direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
vector< vector<bool> > movingCount_visited;   //判断是否走过了
int movingCount_result = 1;   //最后的结果,第一个(0,0)肯定能在，因此就从这个开始走
int movingCount_sum(int n)  //计算n的各位加起来
{
	int sum = 0;
	while (n > 0)
	{
		sum += (n % 10);
		n /= 10;
	}
	return sum;
}
void movingCount_dfs(int row, int column, int k, int m, int n)
{
	if (k == 0)
	{
		movingCount_result = 1;
		return;
	}
	for (int i=0; i<4; ++i)
	{
		int x = row + movingCount_direction[i][0], y = column + movingCount_direction[i][1];
		if (x >= 0 && x < m && y >= 0 && y < n)
		{
			int sumx = movingCount_sum(x), sumy = movingCount_sum(y);
			if (sumx + sumy <= k && !movingCount_visited[x][y])
			{
				movingCount_visited[x][y] = true;  //走过了就不要走回来了，因此不能再恢复为false
				++movingCount_result;
				movingCount_dfs(x, y, k, m, n);
			}
		}
	}
}
int movingCount(int m, int n, int k)  //面试题13. 机器人的运动范围
{
	if (k == 0)
	{
		return 1;
	}
	for (int i=0; i<m; ++i)
	{
		vector<bool> tmp;
		for (int j=0; j<n; ++j)
		{
			tmp.push_back(false);
		}
		movingCount_visited.push_back(tmp);
	}
	movingCount_visited[0][0] = true;
	movingCount_dfs(0, 0, k, m, n);
	delete[] movingCount_direction;  //删除
	movingCount_visited.clear();  //清空数据
	return movingCount_result;
}

int cuttingRope(int n)  //面试题14- I. 剪绳子
{
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	//当我们知道dp(n-1)为n-1时候的最大值，
	//而n=n-1+1或n=n-2+2或n=n-3+3。。。。n=1+n-1
	//也就是说dp(n) = max(dp(n-i)*dp(i))， i从n-1到n/2
	//从另一个角度来说，假设每一刀都是对应最大值时候的其中一刀
	//剪第一刀时，有1,2,3....n-1种情况，那么就剪成了i+j=n,然后dp(n) = max(dp(n-i)*dp(i))
	//那么有没有一种切法能够使得结果不在max(dp(n-i)*dp(i))中呢
	//我们假设存在，那么第一刀下去切出了k+l=n,然后就是对k和l分别切，然而k最多只能是dp(k),l最多是dp(l)，因此dp(n)还是等于dp(k)*dp(l)
	vector<int> dp(n + 1, 0);
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;  //这个只是为了得出结果，与实际n=2时候不符
	dp[3] = 3;  //这个只是为了得出结果，与实际n=3时候不符
	for (int i = 4; i <= n; ++i)
	{
		for (int j = i - 1; j >= i / 2; --j)  //显然根据i-j和j的对称性，j到i/2就可以了
		{
			dp[i] = max(dp[i], dp[j] * dp[i - j]);
		}
	}
	return dp[n];
}
int cuttingRope_1(int n)  //面试题14- I. 剪绳子
{
	//有2和3的话，尽量切出2和3，因为切出4，可以看成两个2，切出5，不如切成2和3，切出6，不如切成3和3
	//切出7，不如3和2和2.。。。也就是说尽量切出2和3
	//他俩比较的话，尽量切出3，因此比方6的话3*3>2*2*2
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	int a = n / 3, b = n % 3;
	if (b == 0) //3的倍数
	{
		return pow(3, a);
	}
	else if (b == 1)//比如7，3 3 1要小于3 2 2,也就是说应该切出3 3 3 ... 3 2 2
	{
		return pow(3, a - 1) * 4;
	}
	else  //b=2
	{
		return pow(3, a) * 2;
	}
}

int cuttingRope(int n)   //面试题14- II. 剪绳子 II  需要取余1000000007
{
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	int a = n / 3, b = n % 3;
	if (b == 1)
	{
		a -= 1;
	}
	int result = 1;
	int tmp = result;
	for (int i = 1; i <= a; ++i)  //pow(3, a)分开累加
	{
		if (result > INT_MAX / 3)
		{
			tmp = result;
			result = result % 1000000007 + result % 1000000007;
			result %= 1000000007;
			result += (tmp % 1000000007);
		}
		else
		{
			result *= 3;
		}
	}
	if (b == 1)
	{
		if (result > INT_MAX / 4)   //乘以4要分开累加
		{
			tmp = result;
			result = result % 1000000007 + result % 1000000007;
			result %= 1000000007;
			result += (tmp % 1000000007);
			result %= 1000000007;
			result += (tmp % 1000000007);
		}
		else
		{
			result *= 4;
		}
	}
	else if (b == 2)
	{
		if (result > INT_MAX / 2)  //乘以2要分开累加
		{
			result = result % 1000000007 + result % 1000000007;
		}
		else
		{
			result *= 2;
		}
	}
	return result % 1000000007;;
}

int hammingWeight(uint32_t n)  //面试题15. 二进制中1的个数
{
	//n&(n-1)为清除最低位的1；n&(-n)为得到最低位的1
	if (n == 0)
	{
		return 0;
	}
	int result = 0;
	while (n != 0)
	{
		++result;
		n &= (n - 1);
	}
	return result;
}

double myPow(double x, int n)  //面试题16. 数值的整数次方
{
	if (x == 0 && n < 0)
	{
		return 0.0;
	}
	if ((x == 0 && n == 0) || n == 0 || x == 1)
	{
		return 1.0;
	}
	if (n == 1)
	{
		return x;
	}
	unsigned int ui = 0; //转换为unsigned int
	if (n < 0)
	{
		ui = -(n + 1);  //避免int_min情况
		ui += 1;
	}
	else
	{
		ui = n;
	}
	double result = myPow(x, ui >> 1);   //右移比除以2快
	result = result * result;
	if (ui & 1)  //判断%2余数直接用&1就可以，如果是奇数，则括号里为true
	{
		result *= x;
	}
	if (n < 0)
	{
		result = 1.0 / result;
	}
	return result;
}

vector<int> printNumbers(int n)   //面试题17. 打印从1到最大的n位数--leetcode上太简单
{
	if (n == 0)
	{
		return {};
	}
	//先找到最大的数
	int ma = 9;
	for (int i = 1; i < n; ++i)
	{
		ma = ma * 10 + 9;
	}
	vector<int> result(ma);
	for (int i = 0; i < ma; ++i)
	{
		result[i] = i + 1;
	}
	return result;
}

string printNumbers_string_plus1(string s)  //s表示的数字加上1,s表示的数是>=0的，非负数
{
	if (s.size() == 0)
	{
		return "";
	}
	int i = s.size() - 1;
	int jinwei = 1;  //因为表示的是s的数字加1，所以刚开始要设为1呀
	while (i >= 0)
	{
		int tmp = s[i] - '0' + jinwei;
		if (tmp < 10)
		{
			s[i] = tmp + '0';
			jinwei = 0;
			break;
		}
		else
		{
			s[i] = tmp - 10 + '0';
			jinwei = 1;
			--i;
		}
	}
	if (jinwei)
	{
		s = "1" + s;
	}
	return s;
}
vector<string> printNumbers_string(int n)   //面试题17. 打印从1到最大的n位数, 这里要考虑n超大的情况
{
	//这个采用数字的字符串+1的方法，一直到字符串+1后位数大于n为止
	if (n == 0)
	{
		return {};
	}
	vector<string> result;
	result.push_back("1");
	string s = "1";
	while (true)
	{
		s = printNumbers_string_plus1(s);
		if (s.size() > n)
		{
			break;
		}
		result.push_back(s);
	}
	return result;
}

vector<string> printNumbers_string_v;  //结果
void printNumbers_string_1_dfs(string s, int n)
{
	if (s.size() == n)
	{
		//先去掉s前面的0
		int i = 0;
		while (i < s.size() && s[i] == '0')
		{
			++i;
		}
		if (i < s.size())  //防止s="000000000"这种情况
		{
			s = s.substr(i);
			printNumbers_string_v.push_back(s);
		}
		return;
	}
	for (char k = '0'; k <= '9'; ++k)
	{
		s.push_back(k);
		printNumbers_string_1_dfs(s, n);  //这一位以k的全都完了，然后弹出k，接下去
		s.pop_back();
	}
}
vector<string> printNumbers_string_1(int n)   //面试题17. 打印从1到最大的n位数, 这里要考虑n超大的情况
{
	//实际上就是0-9，n个数字全排列，只不过要把前面的0去掉
	if (n == 0)
	{
		return {};
	}
	printNumbers_string_1_dfs("", n);
	return printNumbers_string_v;
}

ListNode* deleteNode(ListNode* head, int val)  //面试题18. 删除链表的节点
{
	if (!head)
	{
		return nullptr;
	}
	if (head->val == val)
	{
		head = head->next;
		return head;
	}
	ListNode* result = head;
	while (head->next && head->next->val != val)
	{
		head = head->next;
	}
	if (head->next)  //while中就只能是head->next->val = val跳出来了
	{
		ListNode* tmp = head->next->next;
		head->next = tmp;
	}
	//如果要是head->next跳出来了，就说明当前元素为尾元素，按理说应该要判断一下这个尾元素是否与val相等
	//然后在head为倒数第二个元素的时候，在while中已经判断了倒数第一个元素不等于val，否则head指针不可能向后走
	//所以这里就没有else了
	return result;
}

ListNode* deleteNode_1(ListNode* head, ListNode* p)  //面试题18. 删除链表的节点
{
	//这里p是待删除的节点
	if (!head)  //头指针为空，说明这个p不在链表里
	{
		return nullptr;
	}
	//首先要说明的是，如果p不在所给的链表里，那么需要O(n)的时间来遍历判断是否在不在
	//如果题目要是明确说在，也要看p是否是尾节点
	//假设明确说了在
	if (!p)  //如果p是空
	{
		return head;
	}
	if (p->next)  //p不是尾指针
	{
		//将p->next的值直接覆盖p的值，然后将p指向原先next的next
		ListNode* tmp = p->next->next;
		p->val = p->next->val;
		p->next = tmp;
	}
	else  //尾指针
	{
		if (head == p)  //如果p是头指针
		{
			head = head->next;
		}
		else  //p不是头指针
		{
			ListNode* tmp = head;
			while (tmp->next && tmp->next != p)
			{
				tmp = tmp->next;
			}
			//既然p肯定存在链表中，且是尾指针，那么当tmp为倒数第二个元素时就退出了while
			tmp->next = nullptr;  //直接让倒数第二个元素的下一个为空即可
		}
	}
	return head;
}

ListNode* deleteDuplicates(ListNode* head)  //18的引申--删除排序链表中的重复元素,删除所有重复的元素，使得每个元素只出现一次
{
	if (!head)
	{
		return nullptr;
	}
	//由于重复的元素保留一个即可，因此我们保留第一个
	ListNode* result = head;
	while (head)
	{
		ListNode* n = head->next;
		while (n && n->val == head->val)  //若最后的元素也是重复元素时，n会指向null，则下面的直接head的next指向null
		{
			n = n->next;
		}
		head->next = n;
		head = n;
	}
	return result;
}

ListNode* deleteDuplicates(ListNode* head) //18的引申--删除排序链表中的重复元素 II, 只保留原始链表中 没有重复出现的数字
{
	if (!head || !head->next)
	{
		return head;
	}
	ListNode* result = new ListNode(0);  //哨兵
	ListNode* tmp = result;
	//先看头节点
	if (head->val != head->next->val) //head是唯一的
	{
		result->next = head;  //加入到result后面
		tmp = tmp->next;  //指向待加入后续节点的那个,此时就是head
	}
	//这里要说明的是，如果一个值与前后的值都不相同，那么这个数应该是返回结果的一部分
	ListNode* pre = head;  //如果头指针是唯一的，前面就已经加入了，因此不需要管了
	head = head->next;
	ListNode* n = head->next;
	while (pre && head && n)
	{
		if (head->val != pre->val && head->val != n->val)  //head是唯一的
		{
			tmp->next = head;
			tmp = tmp->next;
		}
		pre = pre->next;
		head = head->next;
		n = n->next;
	}
	//当n为空时候退出来了，此时我们需要看看倒数第一个元素与倒数第二个是否相等，也就是head和pre
	if (head->val != pre->val)  //如果不相等，就说明最后一个元素唯一
	{
		tmp->next = head;
		tmp = tmp->next;
	}
	tmp->next = nullptr; //最后一个指向nullptr
	return result->next;
}

bool isMatch_recursion(string s, string p)
{
	if (p.empty())
	{
		return s.empty();
	}
	if (s.empty())
	{
		if (p.size() > 1 && p[1] == '*')
		{
			return isMatch_recursion(s, p.substr(2));
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (p.size() > 1 && p[1] == '*')
		{
			if (s[0] == p[0] || p[0] == '.')
			{
				//return isMatch_recursion(s.substr(1), p.substr(2)) || isMatch_recursion(s, p.substr(2)) || isMatch_recursion(s.substr(1), p);
				return isMatch_recursion(s, p.substr(2)) || isMatch_recursion(s.substr(1), p);  //匹配一次的时候，也可以跳过s中的这个字符，跳过后，被跳过的字符，就相当于匹配0次
			}
			else
			{
				return isMatch_recursion(s, p.substr(2));
			}
		}
		else
		{
			if (s[0] == p[0] || p[0] == '.')
			{
				return isMatch_recursion(s.substr(1), p.substr(1));
			}
			else
			{
				return false;
			}
		}
	}
}
bool isMatch(string s, string p)  //面试题19. 正则表达式匹配
{
	if (s.size() == 0 && p.size() == 0)
	{
		return true;
	}
	else if (p.size() == 0 && s.size() != 0)
	{
		return false;
	}
	return isMatch_recursion(s, p);
}

bool isNumber(string s)  //面试题20. 表示数值的字符串
{
	if (s.size() == 0)
	{
		return false;
	}
	//消除空格,只能出现在末尾和开头
	while (s.size() && s[0] == ' ')  //消除前面的空格
	{
		s = s.substr(1);
	}
	if (s.size() == 0)  //消除前面的空格之后没了
	{
		return false;
	}
	while (s.size() && s[s.size() - 1] == ' ')  //消除后面的空格
	{
		s.pop_back();
	} 
	if (s.size() == 0)  //消除后面的空格之后没了
	{
		return false;
	}
	int i = 0;
	if (s[i] == '+' || s[i] == '-')  //有正负号
	{
		++i;
	}
	string zhengshu, xiaoshu, zhishu;
	//寻找整数部分
	while (i < s.size())
	{
		if (s[i] >= '0' && s[i] <= '9')  //整数部分只能是0-9，遇到.或e或E要跳出,否则false
		{
			zhengshu = s[i] + zhengshu;
			++i;
		}
		else if (s[i] == '.' || s[i] == 'e' || s[i] == 'E')
		{
			break;
		}
		else
		{
			return false;
		}
	}
	if (i == s.size())  //如果全都是整数
	{
		return true;
	}
	if (s[i] == '.')  //如果跳出来的是小数点，那么小数部分开始
	{
		++i;  //跳过小数点
		while (i < s.size())
		{
			if (s[i] >= '0' && s[i] <= '9')  //小数部分只能是0-9，遇到e或E要跳出，其他字符都为false
			{
				xiaoshu = s[i] + xiaoshu;
				++i;
			}
			else if (s[i] == 'e' || s[i] == 'E')
			{
				break;
			}
			else
			{
				return false;
			}
		}
	}
	if (xiaoshu.size() == 0 && zhengshu.size() == 0)  //小数部分为空且整数部分为空,就类似于.e9这样的，不行，但是1.e9可以
	{
		return false;
	}
	if (i == s.size())  //整数或者小数部分有一个，且i到头了
	{
		return true;
	}
	//如果没到头的话，只能是e或E在某个循环里break了，否则其他字符就会返回false了
	//e或E后面的
	++i; //跳过e或E
	if (i >= s.size())  //e或E是最后一个字符
	{
		return false;
	}
	if (s[i] == '+' || s[i] == '-')  //e或E后面要是有正负号，就跳过
	{
		++i;
	}
	if (i == s.size())  //正负号是最后一个字符
	{
		return false;
	}
	while (i < s.size()) //由于上面判断了e或E是否是最后一个字符，所以能到这里就说明e或E或正负号不是最后一个字符
	{
		if (s[i] >= '0' && s[i] <= '9')  //e或E后面可以是正负号，正负号后面只能是数字
		{
			zhishu = s[i] + zhishu;
			++i;
		}
		else
		{
			return false;
		}
	}
	return true;  //有可能整数小数都没有，如e9，那么此时肯定不行
}

vector<int> exchange(vector<int>& nums)  //面试题21. 调整数组顺序使奇数位于偶数前面
{
	if (nums.size() <= 1)
	{
		return nums;
	}
	int l = 0, r = nums.size() - 1;
	while (l < r)
	{
		//找到左边的
		while (l < r && (nums[l] & 1) == 1)  //遇到偶数要break，遇到奇数要继续
		{
			++l;
		}
		while (l < r && (nums[r] & 1) == 0)  //遇到奇数要break，遇到偶数要继续
		{
			--r;
		}
		if (l < r)
		{
			swap(nums[l], nums[r]);
			++l;
			--r;
		}
	}
	return nums;
}

ListNode* getKthFromEnd(ListNode* head, int k)   //面试题22. 链表中倒数第k个节点
{
	if (k <= 0 || !head)
	{
		return nullptr;
	}
	//定义两个指针
	ListNode* fast = head;
	int i = k;
	while (i > 0 && fast)
	{
		fast = fast->next;
		--i;
	}
	if (i > 0)  //如果i仍然大于0，说明fast为空了，说明还没走出k个距离就空了，说明总数小于k
	{
		return nullptr;
	}
	while (fast)
	{
		fast = fast->next;
		head = head->next;
	}
	return head;
}

ListNode *detectCycle(ListNode *head) //面试题23. 环形链表的入口
{
	//假设从头指针到环入口的长度为l，从环入口到相遇点距离为m，环的剩余部分为n
	//相遇的时候，慢指针走了l+m，快指针走了l+m+n+m=l+2m+n
	//由于快指针速度是慢指针的2倍，所以l+2m+n = 2(l+m)，所以l=n
	//那么现在只需要慢指针再走n步就是环的入口
	//如果此时头指针从头开始走，慢指针从相遇点开始走，两者速度相同
	//由于两者速度相同，且l=n，那么正好当头指针走了l步时慢指针走了l步，也就是n步，而现在正好也就是二者在环的入口相遇了
	//也就是说当两者相遇时，正好就是环的入口
	if (!head || !head->next)
	{
		return nullptr;
	}
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)  //相遇了
		{
			break;
		}
	}
	if (!fast || !fast->next)  //如果fast或下一个为空，说明没有环
	{
		return nullptr;
	}
	while (head != slow)  //两者不相遇就一直走，当两者相遇时，就是到了环的入口
	{
		head = head->next;
		slow = slow->next;
	}
	return head;
}

ListNode* reverseList(ListNode* head)  //面试题24. 反转链表
{
	if (!head)
	{
		return nullptr;
	}
	ListNode* p = nullptr;
	while (head)
	{
		ListNode* tmp = head->next;
		head->next = p;
		p = head;
		head = tmp;
	}
	return p;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)  //面试题25. 合并两个排序的链表
{
	//迭代
	if (!l1)
	{
		return l2;
	}
	if (!l2)
	{
		return l1;
	}
	ListNode* result = new ListNode(0);  //哨兵节点
	ListNode* tmp = result;
	while (l1 && l2)
	{
		if (l1->val <= l2->val)
		{
			tmp->next = l1;
			l1 = l1->next;
		}
		else
		{
			tmp->next = l2;
			l2 = l2->next;
		}
		tmp = tmp->next;
	}
	if (l1)  //l1不为空
	{
		tmp->next = l1;
	}
	else if (l2)
	{
		tmp->next = l2;
	}
	else
	{
		tmp->next = nullptr;
	}
	return result->next;
}

bool isSubStructure_item(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	bool child = false;
	if (A->val == B->val)  //如果值相同,看看左右子节点相不相同，如果相同的话，就往下递归左右子树，否则就不递归
	{
		if ((!A->left && !B->left) || (A->left && !B->left) || (A->left && B->left && A->left->val == B->left->val))  //如果两者左子树都不存在,或者A有B没有，或者都有且值相等
		{
			if ((!A->right && !B->right) || (A->right && !B->right) || (A->right && B->right && A->right->val == B->right->val))
			{
				child = true;
			}
		}
		child = child && isSubStructure_item(A->left, B->left) && isSubStructure_item(A->right, B->right);
	}
	if (child)
	{
		return true;
	}
	return isSubStructure_item(A->left, B) || isSubStructure_item(A->right, B);
}
bool isSubStructure(TreeNode* A, TreeNode* B)  //面试题26. 树的子结构,自己的解法
{
	if (!A || !B)  //约定空树不是任意一个树的子结构
	{
		return false;
	}
	return isSubStructure_item(A, B);
}

bool isSubStructure_item_1_equal(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	if (A->val == B->val)
	{
		return isSubStructure_item_1_equal(A->left, B->left) && isSubStructure_item_1_equal(A->right, B->right);
	}
	else
	{
		return false;
	}
}
bool isSubStructure_item_1(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	bool result = false;
	if (A->val == B->val)  //如果A当前的节点等于B的节点值，那么去看看以A这个节点为根节点的树是否与B匹配,只有左右子树都匹配，才可以
	{
		result = isSubStructure_item_1_equal(A->left, B->left) && isSubStructure_item_1_equal(A->right, B->right);
	}
	if (result)  //如果左右子树都匹配
	{
		return true;
	}
	return isSubStructure_item_1(A->left, B) || isSubStructure_item_1(A->right, B);  //左右子树中有一个能与之匹配即可
}
bool isSubStructure_1(TreeNode* A, TreeNode* B)  //面试题26. 树的子结构
{
	if (!A || !B)  //约定空树不是任意一个树的子结构
	{
		return false;
	}
	return isSubStructure_item_1(A, B);
}

TreeNode* mirrorTree(TreeNode* root)  //面试题27. 二叉树的镜像
{
	if (!root || (!root->left && !root->right))
	{
		return root;
	}
	//左右互换
	TreeNode* tmp = root->left;
	root->left = root->right;
	root->right = tmp;
	//递归把左右子树都镜像
	mirrorTree(root->left);
	mirrorTree(root->right);
	return root;
}

bool isSymmetric_item(TreeNode* A, TreeNode* B)  //A是对称线左边的树，B是对称线右边的树
{
	if (!A && !B)
	{
		return true;
	}
	if ((!A && B) || (A && !B))
	{
		return false;
	}
	if (A->val != B->val)
	{
		return false;
	}
	//对应关系是左边树的左边对应右边树的右边，左边树的右边对应右边树左边
	return isSymmetric_item(A->left, B->right) && isSymmetric_item(A->right, B->left);
}
bool isSymmetric(TreeNode* root)  //面试题28. 对称的二叉树
{
	if (!root || (!root->left && !root->right))
	{
		return true;
	}
	if ((root->left && !root->right) || (!root->left && root->right))
	{
		return false;
	}
	//以上是对于根节点
	return isSymmetric_item(root->left, root->right);
}

vector<int> spiralOrder(vector<vector<int>>& matrix)  //面试题29. 顺时针打印矩阵
{
	if (matrix.size() == 0 || matrix.at(0).size() == 0)
	{
		return {};
	}
	vector< vector<bool> > visited(matrix.size(), vector<bool>(matrix.at(0).size(), false));  //是否被访问了的
	//移动的优先级是右->下->左->上->右->...
	int direction[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	int n = matrix.size(), m = matrix.at(0).size(), i = 0, d = 0; //i是下标，d是当前的方向
	int row = 0, column = 0;  //表示到达的坐标
	vector<int> result(n * m, 0);
	while (i < n * m)
	{
		if (row >= 0 && row < n && column >= 0 && column < m && !visited[row][column])
		{
			result[i] = matrix[row][column];
			visited[row][column] = true;
			row += direction[d][0];
			column += direction[d][1];
			++i; //写入了才要下一个，否则不动等待写入
		}
		else
		{
			//先返回原先的点，然后再变换方向
			row -= direction[d][0];
			column -= direction[d][1];
			//再变换方向
			d = (d + 1) % 4;
			row += direction[d][0];
			column += direction[d][1];
		}
	}
	return result;
}

class MinStack {   // 面试题30. 包含min函数的栈
public:
	int minValue;
	stack<int> s;
	stack<int> tmp; //存放插入到第i个元素时，对应的最小值
	/** initialize your data structure here. */
	MinStack() {
	}

	void push(int x) {
		if (tmp.empty() || x < minValue)  //如果为空或者x较小的话
		{
			minValue = x;
		}
		tmp.push(minValue);  //永远压入当前最小值
		s.push(x);
	}

	void pop() {
		//无论最小值是不是在栈顶，就要把tmp的栈顶清除掉，
		//因为tmp存放的是截至到此时s中的最小值,
		//也就是说s中剩余2个，tmp就应该是剩余两个，因为是截至s中有两个元素时对应的最小值
		if (!s.empty() && !tmp.empty())
		{
			tmp.pop();
			s.pop();
			if (!tmp.empty())
			{
				minValue = tmp.top();
			}
		}
	}

	int top() {
		if (s.empty())
		{
			return -1;
		}
		return s.top();
	}

	int min() {
		return minValue;
	}
};

bool validateStackSequences(vector<int>& pushed, vector<int>& popped)  //面试题31. 栈的压入、弹出序列
{
	if (pushed.size() == 0 && popped.size() == 0)
	{
		return true;
	}
	else if (pushed.size() != popped.size())
	{
		return false;
	}
	stack<int> s;
	int i = 0, j = 0;
	while (i < pushed.size() && j < popped.size())
	{
		while (i < pushed.size() && pushed[i] != popped[j]) //如果当前的i和j不相等，那么就压入栈中，等待一会始放
		{
			s.push(pushed[i]);
			++i;
		}
		//跳过当前相等的，或者没有相等的话，i就超过了pushed的size，就会退出循环
		++i;
		++j;
		while (j < popped.size() && !s.empty() && s.top() == popped[j])  //看看是否可以poped的元素一直在s中
		{
			++j;
			s.pop();
		}
	}
	return (i >= pushed.size() && j >= popped.size() && s.empty());
}

vector<int> levelOrder(TreeNode* root)  //面试题32 - I. 从上到下打印二叉树
{
	if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector<int> result;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector<int> result;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		q.pop();
		result.push_back(root->val);
		if (root->left)
		{
			q.push(root->left);
		}
		if (root->right)
		{
			q.push(root->right);
		}
	}
	return result;
		result.push_back(root->val);
		if (root->left)
		{
			q.push(root->left);
		}
		if (root->right)
		{
			q.push(root->right);
		}
	}
	return result;
}

vector<vector<int>> levelOrder_ii(TreeNode* root)  //面试题32 - II. 从上到下打印二叉树 II
{
	if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector< vector<int> > result;
	q.push(root);
	while (!q.empty())
	{
		int i = q.size();
		vector<int> tmp;
		while (i > 0)
		{
			root = q.front();
			q.pop();
			--i;
			tmp.push_back(root->val);
			if (root->left)
			{
				q.push(root->left);
			}
			if (root->right)
			{
				q.push(root->right);
			}
		}
		result.push_back(tmp);
	}
	return result;
}

vector<vector<int>> levelOrder_iii(TreeNode* root)  //面试题32 - III. 从上到下打印二叉树 III
{
	if (!root)
	{
		return {};
	}
	bool flag = true;  //下一层是否是从左向右
	queue<TreeNode*> q;
	vector< vector<int> > result;
	q.push(root);
	while (!q.empty())
	{
		flag = !flag;
		int i = q.size();
		vector<int> tmp;
		stack<TreeNode*> s;  //假设queue这一层从左往右遍历，那么在加入下一层节点左右孩子时，需要下一层从左往右加入s中，然后再插入到q中
		while (i > 0)
		{
			root = q.front();
			q.pop();
			--i;
			tmp.push_back(root->val);
			if (flag)  //如果下一层是从左往右，那么应该先加入右孩子
			{ 
				if (root->right)
				{
					s.push(root->right);
				}
				if (root->left)
				{
					s.push(root->left);
				}
			}
			else  //如果下一层是从右往左，那么应该先加入左孩子
			{
				if (root->left)
				{
					s.push(root->left);
				}
				if (root->right)
				{
					s.push(root->right);
				}
			}
		}
		while (!s.empty())
		{
			q.push(s.top());
			s.pop();
		}
		result.push_back(tmp);
	}
	return result;
}

vector<vector<int>> levelOrder_iii(TreeNode* root)  //面试题32 - III. 从上到下打印二叉树 III,剑指offer的解法
{
	if (!root)
	{
		return {};
	}
	bool flag = true;  //下一层是否是从左向右
	vector< vector<int> > result;
	vector< stack<TreeNode*> > vs(2); //定义两个栈
	int cur = 0, next = 1;  //当前栈和下一个栈
	vs[0].push(root);
	while (!vs[0].empty() || !vs[1].empty())  //两个栈有一个不为空
	{
		flag = !flag;
		vector<int> tmp;
		int i = vs[cur].size();
		while (i > 0)
		{
			root = vs[cur].top();
			vs[cur].pop();
			--i;
			tmp.push_back(root->val);
			if (flag)  //下一层为左到右,表示这一层的遍历顺序是从右到左,那么应该先加入右孩子，这样栈的顺序就是从左到右
			{
				if (root->right)
				{
					vs[next].push(root->right);
				}
				if (root->left)
				{
					vs[next].push(root->left);
				}
			}
			else  //下一层先右往左，表示这一层是从左向右遍历，那么先加入左孩子,这样栈的顺序就是从右向左
			{
				if (root->left)
				{
					vs[next].push(root->left);
				}
				if (root->right)
				{
					vs[next].push(root->right);
				}
			}
		}
		cur = 1 - cur;  //下一个循环的cur就是1-cur了
		next = 1 - next; //下一个循环的next就是1-next了
		result.push_back(tmp);
	}
	return result;
}

bool verifyPostorder_item(vector<int>& postorder)
{
	if (postorder.size() <= 1)
	{
		return true;
	}
	int rootVal = postorder[postorder.size() - 1];  //后序遍历root值在最后
	bool flag = true;  //是否是左子树的值
	vector<int> l, r;  //左右子树的值序列
	for (int i = 0; i < postorder.size() - 1; ++i)
	{
		if (flag)  //小于root值
		{
			if (postorder[i] > rootVal)  //flag为true，说明是小于root的值，而此时发现了一个大于root值，说明之后应该是右子树的内容
			{
				r.push_back(postorder[i]);
				flag = false;  //此时往后都是右子树的值，因此flag为false
			}
			else
			{
				l.push_back(postorder[i]);
			}
		}
		else //此时往后都是右子树的值,按道理说应该是大于root的值
		{
			if (postorder[i] < rootVal)  //按理说此时应该都是右子树的值,都应该大于root值，但是此时有个值却小于root的值，那么说明不是二叉搜索树
			{
				return false;
			}
			else
			{
				r.push_back(postorder[i]);
			}
		}
	}
	return verifyPostorder_item(l) && verifyPostorder_item(r);  //只有当左右子树都满足条件才是二叉搜索树
}
bool verifyPostorder(vector<int>& postorder)  //面试题33. 二叉搜索树的后序遍历序列
{
	if (postorder.size() <= 1)
	{
		return true;
	}
	return verifyPostorder_item(postorder);
}

vector< vector<int> > pathSum_result;
void pathSum_dfs(int sum, vector<int> tmp, TreeNode* root)
{
	if (!root)
	{
		return;
	}
	tmp.push_back(root->val);  //加入此时的根节点，在路径上
	if (root->val == sum && !root->left && !root->right)  //如果剩余的sum和当前根节点相同，并且此时的节点为叶子节点，那么加入
	{
		pathSum_result.push_back(tmp);
	}
	else  
	{
		//否则，要不就是非叶子节点，虽然有可能存在root->val = sum，但是下面可能有正负的抵消了，因此需要递归下去
		//否则，要不就是root->val != sum,那更应该分别取左右子树寻找,为空的子树就不要走了,都为空就更不需要往下走了
		if (root->left)
		{
			pathSum_dfs(sum - root->val, tmp, root->left);
		}
		if (root->right)
		{
			pathSum_dfs(sum - root->val, tmp, root->right);
		}
	}
}
vector<vector<int>> pathSum(TreeNode* root, int sum)  //面试题34. 二叉树中和为某一值的路径
{
	if (!root)
	{
		return {};
	}
	pathSum_dfs(sum, {}, root);
	return pathSum_result;
}

class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
unordered_map<Node*, Node*> copyRandomList_m;  //存放源节点和复制节点键值对
Node* copyRandomList(Node* head)  //面试题35. 复杂链表的复制
{
	if (!head)
	{
		return head;
	}
	Node* result = new Node(head->val); 
	Node* tmp = result;  //用于连接的临时节点
	Node* head_r = head;  //用于random指针的连接
	//首先根据next，把链表复制出来
	copyRandomList_m.insert(pair<Node*, Node*>(head, result));
	head = head->next;
	while (head)
	{
		Node* t = new Node(head->val);
		tmp->next = t;
		copyRandomList_m.insert(pair<Node*, Node*>(head, t)); //插入键值对
		head = head->next;
		tmp = tmp->next;
	}
	//然后开始赋值random指针
	tmp = result;
	while (head_r && tmp) //他俩相同长度，所以写一个其实也可以
	{
		if (head_r->random && copyRandomList_m.count(head_r->random))  //如果存在
		{
			tmp->random = copyRandomList_m[head_r->random];
		}
		else
		{
			tmp->random = nullptr;
		}
		head_r = head_r->next;
		tmp = tmp->next;
	}
	return result;
}

Node* copyRandomList(Node* head)  //面试题35. 复杂链表的复制,剑指offer做法，空间为O(1)，时间为O(n),我哭了，程序完成后源链表要恢复原样
{
	if (!head)
	{
		return head;
	}
	//复制的节点连接在被复制节点的后面
	Node* tmp = head;
	while (tmp)
	{
		Node* t = new Node(tmp->val);
		t->next = tmp->next;
		tmp->next = t;  //将复制的节点放到被复制节点的后面
		tmp = tmp->next->next;
	}
	//上面就做完了1-1'-2-2'-3-3'这样的
	//接下来进项random的指定,比如1的random指向3，那么只需要让1'的random指向3'
	tmp = head;
	while (tmp)
	{
		if (!tmp->random)  //如果源链表中的random为空，那么复制节点的random也得空
		{
			tmp->next->random = nullptr;
		}
		else  //否则的话，复制节点的random就是源节点random的自身拷贝，也就是源节点random的下一个
		{
			tmp->next->random = tmp->random->next;
		}
		tmp = tmp->next->next;  //指向下一个源链表的节点
	}
	//将复制的节点抽出来,源链表要恢复原样
	Node* result = head->next;
	Node* t = result;
	tmp = head;
	while (t->next)
	{
		tmp->next = t->next;
		tmp = tmp->next;
		t->next = tmp->next;
		t = t->next;
	}
	tmp->next = nullptr;
	return result;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;

	Node() {}

	Node(int _val) {
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};
Node* treeToDoublyList_item(Node* root) //让其内部是双向链表，但是首和尾不能连起来
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		return root;
	}
	Node* l = treeToDoublyList_item(root->left);  //左子树成为双向链表，但是没有首尾相连,中序遍历先遍历左边的
	Node* head = l;
	if (!l)  //左子树为空
	{
		head = root;
	}
	else
	{
		//找到左子树中最靠右的节点
		while (l->right)
		{
			l = l->right;
		}
		//最后一个左子树的节点的后继为root，root的前驱为最后一个左子树中序遍历的节点
		//l为最靠左的节点，因此其左节点为nullptr
		l->right = root;
		root->left = l;
	}
	Node* r = treeToDoublyList_item(root->right);  //右子树成为双向链表，但是没有首尾相连，弄完root和左边的，中序遍历再来右边的
	if(r)  //不能让其首尾相连，因此r为nullptr时候不管了，此时root就是最后一个
	{
		//右子树第一个为root的后继，root的后继为右子树中序遍历第一个
		root->right = r;
		r->left = root;  //r为最靠右的节点，因此其右节点为nullptr，所以主函数中一直往右找循环，不会变成死循环
	}
	return head;
}
Node* treeToDoublyList(Node* root)  //面试题36. 二叉搜索树与双向链表
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		root->left = root;
		root->right = root;
		return root;
	}
	Node* result = treeToDoublyList_item(root); //此时成为一个链表，但是首尾还没连接起来
	Node* tmp = result;
	while (tmp->right)
	{
		tmp = tmp->right;
	}
	tmp->right = result;
	result->left = tmp;
	return result;
}

void treeToDoublyList_inorder(Node* root, stack<Node*> &s)
{
	while (root)
	{
		s.push(root);
		root = root->left;
	}
}
Node* treeToDoublyList(Node* root)  //面试题36. 二叉搜索树与双向链表--迭代中序遍历
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		root->left = root;
		root->right = root;
		return root;
	}
	stack<Node*> s;
	Node* result = new Node(1);  //哨兵节点
	Node* tmp = result;
	while (true)
	{
		treeToDoublyList_inorder(root, s);
		if (s.empty())
		{
			break;
		}
		root = s.top();
		s.pop();
		tmp->right = root;
		root->left = tmp;
		tmp = tmp->right;
		//中序遍历迭代的到右子树
		root = root->right;
	}
	//break后，tmp为最后一个元素
	result = result->right;  //跳过哨兵
	result->left = tmp;
	tmp->right = result;
	return result;
}

class Codec {  //面试题37. 序列化二叉树
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {  //层次遍历序列化--迭代
		if (!root)
		{
			return "[]";
		}
		string s;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			root = q.front();
			q.pop();
			if (!root)  //root为空
			{
				s += "null,";
				continue;
			}
			//不为空的话
			s += std::to_string(root->val);
			s += ",";
			//加入下一级
			q.push(root->left);
			q.push(root->right);
		}
		//消除掉最后的null和逗号
		while (s[s.size() - 1] < '0' || s[s.size() - 1] > '9')
		{
			s.pop_back();
		}
		s = "[" + s + "]";
		return s;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.size() == 0)
		{
			return nullptr;
		}
		while (data.size() > 0 && (data[data.size() - 1] < '0' || data[data.size() - 1] > '9')) //最后不是数字
		{
			data.pop_back();
		}
		if (data.size() == 0)  //如果空了
		{
			return nullptr;
		}
		//消除前面的非数字类字符，负号是算数字字符的
		int i = 0;
		while (i < data.size())
		{
			if ((data[i] >= '0' && data[i] <= '9') || data[i] == '-' || data[i] == '+')
			{
				break;
			}
			++i;
		}
		data = data.substr(i);
		i = 0;
		queue<TreeNode*> q_t; //存储所有的指针
		while (i < data.size())
		{
			string tmp;
			while (i < data.size() && data[i] != ',')
			{
				tmp += data[i];
				++i;
			}
			if (tmp == "null")
			{
				q_t.push(nullptr);
			}
			else if (tmp.size() > 0)
			{
				TreeNode* A = new TreeNode(std::stoi(tmp));
				q_t.push(A);
			}
			++i;
		}
		if (q_t.empty())
		{
			return nullptr;
		}
		TreeNode* root = q_t.front();
		TreeNode* tmp = root;
		q_t.pop();
		queue<TreeNode*> q;  //用于存放已完成的节点
		q.push(root);
		while (!q.empty())
		{
			tmp = q.front();
			q.pop();
			if (!q_t.empty())
			{
				tmp->left = q_t.front();
				q_t.pop();
				if (tmp->left)
				{
					q.push(tmp->left);
				}
			}
			else
			{
				break;
			}
			if (!q_t.empty())
			{
				tmp->right = q_t.front();
				q_t.pop();
				if (tmp->right)
				{
					q.push(tmp->right);
				}
			}
			else
			{
				break;
			}
		}
		return root;
	}
};

void permutation_dfs(string &s, unordered_set<int> &us, unordered_set<string> &st, string &tmp)  //引用更快，快好多
{
	if (tmp.size() == s.size())
	{
		if (!st.count(tmp))
		{
			st.insert(tmp);
		}
		return;
	}
	else if (tmp.size() > s.size())
	{
		return;
	}
	for (int i = 0; i < s.size(); ++i)
	{
		unordered_set<int>::iterator ifind = us.find(i);
		if (ifind == us.end())  //说明当前下标的元素没用
		{
			tmp.push_back(s[i]);
			us.insert(i);
			permutation_dfs(s, us, st, tmp);
			us.erase(i);
			tmp.pop_back();  //tmp也要把当前字符去掉
		}
	}
}
vector<string> permutation(string s)  //面试题38. 字符串的排列
{
	if (s.size() == 0)
	{
		return {};
	}
	if (s.size() == 1)
	{
		return { s };
	}
	unordered_set<string> st; //临时存放结果
	unordered_set<int> us;  //存放下标值是否用过了
	string tmp;  //用于引用
	permutation_dfs(s, us, st, tmp);
	vector<string> result;
	unordered_set<string>::iterator i = st.begin();
	for (; i != st.end(); i++)
	{
		result.push_back(*i);
	}
	return result;
}

int majorityElement(vector<int>& nums)  //面试题39. 数组中出现次数超过一半的数字
{
	//时间复杂度为O(n), 空间O(n)
	if (nums.size() == 0)
	{
		return -1;
	}
	int n = nums.size();
	unordered_map<int, int> um;
	for (int i : nums)
	{
		um[i]++;
		if (um[i] >= n / 2 + 1)
		{
			return i;
		}
	}
	return -1;
}

int majorityElement(vector<int>& nums)  //面试题39. 数组中出现次数超过一半的数字
{
	//时间复杂度为O(n), 空间O(1)
	//貌似是什么投票算法
	if (nums.size() == 0)
	{
		return -1;
	}
	int candidate = nums[0];  //候选人
	int count = 1;  //候选人的次数
	for (int i=1; i<nums.size(); ++i)
	{
		if (count == 0)
		{
			candidate = nums[i];
			count = 1;
		}
		else
		{
			if (nums[i] == candidate)
			{
				++count;
			}
			else
			{
				--count;
			}
		}
	}
	return count > 0 ? candidate : -1;
}

vector<int> getLeastNumbers(vector<int>& arr, int k)  //面试题40. 最小的k个数
{
	if (arr.size() == 0 || k == 0 || k > arr.size())
	{
		return {};
	}
	multiset<int> ms;
	multiset<int>::iterator toDel;
	for (int i : arr)
	{
		if (ms.size() < k)
		{
			ms.insert(i);
		}
		else
		{
			if (i < *(ms.rbegin()))
			{
				toDel = ms.end();
				--toDel;
				ms.erase(toDel);
				ms.insert(i);
			}
		}
	}
	vector<int> result;
	result.assign(ms.begin(), ms.end());
	return result;
}

class MedianFinder {  //面试题41. 数据流中的中位数
public:
	/** initialize your data structure here. */
	vector<int> minHeap, maxHeap; //最小堆和最大堆，满足最小堆里面的数大于等于最大堆里面的数
	MedianFinder() {

	}

	void addNum(int num) {
		if (((minHeap.size() + maxHeap.size()) & 1) == 0)  //如果平均分配了,优先往大顶堆放
		{
			//优先往大顶堆放要注意了，如果这个数比最小堆的堆顶元素(就是最小堆的最小值)大的话，
			//那么应该将这个数放到最小堆里，并且将最小堆的最小数放到最大堆里
			if (minHeap.size() > 0 && num > minHeap[0])  //这个数比最小堆的堆顶元素(就是最小堆的最小值)大
			{
				minHeap.push_back(num);  //放进最小堆
				push_heap(minHeap.begin(), minHeap.end(), greater<int>());  //重新调整堆结构,greater是最小堆的
				num = minHeap[0];  //令num等于最小值
				//pop_heap()不是真的把最大（最小）的元素从堆中弹出来。而是重新排序堆。
				//它把first和last交换，然后将[first, last - 1)的数据再做成一个堆
				pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
				minHeap.pop_back();  //将last处的删掉
			}
			maxHeap.push_back(num);
			push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
		}
		else  //否则往最小堆放
		{
			//这里也要注意，往最小堆放的时候，如果这个值小于最大堆的最大值时，应该放入最大堆中，然后将最大堆的最大值放到最小堆
			if (maxHeap.size() > 0 && num < maxHeap[0])  //这个值小于最大堆的最大值
			{
				maxHeap.push_back(num);
				push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
				num = maxHeap[0];
				pop_heap(maxHeap.begin(), maxHeap.end(), less<int>());
				maxHeap.pop_back();
			}
			minHeap.push_back(num);
			push_heap(minHeap.begin(), minHeap.end(), greater<int>());
		}
	}

	double findMedian() {
		if (minHeap.size() == 0 && maxHeap.size() == 0)
		{
			return 0.0;
		}
		else if (minHeap.size() == 0)
		{
			return maxHeap[0] * 1.0;
		}
		else if (maxHeap.size() == 0)
		{
			return minHeap[0] * 1.0;
		}
		else
		{
			if (((minHeap.size() + maxHeap.size()) & 1) == 0)  //如果是偶数个，那么就是两个堆顶相加除以2
			{
				return (minHeap[0] + maxHeap[0]) * 1.0 / 2.0;
			}
			else  //奇数个
			{
				//因为优先往大顶堆放，因此要去大顶堆寻找
				return maxHeap[0];
			}
		}
	}
};

int maxSubArray(vector<int>& nums)  //面试题42. 连续子数组的最大和
{
	if (nums.size() == 0)
	{
		return 0;
	}
	if (nums.size() == 1)
	{
		return nums[0];
	}
	int result = nums[0];
	int sum = 0;
	for (int i : nums)
	{
		if (i > 0)  //说明对sum有增益作用
		{
			sum += i;
		}
		else  //无增益作用，加上还小于原来的,所以重新开始
		{
			sum = i;
		}
		result = max(result, sum);
	}
	return result;
}

int maxSubArray(vector<int>& nums)  //面试题42. 连续子数组的最大和--动态规划
{
	if (nums.size() == 0)
	{
		return 0;
	}
	if (nums.size() == 1)
	{
		return nums[0];
	}
	vector<int> dp(nums.size(), 0);  //下标第i个数字为结尾的子数组的最大值
	dp[0] = nums[0];
	int result = nums[0];
	for (int i=1; i<nums.size(); ++i)
	{
		if (dp[i - 1] < 0)  //包含第i-1个的字符小于0，那么就舍弃
		{
			dp[i] = nums[i];
		}
		else
		{
			dp[i] = dp[i - 1] + nums[i];
		}
		result = max(result, dp[i]);
	}
	return result;
}

int countDigitOne_item(string s)
{
	//这个也可以这样理解，21345分为1-20000,200001-21345
	//对于200001-21345中的数所有的1其实根1-1345一样，因此这边可以递归求解
	//对于1-20000来说，也即是00001-20000
	//对于最高位万位出现1的次数，有10000-19999共10000个，
	//而万位的数字只能是0或1
	//因此千位的1出现次数位01xxx和11xxx，各有10^3个
	//百位则是0x1xx和1x1xx，各有10^3个
	//十位则是0xx1x和1xx1x，各有10^3个
	//各位则是0xxx1和1xxx1，各有10^3个
	//所以就相当于(0或1)xxxx,把1放到其中一个x上，剩下的x是0-9的全排列，而且有0和1两种，因此就是2 * 4 * 10^3
	//所以就是除最高位外，某一位置1，然后其他非最高位全排列，共有最高位的数字个
	if (s.size() == 0)
	{
		return 0;
	}
	else if (stoi(s) == 0)
	{
		return 0;
	}
	else if (stoi(s) < 10)
	{
		return 1;
	}
	int sum = 0;
	//比如21345，分为1-1345, 1346-21345
	//下面是1346-21345
	//先统计在1在最高位的次数，共有10000-19999个数，
	if (s[0] == '1')
	{
		sum += (stoi(s) - pow(10, s.size() - 1) + 1);
	}
	else if (s[0] > '1' && s[0] <= '9')
	{
		sum += pow(10, s.size() - 1);
	}
	//然后剩下位中的个数，分成两段，分别是1346-11345, 11346-21345
	sum = sum + (s[0] - '0') * (s.size() - 1) * pow(10, s.size() - 2);  //然后统计
	//下面是1-1345
	sum += countDigitOne_item(s.substr(1)); //再统计
	return sum;
}
int countDigitOne(int n)  //面试题43. 1～n整数中1出现的次数,这里要明确11中1出现了两次，不是算1个
{
	if (n <= 0)
	{
		return 0;
	}
	if (n < 10)
	{
		return 1;
	}
	return countDigitOne_item(std::to_string(n));
}

int findNthDigit_item(int n)  //几位数占多少位置，比如2位数共有90个，一个占2个位置，90就占180个位置
{
	if (n == 0)
	{
		return 0;
	}
	else if(n == 1)
	{
		return 10;
	}
	//n位数
	int result = n * pow(10, n - 1);
	return result > INT_MAX / 9 ? INT_MAX : result * 9;
}
int findNthDigit(int n)  //面试题44. 数字序列中某一位的数字
{
	if (n < 0)
	{
		return -1;
	}
	if (n <= 9)
	{
		return n;
	}
	int pre = n;
	int i = 0;
	while (n > 0)
	{
		pre = n;
		++i;
		n -= findNthDigit_item(i);
	}
	//循环退出后，表明所要求的数在i位数中,此时pre表示从第i位数的第一个字开始往后几个
	int tmp = pre / i;  //表明从第一个i位数开始，跳过前面几个i位数
	int mod = pre % i;  //表明跳过前面的i位数之后，要求的数在其所在的i位数中的第几位
	//i位数第一个数是10000(i-1个0),从这个往后数第tmp个i位数,因为是+1递增的，所以直接加上tmp即可
	int begin = pow(10, i - 1);
	begin += tmp;
	string s = std::to_string(begin);
	return s[mod] - '0';
}

static bool minNumber_compare(string &s1, string &s2)  //这里要自定义规则升序,比如参数分别是a和b，要想得到升序排列，那么a < b，那么就要返回true
{
	//这里s1和s2在数组中的顺序是s1在前，s2在后,如果返回true，说明维持当前位置，否则就互换
	if (s1.size() == 0 || s2.size() == 0)
	{
		return false;
	}
	string tmp1 = s1 + s2;  //s2放到s1后面
	string tmp2 = s2 + s1;  //s1放到s2后面
	//比较tmp1和tmp2的大小,可知两者必定是相同长度
	for (int i=0; i<tmp1.size(); ++i)
	{
		if (tmp1[i] > tmp2[i])  //说明应该是s2 + s1的组合，说明在原数组中，s2应该在s1前面，所以应该是返回false，这样就把s2和s1位置互换
		{
			return false;
		}
		else if(tmp1[i] < tmp2[i])
		{
			return true;
		}
	}
	return true;  //tmp1与tmp2相同的话，就把原先在前面的依然放到前面
}
string minNumber(vector<int>& nums)  //面试题45. 把数组排成最小的数
{
	//本质上是定义一种排序规则
	if (nums.size() == 0)
	{
		return "";
	}
	if (nums.size() == 1)
	{
		return std::to_string(nums[0]);
	}
	vector<string> v;
	for (int i : nums)
	{
		v.push_back(std::to_string(i));
	}
	sort(v.begin(), v.end(), minNumber_compare);
	string result;
	for (string s : v)
	{
		result.append(s);
	}
	return result;
}

int translateNum_result = 0;
void translateNum_item(string s, int index)
{
	if (index >= s.size())
	{
		++translateNum_result;
		return;
	}
	//从index开始一个数字或者两个数字
	//一个字符
	int x = s[index] - '0';
	translateNum_item(s, index + 1);
	//两个字符
	if (index < s.size() - 1)  //还能够两个数字
	{
		if (s[index] == '0')  //可能会出现06这种，这样的应该分开0和6，而上面的单字符递归已经这样做了
		{
			return;
		}
		string tmp = s.substr(index, 2);
		x = stoi(tmp);
		if (x <= 25)  //小于25表示有映射的字母
		{
			translateNum_item(s, index + 2);
		}
	}
}
int translateNum(int num) //面试题46. 把数字翻译成字符串
{
	if (num < 0)
	{
		return 0;
	}
	if (num < 10)
	{
		return 1;
	}
	translateNum_item(std::to_string(num), 0);
	return translateNum_result;
}

int maxValue(vector<vector<int>>& grid)
{
	if (grid.size() == 0 || grid.at(0).size() == 0)
	{
		return 0;
	}
	vector< vector<int> > dp(grid.size(), vector<int>(grid.at(0).size(), 0)); //到(i,j)的最大值,因为只能向下和向右，所以(i,j)时候的最大值，只能是dp[i-1][j]和dp[i][j-1]的最大值，加上当前位置的价值
	dp[0][0] = grid[0][0];
	for (int i = 1; i < grid.size(); ++i)  //第一列初始化
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int i=1; i<grid.at(0).size(); ++i)  //第一行初始化
	{
		dp[0][i] = dp[0][i - 1] + grid[0][i];
	}
	for (int i = 1; i < grid.size(); ++i)
	{
		for (int j = 1; j < grid.at(i).size(); ++j)
		{
			dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
		}
	}
	return dp[grid.size() - 1][grid.at(0).size() - 1];
}

int lengthOfLongestSubstring(string s)  //面试题48.最长不含重复字符的子字符串
{
	if (s.size() <= 1)
	{
		return s.size();
	}
	int result = 0;
	unordered_map<char, int> um;  //记录字符最后出现的位置
	for (int i = 0, j = 0; i < s.size(); ++i)  //j是无重复字符的字符串开始位置
	{
		if (um.count(s[i]))  //发现重复字符串
		{
			//那么应该让开始位置置为重复字符串最后出现位置+1和当前值的最大值
			//这里要注意的是，如果um[s[i]] + 1 < j的话，不应该回到um[s[i]] + 1, 
			//因为um[s[i]] + 1到j之间有重复的,否则j也不会是当前的位置，应该在靠前的位置,
			//因为j就是截至到下标i的字符，最大无重复字串的开头，如果um[s[i]] + 1到j当前位置没有重复的话，j应该就是在um[s[i]] + 1处
			//既然这个最大无重复字串开头不是um[s[i]] + 1，说明是有重复的
			j = max(um[s[i]] + 1, j);
		}
		um[s[i]] = i;  //更新或者插入
		result = max(result, i - j + 1);
	}
	return result;
}

int lengthOfLongestSubstring(string s)  //面试题48.最长不含重复字符的子字符串
{
	if (s.size() <= 1)
	{
		return s.size();
	}
	int result = 0;
	unordered_map<char, int> um;  //记录字符最后出现的位置
	vector<int> dp;  //记录包含下标i字符的最大不重复子串
	dp[0] = 1;
	for (int i = 1; i < s.size(); ++i)
	{
		if (um.count(s[i]))
		{
			int d = i - um[s[i]];  //这两个重复字符的距离
			if (d > dp[i - 1]) 
			{
				//大于dp[i-1],说明，这两个重复子串之间还是有其他重复字符,那么就不能是两者之间的长度了
				//并且由于um记录的是此重复字符串在此之前最后出现的位置，说明之间dp[i-1]表示的子串中没有这个字符了
				dp[i] = dp[i - 1] + 1;
			}
			else
			{
				dp[i] = d;
			}
		}
		else
		{
			dp[i] = dp[i - 1] + 1;  //此时这个字符没出现过，直接接到后面
		}
		um[s[i]] = i;  //更新或插入
		result = max(result, dp[i]);
	}
	return result;
}

int nthUglyNumber(int n)  //面试题49. 丑数
{
	if (n <= 0 || n > 1690)
	{
		return -1;
	}
	if (n == 1)
	{
		return 1;
	}
	vector<int> dp(n + 1); //存放第n个丑数
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; ++i)
	{
		dp[i] = INT_MAX;
		//对于第i个丑数，是从第一个到i-1个丑数，三次分别乘2 3 5后，大于dp[i-1]的最小数
		int x = 0, y = 0, z = 0;
		//先乘以2
		for (int j = 1; j < i; ++j)
		{
			x = dp[j] << 1;
			if (x > dp[i - 1])
			{
				break;;
			}
		}
		dp[i] = min(dp[i], x);
		//乘以3
		for (int j = 1; j < i; ++j)
		{
			y = dp[j] * 3;
			if (y > dp[i - 1])
			{
				break;;
			}
		}
		dp[i] = min(dp[i], y);
		//乘以5
		for (int j = 1; j < i; ++j)
		{
			z = dp[j] * 5;
			if (z > dp[i - 1])
			{
				break;;
			}
		}
		dp[i] = min(dp[i], z);
	}
	return dp[n];
}

char firstUniqChar(string s)  //面试题50. 第一个只出现一次的字符
{
	if (s.size() == 0)
	{
		return ' ';
	}
	unordered_map<char, int> um;  //int位出现的次数
	for (char c : s)
	{
		um[c]++;
	}
	unordered_map<char, int>::iterator ifind;
	for (char c : s)
	{
		ifind = um.find(c);
		if (ifind != um.end() && ifind->second == 1)
		{
			return c;
		}
	}
	return ' ';
}

int reversePairs_result = 0;
void reversePairs_mergeSort(vector<int>& nums)
{
	if (nums.size() <= 1)
	{
		return;
	}
	int n = nums.size();
	vector<int> l, r;
	l.assign(nums.begin(), nums.begin() + n / 2);
	r.assign(nums.begin() + n / 2, nums.end());
	reversePairs_mergeSort(l);
	reversePairs_mergeSort(r);
	//合并并看看有多少个
	int i = l.size() - 1, j = r.size() - 1;
	int index = nums.size() - 1;
	while (i >= 0 || j >= 0)
	{
		if (i < 0)  //左边没了，那么逆序对也没了
		{
			nums[index] = r[j];
			--j;
		}
		else if (j < 0)  //右边没了，逆序对也没了
		{
			nums[index] = l[i];
			--i;
		}
		else
		{
			if (l[i] > r[j])
			{
				nums[index] = l[i];
				reversePairs_result += (j + 1);  //对于当前的l[i]，r[j](包括自身之前)都是小于l[i]的，因此都要加上
				--i;
			}
			else
			{
				nums[index] = r[j];
				--j;
			}
		}
		--index;
	}
}
int reversePairs(vector<int>& nums)  //面试题51. 数组中的逆序对
{
	if (nums.size() <= 1)
	{
		return 0;
	}
	reversePairs_mergeSort(nums);
	return reversePairs_result;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)  //面试题52. 两个链表的第一个公共节点
{
	if (!headA || !headB)
	{
		return nullptr;
	}
	ListNode* p1 = headA;
	ListNode* p2 = headB;
	int i = 0, j = 0;
	while (p1 || p2)
	{
		if (p1)
		{
			++i;
			p1 = p1->next;
		}
		if (p2)
		{
			++j;
			p2 = p2->next;
		}
	}
	while (j > i || i > j)
	{
		if (j > i)
		{
			headB = headB->next;
			--j;
		}
		else
		{
			headA = headA->next;
			--i;
		}
	}
	//此时他俩可以往后一起进行
	while (headA && headB && headA != headB)
	{
		headA = headA->next;
		headB = headB->next;
	}
	if (!headA || !headB)  //如果为空了，说明没有
	{
		return nullptr;
	}
	return headA;
}

int search(vector<int>& nums, int target)  //面试题53 - I. 在排序数组中查找数字 I
{
	if (nums.size() == 0)
	{
		return 0;
	}
	int l = 0, r = nums.size() - 1;  //左右边界
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == target)  //如果中间的等于
		{
			if (nums[l] < target)  //如果左边的小于，那么就左边界向后
			{
				++l;
			}
			else if (nums[l] > target) //大于的话就是没有
			{
				return 0;
			}
			else  //如果左边界等于的话
			{
				if (nums[r] == target)  //右边界也等于，就退出，找到了左右边界
				{ 
					break;
				}
				else  //否则话只能是大于target，那么就向左走一个
				{
					--r;
				}
			}
		}
		else if (nums[mid] < target)  //如果中间的小于target
		{
			l = mid + 1;
		}
		else  //如果中间的大于
		{
			r = mid - 1;
		}
	}
	return r - l + 1;  //还要包括左右边界，需要加1
}

int missingNumber(vector<int>& nums)  //面试题53 - II. 0～n-1中缺失的数字
{
	if (nums.size() == 0)
	{
		return 0;
	}
	int n = nums.size();
	n = (n + 1) * n / 2;
	for (int i : nums)
	{
		n -= i;
	}
	return n;
}

int missingNumber(vector<int>& nums)  //面试题53 - II. 0～n-1中缺失的数字
{
	if (nums.size() == 0)
	{
		return 0;
	}
	//二分法
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == mid)
		{
			//因为是排序好的，如果mid和下标一样，说明前面都是一一对应的，否则如果一个缺失，后面的都会错位
			l = mid + 1;
		}
		//nums[mid] < mid，如果前面缺失，那么后面的整体前移，不会出现这种情况，后面缺失也不会这种情况，所以这种不会
		else  //只能是nums[mid] > mid, 就说明mid及其后面都是错位移动过来的，所以缺失的应该在前面
		{
			r = mid - 1;
		}
	}
	return l;
}

int missingNumber(vector<int>& nums)  //面试题53 - II. 0～n-1中缺失的数字
{
	if (nums.size() == 0)
	{
		return 0;
	}
	//二分法
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == mid)
		{
			//因为是排序好的，如果mid和下标一样，说明前面都是一一对应的，否则如果一个缺失，后面的都会错位
			l = mid + 1;
		}
		//nums[mid] < mid，如果前面缺失，那么后面的整体前移，不会出现这种情况，后面缺失也不会这种情况，所以这种不会
		else  //只能是nums[mid] > mid
		{
			if (mid == 0 || nums[mid - 1] == mid - 1)  //如果mid为0，或者前一个元素与其下标相等，那么mid就是缺失的那个
			{
				return mid;
			}
			else  //否则的话，乱序的在前面
			{
				r = mid - 1;
			}
		}
	}
	if (l == nums.size())  //如果l与nums的长度相同，说明缺失的是最后一个元素
	{
		return nums.size();
	}
	return -1;
}

int getNumberSameAsIndex(vector<int>& nums)  //数组中下标和数值相等的元素
{
	//排好序的数组，里面的数字都是唯一的，找到任意一个下标与值相等的元素
	if (nums.size() == 0)
	{
		return 0;
	}
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == mid)
		{
			return mid;
		}
		else if(nums[mid] < mid)
		{
			//如果值小于下标，因为值都是唯一的，向左看的话，下标减小，值也减小，所以左边没有相等的
			l = mid + 1;
		}
		else
		{
			//如果值大于下标，因为值都是唯一的，向右看的话，下标增大，值也增大，所以右边没有相等的
			r = mid - 1;
		}
	}
	return -1;
}

void kthLargestGoAlongRight(TreeNode* root, stack<TreeNode*> &s)
{
	while (root)
	{
		s.push(root);
		root = root->right;
	}
}
int kthLargest(TreeNode* root, int k)
{
	if (!root || k <= 0)
	{
		return -1;
	}
	//我们可以右->根->左这样遍历
	stack<TreeNode*> s;
	while (true)
	{
		kthLargestGoAlongRight(root, s);
		if (s.empty())
		{
			break;
		}
		root = s.top();
		s.pop();
		--k;  //当前元素拿出来了，就要减一
		if (k == 0)
		{
			return root->val;
		}
		root = root->left;
	}
	return -1;
}

int maxDepth(TreeNode* root)  //面试题55 - I.二叉树的深度
{
	if (!root)
	{
		return 0;
	}
	int l = maxDepth(root->left);
	int r = maxDepth(root->right);
	return max(l, r) + 1;
}

bool isBalanced(TreeNode* root)  //面试题55 - II. 平衡二叉树
{
	if (!root || (!root->left && !root->right))
	{
		return true;
	}
	/*
	if (abs(r - l) <= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	*/
	//只判断深度是不行的，因为可能子树内部不行呢
	bool flag_left = isBalanced(root->left);
	bool flag_right = isBalanced(root->right);
	if (flag_left && flag_right)  //左右两者都是平衡的，最后还得看一下深度是否满足
	{
		int l_depth = maxDepth(root->left);
		int r_depth = maxDepth(root->right);
		if (abs(r_depth - l_depth) <= 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool isBalanced_item(TreeNode* root, int &depth)  //depth为当前深度
{
	//后续遍历
	if (!root)
	{
		depth = 0;
		return true;
	}
	if (!root->left && !root->right)
	{
		depth = 1;
		return true;
	}
	int depth_left = 0, depth_right = 0;
	bool flag_left = isBalanced_item(root->left, depth_left);  //返回左子树是否是平衡，并返回深度
	bool flag_right = isBalanced_item(root->right, depth_right);  //返回右子树是否是平衡，并返回深度
	if (flag_left && flag_right && abs(depth_right - depth_left) <= 1)
	{
		depth = max(depth_left, depth_right) + 1;
		return true;
	}
	else
	{
		return false;
	}
}
bool isBalanced(TreeNode* root)  //面试题55 - II. 平衡二叉树
{
	//后续遍历, 遍历的时候记录当前左右子树的深度以及左右子树是否是平衡的
	if (!root || (!root->left && !root->right))
	{
		return true;
	}
	int tmp = 0;
	return isBalanced_item(root, tmp);
}

vector<int> singleNumbers(vector<int>& nums)  //面试题56 - I. 数组中数字出现的次数
{
	if (nums.size() == 0)
	{
		return {};
	}
	int tmp = 0;
	for (int i : nums)
	{
		tmp = tmp ^ i;
	}
	//出来的tmp就是不相同的数字异或的结果，由于两个数字不是同一个，那么异或结果肯定不是0
	//接下来找到tmp的二进制中第一个为1的位置，说明这两个数字的二进制在这一位分别为0和1
	int j = 1;
	while ((tmp & j) == 0)
	{
		j <<= 1;
	}
	//接下来把与j&为0的放一组，为1的放一组，这样就可以把所有数字的二进制在这一位为1的分成一组，为0的为一组,而且重复的数字也正好分配到了一组
	//如能分成4 4 2和3 3 1 这样的两组，这样每组做异或就可以得到
	tmp = 0;
	int temp = 0; //以上两个分别表示j&为0的一组的结果，为1的一组的结果
	for (int i : nums)
	{
		if ((i & j) == 0)
		{
			tmp = tmp ^ i;
		}
		else
		{
			temp = temp ^ i;
		}
	}
	return {tmp, temp};
}

int singleNumber(vector<int>& nums)  //面试题56 - II. 数组中数字出现的次数 II
{
	//哈希表解法
	if (nums.size() == 0)
	{
		return -1;
	}
	unordered_map<int, int> um;
	for (int i : nums)
	{
		um[i]++;
	}
	for (unordered_map<int, int>::iterator i = um.begin(); i != um.end(); i++)
	{
		if (i->second == 1)
		{
			return i->first;
		}
	}
	return -1;
}

int singleNumber(vector<int>& nums)  //面试题56 - II. 数组中数字出现的次数 II
{
	//位运算解法
	//重复三次的数字，他们的二进制每位数字加起来能被3整除，%3剩下的就是单独出现一次的数字的二进制位
	if (nums.size() == 0)
	{
		return -1;
	}
	int bits[32] = { 0 };  //虽然是数组，但是长度为32固定了，相当于建立32个变量,从前往后二进制位增高,就是0下标是2的0次方，下标是2的一次方
	for (int i : nums)
	{
		//对于每个数字，把其二进制位为1的，加入到数组中
		long int b = 1;
		for (int j = 0; j < 32; ++j)
		{
			if ((i & b) == 1)  //说明当前j位为1
			{
				bits[j]++;
			}
			b = b << 1; //右移,不管成不成功，都要看下一位
		}
	}
	//得到的数组每一位%3
	int result = 0;
	for (int i=0; i < 32; ++i)
	{
		int tmp = bits[i];
		tmp %= 3;
		result += (tmp * pow(2, i));
	}
	return result;
}

vector<int> twoSum(vector<int>& nums, int target)  //面试题57. 和为s的两个数字
{
	if (nums.size() <= 1)
	{
		return {};
	}
	if (nums.size() == 2)
	{
		if (nums[0] + nums[1] == target)
		{
			return {nums[0], nums[1]};
		}
		else
		{
			return {};
		}
	}
	//半二分查找
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] >= target)  //省去一半
		{
			r = mid - 1;
		}
		else
		{
			mid = nums[l] + nums[r];
			if (mid == target)
			{
				return { nums[l], nums[r] };
			}
			else if (mid < target)
			{
				++l;
			}
			else
			{
				--r;
			}
		}
	}
	return {};
}

vector<vector<int>> findContinuousSequence(int target)  //面试题57 - II. 和为s的连续正数序列
{
	if (target <= 2)
	{
		return {};
	}
	int l = 1, r = 2;
	vector< vector<int> > result;
	while (l < r)
	{
		//l->r的所有数的和位(l + r) * (r - l + 1) / 2
		int sum = (r + l) * (r - l + 1) / 2;
		if (sum == target)
		{
			vector<int> tmp;
			for (int i=l; i<=r; ++i)
			{
				tmp.push_back(i);
			}
			result.push_back(tmp);
			++l; //加进去之后，说明以l为最左边的序列已经完成使命了，需要向后走看看去
			//++r; //其实这个也可以有，因为，没有这个的话，++l之后，下一个循环l->r的累加值sum肯定小于target了，那么就是++r，所以加上也可以
		}
		else if(sum < target)  //sum小，就往后加一个进来
		{
			++r;
		}
		else  //太大，就去掉最左边的
		{
			++l;
		}
	}
	return result;
}

string reverseWords(string s)  //面试题58 - I. 翻转单词顺序
{
	//清除前后的空格
	while (s.size() > 0 && s[s.size() - 1] == ' ')
	{
		s.pop_back();
	}
	while (s.size() > 0 && s[0] == ' ')
	{
		s = s.substr(1);
	}
	if (s.size() == 0)
	{
		return "";
	}
	string result;
	for (int i = 0; i < s.size(); ++i)
	{
		string tmp;
		while (i < s.size() && s[i] != ' ')
		{
			tmp = tmp + s[i];
			++i;
		}
		if (tmp.size() > 0)
		{
			result = tmp + ' ' + result;
		}
	}
	result.pop_back();  //去掉最后的空格
	return result;
}

void reverseWords_item(string &s)
{
	if (s.size() <= 1)
	{
		return;
	}
	int i = 0, j = s.size() - 1;
	while (i < j)
	{
		swap(s[i], s[j]);
		++i;
		--j;
	}
}
string reverseWords(string s)  //面试题58 - I. 翻转单词顺序
{
	//两步反转
	//清除前后的空格
	while (s.size() > 0 && s[s.size() - 1] == ' ')
	{
		s.pop_back();
	}
	while (s.size() > 0 && s[0] == ' ')
	{
		s = s.substr(1);
	}
	if (s.size() <= 2)  //空了或只剩下一个字符或两个字符，返回
	{
		return s;
	}
	reverseWords_item(s); //翻转一次，abcd efg变成了 gfe dcba,然后每个单词反转
	string result;
	for (int i = 0; i < s.size(); ++i)
	{
		string tmp;
		while (i < s.size() && s[i] != ' ')
		{
			tmp.push_back(s[i]);
			++i;
		}
		if (tmp.size() > 0)
		{
			reverseWords_item(tmp);
			result = result + ' ' + tmp;
		}
	}
	result = result.substr(1);  //去掉前面的空格
	return result;
}

string reverseLeftWords(string s, int n)  //面试题58 - II. 左旋转字符串
{
	if (s.size() == 0 || n >= s.size())
	{
		return s;
	}
	string s1 = s.substr(0, n), s2 = s.substr(n);
	s2.append(s1);
	return s2;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k)  //面试题59 - I. 滑动窗口的最大值
{
	//暴力法
	if (nums.size() == 0)
	{
		return {};
	}
	vector<int> result;
	for (int i = 0; i < nums.size() - k + 1; ++i)
	{
		int maxValue = INT_MIN;
		for (int j = 0; j < k && j + i < nums.size(); ++j)
		{
			maxValue = max(maxValue, nums[j + i]);
		}
		result.push_back(maxValue);
	}
	return result;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k)  //面试题59 - I. 滑动窗口的最大值
{
	//双端队列
	if (nums.size() <= 1)
	{
		return nums;
	}
	deque<int> d; //存值的下标
	vector<int> result;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (d.empty())  //d为空，直接加进去
		{
			d.push_back(i);
		}
		else
		{
			while (!d.empty() && nums[d.back()] <= nums[i])  //把前面比他小的去掉
			{
				d.pop_back();
			}
			d.push_back(i); //加入进去，有可能是后面的最大值
			while (!d.empty() && i - d.front() > k - 1)  //如果前几个已经超过了窗口的范围，就踢出去
			{
				d.pop_front();
			}
		}
		if (i >= k - 1)  //保证刚开始的窗口要等到够了k个数再加入最大值进结果
		{
			result.push_back(nums[d.front()]);
		}
	}
	return result;
}

class MaxQueue {  //面试题59 - II. 队列的最大值
public:
	deque<int> d; //辅助双端队列，用于存放以某元素为开头得最大值
	queue<int> q;
	MaxQueue() {

	}

	int max_value() {
		if (d.empty() || q.empty())  //如果为空，直接返回-1
		{
			return -1;
		}
		return d.front();  //否则返回d
	}

	void push_back(int value) {
		q.push(value);  //q直接加入
		while (!d.empty() && d.back() < value) //把前面比当前元素小的都清除掉，那个当前元素就是以那些比他小的，前面的元素为开头的后面元素的最大值
		{
			d.pop_back();
		}
		d.push_back(value);
	}

	int pop_front() {
		if (q.empty())
		{
			return -1;
		}
		int result = q.front();
		q.pop();
		if (result == d.front())  //如果最大元素在队首，那么就得清除掉，使得d中剩下的头元素为剩下元素的最大值
		{
			d.pop_front();
		}
		return result;
	}
};

vector<double> twoSum(int n)  //面试题60. n个骰子的点数
{
	if (n <= 0)
	{
		return {};
	}
	if (n == 1)
	{
		return { 0.16667,0.16667,0.16667,0.16667,0.16667,0.16667 };
	}
	vector< vector<double> > dp; //投掷i个骰子的点数之和的概率
	//假设已经投掷了i-1个骰子，并且概率已知了
	//i个骰子的和s的范围是[i, 6i]，i-1个骰子的和s范围是[i-1, 6i-6]
	//所以对于任意的点数之和x，x属于[i, 6i]，出现x的概率
	//就是i-1个骰子投出和x-1,此次投出1，i-1个骰子投出和x-2,此次投出2。。。。
	//f(i)(x)表示，投掷了i个骰子，得到和为x
	//所以f(i)(x) = f(i-1)(x-1)*(1/6) + f(i-1)(x-2)*(1/6) + .... + f(i-1)(x-6)*(1/6)
	dp.push_back({});
	dp.push_back({ 0.166667,0.166667,0.166667,0.166667,0.166667,0.166667 }); //这里多写一位啊，否则最后精度会出问题，那样就得用出现的次数/总数
	for (int i = 2; i <= n; ++i) //投掷两个骰子到投掷n个骰子
	{
		vector<double> tmp(5 * i + 1, 0);
		//值应该是[i, 6i]，即j+i，这里简化为[0, 5i], i-1时候就是[0,5i-5]
		//i-1时，应为[i-1, 6i-6],因此计算i-1的时候，其实际和值应该是j+i-k，属于[i-1, 6i-6],
		//映射到[0,5i-5],就是j+i-k-(i-1) = j + 1 - k，就是i-1时候的vectot下标
		for (int j = 0; j <= 5 * i; ++j)
		{
			//当前和为j+i的时候，等于i-1个骰子中相应的加起来
			for (int k = 1; k <= 6; ++k)
			{
				if (j + 1 - k >= 0)
				{
					if (j + 1 - k <= 5 * i - 5)  //超过的话也不能要，但是随着k增加，会减小，所以不能break
					{
						tmp[j] = dp[i - 1][j + 1 - k] * (1.0 / 6) + tmp[j]; //这里
					}
				}
				else  //接下来k增大还是会继续小于0，所以直接break
				{
					break;
				}
			}
		}
		dp.push_back(tmp);
	}
	return dp[n];
}

bool isStraight(vector<int>& nums)  //面试题61. 扑克牌中的顺子
{
	//记录0的个数，记录最大最小值
	//统计最大最小值之间缺少几个
	//如果缺少的小于等于0的个数，那么就可以，否则false
	//如果有重复的数字，那肯定不是顺子了
	if (nums.size() == 0)
	{
		return false;
	}
	sort(nums.begin(), nums.end());
	int count = 0;  //统计0的个数
	int ma = INT_MIN, mi = INT_MAX;  //排好序的数的最大最小值
	unordered_set<int> us;
	//统计0的个数，以及非0的放到一个哈希表里，并且找到最大最小值
	for (int i : nums)
	{
		if (i == 0)
		{
			++count;
		}
		else
		{
			ma = max(ma, i);
			mi = min(mi, i);
			if (!us.count(i))
			{
				us.insert(i);
			}
			else  //如果有重复的，肯定不是顺子
			{
				return false;
			}
		}
	}
	//看看最大最小值之间缺少多少个
	int sum = 0;
	for (int i = mi + 1; i < ma; ++i)
	{
		if (!us.count(i))
		{
			++sum;
		}
	}
	//如果缺少的个数少于等于0的个数，那么就可以用0来代替，因为0能代替任意数，否则false
	return (sum <= count);
}

int lastRemaining(int n, int m)  //面试题62. 圆圈中最后剩下的数字,超时了
{
	//环形链表
	if (n < 1 || m < 1)
	{
		return -1;
	}
	list<int> li;
	for (int i = 0; i < n; ++i)  //创建链表
	{
		li.push_back(i);
	}
	list<int>::iterator index = li.begin();  //从链表开头开始
	int num = m % n;
	while (li.size() > 1)  //如果不剩下最后一个数字，就要继续
	{
		int i = 1;
		while (i < num) //一直往后找
		{
			++i;
			++index;
			if (index == li.end())  //到头了就重新开始
			{
				index = li.begin();
			}
		}
		list<int>::iterator next = ++index;  //记录下一个指针
		li.erase(--index);  //删除掉当前指针
		index = next;  //赋值下一个指针
		if (index == li.end())  //如果是到头了，就重新开始
		{
			index = li.begin();
		}
		num = m % li.size(); 
	}
	return *(index);
}

int lastRemaining(int n, int m)  //面试题62. 圆圈中最后剩下的数字
{
	//递推公式，见剑指offer
	if (n < 1 || m < 1)
	{
		return -1;
	}
	int last = 0;
	for (int i = 2; i <= n; ++i)
	{
		last = (last + m) % i;  //i从2到n，这里递推式上应该是%i，不能一直写成n
	}
	return last;
}

int maxProfit(vector<int>& prices)  //面试题63. 股票的最大利润
{
	if (prices.size() < 2)
	{
		return 0;
	}
	int minPrice = prices[0];
	int result = 0;
	for (int i = 1; i < prices.size(); ++i)
	{
		if (prices[i] < minPrice)
		{
			minPrice = prices[i];
		}
		else
		{
			result = max(result, prices[i] - minPrice);
		}
	}
	return result;
}

int maxProfit(vector<int>& prices)  //面试题63. 股票的最大利润
{
	if (prices.size() < 2)
	{
		return 0;
	}
	vector<int> dp(prices.size(), 0); //在第i天卖出，能够获得的最大利润
	dp[0] = 0;
	int minPrice = prices[0];
	int result = 0;
	for (int i = 1; i < prices.size(); ++i)
	{
		if (prices[i] < minPrice)
		{
			minPrice = prices[i];
		}
		else
		{
			dp[i] = prices[i] - minPrice;  //在第i天卖出，得到的最大值，应该减去之前元素的最小值
		}
		result = max(result, dp[i]);
	}
	return result;
}

int sumNums(int n)  //面试题64. 求1+2+…+n
{
	n && (n += sumNums(n - 1));  //短路特性，n为0的时候，后面就不会计算了,就不会递归下去了
	return n;
}

int add(int a, int b)  //面试题65. 不用加减乘除做加法
{
	if (a == 0)
	{
		return b;
	}
	if (b == 0)
	{
		return a;
	}
	//这里必须要转化为unsigned int
	unsigned int x = a, y = b; //x模拟加法，但是没有进位，y与运算，只有同为1的那一位才为1，并且需要向前进位，进位的话需要左移一位
	while (y != 0)
	{
		int tmp = x ^ y;
		y = (x & y) << 1;
		x = tmp;
	}
	return x;
}

vector<int> constructArr(vector<int>& a)
{
	if (a.size() == 0)
	{
		return {};
	}
	//定义一个两个数组v1和v2存储当前为i的时候a[0]xa[1]xa[2]....xa[i-1]和a[i+1]xa[i+2]...xa[n-1]
	//这样的话，v1[i] = v1[i - 1] * a[i - 1], v2[i] = v2[i + 1] * a[i + 1], 可以用一次循环即可
	//当i为0时，相当于把v1[0] = 1; i为s.size() - 1时，v2[a.size() - 1] = 1,这样在计算结果时候，就是乘了1，相当于没乘，符合题意
	vector<int> v1(a.size(), 1);
	vector<int> v2(a.size(), 1);
	int n = a.size();
	for (int k = 1; k < a.size(); ++k)
	{
		v1[k] = v1[k - 1] * a[k - 1];
		v2[n - k - 1] = v2[n - k] * a[n - k];
	}
	for (int i = 0; i < v1.size(); ++i)
	{
		v1[i] = v1[i] * v2[i];
	}
	return v1;
}

int strToInt(string str)  //面试题67. 把字符串转换成整数
{
	//清除最后的空格
	while (str.size() > 0 && str[str.size() - 1] == ' ')
	{
		str.pop_back();
	}
	while (str.size() > 0 && str[0] == ' ')
	{
		str = str.substr(1);
	}
	if (str.size() == 0)
	{
		return 0;
	}
	bool flag = true; //是否为正数
	int i = 0;
	//跳过正负号
	if (str[0] == '-')
	{
		flag = false;
		++i;
	}
	else if (str[0] == '+')
	{
		++i;
	}
	//跳过后如果没了或者去掉正负号后第一个字符不是数字字符，就返回0, 
	if (i >= str.size() || str[i] < '0' || str[i] > '9')
	{
		return 0;
	}
	int result = 0;
	while (i < str.size())
	{
		if (str[i] < '0' || str[i] > '9')  //第一个循环时候肯定不是
		{
			break;
		}
		int tmp = str[i] - '0';
		if (result > INT_MAX / 10)
		{
			return flag ? INT_MAX : INT_MIN;
		}
		else if (result == INT_MAX / 10)
		{
			if (flag && tmp >= 7)  //如果是正数，而且要加的值大于等于7了，也就是乘10加tmp后大于等于INT_MAX，直接返回最大值即可
			{
				return INT_MAX;
			}
			else if (!flag && tmp >= 8) //如果是负数，而且绝对值乘10加的值大于等于8，那么直接返回INT_MIN
			{
				//如果这里tmp=7时，绝对值就到了INT_MAX,但是还没溢出，不要紧,所以不能返回INT_MIN
				return INT_MIN;
			}
			else
			{
				result = result * 10 + tmp;
			}
		}
		else
		{
			result = result * 10 + tmp;
		}
		++i;
	}
	return flag ? result : -result;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)  //面试题68 - I. 二叉搜索树的最近公共祖先
{
	if (!root)
	{
		return nullptr;
	}
	if (!p)
	{
		return q;
	}
	if (!q)
	{
		return p;
	}
	if (p == q)
	{
		return p;
	}
	if (p == root || q == root)
	{
		return root;
	}
	if ((p->val <= root->val && q->val >= root->val) || (p->val >= root->val && q->val <= root->val))
	{
		return root;
	}
	else if (p->val <= root->val && q->val <= root->val)
	{
		return lowestCommonAncestor(root->left, p, q);
	}
	else
	{
		return lowestCommonAncestor(root->right, p, q);
	}
}

bool lowestCommonAncestor_item(TreeNode* root, TreeNode* &destiny, vector<TreeNode*> &v) //root指上一步添加的
{
	if (!root || !destiny)
	{
		v.clear();
		return false;
	}
	if (root == destiny)  //在这里判断上一步递归添加的那个节点是否与目标节点同一个，这样的话，上一步递归中只需要pop_back一步即可，否则需要循环pop_back, 其实是一样的
	{
		return true;
	}
	bool flag = false;  //是否找到了目标节点的路径
	if (root->left)  //去左节点寻找
	{
		v.push_back(root->left);
		flag = lowestCommonAncestor_item(root->left, destiny, v);
		if (flag)  //如果成功，直接返回
		{
			return true;
		}
		else
		{
			v.pop_back();
		}
	}
	if (root->right) //右节点存在
	{
		v.push_back(root->right);
		flag = lowestCommonAncestor_item(root->right, destiny, v);
		if (flag)  //如果成功，直接返回
		{
			return true;
		}
		else
		{
			v.pop_back();
		}
	}
	return false;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)  //面试题68 - II. 二叉树的最近公共祖先
{
	if (!root)
	{
		return nullptr;
	}
	if (!p)
	{
		return q;
	}
	if (!q)
	{
		return p;
	}
	if (p == q)
	{
		return p;
	}
	if (p == root || q == root)
	{
		return root;
	}
	//找寻路径
	vector<TreeNode*> v1; //p的路径
	vector<TreeNode*> v2; //q的路径
	//先添加再去判断
	v1.push_back(root);
	v2.push_back(root);
	lowestCommonAncestor_item(root, p, v1);
	lowestCommonAncestor_item(root, q, v2);
	TreeNode* result = root;
	for (int i = 0, j = 0; i < v1.size() && j < v2.size(); ++i, ++j)
	{
		if (v1[i] != v2[j])
		{
			break;;
		}
		result = v1[i];
	}
	return result;
}

bool lowestCommonAncestor_item(TreeNode* root, TreeNode* &destiny, vector<TreeNode*> &v)
{
	if (!root || !destiny)
	{
		v.clear();
		return false;
	}
	v.push_back(root);
	if (root == destiny)  //在这里判断上一步递归添加的那个节点是否与目标节点同一个，这样的话，上一步递归中只需要pop_back一步即可，否则需要循环pop_back, 其实是一样的
	{
		return true;
	}
	bool flag = false;  //是否找到了目标节点的路径
	if (root->left)  //去左节点寻找
	{
		flag = lowestCommonAncestor_item(root->left, destiny, v);
		if (flag)  //如果成功，直接返回
		{
			return true;
		}
		else
		{
			v.pop_back();
		}
	}
	if (root->right) //右节点存在
	{
		flag = lowestCommonAncestor_item(root->right, destiny, v);
		if (flag)  //如果成功，直接返回
		{
			return true;
		}
		else
		{
			v.pop_back();
		}
	}
	return flag;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)  //面试题68 - II. 二叉树的最近公共祖先
{
	if (!root)
	{
		return nullptr;
	}
	if (!p)
	{
		return q;
	}
	if (!q)
	{
		return p;
	}
	if (p == q)
	{
		return p;
	}
	if (p == root || q == root)
	{
		return root;
	}
	//找寻路径
	vector<TreeNode*> v1; //p的路径
	vector<TreeNode*> v2; //q的路径
	lowestCommonAncestor_item(root, p, v1);
	lowestCommonAncestor_item(root, q, v2);
	TreeNode* result = root;
	for (int i = 0, j = 0; i < v1.size() && j < v2.size(); ++i, ++j)
	{
		if (v1[i] != v2[j])
		{
			break;;
		}
		result = v1[i];
	}
	return result;
}

int main()
{
	//面试题03. 数组中重复的数字
	//findRepeatNumber

	//面试题04. 二维数组中的查找
	//findNumberIn2DArray

	//面试题05. 替换空格
	//replaceSpace

	//面试题06. 从尾到头打印链表
	//reversePrint

	//面试题07. 重建二叉树
	//buildTree

	//二叉树的下一个结点---在牛客上
	//GetNext

	//面试题09. 用两个栈实现队列
	//CQueue

	//用队列实现栈--09的引申题

	//面试题10- I. 斐波那契数列
	//fib

	//面试题10- II. 青蛙跳台阶问题
	//numWays

	//面试题11. 旋转数组的最小数字
	//minArray

	//面试题12. 矩阵中的路径
	//exist

	//面试题13. 机器人的运动范围
	//movingCount

	//面试题14- I. 剪绳子
	//cuttingRope

	//面试题14- II. 剪绳子 II
	//cuttingRope

	//面试题15. 二进制中1的个数
	//hammingWeight

	//面试题16. 数值的整数次方
	//myPow

	//面试题17. 打印从1到最大的n位数
	//printNumbers

	//面试题18. 删除链表的节点
	//deleteNode

	//18的引申--删除排序链表中的重复元素,删除所有重复的元素，使得每个元素只出现一次
	//deleteDuplicates

	//18的引申--删除排序链表中的重复元素 II, 只保留原始链表中 没有重复出现的数字

	//面试题19. 正则表达式匹配
	//isMatch

	//面试题20. 表示数值的字符串
	//isNumber

	//面试题21. 调整数组顺序使奇数位于偶数前面
	//exchange

	//面试题22. 链表中倒数第k个节点
	//getKthFromEnd

	//面试题23. 环形链表的入口
	//detectCycle

	//面试题24. 反转链表
	//reverseList

	//面试题25. 合并两个排序的链表
	//mergeTwoLists

	//面试题26. 树的子结构
	//isSubStructure

	//面试题27. 二叉树的镜像
	//mirrorTree

	//面试题28. 对称的二叉树
	//isSymmetric

	//面试题29. 顺时针打印矩阵
	//spiralOrder

	//面试题30. 包含min函数的栈
	//class MinStack

	//面试题31. 栈的压入、弹出序列
	//validateStackSequences

	//面试题32 - I. 从上到下打印二叉树
	//levelOrder

	//面试题32 - II. 从上到下打印二叉树 II
	//levelOrder_ii

	//面试题32 - III. 从上到下打印二叉树 III
	//levelOrder_iii

	//面试题33. 二叉搜索树的后序遍历序列
	//verifyPostorder

	//面试题34. 二叉树中和为某一值的路径
	//pathSum

	//面试题35. 复杂链表的复制
	//copyRandomList

	//面试题36. 二叉搜索树与双向链表
	//treeToDoublyList

	//面试题37. 序列化二叉树
	//class Codec

	//面试题38. 字符串的排列
	//permutation

	//面试题39. 数组中出现次数超过一半的数字
	//majorityElement

	//面试题40. 最小的k个数
	//getLeastNumbers

	//面试题41. 数据流中的中位数
	//class MedianFinder

	//面试题42. 连续子数组的最大和
	//maxSubArray

	//面试题43. 1～n整数中1出现的次数
	//countDigitOne

	//面试题44. 数字序列中某一位的数字
	//findNthDigit

	//面试题45. 把数组排成最小的数
	//minNumber

	//面试题46. 把数字翻译成字符串
	//translateNum

	//面试题47. 礼物的最大价值
	//maxValue

	//面试题48. 最长不含重复字符的子字符串
	//lengthOfLongestSubstring

	//面试题49. 丑数
	//nthUglyNumber

	//面试题50. 第一个只出现一次的字符
	//firstUniqChar

	//面试题51. 数组中的逆序对
	//reversePairs

	//面试题52. 两个链表的第一个公共节点
	//getIntersectionNode

	//面试题53 - I. 在排序数组中查找数字 I
	//search

	//面试题53 - II. 0～n-1中缺失的数字
	//missingNumber

	//53引申--数组中下标和数值相等的元素
	//getNumberSameAsIndex

	//面试题54. 二叉搜索树的第k大节点
	//kthLargest

	//面试题55 - I. 二叉树的深度
	//maxDepth

	//面试题55 - II. 平衡二叉树
	//isBalanced

	//面试题56 - I. 数组中数字出现的次数
	//singleNumbers

	//面试题56 - II. 数组中数字出现的次数 II
	//singleNumber

	//面试题57. 和为s的两个数字
	//twoSum

	//面试题57 - II. 和为s的连续正数序列
	//findContinuousSequence

	//面试题58 - I. 翻转单词顺序
	//reverseWords

	//面试题58 - II. 左旋转字符串
	//reverseLeftWords

	//面试题59 - I. 滑动窗口的最大值
	//maxSlidingWindow

	//面试题59 - II. 队列的最大值
	//MaxQueue

	//面试题60. n个骰子的点数
	//twoSum

	//面试题61. 扑克牌中的顺子
	//isStraight

	//面试题62. 圆圈中最后剩下的数字
	//lastRemaining

	//面试题63. 股票的最大利润
	//maxProfit

	//面试题64. 求1+2+…+n
	//sumNums

	//面试题65. 不用加减乘除做加法
	//add

	//面试题66. 构建乘积数组
	//constructArr

	//面试题67. 把字符串转换成整数
	//strToInt

	//面试题68 - I. 二叉搜索树的最近公共祖先
	//lowestCommonAncestor

	//面试题68 - II. 二叉树的最近公共祖先
	//lowestCommonAncestor
	return 0;
}