#include "BookSystemStruct.h"

void Menu()
{
	std::cout << "\t\t ***Bookshop Management System*** \n\n";
	std::cout << "\t\t\t 1. Add Book Records \n"
		<< "\t\t\t 2. Show Book Records \n"
		<< "\t\t\t 3.Check Availability \n"
		<< "\t\t\t 4. Modify Book Records \n"
		<< "\t\t\t 5. Delete Book Records \n"
		<< "\t\t\t 6. Quit \n";
}

BookInfo InputedInformation()
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

	return BookInfo(bookName, authorName, quantity);
}


int main()
{
	Menu();

	BookSystem MainSystem;
	MainSystem.readJSON();
	while (true)
	{
		std::cout << "Enter your choice: ";

		unsigned int choice;
		std::cin >> choice;

		assert(choice >= 1 && choice <= 6);

		switch (choice)
		{
		case 1:
		{
			MainSystem.AddBookRecords(InputedInformation());
			break;
		}

		case 2:
		{
			MainSystem.ShowBookRecords();
			break;
		}

		case 3:
		{
			MainSystem.CheckAvailability(InputedInformation());
			break;
		}

		case 4:
		{
			MainSystem.ModifyBookRecords();
			break;
		}

		case 5:
		{
			MainSystem.DeleteBookRecords(InputedInformation());
			break;
		}

		case 6:
		{
			MainSystem.writeJson();
			return 0;
		}

		}
	}
}