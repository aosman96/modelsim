#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"
#include <string>
using std::string;
class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	int LastX,LastY; //last point click by the user. usefull in select and sim actions
public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	void GetLastPointClicked(int &x, int &y);	//Get the last point clicked
	string GetString(Output*,string Message="", string str="");		//Returns a string entered by the user
	clicktype GetMouseClick(int &iX,int &iY); //Added by karim
	void GetMouseCoord(int &iX,int &iY) const; //Added By karim
	ActionType GetUserAction(); //Reads the user click and maps it to an action
	keytype GetKeyPress(char& cKeyData);
	keytype GetKeyPressType();
	clicktype WaitMouseClick(int& x,int& y);
	buttonstate GetMouseButtonState(button b,int& x,int& y);
	bool GetOpenFilename(string &str);
	bool GetSaveFilename(string &str);
	bool GetExportFilename(string &str);

	~Input();
};
