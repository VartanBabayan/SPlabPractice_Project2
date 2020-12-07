#include "UserControllerInterface.h"

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

json UserRequestManager::BookInputedInformation() const
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
		std::cout << "Wrong input, quantity is a number, not string, please try again: \n\n";

		std::cout << "Number of copies should be provided: ";
		count.clear();
		std::getline(std::cin, count);
	}

	unsigned int quantity;
	quantity = std::stoi(count);

	return json(BookInfo(bookName, authorName, quantity));
}

// using this function to find books only by Name (without quantity)
json UserRequestManager::inputToFindBook() const
{
	std::cout << "Information such as name of the book: ";
	std::string bookName{};
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";
	std::string authorName{};
	std::getline(std::cin, authorName);

	return json(BookInfo(bookName, authorName, 0));
}