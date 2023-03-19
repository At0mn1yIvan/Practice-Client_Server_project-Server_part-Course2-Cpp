#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> // Библиотека для работы с сетью (2 версия)
#include "PatientRepository.h"
#include <iostream>
#include "DataHandler.h"

#pragma warning(disable: 4996)

// Server
class ConnectionListener
{
private:
	enum class RequestType {
		LOGIN,
		GETPATIENT,
		LOGOUT,
	};


	enum class LoggingResponse {
		AOS,
		CORRECT,
		INCORRECT,
	}; 

	//SOCKET _socket;
	static SOCKET Connections[100];
	static int Counter; // Переменная, хранящая индекс соединения
	static PatientRepository _patient;
	static DataHandler _optData;
	static std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> _loggingData;
	SOCKADDR_IN addr;

	void Listen(int _sizeofaddr);
	static void ClientHandler(int index);
	static LoggingResponse checkData(const std::string& login, const std::string& password, SOCKET socket);

public:
	ConnectionListener(const char* ip_addr, int port);
};


