#pragma once

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#define BookName "BookName" 
#define AuthorName "AuthorName"
#define BookQuantity "BookQuantity" 

// Object Book to work with JSON
class BookInfo 
{
private:
	std::string bookName{};
	std::string authorName{};
	unsigned int copiesQuantity{};

public:
	BookInfo() {}

	BookInfo(const std::string& bookName, const std::string& authorName, const int quantity);

	friend void to_json(json& BookStorage, const BookInfo& p);
	friend void from_json(const json& BookStorage, BookInfo& p);

	~BookInfo() {}
};