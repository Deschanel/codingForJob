#include <sys/types.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <thread>
#include <iostream>
#include <list>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

/*
//普通聊天程序服务端
int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//创建socket套接字
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);  //0就是自动推演是什么协议
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//socket服务端的地址端口协议族之类的
	sockaddr_in server_addr; 
	server_addr.sin_family = AF_INET;  //协议族
	server_addr.sin_port = htons(8000);  //端口
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //也就是监听0.0.0.0，监听所有的
	//bind绑定信息
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //LPSOCKADDR其实就是SOCKADDR*,这里不用sockaddr_in*的原因是为了使用通用的结构体，因为sockaddr_in只能ipv4
	if (bindResult == SOCKET_ERROR) 
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//listen闯进最大连接数
	int listenRestlt = listen(s, 20);  //最大连接数20
	if (listenRestlt == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}
	//accept
	sockaddr_in client_addr;  //创建, 用来接收客户端的信息,保存客户端的地址端口等信息
	int client_addr_len = sizeof(client_addr);
	SOCKET con = accept(s, (LPSOCKADDR)&client_addr, &client_addr_len); //第三个参数竟然是长度的指针
	if (con == INVALID_SOCKET)
	{
		std::cout << "error accept" << std::endl;
		return 0;
	}
	while (1)  //一直循环等待来消息
	{
		char buffer[1024];
		//接收数据
		int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0的话相当于read, 返回接收到的字节数
		if (recvResult > 0)  //如果接收到了数据
		{
			buffer[recvResult] = '\0'; //将最后的置为\0，这样的话，假如实际接受了100个字符，那么加上\0后，就不会读取100个以后的没有的数据了
			std::cout << "接收的数据是" << buffer << std::endl;
		}
		else  //没有数据
		{
			break;
		}
		//发送数据,将收到的原封不动返回
		int sendResult = send(con, buffer, recvResult, 0); //0的话相当于write, 返回发送的字节数
		if (sendResult > 0)
		{
			std::cout << "发送的数据是" << buffer << std::endl;
		}
		else  //没有数据
		{
			break;
		}
	}
	closesocket(con);  //关闭con套接字
	closesocket(s);  //关闭s套接字
	return 0;
}
*/

/*
//普通聊天程序客户端
int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //0是自动推演什么协议类型
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//connect
	//服务端地址
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //服务端的ip
	server_addr.sin_port = htons(8000);  //服务端的端口
	int connectResult = connect(s, (LPSOCKADDR)&server_addr, sizeof(server_addr));
	if (connectResult == SOCKET_ERROR)
	{
		std::cout << "error connect" << std::endl;
		return 0;
	}
	std::string str;
	while (std::cin >> str)  //如果一直有输入
	{
		const char *msg = str.c_str();
		//发送数据
		int sendResult = send(s, msg, strlen(msg), 0);  //返回发送的字节数
		if (sendResult > 0)
		{
			std::cout << "发送的数据是" << str << std::endl;
		}
		else  //发送失败
		{
			break;
		}
		//接收数据
		char buffer[1024];
		int recvResult = recv(s, buffer, sizeof(buffer), 0); //0的话相当于read, 返回接收到的字节数
		if (recvResult > 0)
		{
			buffer[recvResult] = '\0';
			std::cout << "接收的数据是" << buffer << std::endl;
		}
		else  //接收失败
		{
			break;
		}
	}
	closesocket(s);
	return 0;
}
*/

/*
//异步聊天服务端，用select
int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//fd_set其实这是一个数组的宏定义，实际上是一long类型的数组，
	//每一个数组元素都能与一打开的文件句柄(socket、文件、管道、设备等)建立联系，
	//建立联系的工作由程序员完成，当调用select()时，由内核根据IO状态修改fd_set的内容，
	//由此来通知执行了select()的进程哪个句柄可读
	fd_set fs;  //fd_set数组
	timeval tv; //间隔时间
	int maxfd; //此socket最大进程数
	int retVal; //select的返回值
	//建立socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//创建bind信息
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000); //监听端口
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //监听0.0.0.0
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //绑定
	if (bindResult == SOCKET_ERROR)
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//lister
	int listenResult = listen(s, 20); //最大监听数
	if (listenResult == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}
	//accept
	//建立信息来保存客户端的端口地址等
	sockaddr_in client_addr;
	int len = sizeof(client_addr);
	SOCKET con = accept(s, (LPSOCKADDR)&client_addr, &len);
	if (con == INVALID_SOCKET)
	{
		std::cout << "error accept" << std::endl;
		return 0;
	}
	while (true)
	{
		FD_ZERO(&fs); //将文件描述符清空
		FD_SET(0, &fs); //将标准输入加进去，0是输入stdin，1是输出stdout，2是出错
		maxfd = 0; //初始化最大连接的描述符
		FD_SET(con, &fs); //将当前accept的进程描述符加进去
		maxfd = max(maxfd, con);
		//设置倒计时
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		//等待聊天，用select来等待
		//五个参数,返回fd的总数，错误时返回SOCKET_ERROR
		//1. nfds需要检查的文件描述字个数
		//2. readset 用来检查可读性的一组文件描述字。
		//3. writeset用来检查可写性的一组文件描述字。
		//4. exceptset用来检查是否有异常条件出现的文件描述字。(注：错误不包括在异常条件之内)
		//5. timeout超时，填NULL为阻塞，填0为非阻塞，其他为一段超时时间
		retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv);
		if (retVal < 0)
		{
			std::cout << "select出错" << std::endl;
			break;
		}
		else if (retVal == 0)
		{
			std::cout << "没有连接，等待" << std::endl;
			continue;
		}
		else  //连接来了
		{
			if (FD_ISSET(con, &fs))  //如果是con来消息了
			{
				char buffer[1024];
				int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0的话相当于read, 返回接收到的字节数
				if (recvResult > 0)
				{
					buffer[recvResult] = '\0';
					std::cout << "接收的数据是" << buffer << std::endl;
				}
				else  //接收失败
				{
					break;
				}
			}
			if (FD_ISSET(0, &fs))  //如果服务器有输入，即有数据要发送给客户端
			{
				std::string str;
				std::cin >> str;
				const char* msg = str.c_str();
				int sendResult = send(con, msg, strlen(msg), 0); //返回发送的字节数
				if (sendResult > 0)
				{
					std::cout << "发送的数据是" << str << std::endl;
				}
				else  //发送失败
				{
					break;
				}
			}
		}
	}
	closesocket(con);
	closesocket(s);
	return 0;
}
*/

/*
//异步聊天客户端
int main()
{	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	int maxfd, retVal;
	fd_set fs;
	timeval tv;
	//建立socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //0是自动推演什么协议类型
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//connect
	//服务端地址
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //服务端的ip
	server_addr.sin_port = htons(8000);  //服务端的端口
	int connectResult = connect(s, (LPSOCKADDR)&server_addr, sizeof(server_addr));
	if (connectResult == SOCKET_ERROR)
	{
		std::cout << "error connect" << std::endl;
		return 0;
	}
	while (true)  //如果一直有输入
	{
		FD_ZERO(&fs); //将文件描述符清空
		FD_SET(0, &fs); //将标准输入加进去，0是输入stdin，1是输出stdout，2是出错
		maxfd = 0; //初始化最大连接的描述符
		FD_SET(s, &fs); //将当前accept的进程描述符加进去
		maxfd = max(maxfd, s);
		//设置倒计时
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		//等待聊天，用select来等待
		//五个参数,返回fd的总数，错误时返回SOCKET_ERROR
		//1. nfds需要检查的文件描述字个数
		//2. readset 用来检查可读性的一组文件描述字。
		//3. writeset用来检查可写性的一组文件描述字。
		//4. exceptset用来检查是否有异常条件出现的文件描述字。(注：错误不包括在异常条件之内)
		//5. timeout超时，填NULL为阻塞，填0为非阻塞，其他为一段超时时间
		retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv);
		if (retVal < 0)
		{
			std::cout << "select出错" << std::endl;
			break;
		}
		else if (retVal == 0)
		{
			std::cout << "没有连接，等待" << std::endl;
			continue;
		}
		else
		{
			if (FD_ISSET(0, &fs))  //有数据要发送给服务端
			{
				std::string str;
				std::cin >> str;
				const char* msg = str.c_str();
				int sendResult = send(s, msg, strlen(msg), 0);
				if (sendResult > 0)
				{
					std::cout << "发送的数据是" << str << std::endl;
				}
				else  //发送失败
				{
					break;
				}

			}
			if (FD_ISSET(s, &fs))  //如果是con来消息了
			{
				char buffer[1024];
				int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0的话相当于read, 返回接收到的字节数
				if (recvResult > 0)
				{
					buffer[recvResult] = '\0';
					std::cout << "接收的数据是" << buffer << std::endl;
				}
				else  //接收失败
				{
					break;
				}
			}
		}
	}
	closesocket(s);
	return 0;
}
*/

/*
//对于多人聊天的话，不能创建好多的线程分别对应一个连接，否则的话线程太多了
//一个解决办法就是用stl的list，将每个套接字放到list中
//这样就可以创建三个线程，一个用来接收套接字并放到list中，类似于线程池
//一个用来接收数据
//一个用来发送数据
std::list<int> socket_list;
SOCKET s;  //只需要一个s来监听自己的端口即可
fd_set fs;  //用来监听描述符
timeval tv; //设置select等到的倒计时时间

void getConn()
{
	while (true)
	{
		sockaddr_in client_addr;
		int len = sizeof(client_addr);
		int conn = accept(s, (LPSOCKADDR)&client_addr, &len);
		if (conn != SOCKET_ERROR)
		{
			socket_list.push_back(conn);
		}
	}
}

void getData()
{
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	while (true)
	{
		//对于每一个socket连接
		for (std::list<int>::iterator it = socket_list.begin(); it != socket_list.end(); it++)
		{
			FD_ZERO(&fs); //清空描述符
			FD_SET(*it, &fs); //加入当前的套接字连接
			int maxfd = 0;
			maxfd = max(maxfd, *it);
			int retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv); //tv时间内有没有来临事件
			if (retVal < 0)
			{
				std::cout << "select出错" << std::endl; //继续下一个socket的select
			}
			else if (retVal == 0)
			{
				std::cout << "没有连接，等待" << std::endl;
				continue;
			}
			else
			{
				char buffer[1024];
				int recvResult = recv(*it, buffer, sizeof(buffer), 0);
				if (recvResult > 0)
				{
					buffer[recvResult] = '\0';
					std::cout << buffer << std::endl;
				}
			}
		}
		Sleep(1);
	}
}

void sendMessage()
{
	while (true)
	{
		for (std::list<int>::iterator it = socket_list.begin(); it != socket_list.end(); it++)
		{
			std::string str;
			std::cin >> str;
			const char* msg = str.c_str();
			int sendResult = send(*it, msg, strlen(msg), 0);
		}
	}
}

int main()
{
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	//创建bind信息
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000); //监听端口
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //监听0.0.0.0
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //绑定
	if (bindResult == SOCKET_ERROR)
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//lister
	int listenResult = listen(s, 20); //最大监听数
	if (listenResult == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}

	//thread : while ==>> accpet
	std::thread t(getConn);
	t.detach();//detach的话后面的线程不用等前面的进程完成后才能进行，如果这里改为join则堵塞
	//thread : input ==>> send
	std::thread t1(sendMessage);
	t1.detach();
	//thread : recv ==>> show
	std::thread t2(getData);
	t2.detach();
	while (1)//做一个死循环使得主线程不会提前退出
	{

	}
	return 0;
}

//多人聊天客户端与异步的一样
*/

/* epoll
int main()
{
	//声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
	struct epoll_event ev, events[20];

	epfd = epoll_create(10000); //创建epoll句柄

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	//把socket设置为非阻塞方式
	setnonblocking(listenfd);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(SERV_PORT);
	bind(listenfd, (struct sockaddr)&serveraddr, sizeof(serveraddr));
	listen(listenfd, 255);

	//设置与要处理的事件相关的文件描述符
	ev.data.fd = listenfd;
	//设置要处理的事件类型
	ev.events = EPOLLIN;
	//注册epoll事件
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

	for (; ; ) {
		//等待epoll事件的发生
		nfds = epoll_wait(epfd, events, 20, 1000);
		//处理所发生的所有事件
		for (i = 0; i < nfds; ++i) {
			if (events.data.fd == listenfd) {
				connfd = accept(listenfd, (struct sockaddr)&clientaddr, &clilen);
				if (connfd < 0) {
					perror("connfd<0");
				}
				setnonblocking(connfd);
				//设置用于读操作的文件描述符
				ev.data.fd = connfd;
				//设置用于注测的读操作事件
				ev.events = EPOLLIN | EPOLLET;
				//注册event
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			}
			else if (events.events&EPOLLIN) {
				read_socket(events.data.fd);
				ev.data.fd = events.data.fd;
				ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else if (events.events&EPOLLOUT) {
				write_socket(events.data.fd);
				ev.data.fd = events.data.fd;
				ev.events = EPOLLIN | EPOLLET; //ET模式
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else {
				perror("other event");
			}
		}
	}

	return 0;
}
*/