/// Client code 

#include <iostream>                                   

#include<WinSock2.h>
#include<stdio.h>
#include<ws2tcpip.h>
#include<string>
#include<thread> 


using namespace std;

#pragma comment(lib, "ws2_32.lib")







bool Initialize()
{

	WSADATA data;

	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}





///part 4

void SendMsg(SOCKET s)
{
	/// Contiousely working 
	cout << "Enter your chat name:\n";

	string name;

	getline(cin, name );

	
	



	string message;
		
	while (1)
	{
		getline(cin, message);
	
		/// replacement of the getline function 
 	string msg = name + ":" + message;

	
		int bytesent = send(s, msg.c_str(), msg.length(), 0);

		if (bytesent == SOCKET_ERROR)
		{
			cout << "error in sending message \n";
			break;

		}


		if (message == "quit")
		{
			
			cout << "stopping the application :";
			break;
		}
	}
	closesocket(s);

	WSACleanup();
}



void ReceiverMsg(SOCKET s)
{

	char buffer[4096];
	int recvlength;

	while (1)
	{
		recvlength = recv(s, buffer, sizeof(buffer), 0);
		string msg = "";

		if (recvlength <= 0)

		{
			cout << "disconnected from the server \n";
			break;

		}



	




		else {
			msg = string(buffer, recvlength);

			cout << msg<<"\n";
		}


	}
	closesocket(s);

	WSACleanup();
}






int main()
{

	if (!Initialize()) 
	{
		cout << "Initialize of winsock failed \n";

	}



	SOCKET s;


	s = socket(AF_INET, SOCK_STREAM, 0);

	if (s == INVALID_SOCKET)


	{


		cout << " invaild socket created  \n";


		return 1;

	}

	string serveraddress = "127.0.0.1";
	int port = 12345;


	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;

	serveraddr.sin_port = htons(port);


	inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));



	if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)


	{
		cout << "not able to connect to server  \n";


		closesocket(s);

		WSACleanup();


		return 1;


	}

	cout << "successfully connected to server \n ";


	


	thread senderthread(SendMsg,s);
	thread receiverthread(ReceiverMsg, s);



	cout << " client code standby ";


	senderthread.join();
	receiverthread.join();
}