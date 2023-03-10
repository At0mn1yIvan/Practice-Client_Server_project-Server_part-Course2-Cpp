#pragma once

#include "Patient.h"
#include "Queue.h"
#include <iostream>


class PatientRepository
	// добавление и обработка клиентов в очереди 
{
private:
	Queue<Patient> _patients;
public:
	PatientRepository() {
		Patient = 
		VIP_Patient = 
	
	
	}

	Patient GetPatient() {
		if (!_patients.isEmpty())
			_patients.Pop();
		else
			throw std::out_of_range("Queue is empty");
	}

	void AddPatient(Patient& patient) {
		if (dynamic_cast<VIP_Patient*>(&patient) == nullptr){
			
		}
		_patients.Push(patient);
	}
};

