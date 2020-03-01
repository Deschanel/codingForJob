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
	return 0;
}