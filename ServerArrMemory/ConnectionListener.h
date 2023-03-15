#pragma once
#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // ���������� ��� ������ � ����� (2 ������)
#include "PatientRepository.h"
#include <iostream>
#include "DataHandler.h"



#pragma warning(disable: 4996)



// Server
class ConnectionListener
{
private:
	enum RequestType : char {
		Login,
		Get_Patient,
		Logout
	};

	//SOCKET _socket;
	static SOCKET Connections[100];
	//static int Counter; // ����������, �������� ������ ����������
	static PatientRepository _patient;
	static DataHandler _optData;
	SOCKADDR_IN addr;
	void Listen(int _sizeofaddr) {
		//�������� ������. 
	//����� - ����������� ����������� �� IP-������ � ������ �����. ��� ������������� ��� ����, ����� ��������� ����� ���������� ������ ���� ����� ���� � �������� ������ ����������
		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //AF_INET ��������� �� ��, ��� ����� �������������� ��������� ��������-����������;SOCK_STREAM ��������� �� ��������, ���������� ����������

		//��� �������� ������ ������ ������������ ������� bind
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

		//����� ����, ��� ��������� ����� � ���� ��������� � ������, ����� ���������� � ������������� ����� � �������� ���������� �� ������� �������
		listen(sListen, SOMAXCONN); //�� ������� ��������� �-�� ����������, �� ������ ����� ����� ��������� �������������. ������ �������� - ����������� ���������� ����� ��������, ��������� ���������

		SOCKET newConnection;
		for (int i = 0; i < 100; i++) {
			newConnection = accept(sListen, (SOCKADDR*)&addr, &_sizeofaddr); // accept ���������� ��������� �� ����� �����;����� ���������� ������� accept ������ �������� ����� ������� �������� �� IP-������ �������, ������� �������� ����������� 
			if (newConnection == 0) {
				std::cout << "Error #2 \n";
			}
			else {
				std::cout << "Client Connected! \n";
				Connections[i] = newConnection;
				//Counter++;
				//����� ���������� ��������� ������� � ��� ����� �������� ��� ������
				//������������ �������� main ����� ����������� ����� ����������, � � ��������� ClientHandler ����� ��������� � ������������ ��������� �������� 
				//� ������ ����� ����������� ����� ����������� ����� ����� ��� �������� ��������� �� ������ �������
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			}
		}

	}


public:
	
	ConnectionListener(const char* ip_addr, int port) {
		WSAData wsaData; // ���������, ���������� �������� � ���������� ������� Windows 
		WORD DLLVersion = MAKEWORD(2, 2); //������������� ������ ���������� winsock
		if (WSAStartup(DLLVersion, &wsaData) != 0) { //������� ��� �������� ���������� (����������� ������ 2.2 Winsock � ������� � ������ � �������� ����� ������� ������ Windows Sockets ���������
			std::cout << "Error" << std::endl;
			exit(1);
		}

		//����� �������� ���������� ���������� ��������� ���������� �� ������ ������
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr(ip_addr); // ��������� ��� �������� IP-������
		addr.sin_port = htons(port); // ���� ��� ������������� ���������, � ������������ �������, ������ ���� ������ ���� ��������
		addr.sin_family = AF_INET; // ��������� ����������. ��� �������� ���������� ����������� ��������� AF_INET

		Listen(sizeofaddr);
	}
	static void ClientHandler(int index) {
		//char* msg;
		//int msg_size;
		/*while (true) {
			recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(Connections[index], msg, msg_size, NULL);

			std::string pat = _optData.Packing(_patient.GetPatient());
			int pat_size = pat.size();
			send(Connections[index], (char*)&pat_size, sizeof(int), NULL);
			send(Connections[index], pat.c_str(), pat_size, NULL);
		}*/
		while (true) {
			char buffer[1024];
			int bytesReceived = recv(Connections[index], buffer, 1024, 0);
			if (bytesReceived > 0)
			{
				RequestType type = (RequestType)buffer[0];
				switch (type)
				{
				case Login:
					break;
				case Get_Patient: {
					std::string pat = _optData.Packing(_patient.GetPatient());
					int pat_size = pat.size();
					send(Connections[index], (char*)&pat_size, sizeof(int), NULL);
					send(Connections[index], pat.c_str(), pat_size, NULL);
					break;
				}
				case Logout:
					break;
				}
			}
		}
		//delete[] msg;
	}
};


