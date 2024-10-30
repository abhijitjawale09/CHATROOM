//Server file 


#include<iostream>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>

#include<vector>



using namespace std;



#pragma comment(lib, "ws2_32.lib")






bool Initialize() {

	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;

}


void InteractWithClient(SOCKET clientSocket, vector <SOCKET>& clients)
{

	cout << "client connected  \n";

	char buffer[4096];

	while (1) {






		int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);  // flag// recv// Blocking call


		if (bytesrecvd <= 0)
		{
			cout << " client  Disconnected\n ";
			break;

		}



		string message(buffer, bytesrecvd);

		cout << " message from client : " << message << endl;



		for (auto client : clients)
		{

			if (client != clientSocket)


			{
				send(client, message.c_str(), message.length(), 0);
			}

		}


	}




	closesocket(clientSocket);

	auto it = find(clients.begin(), clients.end(), clientSocket);

	if (it != clients.end())

	{
		clients.erase(it);
	}


}

int main()
{
	if (!Initialize())
	{

		cout << "Winsock intialization failed \n";
		return 1;
	}


	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0); //// IPV4 MACHIMS, PROTOCOL IT IS TCP , WHAT TYPE OF PROCTOL IS BEING USEIN HERE WE USED ZERO BECAUSE MAKE THE SERVER PROVIDE TO DEICDED 


	if (listenSocket == INVALID_SOCKET)
	{
		cout << "socket creation failed" << endl;

		return 1;
	}

	////create address structure 
	int port = 12345;/// port 
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);



	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) // Binary format checking 

	{
		cout << " setting address structrue failded \n";

		closesocket(listenSocket);

		WSACleanup();
		return 1;
	}




	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)/// It takes server address  in structre not server addresss  

	{

		cout << "bind failed " << endl;


		closesocket(listenSocket);

		WSACleanup();
		return 1;



	}





	if (listen(listenSocket, SOMAXCONN))//SOMAX CONN SIGN INTER


	{
		cout << " Listen failed /n";
		return 1;



	}




	cout << " server has started listening on port " << port << endl;

	vector <SOCKET> clients;

	while (1)
	{
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);////accept 




		if (clientSocket == INVALID_SOCKET)
		{
			cout << "invalid client socket \n";
		}


		clients.push_back(clientSocket);



		thread t1(InteractWithClient, clientSocket, std::ref(clients));



		t1.detach();

	}



	closesocket(listenSocket);
	WSACleanup();
	return 0;
}


/// server code