#include "JSONBookSystemStruct.h"

int main()
{
	DataBaseBookSystem* MainManager = new JSONBookSystem;

	MainManager->Run();

	delete MainManager;

	return EXIT_SUCCESS;
}