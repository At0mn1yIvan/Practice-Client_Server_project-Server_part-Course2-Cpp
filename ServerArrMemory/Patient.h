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
	Patient() : _patientState(State::Undefined){}

	Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state) : _name(firstName),
		_surname(lastName),
		_patronymic(patronymic),
		_patientState(state)
	{}

	std::string GetFirstName() const {
		return _name;
	}
	std::string GetLastName() const {
		return _surname;
	}
	std::string GetPatronymic() const {
		return _patronymic;
	}
	State GetState() const {
		return _patientState;
	}

	virtual ~Patient() {}


	bool operator>(const Patient& p) const
	{
		if (this->GetState() > p.GetState())
			return true;
		else
			return false;
	}
	
};








