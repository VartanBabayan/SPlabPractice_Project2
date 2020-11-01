#include "BookSystemStruct.h"

//functions "to_json" and "from_json" to work with Object "BookInfo"
void to_json(json& j, const BookInfo& p) {
	j = json{ {"BookName", p.bookName}, {"AuthorName", p.authorName}, {"BookQuantity", p.copiesQuantity} };
}

void from_json(const json& j, BookInfo& p) {
	j.at("BookName").get_to(p.bookName);
	j.at("AuthorName").get_to(p.authorName);
	j.at("BookQuantity").get_to(p.copiesQuantity);
}

//to read JSON when program starts
void BookSystem::readJSON()
{
	std::ifstream fin("Base.json");

	std::string tempInfo;
	while (std::getline(fin, tempInfo)) {
		j.push_back(json::parse(tempInfo)); //parse string to json 
	}
	fin.close();
}

//to change JSON after modifying while program worked
void BookSystem::writeJson()
{
	std::ofstream fout("Base.json", std::ios_base::trunc);
	for (int i = 0; i < j.size(); ++i)
		fout << j[i] << "\n";

	fout.close();
}

json BookSystem::InputedInformation()
{
	std::cout << "Information such as name of the book: ";
	std::string bookName;
	std::cin.ignore();
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";
	std::string authorName;
	std::getline(std::cin, authorName);

	std::cout << "Number of copies should be provided: ";
	unsigned int quantity;
	std::cin >> quantity;

	return json(BookInfo(bookName, authorName, quantity));
}

void BookSystem::AddBookRecords(json book)
{
	j.push_back(book);

	std::ofstream fout("Base.json", std::ios_base::out | std::ios_base::app);
	fout << j.back() << "\n";
	fout.close();
}

void BookSystem::ShowBookRecords()
{
	if (j.empty())
	{
		std::cout << "Sorry, There is no books in our Storage yet\n";
		return;
	}

	for (int i = 0; i < j.size(); ++i) 
		std::cout << j[i] << "\n";

	std::cout << "\n";
}

bool BookSystem::CheckAvailability(json book)
{	
	for (int i = 0; i < j.size(); ++i)
	{
		if (j[i] == book) {
			std::cout << "\n" << book << "\n";
			std::cout << "Our BookStorage contains this book \n";
			return true;
		}
	}
	std::cout << "\nSorry, our BookStorage does not contain this book\n";
	return false;
}

void BookSystem::ModifyBookRecords()
{
	std::cout << "There are " << j.size() << " books in our Storage \n";
	std::cout << "Enter Information about the book you want to edit: \n";
	json book(InputedInformation());

	if (CheckAvailability(book))
	{
		std::cout << "Enter new information about this book: \n";

		json modified(InputedInformation());
		for (int i = 0; i < j.size(); ++i)
		{
			if (j[i] == book) 
				j[i] = modified;
		}

		std::cout << "\nModified Succesfully\n";
	}
	return;
}

void BookSystem::DeleteBookRecords(json book)
{
	if (CheckAvailability(book))
	{
		for (int i = 0; i < j.size(); ++i)
		{
			if (j[i] == book)
				j.erase(j.begin() + i);
		}

		std::cout << "\n\nDeleted Succesfully\n\n";
		return;
	}
	std::cout << "\nSomething went wrong, No such book to delete in our System \n";
	return;
}
