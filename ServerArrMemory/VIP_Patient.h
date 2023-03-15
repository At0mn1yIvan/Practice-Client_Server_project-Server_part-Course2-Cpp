#pragma once
#include "Patient.h"

class VIP_Patient : public Patient {
protected:
	size_t _moneyAmount;
public:
	VIP_Patient(): Patient(){}

	VIP_Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state,
		size_t moneyAmount = 1000) : Patient(firstName, lastName, patronymic, state), _moneyAmount(moneyAmount) {}

	size_t GetMoney() const { return _moneyAmount; }


	bool operator>(const VIP_Patient& p) const
	{
		if (this->GetState() == p.GetState() && this->GetMoney() > p.GetMoney())
			return true;
		else if (this->GetState() > p.GetState())
			return true;
		else
			return false;
	}
};

