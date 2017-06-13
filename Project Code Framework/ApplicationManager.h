#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include <stack>
#include <vector>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stack;

//Forward declaration better than including the header file
class Action;
class Component;
class InputPin;
class OutputPin;
class Led;
class Switch;
class Connection;
//End forward declaration

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	int ConnCount;		//Actual number of Connections
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	vector<Component*> SelectionList;
	vector<Component*> ClipBoard;

	vector <Switch*> sim_switchs;
	vector <Led*> sim_leds;

	stack <Action*> UndoActions;
	stack <Action*> RedoActions;

	int ActionLevel;

	bool UpdateToolBar;

public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	void FastUpdateInterface(); //Redraws Only the drawing area to be more efficient

	void DrawNonSelectedItems(); //Redraws only non-selected (Move action)

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();


	//undo and redo latest action  
	void undo();
	void redo();
	
	//clears the undo and redo stacks and DELETE All actions in both stacks
	void flush_redo();
	void flush_undo();

	//Reset the action balance counter (if the balance is zero, then save is disabled)
	void ResetActionLevel();

	//Saving and Loading functions
	void SaveFile(ofstream& file);
	void LoadFile(ifstream& file);

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Function to avoid overlap when adding a new gate
	bool CheckConflict_GATE(const GraphicsInfo& gfx)const;

	//Function to avoid overlap when multimoving
	bool CheckConflict_MOVE(const GraphicsInfo& gfx)const;

	void HighlightPinsAT(int x,int y);

	//For Selection in Design Mode: Returns Componenent At the given point
	Component* GetComponentAt(int x,int y);

	//Just Remove DONT delete to be able to undo this action
	void RemoveByID(int compID);

	//Just Remove DONT delete to be able to undo this action
	void RemoveByPTR(Component* comp);


	//Get ClipBoard (Paste Action)
	vector <Component*> GetClipBoard();
	
	//SetClipBoard (Cut/Copy Action)
	void SetClipBoard(const vector <Component*>& list);

	//For Select Action
	vector <Component*> GetSelectedComponentList();
	vector <Component*> GetComponentsInsideAndSelect(const GraphicsInfo& Rectangle);
	void SelectComponentsInside(const GraphicsInfo& Rectangle); //Same functionality as "GetComponentsInsideAndSelect" but used in an attempt to reduce overhead when multiselecting
	void SetSelectedComponentList(const vector <Component*>& list);
	void ResetSelectedComponentList();

	//In some cases we need to unselect all. example changing to simulation we must un select
	void DestroySelectionList();
	
	//Returns the Pins found at X and Y within the allowed precision +/- 5 pass by ref to adjust them accuartly
	OutputPin* ReturnOutputPinAT(int& x,int& y);
	InputPin* ReturnInputPinAT(int& x,int& y);

	//For the simulation : Validate the circuit, returns int code representing the errors in the circuit
	int ValidateCircuit();

	//Creating the Simulation Parameters at start of the simulation
	void CreateSimulationParameters();

	//Resetting the simulation parameters at the end of the simulation
	void DestroySimulationParameters();

	//This is where the simulation takes place
	void OperateCicuit();

	//When Finishing the simulation 
	void ResetCircuit();
	
	//For TruthTable
	vector <Switch*> get_all_switch();
	vector <Led*> get_all_leds();

	//Resetting the App removing everything from the scratch as we are opening the app for the first time
	//Needed for loading new files 
	void ResetApp();

	//destructor
	~ApplicationManager();
};

#endif