#pragma once
#include "AbstractBaseClass.h"
#include "ClassBook.h"

// class that simulate all JSONBookSystem
class JSONBookSystem : public DataBaseBookSystem {
private:
	json BookStorage = json::array();
	void Menu();

public:
	void AddBookRecords(const json& book) override;
	void ShowBookRecords() const override;
	bool CheckAvailability(const json& book) const override;
	void ModifyBookRecords(const json& book) override;
	void DeleteBookRecords(const json& book) override;
	void Run() override;

	json BookInputedInformation() const; // book parsed into json
	json inputToFindBook() const;

	bool isBaseEmpty() const;
	bool isRightInput(std::string& choice);

	void readJSON();
	void writeJson();

	virtual ~JSONBookSystem() {}
};