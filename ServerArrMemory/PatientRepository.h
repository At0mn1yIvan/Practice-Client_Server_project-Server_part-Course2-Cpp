#pragma once

#include "Patient.h"
#include "VIP_Patient.h"
#include "Queue.h"
#include <iostream>


class PatientRepository
	// ���������� � ��������� �������� � ������� 
{
private:
	Queue<Patient> _patients;
	Queue<VIP_Patient> _VipPatients;
public:
	PatientRepository();
	Patient GetPatient();
	void AddPatient(Patient& patient);
};

