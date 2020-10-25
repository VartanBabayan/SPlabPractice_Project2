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
		BookStorage.push_back(tempInfo);
		j.emplace_back(tempInfo);
	}
	fin.close();
}

//to change JSON after modifying while program worked
void BookSystem::writeJson()
{
	std::ofstream fout("Base.json", std::ios_base::trunc);
	for (int i = 0; i < BookStorage.size(); ++i)
	{
		fout << BookStorage[i] << "\n";
	}
	fout.close();
}

void BookSystem::AddBookRecords(BookInfo book)
{
	j.emplace_back(book);
	BookStorage.push_back(j.back().dump());

	std::ofstream fout("Base.json", std::ios_base::out | std::ios_base::app);
	fout << j.back() << "\n";
	fout.close();
}

void BookSystem::ShowBookRecords()
{
	for(int i = 0; i < BookStorage.size(); ++i)
		std::cout << BookStorage[i] << "\n";

	std::cout << "\n";
}

bool BookSystem::CheckAvailability(BookInfo book)
{	
	json temp(book);

	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i] == temp.dump())
		{
			std::cout << "\n\n" << temp.dump() << "\n";
			std::cout << "Our BookStorage contains this book \n\n";
			return true;
		}
	}
	std::cout << "\n\nSorry, our BookStorage does not contain this book\n\n";
	return false;
}

// !!!Attention!!! Bad code in this function, must be upgraded
void BookSystem::ModifyBookRecords()
{
	std::cout << "There are " << BookStorage.size() << " books in the file \n\n";

	std::cout << "Enter Name of the book to edit: ";
	std::string bookName;
	std::cin.ignore();
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";
	std::string authorName;
	std::getline(std::cin, authorName);

	std::cout << "Number of copies: ";
	int quantity;
	std::cin >> quantity;

	json temp(BookInfo(bookName, authorName, quantity));

	if (CheckAvailability(BookInfo(bookName, authorName, quantity)));
	{
		std::cout << "Enter new information about the book: \n";

		std::cout << "Enter Name of the book: ";
		std::string bookName;
		std::cin.ignore();
		std::getline(std::cin, bookName);

		std::cout << "Author Name: ";
		std::string authorName;
		std::getline(std::cin, authorName);

		std::cout << "Number of copies: ";
		int quantity;
		std::cin >> quantity;
			
		json modified(BookInfo(bookName, authorName, quantity));
		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i] == temp.dump())
			{
				BookStorage[i] = modified.dump();
			}
		}

		std::cout << "\n\nModified Succesfully\n\n";
	}
	return;
}

void BookSystem::DeleteBookRecords(BookInfo book)
{
	json temp(book);

	if (CheckAvailability(book))
	{
		BookStorage.erase(std::remove(BookStorage.begin(), BookStorage.end(), temp.dump()));
		std::cout << "\n\nDeleted Succesfully\n\n";
		return;
	}
	std::cout << "\n\nSomething went wrong, No such book to delete in our System \n\n";
	return;
}
