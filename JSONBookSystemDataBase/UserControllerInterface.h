#include <iostream>
#include "ClassBook.h"

// class to proccess user request
class UserRequestManager
{
public:
	json BookInputedInformation() const; // book parsed into json
	json inputToFindBook() const;
};