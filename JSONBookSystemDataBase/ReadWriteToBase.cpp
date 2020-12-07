#include "ReadWriteToBase.h"

// to read JSON when program starts
void JSONBaseWorker::readJSON()
{
	std::ifstream fin(BaseFileName);
	
	// NOT WORKING WITH THIS "IF" IN LINUX
	/* if (!fin) // checking if some problems with file
	{
		std::cout << "There is some error to open the file, please reboot the program\n";
		exit(EXIT_FAILURE);
	} */

	std::string tempInfo;
	while (std::getline(fin, tempInfo)) {
		BookStorage.push_back(json::parse(tempInfo)); // parse string to json 
	}
	fin.close();
}

// to change JSON after modifying while program worked
void JSONBaseWorker::writeJSON()
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

bool JSONBaseWorker::isBaseEmpty() const
{
	return BookStorage.empty();
}