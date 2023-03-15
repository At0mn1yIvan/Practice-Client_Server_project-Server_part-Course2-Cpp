#pragma once
#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // Библиотека для работы с сетью (2 версия)
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
	//static int Counter; // Переменная, хранящая индекс соединения
	static PatientRepository _patient;
	static DataHandler _optData;
	SOCKADDR_IN addr;
	void Listen(int _sizeofaddr) {
		//Создание сокета. 
	//Сокет - виртуальная конструкция из IP-адреса и номера порта. Она предназначена для того, чтобы программы могли передавать данные друг другу даже в пределах одного компьютера
		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //AF_INET указывает на то, что будет использоваться семейство интернет-протоколов;SOCK_STREAM указывает на протокол, содержащий соединение

		//Для привязки адреса сокету используется функция bind
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

		//После того, как локальный адрес и порт привязаны к сокету, нужно приступить к прослушиванию порта в ожидании соединения со стороны клиента
		listen(sListen, SOMAXCONN); //По первому параметру ф-ия определяет, по какому порту можно запустить прослушивание. Второй параметр - максимально допустимое число запросов, ожидающих обработки

		SOCKET newConnection;
		for (int i = 0; i < 100; i++) {
			newConnection = accept(sListen, (SOCKADDR*)&addr, &_sizeofaddr); // accept возвращает указатель на новый сокет;После выполнения функции accept второй параметр будет держать сведения об IP-адресе клиента, который произвел подключение 
			if (newConnection == 0) {
				std::cout << "Error #2 \n";
			}
			else {
				std::cout << "Client Connected! \n";
				Connections[i] = newConnection;
				//Counter++;
				//После выполнения следующей функции у нас будут работать два потока
				//Одновременно функцией main будут приниматься новые соединения, а в процедуре ClientHandler будут ожидаться и отправляться сообщения клиентам 
				//С каждым новым соединением будет запускаться новый поток для принятия сообщения от нового клиента
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			}
		}

	}


public:
	
	ConnectionListener(const char* ip_addr, int port) {
		WSAData wsaData; // Структура, содержащая сведения о реализации сокетов Windows 
		WORD DLLVersion = MAKEWORD(2, 2); //Запрашиваемая версия библиотеки winsock
		if (WSAStartup(DLLVersion, &wsaData) != 0) { //Функция для загрузки библиотеки (запрашивает версию 2.2 Winsock в системе и задает в качестве самой высокой версии Windows Sockets поддержки
			std::cout << "Error" << std::endl;
			exit(1);
		}

		//После загрузки библиотеки необходимо заполнить информацию об адресе сокета
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr(ip_addr); // Структура для хранения IP-адреса
		addr.sin_port = htons(port); // Порт для идентификации программы, с поступающими данными, данный порт должен быть свободен
		addr.sin_family = AF_INET; // Семейство протоколов. Для интернет протоколов указывается константа AF_INET

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


