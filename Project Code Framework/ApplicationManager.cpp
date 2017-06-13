#include "ApplicationManager.h"
#include "Utility\RouteFollower.h"
#include "Actions\AllActions.h"
#include "Components\AllComponents.h"
#include "Utility\RTTI.h"

//Although these are implicity included by AllComponents but I prefer to keep them 
#include "Components\InputPin.h"
#include "Components\OutputPin.h"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include <cstring>
using namespace std;

ApplicationManager::ApplicationManager()
{
	ActionLevel = 0;
	CompCount = 0;
	ConnCount = 0;
	
	memset(CompList,NULL,sizeof(CompList));

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
	if(is_a(pComp,Connection))
		ConnCount++;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	ActionType t;
	Component* clickedcomp=NULL;
	int x,y;
	t=InputInterface->GetUserAction(); 	
	if(t==SELECT)
	{
		InputInterface->GetLastPointClicked(x,y);
		clickedcomp=GetComponentAt(x,y);
		if(ReturnOutputPinAT(x,y))
			return ADD_CONNECTION;
		if(!clickedcomp)
			return SELECT;
		else if(clickedcomp->is_selected() && is_not_a(clickedcomp,Connection)) //User clicked on one of the already selected component(s) -> user wants to move them
			return MOVE;

		return SELECT;
	}
	return t;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	UpdateToolBar=false;
	switch (ActType)
	{
		case ADD_Buff:
			pAct = new AddBuff(this);
			break;
		case ADD_INV:
			pAct = new AddNOT(this);
			break;
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_OR_GATE_2:
			pAct= new AddORgate2(this);
			break;
		case ADD_NAND_GATE_2:
			pAct= new AddNANDgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct= new AddNORgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct= new AddXORgate2(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct= new AddXNORgate2(this);
			break;
		case ADD_AND_GATE_3:
			pAct= new AddANDgate3(this);
			break;
		case ADD_OR_GATE_3:
			pAct= new AddORgate3(this);
			break;
		case ADD_NOR_GATE_3:
			pAct= new AddNORgate3(this);
			break;
		case ADD_XOR_GATE_3:
			pAct= new AddXORgate3(this);
			break;
		case ADD_XNOR_GATE_3:
			pAct= new AddXNORgate3(this);
			break;
		case ADD_CONNECTION:
			pAct= new AddConnection(this);
			break;
		case ADD_Switch:
			pAct= new AddSwitch(this);
			break;
		case ADD_LED:
			pAct= new AddLed(this);
			break;
		case SIM_MODE:
			pAct= new SimModeAction(this);
			break;
		case TOOLBAR_SCROLL_NEXT:
			UpdateToolBar=true;
			UI.ScrollCount=SCROLL(int(UI.ScrollCount)+1);
			break;
		case TOOLBAR_SCROLL_BACK:
			UpdateToolBar=true;
			UI.ScrollCount=SCROLL(int(UI.ScrollCount)-1);
			break;
		case TAB_SELECT_API: 
			UpdateToolBar=true;
			UI.SelectedTab=API_TAB;
			break;
		case TAB_SELECT_OPTIONS:
			UpdateToolBar=true;
			UI.SelectedTab=OPTIONS_TAB;
			break;
		case Change_Mode:
			UpdateToolBar=true;
			if(UI.AppMode==DESIGN)
				pAct= new ChangeToSimulation(this);
			else{
				pAct= new ChangeToDesign(this);
				if(!UndoActions.empty()) UI.enable_undo=true;
				if(!RedoActions.empty()) UI.enable_redo=true;
				if(!ClipBoard.empty()) UI.enable_paste=true;
			}
			UI.SelectedTab=API_TAB;
			break;
		case STATUS_BAR:
			OutputInterface->PrintMsg("Ready");
			break;
		case Create_TruthTable:
			pAct= new CreateTruthTable(this);
			break;
		case SAVE:
			UpdateToolBar=true;
			pAct= new SaveFileAction(this);
			break;
		case LOAD:
			UpdateToolBar=true;
			pAct= new OpenFileAction(this);
			break;
		case SELECT:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Select(this);
			break;
		case MOVE:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Move(this);
			break;
		case COPY:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Copy(this);
			break;
		case CUT:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Cut(this);
			break;
		case PASTE:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Paste(this);
			break;
		case DEL:
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			pAct= new Delete(this);
			break;
		case EDIT_Label:
			UpdateToolBar=true;
			pAct= new Edit(this);
			break;
		case RECONNECT:
			UpdateToolBar=true;
			pAct= new EditConnection(this);
			break;
		case DSN_TOOL:
			OutputInterface->PrintMsg("Ready");
			break;
		case UNDO:
			UpdateToolBar=true;
			this->undo();
			break;
		case REDO:
			UpdateToolBar=true;
			this->redo();
			break;
		case EXIT:
			pAct= new Exit(this);
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		if(pAct->CanBe_Undone())
		{
			if(UI.SelectedTab==OPTIONS_TAB) UpdateToolBar=true;
			UndoActions.push(pAct);
			flush_redo();
			UI.enable_redo=false;
			UI.enable_save=true;
			UI.enable_undo=true;
			ActionLevel++;
		}
		else
			delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

vector <Component*> ApplicationManager::GetSelectedComponentList()
{
	return SelectionList;
}

void ApplicationManager::RemoveByID(int CompID)
{
	for(int i=0;i<CompCount;i++)
	{
		if(CompList[i]->GetID()==CompID)
		{
			//No I am not deleting to let UNDO be able to bring it back again 
			//Also note that ApplicationManager is not the creater of it, thus not of 
			//it's responsibility to delete it
			if(is_a(CompList[i],Connection))
				ConnCount--;
			CompList[i]=NULL;
			swap(CompList[i],CompList[--CompCount]);
			return;
		}
	}
}

void ApplicationManager::RemoveByPTR(Component* Comp) 
{
	for(int i=0;i<CompCount;i++)
	{
		if(CompList[i]==Comp)
		{
			//No I am not deleting to let UNDO be able to bring it back again 
			//Also note that ApplicationManager is not the creater of it, thus not of 
			//it's responsibility to delete it
			if(is_a(CompList[i],Connection))
				ConnCount--;
			CompList[i]=NULL;
			swap(CompList[i],CompList[--CompCount]);
			return;
		}
	}
}


void ApplicationManager::SetSelectedComponentList(const vector <Component*>& list)
{
	SelectionList=list;
}

void ApplicationManager::ResetSelectedComponentList()
{
	for(auto& Comp:SelectionList)
		Comp->un_select();
	SelectionList.clear();
	UI.enable_edit=UI.enable_editconn=UI.enable_copy_cut_delete=false;
}

vector <Component*> ApplicationManager::GetComponentsInsideAndSelect(const GraphicsInfo& Rectangle)
{
	vector <Component*> newly_selected;
	for(int i=0;i<CompCount;i++)
		if(CompList[i]->set_selected(Rectangle))
			newly_selected.push_back(CompList[i]);
	return newly_selected;
}

void ApplicationManager::SelectComponentsInside(const GraphicsInfo& Rectangle)
{
	for(int i=0;i<CompCount;i++)
		CompList[i]->set_selected(Rectangle); 
}

void ApplicationManager::UpdateInterface()
{
	string title;
	title = (UI.enable_save ? "*" : "");
	title += (UI.filename=="" ? "Untitled" : UI.filename);
	title += " - Logic Simulator";
	OutputInterface->ChangeTitle(title);
	
	if(UpdateToolBar)
		OutputInterface->CreateTabToolbar();

	FastUpdateInterface();
	OutputInterface->UpdateBuffer();
}

void ApplicationManager::FastUpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);
}

void ApplicationManager::DrawNonSelectedItems()
{
	for(int i=0;i<CompCount;i++)
		if(!CompList[i]->is_selected())
			CompList[i]->Draw(OutputInterface);
}


////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////
//For UNDO/REDO

void ApplicationManager::undo()
{
	Action *pAct;
	pAct=UndoActions.top();
	UndoActions.pop();
	pAct->Undo();
	RedoActions.push(pAct);
	UI.enable_redo=true;
	if(UndoActions.empty())
		UI.enable_undo=false;
	ActionLevel--;
	UI.enable_save=(ActionLevel!=0);
}

void ApplicationManager::redo()
{
	Action *pAct;
	pAct=RedoActions.top();
	RedoActions.pop();
	pAct->Redo();
	UndoActions.push(pAct);
	UI.enable_undo=true;
	UI.enable_save=true;
	if(RedoActions.empty())
		UI.enable_redo=false;
	ActionLevel++;
	UI.enable_save=(ActionLevel!=0);
}

void ApplicationManager::flush_redo()
{
	Action *pAct;
	while(!RedoActions.empty())
	{
		pAct=RedoActions.top();
		delete pAct;
		RedoActions.pop();
	}
	UI.enable_redo=false;
}

void ApplicationManager::flush_undo()
{
	Action *pAct;
	while(!UndoActions.empty())
	{
		pAct=UndoActions.top();
		delete pAct;
		UndoActions.pop();
	}
	UI.enable_undo=false;
}

void ApplicationManager::ResetActionLevel()
{
	ActionLevel=0;
}

void ApplicationManager::HighlightPinsAT(int x,int y)
{
	for(int i=0;i<CompCount;i++)
	{
		CompList[i]->HighlightPinsAT(x,y);
	}
}

bool ApplicationManager::CheckConflict_GATE(const GraphicsInfo& gfx)const
{
	for(int i=0;i<CompCount;i++)
	{
		if(!CompList[i]->CheckSpaceVacancy_GATE(gfx))
			return true;
	}
	return false;
}

bool ApplicationManager::CheckConflict_MOVE(const GraphicsInfo& gfx)const
{
	for(int i=0;i<CompCount;i++)
	{
		if(!CompList[i]->CheckSpaceVacancy_GATE(gfx) && !CompList[i]->is_selected() && is_not_a(CompList[i],Connection))
			return true;
	}
	return false;
}

void ApplicationManager::SaveFile(ofstream& out)
{
	out << CompCount-ConnCount << endl;
	for(int i=0;i<CompCount;i++)
		if(is_not_a(CompList[i],Connection))
			CompList[i]->Save(out);
	
	out << endl << "Connections" << endl;

	for(int i=0;i<CompCount;i++)
		if(is_a(CompList[i],Connection))
			CompList[i]->Save(out);

	out << endl << -1;
}

void ApplicationManager::LoadFile(ifstream& in)
{
	unordered_map<int,Component*> map;
	unordered_map<int,Component*>::iterator Iterator1,Iterator2;

	OutputPin* src;
	InputPin* des;	
	int n;

	string Current;

	Component* c;

	in>>n;

	for(int i=0;i<n;i++)
	{
		c=NULL;
		in >> Current;
		if(Current==AND2Type)
			c=new AND2(AND2_FANOUT);
		else if(Current==AND3Type)
			c=new AND3(AND3_FANOUT);
		else if(Current==LEDType)
			c=new Led;
		else if(Current==NAND2Type)
			c=new NAND2(NAND2_FANOUT);
		else if(Current==NOR2Type)
			c=new NOR2(NOR2_FANOUT);
		else if(Current==NOR3Type)
			c=new NOR3(NOR3_FANOUT);
		else if(Current==NOTType)
			c=new NOT(NOT_FANOUT);
		else if(Current==OR2Type)
			c=new OR2(OR2_FANOUT);
		else if(Current==OR3Type)
			c=new OR3(OR3_FANOUT);
		else if(Current==SWITCHType)
			c=new Switch;
		else if(Current==XNOR2Type)
			c=new XNOR2(XNOR2_FANOUT);
		else if(Current==XNOR3Type)
			c=new XNOR3(XNOR3_FANOUT);
		else if(Current==XOR2Type)
			c=new XOR2(XOR2_FANOUT);
		else if(Current==XOR3Type)
			c=new XOR3(XOR3_FANOUT);
		else if(Current==BUFFERType)
			c=new Buffer(Buffer_FANOUT);
		else 
			throw exception(string("Error 1: Invalid Component type: "+Current).c_str());

		c->Load(in);
		AddComponent(c);
		map.insert(make_pair(c->GetID(),c));
	}

	in >> Current;

	int SrcID, DesID, PinNo;
	
	in >> SrcID;

	while(SrcID!=-1)
	{
		
		des=NULL;
		src=NULL;
		in >> DesID >> PinNo;

		Iterator1=map.find(SrcID);
		Iterator2=map.find(DesID);

		if(Iterator1!=map.end())
			src=Iterator1->second->GetOutputPin();
		else 
			throw exception(string("Error 2: Invalid SrcPin Component ID: "+to_string(SrcID)).c_str());

		if(!src->Connectable())
			throw exception(string("Error 4: SrcPin for Component ID: "+to_string(SrcID) + " maximum fanout reached").c_str());

		if(Iterator2!=map.end())
			des=Iterator2->second->GetInputPin(PinNo);
		else
			throw exception(string("Error 3: Invalid DesPin Component ID: "+to_string(DesID)).c_str());

		if(des->is_connected())
			throw exception(string("Error 5: Duplicate connection for DesPin for Component ID: "+to_string(SrcID) + " PinNo: "+to_string(PinNo)).c_str());

		c=new Connection(src,des);
		c->Load(in);
		in >> SrcID;
		AddComponent(c);

	}
}
OutputPin* ApplicationManager::ReturnOutputPinAT(int& x,int& y)
{
	OutputPin* pin=NULL;
	for(int i=0;i<CompCount;i++)
	{
		pin=CompList[i]->ReturnOutputPinAT(x,y);
		if(pin)
			return pin;
	}
	return NULL;
}

vector <Component*> ApplicationManager::GetClipBoard()
{
	return ClipBoard;
}

void ApplicationManager::SetClipBoard(const vector <Component*>& list)
{
	ClipBoard=list;
}

InputPin* ApplicationManager::ReturnInputPinAT(int& x,int& y)
{
	InputPin* pin=NULL;
	for(int i=0;i<CompCount;i++)
	{
		pin=CompList[i]->ReturnInputPinAT(x,y);
		if(pin)
			return pin;
	}
	return NULL;
}

Component* ApplicationManager::GetComponentAt(int x,int y)
{
	for(int i=0;i<CompCount;i++)
		if(CompList[i]->isAt(x,y))
			return CompList[i];

	return NULL;
}

int ApplicationManager::ValidateCircuit()
{
	int circuit_errors=NO_ERRORS;
	int count=0;
	Traverser t;
	
	//0 Check: Check if there is a component 
	if(CompCount==0)
		return NOTHING_TO_SIMULATE;

	//1st pass Check: First Check if there is no pins are floating
	//and Check for first level & last level errors
	for(int i=0;i<CompCount;i++)
	{
		circuit_errors|=CompList[i]->Validate();
	}

	//Second Check for feedback error and meanwhile add levels to each gate also. i.e follow the route starting form the switches
	for(int i=0;i<CompCount;i++)
	{
		if(is_a(CompList[i],Switch))
		{
			t.set_starting_point(CompList[i]);
			circuit_errors|=t.Loop_detect();
			OutputInterface->PrintMsg("Validating circuit... " + to_string(count*100/CompCount) + "%");
			count++;
			if(circuit_errors&FEEDBACK)
				break;
		}
	}

	count=t.Get_NumberOf_Visited_Components();
	
	//No Switches
	if(count==0)
		circuit_errors|=FIRST_LEVEL_ERROR;
	//All Components are visited which means all components are reachable from the switches
	else if(count==CompCount)
		return circuit_errors;
	
	//If not, it means that some are not reachable form the switches (FIRST_LEVEL_ERROR)
	circuit_errors|=FIRST_LEVEL_ERROR;
	
	for(int i=0;i<CompCount;i++)
	{
		//Optionally, we may just break here but we are interseted to detect Feedbacks in them
		if(CompList[i]->getLevel()==-1)
		{
			t.set_starting_point(CompList[i]);
			circuit_errors|=t.Loop_detect();
			count++;
			if(circuit_errors&FEEDBACK)
				break;
		}
		OutputInterface->PrintMsg("Validating circuit... " + to_string(count*100/CompCount) + "%");
	}

	return circuit_errors;
}

void ApplicationManager::OperateCicuit()
{
	for(int i=0;i<CompCount;i++)
		CompList[i]->Operate();
}

void ApplicationManager::CreateSimulationParameters()
{
	for(int i=0;i<CompCount;i++)
	{	
		if(is_a(CompList[i],Switch))
			sim_switchs.push_back(dynamic_cast<Switch*>(CompList[i]));
		else if(is_a(CompList[i],Led))
			sim_leds.push_back(dynamic_cast<Led*>(CompList[i]));
	}

	sort(sim_switchs.begin(),sim_switchs.end(),[](Switch* s1,Switch* s2)->bool{
		return s1->GetLabel() < s2->GetLabel();
	});

	sort(sim_leds.begin(),sim_leds.end(),[](Led* l1,Led* l2)->bool{
		return l1->GetLabel() < l2->GetLabel();
	});

	sort(CompList,CompList+CompCount,[](Component* c1,Component* c2)->bool{
		return c1->getLevel() < c2->getLevel();
	});

}

vector <Switch*> ApplicationManager::get_all_switch()
{
	return sim_switchs;
}

vector <Led*> ApplicationManager::get_all_leds()
{
	return sim_leds;
}

void ApplicationManager::DestroySimulationParameters()
{
	sim_switchs.clear();
	sim_leds.clear();
	for(int i=0;i<CompCount;i++)
		CompList[i]->resetLevel();

}

void ApplicationManager::ResetCircuit()
{
	for(int i=0;i<CompCount;i++)
		CompList[i]->Reset();
}

void ApplicationManager::DestroySelectionList()
{
	ResetSelectedComponentList();
}

void ApplicationManager::ResetApp()
{
	flush_undo();
	flush_redo();

	DestroySelectionList();
	DestroySimulationParameters();

	for(auto& Comp:CompList)
		delete Comp;

	memset(CompList,NULL,sizeof(CompList));

	ActionLevel=0;
	CompCount=0;
	ConnCount=0;
	UI.enable_copy_cut_delete=false;
	UI.enable_undo=false;
	UI.enable_redo=false;
	UI.enable_save=false;
	UI.enable_edit=false;
	UI.enable_editconn=false;
	UI.AppMode=DESIGN;
	UI.filename.clear();
	Component::ResetCount();
	Switch::resetSwitchCount();
	Led::resetLedCount();
}

ApplicationManager::~ApplicationManager()
{	
	for(auto& Comp:ClipBoard)
		delete Comp;

	ClipBoard.clear();
	
	flush_undo();
	flush_redo();

	for(auto& Comp:CompList)
		delete Comp;
 
	delete OutputInterface;
	delete InputInterface;
}