#pragma comment(lib, "ws2_32.lib") // ������ � �����������
#include <winsock2.h> // ���������� ��� ������ � ����� (2 ������)
#include <iostream>

#pragma warning(disable: 4996)

//������ ��� �������� �������
SOCKET Connections[100];
int Counter = 0; // ����������, �������� ������ ����������

void ClientHandler(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < 100; i++) {
			if (i == index) {
				continue;
			}
			send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[i], msg, msg_size, NULL);
		}

		delete[] msg;
	}
}



//int main() {
//	// ������ ��� ������ ������ � �����, ���������� ��������� ������ ����������
//	// ��� �������� ���������� ������������ WSAStartup
//
//
//	WSAData wsaData; // ���������, ���������� �������� � ���������� ������� Windows 
//	WORD DLLVersion = MAKEWORD(2, 2); //������������� ������ ���������� winsock
//	if (WSAStartup(DLLVersion, &wsaData) != 0) { //������� ��� �������� ���������� (����������� ������ 2.2 Winsock � ������� � ������ � �������� ����� ������� ������ Windows Sockets ���������
//		std::cout << "Error" << std::endl;
//		exit(1);
//
//	}
//
//	//����� �������� ���������� ���������� ��������� ���������� �� ������ ������
//	SOCKADDR_IN addr; //���������, ��������������� ��� �������� ������
//	int sizeofaddr = sizeof(addr);
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ��������� ��� �������� IP-������
//	addr.sin_port = htons(1111); // ���� ��� ������������� ���������, � ������������ �������, ������ ���� ������ ���� ��������
//	addr.sin_family = AF_INET; // ��������� ����������. ��� �������� ���������� ����������� ��������� AF_INET
//
//	//�������� ������. 
//	//����� - ����������� ����������� �� IP-������ � ������ �����. ��� ������������� ��� ����, ����� ��������� ����� ���������� ������ ���� ����� ���� � �������� ������ ����������
//	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //AF_INET ��������� �� ��, ��� ����� �������������� ��������� ��������-����������;SOCK_STREAM ��������� �� ��������, ���������� ����������
//
//	//��� �������� ������ ������ ������������ ������� bind
//	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
//
//	//����� ����, ��� ��������� ����� � ���� ��������� � ������, ����� ���������� � ������������� ����� � �������� ���������� �� ������� �������
//	listen(sListen, SOMAXCONN); //�� ������� ��������� �-�� ����������, �� ������ ����� ����� ��������� �������������. ������ �������� - ����������� ���������� ����� ��������, ��������� ���������
//
//	//������� ����� �����, ��� ��������� ���������� � ��������
//	SOCKET newConnection;
//	for (int i = 0; i < 100; i++) {
//		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr); // accept ���������� ��������� �� ����� �����;����� ���������� ������� accept ������ �������� ����� ������� �������� �� IP-������ �������, ������� �������� ����������� 
//		if (newConnection == 0) {
//			std::cout << "Error #2 \n";
//		}
//		else {
//			std::cout << "Client Connected! \n";
//			std::string msg = "Hola hola UNN";
//			int msg_size = msg.size();
//			send(newConnection, (char*)& msg_size, sizeof(int), NULL); //������� ��� �������� ����� ������
//			send(newConnection, msg.c_str(), msg_size, NULL); //������� ��� �������� ������ �������
//
//			Connections[i] = newConnection;
//			Counter++;
//			//����� ���������� ��������� ������� � ��� ����� �������� ��� ������
//			//������������ �������� main ����� ����������� ����� ����������, � � ��������� ClientHandler ����� ��������� � ������������ ��������� �������� 
//			//� ������ ����� ����������� ����� ����������� ����� ����� ��� �������� ��������� �� ������ �������
//			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
//		}
//	}
//
//
//	system("pause");
//	return 0;
//}


