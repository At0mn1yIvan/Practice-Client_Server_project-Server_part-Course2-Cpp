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
private:
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

	std::string GetFirstName() {
		return _name;
	}
	std::string GetLastName() {
		return _surname;
	}
	std::string GetPatronymic() {
		return _patronymic;
	}
	State GetState() const {
		return _patientState;
	}

	virtual ~Patient();

};



class VIP_Patient : public Patient {
private:
	size_t moneyAmount;
public:
	VIP_Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state,
		size_t _moneyAmount = 1000): Patient(firstName, lastName, patronymic, state), moneyAmount(_moneyAmount) {
		
	}

	size_t getMoney() { return moneyAmount; }
};




