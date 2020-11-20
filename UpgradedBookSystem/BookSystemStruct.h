#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <exception>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

// Object Book
class BookInfo {
private:
	std::string bookName{};
	std::string authorName{};
	unsigned int copiesQuantity{};

public:
	BookInfo() {}

	BookInfo(std::string bookName, std::string authorName, int quantity)
		: bookName(bookName),
		authorName(authorName),
		copiesQuantity(quantity)
	{
	}

	friend void to_json(json& j, const BookInfo& p);
	friend void from_json(const json& j, BookInfo& p);

	~BookInfo() {}
};

// class that simulate all my BookSystem
class BookSystem {
private:
	json BookStorage = json::array();

public:
	void AddBookRecords(const json& book);
	void ShowBookRecords() const;
	bool CheckAvailability(const json& book) const;
	void ModifyBookRecords();
	void DeleteBookRecords(const json& book);

	json InputedInformation() const; // book parsed into json
	json inputToFindBook() const;

	bool isBaseEmpty() const;

	void readJSON();
	void writeJson();

	~BookSystem() {}
};