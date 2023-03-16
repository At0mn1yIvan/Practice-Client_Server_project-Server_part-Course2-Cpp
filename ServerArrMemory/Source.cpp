#pragma once
#include <iostream>
#include "ConnectionListener.h"

std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> ConnectionListener::_loggingData;


int main(){
	
	ConnectionListener cl("127.0.0.1", 1111);

	return 0;
}