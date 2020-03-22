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
//��ͨ�����������
int main()
{
	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//����socket�׽���
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);  //0�����Զ�������ʲôЭ��
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//socket����˵ĵ�ַ�˿�Э����֮���
	sockaddr_in server_addr; 
	server_addr.sin_family = AF_INET;  //Э����
	server_addr.sin_port = htons(8000);  //�˿�
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //Ҳ���Ǽ���0.0.0.0���������е�
	//bind����Ϣ
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //LPSOCKADDR��ʵ����SOCKADDR*,���ﲻ��sockaddr_in*��ԭ����Ϊ��ʹ��ͨ�õĽṹ�壬��Ϊsockaddr_inֻ��ipv4
	if (bindResult == SOCKET_ERROR) 
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//listen�������������
	int listenRestlt = listen(s, 20);  //���������20
	if (listenRestlt == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}
	//accept
	sockaddr_in client_addr;  //����, �������տͻ��˵���Ϣ,����ͻ��˵ĵ�ַ�˿ڵ���Ϣ
	int client_addr_len = sizeof(client_addr);
	SOCKET con = accept(s, (LPSOCKADDR)&client_addr, &client_addr_len); //������������Ȼ�ǳ��ȵ�ָ��
	if (con == INVALID_SOCKET)
	{
		std::cout << "error accept" << std::endl;
		return 0;
	}
	while (1)  //һֱѭ���ȴ�����Ϣ
	{
		char buffer[1024];
		//��������
		int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0�Ļ��൱��read, ���ؽ��յ����ֽ���
		if (recvResult > 0)  //������յ�������
		{
			buffer[recvResult] = '\0'; //��������Ϊ\0�������Ļ�������ʵ�ʽ�����100���ַ�����ô����\0�󣬾Ͳ����ȡ100���Ժ��û�е�������
			std::cout << "���յ�������" << buffer << std::endl;
		}
		else  //û������
		{
			break;
		}
		//��������,���յ���ԭ�ⲻ������
		int sendResult = send(con, buffer, recvResult, 0); //0�Ļ��൱��write, ���ط��͵��ֽ���
		if (sendResult > 0)
		{
			std::cout << "���͵�������" << buffer << std::endl;
		}
		else  //û������
		{
			break;
		}
	}
	closesocket(con);  //�ر�con�׽���
	closesocket(s);  //�ر�s�׽���
	return 0;
}
*/

/*
//��ͨ�������ͻ���
int main()
{
	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //0���Զ�����ʲôЭ������
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//connect
	//����˵�ַ
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //����˵�ip
	server_addr.sin_port = htons(8000);  //����˵Ķ˿�
	int connectResult = connect(s, (LPSOCKADDR)&server_addr, sizeof(server_addr));
	if (connectResult == SOCKET_ERROR)
	{
		std::cout << "error connect" << std::endl;
		return 0;
	}
	std::string str;
	while (std::cin >> str)  //���һֱ������
	{
		const char *msg = str.c_str();
		//��������
		int sendResult = send(s, msg, strlen(msg), 0);  //���ط��͵��ֽ���
		if (sendResult > 0)
		{
			std::cout << "���͵�������" << str << std::endl;
		}
		else  //����ʧ��
		{
			break;
		}
		//��������
		char buffer[1024];
		int recvResult = recv(s, buffer, sizeof(buffer), 0); //0�Ļ��൱��read, ���ؽ��յ����ֽ���
		if (recvResult > 0)
		{
			buffer[recvResult] = '\0';
			std::cout << "���յ�������" << buffer << std::endl;
		}
		else  //����ʧ��
		{
			break;
		}
	}
	closesocket(s);
	return 0;
}
*/

/*
//�첽�������ˣ���select
int main()
{
	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	//fd_set��ʵ����һ������ĺ궨�壬ʵ������һlong���͵����飬
	//ÿһ������Ԫ�ض�����һ�򿪵��ļ����(socket���ļ����ܵ����豸��)������ϵ��
	//������ϵ�Ĺ����ɳ���Ա��ɣ�������select()ʱ�����ں˸���IO״̬�޸�fd_set�����ݣ�
	//�ɴ���ִ֪ͨ����select()�Ľ����ĸ�����ɶ�
	fd_set fs;  //fd_set����
	timeval tv; //���ʱ��
	int maxfd; //��socket��������
	int retVal; //select�ķ���ֵ
	//����socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//����bind��Ϣ
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000); //�����˿�
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //����0.0.0.0
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //��
	if (bindResult == SOCKET_ERROR)
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//lister
	int listenResult = listen(s, 20); //��������
	if (listenResult == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}
	//accept
	//������Ϣ������ͻ��˵Ķ˿ڵ�ַ��
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
		FD_ZERO(&fs); //���ļ����������
		FD_SET(0, &fs); //����׼����ӽ�ȥ��0������stdin��1�����stdout��2�ǳ���
		maxfd = 0; //��ʼ��������ӵ�������
		FD_SET(con, &fs); //����ǰaccept�Ľ����������ӽ�ȥ
		maxfd = max(maxfd, con);
		//���õ���ʱ
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		//�ȴ����죬��select���ȴ�
		//�������,����fd������������ʱ����SOCKET_ERROR
		//1. nfds��Ҫ�����ļ������ָ���
		//2. readset �������ɶ��Ե�һ���ļ������֡�
		//3. writeset��������д�Ե�һ���ļ������֡�
		//4. exceptset��������Ƿ����쳣�������ֵ��ļ������֡�(ע�����󲻰������쳣����֮��)
		//5. timeout��ʱ����NULLΪ��������0Ϊ������������Ϊһ�γ�ʱʱ��
		retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv);
		if (retVal < 0)
		{
			std::cout << "select����" << std::endl;
			break;
		}
		else if (retVal == 0)
		{
			std::cout << "û�����ӣ��ȴ�" << std::endl;
			continue;
		}
		else  //��������
		{
			if (FD_ISSET(con, &fs))  //�����con����Ϣ��
			{
				char buffer[1024];
				int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0�Ļ��൱��read, ���ؽ��յ����ֽ���
				if (recvResult > 0)
				{
					buffer[recvResult] = '\0';
					std::cout << "���յ�������" << buffer << std::endl;
				}
				else  //����ʧ��
				{
					break;
				}
			}
			if (FD_ISSET(0, &fs))  //��������������룬��������Ҫ���͸��ͻ���
			{
				std::string str;
				std::cin >> str;
				const char* msg = str.c_str();
				int sendResult = send(con, msg, strlen(msg), 0); //���ط��͵��ֽ���
				if (sendResult > 0)
				{
					std::cout << "���͵�������" << str << std::endl;
				}
				else  //����ʧ��
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
//�첽����ͻ���
int main()
{	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	int maxfd, retVal;
	fd_set fs;
	timeval tv;
	//����socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //0���Զ�����ʲôЭ������
	if (s == INVALID_SOCKET)
	{
		std::cout << "error socket" << std::endl;
		return 0;
	}
	//connect
	//����˵�ַ
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //����˵�ip
	server_addr.sin_port = htons(8000);  //����˵Ķ˿�
	int connectResult = connect(s, (LPSOCKADDR)&server_addr, sizeof(server_addr));
	if (connectResult == SOCKET_ERROR)
	{
		std::cout << "error connect" << std::endl;
		return 0;
	}
	while (true)  //���һֱ������
	{
		FD_ZERO(&fs); //���ļ����������
		FD_SET(0, &fs); //����׼����ӽ�ȥ��0������stdin��1�����stdout��2�ǳ���
		maxfd = 0; //��ʼ��������ӵ�������
		FD_SET(s, &fs); //����ǰaccept�Ľ����������ӽ�ȥ
		maxfd = max(maxfd, s);
		//���õ���ʱ
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		//�ȴ����죬��select���ȴ�
		//�������,����fd������������ʱ����SOCKET_ERROR
		//1. nfds��Ҫ�����ļ������ָ���
		//2. readset �������ɶ��Ե�һ���ļ������֡�
		//3. writeset��������д�Ե�һ���ļ������֡�
		//4. exceptset��������Ƿ����쳣�������ֵ��ļ������֡�(ע�����󲻰������쳣����֮��)
		//5. timeout��ʱ����NULLΪ��������0Ϊ������������Ϊһ�γ�ʱʱ��
		retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv);
		if (retVal < 0)
		{
			std::cout << "select����" << std::endl;
			break;
		}
		else if (retVal == 0)
		{
			std::cout << "û�����ӣ��ȴ�" << std::endl;
			continue;
		}
		else
		{
			if (FD_ISSET(0, &fs))  //������Ҫ���͸������
			{
				std::string str;
				std::cin >> str;
				const char* msg = str.c_str();
				int sendResult = send(s, msg, strlen(msg), 0);
				if (sendResult > 0)
				{
					std::cout << "���͵�������" << str << std::endl;
				}
				else  //����ʧ��
				{
					break;
				}

			}
			if (FD_ISSET(s, &fs))  //�����con����Ϣ��
			{
				char buffer[1024];
				int recvResult = recv(con, buffer, sizeof(buffer), 0);  //0�Ļ��൱��read, ���ؽ��յ����ֽ���
				if (recvResult > 0)
				{
					buffer[recvResult] = '\0';
					std::cout << "���յ�������" << buffer << std::endl;
				}
				else  //����ʧ��
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
//���ڶ�������Ļ������ܴ����ö���̷ֱ߳��Ӧһ�����ӣ�����Ļ��߳�̫����
//һ������취������stl��list����ÿ���׽��ַŵ�list��
//�����Ϳ��Դ��������̣߳�һ�����������׽��ֲ��ŵ�list�У��������̳߳�
//һ��������������
//һ��������������
std::list<int> socket_list;
SOCKET s;  //ֻ��Ҫһ��s�������Լ��Ķ˿ڼ���
fd_set fs;  //��������������
timeval tv; //����select�ȵ��ĵ���ʱʱ��

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
		//����ÿһ��socket����
		for (std::list<int>::iterator it = socket_list.begin(); it != socket_list.end(); it++)
		{
			FD_ZERO(&fs); //���������
			FD_SET(*it, &fs); //���뵱ǰ���׽�������
			int maxfd = 0;
			maxfd = max(maxfd, *it);
			int retVal = select(maxfd + 1, &fs, nullptr, nullptr, &tv); //tvʱ������û�������¼�
			if (retVal < 0)
			{
				std::cout << "select����" << std::endl; //������һ��socket��select
			}
			else if (retVal == 0)
			{
				std::cout << "û�����ӣ��ȴ�" << std::endl;
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
	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	//����bind��Ϣ
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000); //�����˿�
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY; //����0.0.0.0
	int bindResult = bind(s, (LPSOCKADDR)&server_addr, sizeof(server_addr)); //��
	if (bindResult == SOCKET_ERROR)
	{
		std::cout << "error bind" << std::endl;
		return 0;
	}
	//lister
	int listenResult = listen(s, 20); //��������
	if (listenResult == SOCKET_ERROR)
	{
		std::cout << "error listen" << std::endl;
		return 0;
	}

	//thread : while ==>> accpet
	std::thread t(getConn);
	t.detach();//detach�Ļ�������̲߳��õ�ǰ��Ľ�����ɺ���ܽ��У���������Ϊjoin�����
	//thread : input ==>> send
	std::thread t1(sendMessage);
	t1.detach();
	//thread : recv ==>> show
	std::thread t2(getData);
	t2.detach();
	while (1)//��һ����ѭ��ʹ�����̲߳�����ǰ�˳�
	{

	}
	return 0;
}

//��������ͻ������첽��һ��
*/

/* epoll
int main()
{
	//����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�
	struct epoll_event ev, events[20];

	epfd = epoll_create(10000); //����epoll���

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	//��socket����Ϊ��������ʽ
	setnonblocking(listenfd);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(SERV_PORT);
	bind(listenfd, (struct sockaddr)&serveraddr, sizeof(serveraddr));
	listen(listenfd, 255);

	//������Ҫ������¼���ص��ļ�������
	ev.data.fd = listenfd;
	//����Ҫ������¼�����
	ev.events = EPOLLIN;
	//ע��epoll�¼�
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

	for (; ; ) {
		//�ȴ�epoll�¼��ķ���
		nfds = epoll_wait(epfd, events, 20, 1000);
		//�����������������¼�
		for (i = 0; i < nfds; ++i) {
			if (events.data.fd == listenfd) {
				connfd = accept(listenfd, (struct sockaddr)&clientaddr, &clilen);
				if (connfd < 0) {
					perror("connfd<0");
				}
				setnonblocking(connfd);
				//�������ڶ��������ļ�������
				ev.data.fd = connfd;
				//��������ע��Ķ������¼�
				ev.events = EPOLLIN | EPOLLET;
				//ע��event
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
				ev.events = EPOLLIN | EPOLLET; //ETģʽ
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