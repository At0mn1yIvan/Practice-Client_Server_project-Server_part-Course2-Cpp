#pragma comment(lib, "ws2_32.lib") // доступ к функционалу
#include <winsock2.h> // Библиотека для работы с сетью (2 версия)
#include <iostream>

#pragma warning(disable: 4996)

//Массив для хранения сокетов
SOCKET Connections[100];
int Counter = 0; // Переменная, хранящая индекс соединения

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
//	// Прежде чем начать работу с сетью, необходимо загрузить нужную библиотеку
//	// Для загрузки библиотеки используется WSAStartup
//
//
//	WSAData wsaData; // Структура, содержащая сведения о реализации сокетов Windows 
//	WORD DLLVersion = MAKEWORD(2, 2); //Запрашиваемая версия библиотеки winsock
//	if (WSAStartup(DLLVersion, &wsaData) != 0) { //Функция для загрузки библиотеки (запрашивает версию 2.2 Winsock в системе и задает в качестве самой высокой версии Windows Sockets поддержки
//		std::cout << "Error" << std::endl;
//		exit(1);
//
//	}
//
//	//После загрузки библиотеки необходимо заполнить информацию об адресе сокета
//	SOCKADDR_IN addr; //Структура, предназначенная для хранения адреса
//	int sizeofaddr = sizeof(addr);
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Структура для хранения IP-адреса
//	addr.sin_port = htons(1111); // Порт для идентификации программы, с поступающими данными, данный порт должен быть свободен
//	addr.sin_family = AF_INET; // Семейство протоколов. Для интернет протоколов указывается константа AF_INET
//
//	//Создание сокета. 
//	//Сокет - виртуальная конструкция из IP-адреса и номера порта. Она предназначена для того, чтобы программы могли передавать данные друг другу даже в пределах одного компьютера
//	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //AF_INET указывает на то, что будет использоваться семейство интернет-протоколов;SOCK_STREAM указывает на протокол, содержащий соединение
//
//	//Для привязки адреса сокету используется функция bind
//	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
//
//	//После того, как локальный адрес и порт привязаны к сокету, нужно приступить к прослушиванию порта в ожидании соединения со стороны клиента
//	listen(sListen, SOMAXCONN); //По первому параметру ф-ия определяет, по какому порту можно запустить прослушивание. Второй параметр - максимально допустимое число запросов, ожидающих обработки
//
//	//Сделаем новый сокет, для удержания соединения с клиентом
//	SOCKET newConnection;
//	for (int i = 0; i < 100; i++) {
//		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr); // accept возвращает указатель на новый сокет;После выполнения функции accept второй параметр будет держать сведения об IP-адресе клиента, который произвел подключение 
//		if (newConnection == 0) {
//			std::cout << "Error #2 \n";
//		}
//		else {
//			std::cout << "Client Connected! \n";
//			std::string msg = "Hola hola UNN";
//			int msg_size = msg.size();
//			send(newConnection, (char*)& msg_size, sizeof(int), NULL); //Функция для передачи длины строки
//			send(newConnection, msg.c_str(), msg_size, NULL); //Функция для передачи строки клиенту
//
//			Connections[i] = newConnection;
//			Counter++;
//			//После выполнения следующей функции у нас будут работать два потока
//			//Одновременно функцией main будут приниматься новые соединения, а в процедуре ClientHandler будут ожидаться и отправляться сообщения клиентам 
//			//С каждым новым соединением будет запускаться новый поток для принятия сообщения от нового клиента
//			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
//		}
//	}
//
//
//	system("pause");
//	return 0;
//}


