#include "ConnectionListener.h"


SOCKET ConnectionListener::Connections[100];
int ConnectionListener::Counter = 0; 
PatientRepository ConnectionListener::_patient;
//std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> ConnectionListener::_loggingData;

void ConnectionListener::Listen(int _sizeofaddr)
{
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
			Counter++;
			//����� ���������� ��������� ������� � ��� ����� �������� ��� ������
			//������������ �������� main ����� ����������� ����� ����������, � � ��������� ClientHandler ����� ��������� � ������������ ��������� �������� 
			//� ������ ����� ����������� ����� ����������� ����� ����� ��� �������� ��������� �� ������ �������
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
}

void ConnectionListener::ClientHandler(int index)
{
	RequestType req;
	std::string msg_response;
	int msg_size;
	while (true)
	{
		if (recv(Connections[index], (char*)&req, sizeof(RequestType), NULL) == -1)
		{
			for (int i = 0; i < _loggingData.size(); i++)
			{
				if (_loggingData[i].second == Connections[index])
				{
					_loggingData[i].second = 0;
					std::cout << "Client � " << index + 1 << " disconnected from server" << std::endl;
				}

			}
			break;
		}

		switch (req)
		{
		case  RequestType::LOGIN: {
			//login
			recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			char* client_login = new char[msg_size + 1];
			client_login[msg_size] = '\0';
			recv(Connections[index], client_login, msg_size, NULL);
			//password
			recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			char* client_password = new char[msg_size + 1];
			client_password[msg_size] = '\0';
			recv(Connections[index], client_password, msg_size, NULL);

			LoggingResponse lr = checkData(client_login, client_password, Connections[index]);
			send(Connections[index], (char*)&lr, sizeof(LoggingResponse), NULL);
			break;
		}
		case  RequestType::GETPATIENT: {

			try
			{
				msg_response = _optData.Packing(_patient.GetPatient());
			}
			catch (std::out_of_range)
			{
				msg_response = "Queue is empty";
			}
			msg_size = msg_response.size();
			send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[index], msg_response.c_str(), msg_size, NULL);
			break;
		}
		case  RequestType::LOGOUT: {
			for (int i = 0; i < _loggingData.size(); i++)
			{
				if (_loggingData[i].second == Connections[index])
					Connections[index] = 0;
			}
			break;
		}
		}

	}
}

ConnectionListener::LoggingResponse ConnectionListener::checkData(const std::string& login, const std::string& password, SOCKET socket)
{
		for (int i = 0; i < _loggingData.size(); i++)
		{
			if (_loggingData[i].first.first == login && _loggingData[i].first.second == password)
				if (!_loggingData[i].second)
				{
					_loggingData[i].second = socket;
					return LoggingResponse::CORRECT;
				}
				else
					return LoggingResponse::AOS;
		}
		return LoggingResponse::INCORRECT;
}


ConnectionListener::ConnectionListener(const char* ip_addr, int port)
{
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

	//������ � ������:
	std::pair<std::string, std::string> loPas1("hv", "123");
	std::pair<std::string, std::string> loPas2("atom", "345");
	std::pair<std::pair<std::string, std::string>, SOCKET> user1(loPas1, 0);
	std::pair<std::pair<std::string, std::string>, SOCKET> user2(loPas2, 0);
	_loggingData.push_back(user1);
	_loggingData.push_back(user2);


	Listen(sizeofaddr);
}


