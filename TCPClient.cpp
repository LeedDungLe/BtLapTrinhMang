#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>



int main(int argc, char** argv) {
	
	
	char *addrIp = argv[1];
	int port = atoi(argv[2]);
	
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	int ret;

	if (isalnum(addrIp[0])) {
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(addrIp);
		addr.sin_port = htons(port);
	}
	
	
	
	ret = connect(server, (SOCKADDR *)&addr, sizeof(addr));
	
	if (ret == SOCKET_ERROR)
	{
		ret = WSAGetLastError();
		printf("Ma loi: %d", ret);
		system("PAUSE");

		return 1;
	}


	char msg[400];
	printf("Nhap vao thong diep gui len server: ");
	gets(msg);
	send(server, msg, strlen(msg), 0);

	char buf[256];

	while (1)
	{
		ret = recv(server, buf, sizeof(buf), 0);
		if (ret <= 0)
			break;

		buf[ret] = '\0';
		printf("Thong diep tu server : %s", buf);
		gets(msg);
		send(server, msg, strlen(msg), 0);
		
	}

	closesocket(server);
	WSACleanup();

	system("PAUSE");

	return 0;
}