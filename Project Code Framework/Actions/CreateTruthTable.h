#ifndef _CreateTruthTable_H
#define _CreateTruthTable_H

#include "action.h"
#include <vector>
#include <string>

using std::vector;
using std::string;
class Led;
class Switch;

class CreateTruthTable :public Action
{
	int combinations;
	vector<Led*> leds;
	vector<Switch*> switches;
	bool SaveToFile;
	string File;
	string **table;
	int rows;
	int columns;
	void PrintIntoAfile();
	void PrintIntoSimArea();
public:
	CreateTruthTable(ApplicationManager *pApp);
	virtual ~CreateTruthTable(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif