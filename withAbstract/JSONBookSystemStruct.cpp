#include "JSONBookSystemStruct.h"

void JSONBookSystem::Menu()
{
	std::cout << "\t\t ***Bookshop Management System*** \n\n";
	std::cout << "\t\t\t 1. Add Book Records \n"
		<< "\t\t\t 2. Show Book Records \n"
		<< "\t\t\t 3. Check Availability \n"
		<< "\t\t\t 4. Modify Book Records \n"
		<< "\t\t\t 5. Delete Book Records \n"
		<< "\t\t\t 6. Quit \n";
}

void JSONBookSystem::AddBookRecords(const json& book)
{
	if (CheckAvailability(book)) // case when user inputed book that already in Base we increase the Quantity of given book
	{
		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
			{
				int firstQuantity = BookStorage[i].at(BookQuantity);
				int secondQuantity = book.at(BookQuantity);
				BookStorage[i].at(BookQuantity) = std::to_string(firstQuantity + secondQuantity);
			}
		}
		return;
	}

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

void JSONBookSystem::ShowBookRecords() const
{
	for (int i = 0; i < BookStorage.size(); ++i)
		std::cout << BookStorage[i] << "\n";

	std::cout << "\n";
}

bool JSONBookSystem::CheckAvailability(const json& book) const
{
	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName]) 
		{
			std::cout << "\n" << BookStorage[i] << "\n";
			
			std::cout << "Our BookStorage contains this book \n\n";
			
			return true;
		}
	}

	std::cout << "\nSorry, our BookStorage does not contain this book\n";
	return false;
}

void JSONBookSystem::ModifyBookRecords(const json& book)
{	
	std::cout << "\nEnter new information about this book: \n";
	json modified(BookInputedInformation());

	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
			BookStorage[i] = modified;
	}

	std::cout << "\nModified Succesfully\n\n";
}

void JSONBookSystem::DeleteBookRecords(const json& book)
{
	if (CheckAvailability(book))
	{
		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
				BookStorage.erase(BookStorage.begin() + i);
		}

		std::cout << "\n\nDeleted Succesfully\n\n";
		return;
	}
	std::cout << "\nSomething went wrong, No such book to delete in our System \n";
	return;
}

// to read JSON when program starts
void JSONBookSystem::readJSON()
{
	std::ifstream fin(BaseFileName);

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
void JSONBookSystem::writeJson()
{
	std::ofstream fout(BaseFileName, std::ios_base::trunc);

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

json JSONBookSystem::BookInputedInformation() const
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
json JSONBookSystem::inputToFindBook() const
{
	std::cout << "Information such as name of the book: ";
	std::string bookName{};
	std::getline(std::cin, bookName);

	std::cout << "Author Name: ";
	std::string authorName{};
	std::getline(std::cin, authorName);

	return json(BookInfo(bookName, authorName, 0));
}

bool JSONBookSystem::isBaseEmpty() const
{
	return BookStorage.size() == 0;
}

bool JSONBookSystem::isRightInput(std::string& choice)
{
	try
	{
		std::getline(std::cin, choice);

		if (choice.size() != 1)
		{
			throw "Our System can not treat your request, please verify that you choose one of this steps: \n";
		}

		if (!(choice[0] >= '1' && choice[0] <= '6'))
		{
			throw "Our System can not treat your request, please verify that you choose one of this steps: \n";
		}
	}
	catch (const char* exception)
	{
		std::cerr << "Error: " << exception << '\n';

		return false;
	}

	return true;
}

void JSONBookSystem::Run()
{
	readJSON(); // first of all read the Base
	
	Menu();

	std::string choice;
	while (true)
	{
		std::cout << "Enter your choice: ";

		if (!isRightInput(choice)) {
			Menu();
			continue;
		}

		switch (choice[0])
		{
		case '1':
		{
			AddBookRecords(BookInputedInformation());
			break;
		}

		case '2':
		{
			if (isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			ShowBookRecords();
			break;
		}

		case '3':
		{
			if (isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			CheckAvailability(inputToFindBook());
			break;
		}

		case '4':
		{
			if (isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			std::cout << "There are " << BookStorage.size() << " books in our Storage \n";
			std::cout << "Enter Information about the book you want to edit: \n";

			json tempBook = inputToFindBook();
			
			if (!CheckAvailability(tempBook))
				continue;

			ModifyBookRecords(tempBook);
			break;
		}

		case '5':
		{
			if (isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			DeleteBookRecords(inputToFindBook());
			break;
		}

		case '6':
		{
			writeJson(); // in the end write to the Base new info
			return;
		}

		}
	}

}