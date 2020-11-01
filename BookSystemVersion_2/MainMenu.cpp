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

int main()
{
	Menu();

	BookSystem MainSystem;
	MainSystem.readJSON();
	while (true)
	{
		std::cout << "Enter your choice: ";
		//assert(choice >= 1 && choice <= 6);

		int choice;
		try
		{
			std::cin >> choice;

			if (!(choice >= 1 && choice <= 6))
			{
				throw "Our System can not treat your request, please verify that you choose one of this steps: \n";
			}
		}
		catch (const char* exception) // ���������� ���������� ���� const char*
		{
			std::cerr << "Error: " << exception << '\n';
			Menu();
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			MainSystem.AddBookRecords(MainSystem.InputedInformation());
			break;
		}

		case 2:
		{
			MainSystem.ShowBookRecords();
			break;
		}

		case 3:
		{
			MainSystem.CheckAvailability(MainSystem.InputedInformation());
			break;
		}

		case 4:
		{
			MainSystem.ModifyBookRecords();
			break;
		}

		case 5:
		{
			MainSystem.DeleteBookRecords(MainSystem.InputedInformation());
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