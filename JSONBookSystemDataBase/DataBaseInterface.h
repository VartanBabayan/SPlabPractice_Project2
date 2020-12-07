#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <exception>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#define BaseFileName "Base.json"

class DataBaseInterface 
{
public:
	virtual void AddBookRecords() = 0;
	virtual void ShowBookRecords() const = 0;
	virtual bool CheckAvailability() const = 0;
	virtual void ModifyBookRecords() = 0;
	virtual void DeleteBookRecords() = 0;

	virtual ~DataBaseInterface() { }
};