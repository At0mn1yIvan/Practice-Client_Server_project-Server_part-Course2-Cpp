#include "DataHandler.h"

std::string DataHandler::Packing(const Patient& p)
{
	json toJson = json{ {"Firstname", p.GetFirstName()}, {"Lastname", p.GetLastName()}, {"Patronymic", p.GetPatronymic()}, {"State", p.GetState()} };
	return toJson.dump();
}

std::string DataHandler::Packing(const VIP_Patient& vp)
{
	json toJson = json{ {"Firstname", vp.GetFirstName()}, {"Lastname", vp.GetLastName()}, {"Patronymic", vp.GetPatronymic()}, {"State", vp.GetState()}, {"Money", vp.GetMoney()} };
	return toJson.dump();
}

Patient DataHandler::Unpacking(const std::string& str)
{
	json fromJson = json::parse(str);
	if (fromJson.contains("Money")) {
		return VIP_Patient(fromJson.at("Firstname"), fromJson.at("Lastname"), fromJson.at("Patronymic"), fromJson.at("State"), fromJson.at("Money"));
	}
	else {
		return Patient(fromJson.at("Firstname"), fromJson.at("Lastname"), fromJson.at("Patronymic"), fromJson.at("State"));

	}
}

