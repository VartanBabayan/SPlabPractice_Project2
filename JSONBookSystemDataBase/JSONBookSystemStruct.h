#pragma once
#include "DataBaseInterface.h"
#include "UserControllerInterface.h"

// class that simulate all JSONBookSystem
class JSONBookSystem : public DataBaseInterface 
{
protected:
	static json BookStorage;
	UserRequestManager inputInfo;

public:
	void AddBookRecords() override;
	void ShowBookRecords() const override;
	bool CheckAvailability() const override;
	void ModifyBookRecords() override;
	void DeleteBookRecords() override;

	virtual ~JSONBookSystem() {}
};