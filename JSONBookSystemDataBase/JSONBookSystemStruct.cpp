#include "JSONBookSystemStruct.h"

json JSONBookSystem::BookStorage = json::array();

void JSONBookSystem::AddBookRecords()
{
	json book = inputInfo.BookInputedInformation();

	// case when user inputed book that already in Base we increase the Quantity of given book
	bool isBookAlreadyInBase = false;
	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
		{
			isBookAlreadyInBase = true;

			int firstQuantity = BookStorage[i].at(BookQuantity);
			int secondQuantity = book.at(BookQuantity);
			BookStorage[i].at(BookQuantity) = std::to_string(firstQuantity + secondQuantity);
		}
	}

	if(isBookAlreadyInBase)
		return;


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

bool JSONBookSystem::CheckAvailability() const
{
	json book = inputInfo.inputToFindBook();

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

void JSONBookSystem::ModifyBookRecords()
{	
	std::cout << "Enter Information about the book you want to edit: \n";
	
	json book = inputInfo.inputToFindBook();
	bool isBookInBase = false;
	for (int i = 0; i < BookStorage.size(); ++i) 
	{
		if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
			isBookInBase = true;
	}

	if (isBookInBase)
	{
		std::cout << "\nOur BookStorage contains this book \n";
		std::cout << "\nEnter new information about this book: \n";
		json modified = inputInfo.BookInputedInformation();

		for (int i = 0; i < BookStorage.size(); ++i)
		{
			if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
				BookStorage[i] = modified;
		}

		std::cout << "\nModified Succesfully\n\n";
		return;
	}

	std::cout << "\nSorry, our BookStorage does not contain this book\n";
}

void JSONBookSystem::DeleteBookRecords()
{
	json book = inputInfo.inputToFindBook();
	bool isBookInBase = false;
	for (int i = 0; i < BookStorage.size(); ++i)
	{
		if (BookStorage[i][BookName] == book[BookName] && BookStorage[i][AuthorName] == book[AuthorName])
			isBookInBase = true;
	}

	if (isBookInBase)
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
}