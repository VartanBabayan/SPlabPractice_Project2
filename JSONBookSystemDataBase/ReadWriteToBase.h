#include "JSONBookSystemStruct.h"

class JSONBaseWorker : public JSONBookSystem
{
public:
	void readJSON();
	void writeJSON();
	bool isBaseEmpty() const;
};