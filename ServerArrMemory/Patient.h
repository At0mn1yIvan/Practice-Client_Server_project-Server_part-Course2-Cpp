#pragma once
#include <string>

enum class State {
	Regular,
	Medium,
	Critical,
	Undefined,
};


class Patient
{
protected:
	std::string _name;
	std::string _surname;
	std::string _patronymic;
	State _patientState;
public:
	Patient();
	Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state);
	std::string GetFirstName() const;
	std::string GetLastName() const;
	std::string GetPatronymic() const;
	State GetState() const;
	virtual ~Patient();
	bool operator>(const Patient& p) const;

};








