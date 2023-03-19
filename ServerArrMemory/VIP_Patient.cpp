#include "VIP_Patient.h"

VIP_Patient::VIP_Patient() : Patient()
{
}

VIP_Patient::VIP_Patient(const std::string& firstName, const std::string& lastName, const std::string& patronymic, State state, size_t moneyAmount) : Patient(firstName, lastName, patronymic, state), _moneyAmount(moneyAmount)
{

}

size_t VIP_Patient::GetMoney() const
{
	return _moneyAmount;
}

bool VIP_Patient::operator>(const VIP_Patient& p) const
{
	if (this->GetState() == p.GetState() && this->GetMoney() > p.GetMoney())
		return true;
	else if (this->GetState() > p.GetState())
		return true;
	else
		return false;
}
