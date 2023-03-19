#pragma once
#include <string>
#include "Patient.h"
#include <nlohmann/json.hpp>
#include "VIP_Patient.h"

using json = nlohmann::json;

class DataHandler
{
public:
	static std::string Packing(const Patient& p);   //To JSON
	static std::string Packing(const VIP_Patient& vp);   //To JSON
	static Patient Unpacking(const std::string& str); // from JSON to data
};

