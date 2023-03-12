#pragma once
#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // ���������� ��� ������ � ����� (2 ������)
#include "Patient.h"
#include <iostream>
#include <WinUser.h>



#pragma warning(disable: 4996)


// Server
class ConnectionListener
{
private:
	
	//SOCKET _socket;
	static SOCKET Connections[100];
	static int Counter; // ����������, �������� ������ ����������
	SOCKADDR_IN addr;
	void Listen(int _sizeofaddr){
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
				std::string msg = "Hola hola UNN";
				int msg_size = msg.size();
				send(newConnection, (char*)&msg_size, sizeof(int), NULL); //������� ��� �������� ����� ������
				send(newConnection, msg.c_str(), msg_size, NULL); //������� ��� �������� ������ �������

				Connections[i] = newConnection;
				Counter++;
				//����� ���������� ��������� ������� � ��� ����� �������� ��� ������
				//������������ �������� main ����� ����������� ����� ����������, � � ��������� ClientHandler ����� ��������� � ������������ ��������� �������� 
				//� ������ ����� ����������� ����� ����������� ����� ����� ��� �������� ��������� �� ������ �������
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			}
		}

	}
	void PrepareData();
	Patient GetCurPatient();
	
	
public:
	ConnectionListener() {
		Counter = 0;
		WSAData wsaData; // ���������, ���������� �������� � ���������� ������� Windows 
		WORD DLLVersion = MAKEWORD(2, 2); //������������� ������ ���������� winsock
		if (WSAStartup(DLLVersion, &wsaData) != 0) { //������� ��� �������� ���������� (����������� ������ 2.2 Winsock � ������� � ������ � �������� ����� ������� ������ Windows Sockets ���������
			std::cout << "Error" << std::endl;
			exit(1);
		}

		//����� �������� ���������� ���������� ��������� ���������� �� ������ ������
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ��������� ��� �������� IP-������
		addr.sin_port = htons(1111); // ���� ��� ������������� ���������, � ������������ �������, ������ ���� ������ ���� ��������
		addr.sin_family = AF_INET; // ��������� ����������. ��� �������� ���������� ����������� ��������� AF_INET

		Listen(sizeofaddr);
	}
	static void ClientHandler(int index) {
		int msg_size;
		while (true) {
			recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			char* msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(Connections[index], msg, msg_size, NULL);
			for (int i = 0; i < Counter; i++) {
				if (i == index) {
					continue;
				}
				send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
				send(Connections[i], msg, msg_size, NULL);
			}

			delete[] msg;
		}
	}
};


