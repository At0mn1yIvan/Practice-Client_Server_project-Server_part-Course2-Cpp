#pragma once

#include "Patient.h"
#include "VIP_Patient.h"
#include "Queue.h"
#include <iostream>


class PatientRepository
	// добавление и обработка клиентов в очереди 
{
private:
	Queue<Patient> _patients;
	Queue<VIP_Patient> _VipPatients;
public:
	PatientRepository() {
		//VIP_Patient p1 = VIP_Patient("name1", "surname1", "patromymic1", State::Regular, 10000);
		Patient p2 = Patient("name2", "surname2", "patromymic2", State::Regular);
		Patient p3 = Patient("name3", "surname3", "patromymic3", State::Critical);
		VIP_Patient p4 = VIP_Patient("name4", "surname4", "patromymic4", State::Regular, 30000);
		//AddPatient(p1);
		AddPatient(p2);
		AddPatient(p3);
		AddPatient(p4);
	}

	Patient GetPatient() {
		if (!_patients.isEmpty() || !_VipPatients.isEmpty()) {
			if (_patients.Top() > _VipPatients.Top()) return _patients.Pop();
			else return _VipPatients.Pop();
		}
		else
			throw std::out_of_range("Queue is empty");
	}

	void AddPatient(Patient& patient) {
		VIP_Patient* cast = dynamic_cast<VIP_Patient*>(&patient);
		if (cast != nullptr){
			_VipPatients.PriorityPush(*cast);
		}
		else
		{
			_patients.PriorityPush(*patient);
		}
	}
};

