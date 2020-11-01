#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

//Object Book
class BookInfo {
private:
	std::string bookName;
	std::string authorName;
	unsigned int copiesQuantity;

public:
	BookInfo() {}

	BookInfo(std::string bookName, std::string authorName, unsigned int quantity)
		: bookName(bookName),
		authorName(authorName),
		copiesQuantity(quantity)
	{
	}

	friend void to_json(json& j, const BookInfo& p);
	friend void from_json(const json& j, BookInfo& p);

	~BookInfo() {}
};

//class that simulate all my BookSystem
class BookSystem {
private:
	std::vector<std::string> BookStorage;
	json j = json::array();
	
public:
	void AddBookRecords(BookInfo book);
	void ShowBookRecords();
	bool CheckAvailability(BookInfo book);
	void ModifyBookRecords();
	void DeleteBookRecords(BookInfo book);
	
	void readJSON();
	void writeJson();

	~BookSystem() {}
};




