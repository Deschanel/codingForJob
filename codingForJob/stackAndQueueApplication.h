#pragma once
#include "common.h"
#include <stack>

using namespace std;

class stackAndQueueApplication
{
public:
	stackAndQueueApplication() {}
	~stackAndQueueApplication() {}
	void convert(int n, int base);  //����ת��
	bool kuohaoMatch();  //����ƥ��
	bool zhanhunxi();   //ջ��ϴ
	void reverseStack(stack<int> &s);
};

void stackAndQueueApplication::convert(int n, int base)
{
	static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	stack<char> s;
	while (n > 0)
	{
		s.push(digit[n % base]);
		n /= base;
	}
}

inline bool stackAndQueueApplication::kuohaoMatch()
{
	stack<char> s;
	string exp = "(())[][]{[()]}";
	for (int i=0; i<exp.size(); i++)
	{
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
		{
			s.push(exp[i]);
		}
		else if (exp[i] == ')')
		{
			if (s.empty())
			{
				return false;
			}
			else if (s.top() == '(')
			{
				s.pop();
			}
			else
			{
				return false;
			}
		}
		else if (exp[i] == ']')
		{
			if (s.empty())
			{
				return false;
			}
			else if (s.top() == '[')
			{
				s.pop();
			}
			else
			{
				return false;
			}
		}
		else if (exp[i] == '}')
		{
			if (s.empty())
			{
				return false;
			}
			else if (s.top() == '{')
			{
				s.pop();
			}
			else
			{
				return false;
			}
		}
	}
	return s.empty();
}

inline bool stackAndQueueApplication::zhanhunxi()
{
	stack<int> a, b, s; //a��ԭջ��b�ǻ�ϴ���ջ��s����תջ
	//ջ��ʼ��
	for (int i=1; i<=10; i++)
	{
		a.push(11-i);  //��ջ����ջ��������12345678910
		b.push(i);  //��ջ����ջ��������10987654321
	}
	reverseStack(b); //��b��ת
	//��һ��Ԫ�ؿ϶�Ҫ��sջ
	s.push(a.top());
	a.pop();
	while (!s.empty() || !a.empty())
	{
		if (s.empty())
		{
			if (a.empty())
			{
				break;
			}
			else
			{
				s.push(a.top());
				a.pop();
			}
		}
		if (s.top() == b.top())
		{
			s.pop();
			b.pop();
		}
		else
		{
			if (a.empty())
			{
				break;
			}
			else
			{
				s.push(a.top());
				a.pop();
			}
		}
	}
	return b.empty();
}

inline void stackAndQueueApplication::reverseStack(stack<int>& s)
{
	if (s.empty())
	{
		return;
	}
	else
	{
		int i = s.top();
		s.pop();
		if (s.empty())
		{
			s.push(i);
			return;
		}
		else
		{
			s.push(i);
		}
	}
	int tmp1 = s.top();
	s.pop();
	reverseStack(s);
	int j = s.top();
	s.pop();
	reverseStack(s);
	s.push(tmp1);
	reverseStack(s);
	s.push(j);
}
