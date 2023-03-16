#include "ConnectionListener.h"


SOCKET ConnectionListener::Connections[100];
int ConnectionListener::Counter = 0; 
PatientRepository ConnectionListener::_patient;
//std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> ConnectionListener::_loggingData;