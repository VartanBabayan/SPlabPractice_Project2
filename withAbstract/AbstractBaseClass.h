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

class DataBaseBookSystem
{
public:
	virtual void AddBookRecords(const json& book) = 0;
	virtual void ShowBookRecords() const = 0;
	virtual bool CheckAvailability(const json& book) const = 0;
	virtual void ModifyBookRecords(const json& book) = 0;
	virtual void DeleteBookRecords(const json& book) = 0;
	virtual void Run() = 0;

	virtual ~DataBaseBookSystem() { }
};