#include "JSONBookSystemStruct.h"
#include "ReadWriteToBase.h"

void Menu()
{
	std::cout << "\t\t ***Bookshop Management System*** \n\n";
	std::cout << "\t\t\t 1. Add Book Records \n"
		<< "\t\t\t 2. Show Book Records \n"
		<< "\t\t\t 3. Check Availability \n"
		<< "\t\t\t 4. Modify Book Records \n"
		<< "\t\t\t 5. Delete Book Records \n"
		<< "\t\t\t 6. Quit \n";
}

bool isRightInput(std::string& choice)
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

int main()
{
	DataBaseInterface* MainSystem = new JSONBookSystem;
	JSONBaseWorker Manager;

	Manager.readJSON(); // first of all read the Base

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
			MainSystem->AddBookRecords();
			break;
		}

		case '2':
		{
			if (Manager.isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			MainSystem->ShowBookRecords();
			break;
		}

		case '3':
		{
			if (Manager.isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			MainSystem->CheckAvailability();
			break;
		}

		case '4':
		{
			if (Manager.isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}


			MainSystem->ModifyBookRecords();
			break;
		}

		case '5':
		{
			if (Manager.isBaseEmpty())
			{
				std::cout << "Sorry, There is no books in our Storage yet\n";
				std::cout << "Add some books before doing something\n";

				continue;
			}

			MainSystem->DeleteBookRecords();
			break;
		}

		case '6':
		{
			Manager.writeJSON(); // in the end write to the Base new info
			return EXIT_SUCCESS;
		}

		}
	}
}