#pragma once
#include "Patient.h"

class VIP_Patient : public Patient {
private:
	size_t _moneyAmount;
public:
	VIP_Patient();
	VIP_Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state,
		size_t moneyAmount = 1000);
	size_t GetMoney() const;
	bool operator>(const VIP_Patient& p) const;
};



