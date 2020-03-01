#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <stack>
#include <queue>
using namespace std;

int findRepeatNumber_1(vector<int>& nums)    ////������03. �������ظ�������
{
	//ԭ���㷨,��sort����󣬲��ҵ�ǰ���һ����ͬ������
	if (nums.size() <= 1)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());  //ʱ��O(nlogn)
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

int findRepeatNumber_2(vector<int>& nums)    ////������03. �������ظ�������
{
	//ʹ��unorder_set������֮ǰ�Ƿ��Ѿ����ˣ��ռ�O(n)��ʱ��O(n)
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

int findRepeatNumber_3(vector<int>& nums)    ////������03. �������ظ�������
{
	//���Ҫ��û���ظ��Ļ����±���ֵӦ�����
	//�±�Ϊi��ֵΪm����m==i����������������ȵĻ������Ǿ�ȥ���±�Ϊm����k�����k=m�Ļ����ظ��˷���
	//������ȵĻ�����m��k������Ҳ����m�ŵ��±�Ϊm��λ�ã�k�ŵ��±�Ϊi��λ�ã���ȥ���±�Ϊk����n���������ϲ���
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
	//��ʣ��������Ͻ��Ǹ���m���������ֱ�ӷ��أ�
	//���m����target����ôm����һ���޳���Ҳ���Ǵ�ʱӦ�ÿ���mͬ�е���������
	//���С�ڣ���m�����б��޳�����ʱҪ����mͬ�е��������
	//ѭ������ִ����ȥ
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

string replaceSpace_1(string s)  //������05. �滻�ո�
{
	//ԭ���㷨����s���ݣ�Ȼ��һ��ָ��p1��ԭ��δ���ݵ��ַ��������һ���ַ���ǰ��һ��ָ��p2�����ݺ���ַ����һ��λ����ǰ
	//���p1ָ���ֵ��Ϊ�ո���ô�Ͱ����ֵ��ֵ��p2ָ���λ�ã�
	//������ڿո���ôp2��ǰ�ֱ����02%��Ȼ����������ǰ��,ֱ��p1���˵�0���ַ�
	//���ڰѿո�ת��Ϊ%20��1����Ϊ������Ҳ����˵һ���ո��Ҫ�������2���ַ��ĳ��ȣ�����count���ո񣬾�Ҫ�������2*count������
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

string replaceSpace_2(string s)  //������05. �滻�ո�
{
	//��ԭ���㷨
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

vector<int> reversePrint_1(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��¼����ĳ��ȣ�Ȼ�󿪱�һ���˳��ȵ����飬Ȼ�������ͷ������ֵ�������дӺ���ǰд
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

vector<int> reversePrint_2(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��ջ
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

vector<int> reversePrint_3(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��ת����
	if (!head)
	{
		return {};
	}
	ListNode* p = nullptr;
	while (head)
	{
		ListNode* tmp = head->next;
		head->next = p;
		p = head;  //��tmpΪnullptrʱ����һ��ѭ���ͽ���ȥ�ˣ�headΪnullptr�ˣ���p�Ǵ�ʱ��ͷԪ��
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
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)  //������07. �ؽ�������
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
TreeLinkNode* GetNext(TreeLinkNode* pNode)  //����������һ�����---��ţ����
{
	//�����pNode�����Ǹ��ڵ㣬���Ƕ��������������һ���ڵ㣬����������������
	if (!pNode)
	{
		return nullptr;
	}
	TreeLinkNode* p = nullptr;
	if (pNode->right)   //���������������ô��һ���ڵ����������������ߵĽڵ�
	{
		p = pNode->right;
		while (p->left)
		{
			p = p->left;
		}
	}
	else if (pNode->next)  //��������������ڣ��Ҹ��ڵ����
	{
		p = pNode->next;  //ָ�򸸽ڵ�
		//������ڵ����ڵ���pNode����ô��һ���ڵ���Ǿ��Ǹ��ڵ�
		//������ڵ���ҽڵ���pNode����ô�������ң�ֱ�������ҵ���ĳ���ڵ�i��i�ĸ��ڵ����ڵ㣬��ô��һ���ڵ����i�ĸ��ڵ�
		while (p && pNode == p->right)
		{
			pNode = p;
			p = p->next;
		}
	}
	return p;
}

class CQueue_1 {       //������09. ������ջʵ�ֶ���
//ɾ��ʱ������һ����ʱջ���򱣴�s�е�Ԫ�أ���ô��ʱջ�Ķ�������Ҫɾ����Ԫ�أ�ɾ��֮���ٰ�Ԫ�ط��ص�s��
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

class CQueue_2 {       //������09. ������ջʵ�ֶ���
//����ջ��һ���ܲ��룬һ����ɾ��
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

class MyStack_1 {   //�ö���ʵ��ջ--09��������
//����ʱ��ֱ�Ӳ��룬ɾ��ʱ������ʱ����
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

class MyStack_2 {   //�ö���ʵ��ջ--09��������
//�ĸ���Ϊ�վͲ��뵽�ĸ�����
//������popɾ��ʱ�򣬿���ѭ�����뵽��һ��Ϊ�յģ�ѭ�������һ��Ԫ��ʱ�򲻷���
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

int fib(int n)   //������10- I. 쳲���������
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
		if (p > 1000000007 - cur)   //��ĿҪ�����Ҫȡģ 1e9+7��1000000007��
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int numWays(int n)  //������10- II. ������̨������
{
	if (n <= 1)
	{
		return 1;
	}
	int p = 1, cur = 1;
	for (int i=2; i<=n; ++i)
	{
		if (p > 1000000007 - cur) //��ĿҪ�����Ҫȡģ 1e9+7��1000000007��
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int main()
{
	//������03. �������ظ�������
	//findRepeatNumber

	//������04. ��ά�����еĲ���
	//findNumberIn2DArray

	//������05. �滻�ո�
	//replaceSpace

	//������06. ��β��ͷ��ӡ����
	//reversePrint

	//������07. �ؽ�������
	//buildTree

	//����������һ�����---��ţ����
	//GetNext

	//������09. ������ջʵ�ֶ���
	//CQueue

	//�ö���ʵ��ջ--09��������

	//������10- I. 쳲���������
	//fib

	//������10- II. ������̨������
	//numWays
	return 0;
}