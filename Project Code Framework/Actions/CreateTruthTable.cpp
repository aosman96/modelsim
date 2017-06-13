#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\Led.h"
#include <fstream>
using std::ofstream;

CreateTruthTable::CreateTruthTable(ApplicationManager *pApp):Action(pApp),table(NULL)
{
	leds=pManager->get_all_leds();
	switches=pManager->get_all_switch();

	combinations = 1 << switches.size();
	
	SaveToFile=false;
	CanBeUndone=false;
}

CreateTruthTable::~CreateTruthTable(void)
{
}

void CreateTruthTable::ReadActionParameters()
{
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	int ans=0;
	int n_leds=leds.size();
	int n_switches=switches.size();
	
	if(switches.size()>4)
	{
		ans=pOut->Display_MessageBox("Truth Table is too large.\nExport to a text file instead?","Logic Simulator",MB_OKCANCEL|MB_ICONQUESTION);
		if(ans==IDOK)
			SaveToFile=true;
	}
	if(SaveToFile)
		SaveToFile=pIn->GetExportFilename(File);
}

void CreateTruthTable::Execute()
{
	//Get Center point of the Gate
	Output* pOut = pManager->GetOutput();
	
	ReadActionParameters();

	if(switches.size()>4 && !SaveToFile)
		return;
	
	int n_switches=switches.size();
	int n_leds=leds.size();

	rows=combinations+1;		//Additional one for the headings
	columns=n_switches + n_leds;

	table = new string*[rows];
	for(int i=0;i<rows;i++)
		table[i]=new string[columns];

	int bit_mask=1;
	STATUS on;

	STATUS* Intial_condions=new STATUS[n_switches];


	for(int x=0;x<n_switches;x++){
		Intial_condions[x]=switches[x]->GetOutPinStatus();
		table[0][x]=switches[x]->GetLabel();
	}

	for(int i=0;i<n_leds;i++)
		table[0][n_switches+i]=leds[i]->GetLabel();

	for(int i=0;i<combinations;i++)
	{
		bit_mask=1;

		for(int j=n_switches-1;j>=0;j--)
		{
			on=(i & bit_mask)? HIGH:LOW;
			switches[j]->set_status(on);
			table[i+1][j]=(on?"1" : "0");
			bit_mask <<= 1;
		} 
		pManager->OperateCicuit(); //Operating the circuit in each combination is too costly,any smarter idea ?
		for(int j=0;j<n_leds;j++)
		{
			on=leds[j]->GetOpStatus();
			table[i+1][n_switches+j]=(on?"1" : "0");
		}
	}


	for(int i=0;i<n_switches;i++)
		switches[i]->set_status(Intial_condions[i]);

	pManager->OperateCicuit();

	if(SaveToFile)
		PrintIntoAfile();
	else{
		pOut->PrintMsg("Close the truth table to continue the simulation...");
		PrintIntoSimArea();
		pOut->PrintMsg("Simulation Started");
	}
	
	for(int i=0;i<rows;i++)
		delete [] table[i];
	delete [] table;
	delete [] Intial_condions;
}

void CreateTruthTable::PrintIntoAfile()
{
	ofstream out;
	out.open(File);

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			out << table[i][j] << "\t";
		}
		out << endl;
	}

	out.close();
}

void CreateTruthTable::PrintIntoSimArea()
{
	Output* pOut = pManager->GetOutput();
	pOut->DisplayTable(table,rows,columns);
}


void CreateTruthTable::Undo()
{}

void CreateTruthTable::Redo()
{}

