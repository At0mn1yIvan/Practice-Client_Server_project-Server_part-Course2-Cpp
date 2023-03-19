#include "Patient.h"

Patient::Patient()
{
}

Patient::Patient(const std::string& firstName, const std::string& lastName, const std::string& patronymic, State state) : _name(firstName),
_surname(lastName),
_patronymic(patronymic),
_patientState(state)
{}

std::string Patient::GetFirstName() const
{
	return _name;
}

std::string Patient::GetLastName() const
{
	return _surname;
}

std::string Patient::GetPatronymic() const
{
	return _patronymic;
}

State Patient::GetState() const
{
	return _patientState;
}

Patient::~Patient()
{
}

bool Patient::operator>(const Patient& p) const
{
	if (this->GetState() > p.GetState())
		return true;
	else
		return false;
}
