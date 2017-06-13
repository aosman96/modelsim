#include "ChangeToSimulation.h"
#include "..\ApplicationManager.h"

ChangeToSimulation::ChangeToSimulation(ApplicationManager *pApp):Action(pApp)
{
	CanBeUndone=false;
}

ChangeToSimulation::~ChangeToSimulation(void)
{}

void ChangeToSimulation::ReadActionParameters()
{}

void ChangeToSimulation::Execute()
{
	int simulation_errors=0;
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Validating circuit....");

	simulation_errors=pManager->ValidateCircuit();
	
	string errormsg="Circuit Validation Failed!\n\n";

	if(simulation_errors & PIN_NOT_CONNECT)
		errormsg+=" -- One or more of the pins are not connected\n";
	if(simulation_errors & FIRST_LEVEL_ERROR)
		errormsg+=" -- First circuit level contains components other than switches\n";
	if(simulation_errors & LAST_LEVEL_ERROR)
		errormsg+=" -- Last circuit level contains components other than LEDs\n";
	if(simulation_errors & FEEDBACK)
		errormsg+=" -- A feedback in the circuit\n";
	if(simulation_errors & NOTHING_TO_SIMULATE)
		errormsg+=" -- Nothing to simulate ! \n";

	if(simulation_errors)
	{
		errormsg+="\n";
		pOut->PrintMsg("Simulation Failed");
		pOut->Display_MessageBox(errormsg,"Logic Simulator",MB_OK|MB_ICONERROR);
		pManager->DestroySimulationParameters();
		return;
	}

	pManager->DestroySelectionList();
	pManager->CreateSimulationParameters();

	UI.AppMode=SIMULATION;

	UI.enable_undo=false;
	UI.enable_redo=false;
	UI.enable_paste=false;
	UI.enable_edit=false;
	UI.enable_editconn=false;
	UI.enable_copy_cut_delete=false;

	pOut->PrintMsg("Simulation Started");
	pManager->OperateCicuit();
}

void ChangeToSimulation::Undo()
{}

void ChangeToSimulation::Redo()
{}

