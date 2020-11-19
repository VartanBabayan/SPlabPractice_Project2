#include "BookSystemStruct.h"

//functions "to_json" and "from_json" to work with Object "BookInfo"
void to_json(json& BookStorage, const BookInfo& p) {
	BookStorage = json{ {"BookName", p.bookName}, {"AuthorName", p.authorName}, {"BookQuantity", p.copiesQuantity} };
}

void from_json(const json& BookStorage, BookInfo& p) {
	BookStorage.at("BookName").get_to(p.bookName);
	BookStorage.at("AuthorName").get_to(p.authorName);
	BookStorage.at("BookQuantity").get_to(p.copiesQuantity);
}

// to read JSON when program starts
void BookSystem::readJSON()
{
	std::ifstream fin("Base.json");

	if (!fin) // checking if some problems with file
	{
		std::cout << "There is some error to open the file, please reboot the program\n";
		exit(EXIT_FAILURE);
	}

	std::string tempInfo;
	while (std::getline(fin, tempInfo)) {
		BookStorage.push_back(json::parse(tempInfo)); // parse string to json 
	}
	fin.close();
}

// to change JSON after modifying while program worked
void BookSystem::writeJson()
{
	std::ofstream fout("Base.json", std::ios_base::trunc);

	if (!fout) // checking if some problems with file
	{
		std::cout << "There is some error to open the file, please reboot the program\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < BookStorage.size(); ++i)
		fout << BookStorage[i] << "\n";

	fout.close();
}


// to check if input quantity is contain other chars than numbers
bool isValidInput_Quantity(const std::string& count)
{
	for (int i = 0; i < count.size(); ++i)
	{
		if (!(count[i] >= '0' && count[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}

json BookSystem::InputedInformation() const 
{	
	std::cout << "Information such as name of the book: ";
	std::string bookName{};
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";   
	std::string authorName{};
	std::getline(std::cin, authorName);

	std::cout << "Number of copies should be provided: ";
	std::string count; // to clear buffer and cin new info
	std::getline(std::cin, count);
	
	while (!(isValidInput_Quantity(count)))
	{
		std::cout << "Wrong input, quantity is a number, not string, please try again: \n";

		std::cout << "Number of copies should be provided: ";
		count.clear();
		std::getline(std::cin, count);
	}

	unsigned int quantity;
	quantity = std::stoi(count);

	return json(BookInfo(bookName, authorName, quantity));
}

// using this function to find books only by Name (without quantity)
json BookSystem::inputToFindBook() const
{
	std::cout << "Information such as name of the book: ";
	std::string bookName{};
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";
	std::string authorName{};
	std::getline(std::cin, authorName);

	return json(BookInfo(bookName, authorName, 0));
}

void BookSystem::AddBookRecords(const json& book)
{
	BookStorage.push_back(book);

	std::ofstream fout("Base.json", std::ios_base::out | std::ios_base::app);
	
	if (!fout) //checking if some problems with file
	{
		std::cout << "There is some error to open the file, please reboot the program\n";
		exit(EXIT_FAILURE);
	}

	fout << BookStorage.back() << "\n";
	fout.close();
}

void BookSystem::ShowBookRecords() const
{
	for (int i = 0; i < BookStorage.size(); ++i)
		std::cout << BookStorage[i] << "\n";

	std::cout << "\n";
}

bool BookSystem::CheckAvailability(const json& book) const
{
	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i]["BookName"] == book["BookName"] && BookStorage[i]["AuthorName"] == book["AuthorName"]) 
		{
			std::cout << "\n" << BookStorage[i] << "\n";
			
			std::cout << "Our BookStorage contains this book \n";
			
			return true;
		}
	}

	std::cout << "\nSorry, our BookStorage does not contain this book\n";
	return false;
}

void BookSystem::ModifyBookRecords()
{
	std::cout << "There are " << BookStorage.size() << " books in our Storage \n";
	std::cout << "Enter Information about the book you want to edit: \n";
	json book(inputToFindBook());

	if (CheckAvailability(book))
	{
		std::cout << "Enter new information about this book: \n";
		json modified(InputedInformation());

		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i]["BookName"] == book["BookName"] && BookStorage[i]["AuthorName"] == book["AuthorName"])
				BookStorage[i] = modified;
		}

		std::cout << "\nModified Succesfully\n";
	}
	return;
}

void BookSystem::DeleteBookRecords(const json& book)
{
	if (CheckAvailability(book))
	{
		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i]["BookName"] == book["BookName"] && BookStorage[i]["AuthorName"] == book["AuthorName"])
				BookStorage.erase(BookStorage.begin() + i);
		}

		std::cout << "\n\nDeleted Succesfully\n\n";
		return;
	}
	std::cout << "\nSomething went wrong, No such book to delete in our System \n";
	return;
}
