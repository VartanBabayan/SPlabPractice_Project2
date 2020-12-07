#pragma once

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