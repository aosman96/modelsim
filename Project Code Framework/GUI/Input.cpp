//#include "Input.h"  //Implicity included by Output.h
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
	LastX=LastY=-1;
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
	LastX=x;
	LastY=y;
}

void Input::GetLastPointClicked(int &x, int &y)
{
	x=LastX;
	y=LastY;
}

clicktype Input::WaitMouseClick(int& x,int& y)
{
	return pWind->WaitMouseClick(x, y);
}

buttonstate Input::GetMouseButtonState(button b,int& x,int& y)
{
	return pWind->GetButtonState(b,x,y);
}

keytype Input::GetKeyPress(char& cKeyData)
{
	return pWind->GetKeyPress(cKeyData);
}

keytype Input::GetKeyPressType()
{
	char c;
	return pWind->GetKeyPress(c);
}

string Input::GetString(Output *pOut,string Message,string str)
{
	//TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	
	keytype key;
	const char* cursor="|";
	char c;
	
	int count=0;
	int follower=0;
	
	follower=count=str.size();

	pOut->PrintMsg(Message+str);
	pWind->FlushKeyQueue();
	key = pWind->WaitKeyPress(c);

	while(c!=ENTER)
	{

		if(key==ESCAPE)
		{
			str.erase();
			break;
		}
		else if(key == ARROW) 
		{
			switch(c)
			{
				case 1:
				//The End key was pressed.
					follower=count;
					break;
				case 4:
					//The Left Arrow key was pressed.
					if(follower!=0) 
						--follower;
					break;
				case 6:
					//Rigth ARROW
					if(follower!=count)
						++follower; 
					break;
				case 7:
					//Home button
					follower=0;
					break;
			}
      
		}
		else if(c==BACKSPACE)
		{
			if(follower!=0 && !str.empty())
			{
				str.erase(--follower,1);
				count--;
			}
		}
		else
		{
			str.insert(str.begin()+follower,c);
			count++;
			follower++;
		}
		
		str.insert(follower,cursor);

		pOut->PrintMsg(Message + str);
		Sleep(50);
		str.erase(follower,1);
		pOut->PrintMsg(Message + str);

		key = pWind->WaitKeyPress(c);

	}
	return str;
}



clicktype Input::GetMouseClick(int &iX,int &iY) 
{
	clicktype click;
	click= pWind->GetMouseClick(iX, iY);
	LastX=iX;
	LastY=iY;
	return click;
}

void Input::GetMouseCoord(int &iX,int &iY) const
{
	pWind->GetMouseCoord(iX, iY);
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() 
{	
	int x,y,tx,ty;
	clicktype click=NO_CLICK;
	char c;
	/*Variant 1*/
	//click=pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	
	/*Variant 2*/
	//Kludge, had to do it this wired way for the dragging to work problably and added keyboard shortcuts
	pWind->FlushKeyQueue();
	while(pWind->GetButtonState(LEFT_BUTTON,x,y)==BUTTON_UP){
		if(pWind->GetKeyPress(c))
		{
			if(c==127 && UI.enable_copy_cut_delete)
				return DEL;
			c+=64;
			if(c=='X' && UI.enable_copy_cut_delete)
				return CUT;
			else if(c=='C' && UI.enable_copy_cut_delete)
				return COPY;
			else if(c=='V' && UI.enable_paste)
				return PASTE;
			else if(c=='E' && UI.enable_edit)
				return EDIT_Label;
			else if(c=='Z' && UI.enable_undo)
				return UNDO;
			else if(c=='Y' && UI.enable_redo)
				return REDO;
			else if(c=='O')
				return LOAD;
			else if(c=='S' && UI.enable_save)
				return SAVE;
		}
		pWind->WaitUserInput();
	}

	if(y<UI.DrawingAreaYsrt || y>UI.height-UI.StatusBarHeight || UI.AppMode==SIMULATION){
		click=pWind->WaitMouseClick(tx,ty);
	}

	LastX=x;
	LastY=y;

	if(click==CLOSE_CLICK)
		return EXIT;
	
	int ClickedItemOrder;
	if(y>0 && y<=UI.TabsHeight) //Regardless of Mode
	{
		if(x>0 && x<UI.TabsItemWidth)
			return TAB_SELECT_API;
		else if(x>UI.TabsItemWidth && x<2*UI.TabsItemWidth)
			return TAB_SELECT_OPTIONS;
		else
			return DSN_TOOL;
	}
	else if(UI.SelectedTab==OPTIONS_TAB)
	{
		ClickedItemOrder = (x / UI.ToolItemWidth);
		if ( y >= UI.TabsHeight && y < UI.ToolBarHeight + UI.TabsHeight)
		{
			switch (ClickedItemOrder)
			{
				case ITM_ChangeMode: return Change_Mode;
				case ITM_OPEN : return LOAD;
				case ITM_EDITCONN:
					if(UI.enable_editconn)
						return RECONNECT;
					else return DSN_TOOL;
				case ITM_EDIT:
					if(UI.enable_edit)
						return EDIT_Label;
					else return DSN_TOOL;
				case ITM_SAVE : 
					if(UI.enable_save)
						return SAVE;
					else return DSN_TOOL;
				case ITM_CUT : 
					if(UI.enable_copy_cut_delete)
						return CUT;
					else return DSN_TOOL;
				case ITM_COPY : 
					if(UI.enable_copy_cut_delete)
						return COPY;
					else return DSN_TOOL;
				case ITM_PASTE : 
					if(UI.enable_paste)
						return PASTE;
					else return DSN_TOOL;
				case ITM_UNDO : 
					if(UI.enable_undo)
						return UNDO;
					else return DSN_TOOL;
				case ITM_REDO : 
					if(UI.enable_redo)
						return REDO;
					else return DSN_TOOL;
				case ITM_DELETE:
					if(UI.enable_copy_cut_delete)
						return DEL;
					else return DSN_TOOL;
				case ITM_EXIT : return EXIT;
				default: return DSN_TOOL;
			}
		}
	}
	else if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= UI.TabsHeight && y < UI.ToolBarHeight + UI.TabsHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			//===============> Formula edit by karim
			ClickedItemOrder = min((x / UI.ToolItemWidth),UI.disp_max-1)+UI.ScrollCount*UI.disp_max;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_INV: return ADD_INV;
			case ITM_Buff: return ADD_Buff;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_OR3: return ADD_OR_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;


			
			case ITM_MORE1: return TOOLBAR_SCROLL_NEXT; 
			case ITM_BACK1: return TOOLBAR_SCROLL_BACK;
			
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_XNOR3: return ADD_XNOR_GATE_3;

			case ITM_WIRE: return ADD_CONNECTION;
			case ITM_LED: return ADD_LED;
			case ITM_SWITCH: return ADD_Switch;
			
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
	}
	else	//Application is in Simulation mode
	{
		if ( y >= UI.TabsHeight && y < UI.ToolBarHeight + UI.TabsHeight)
		{	
			ClickedItemOrder = (x / UI.ToolItemWidth);
			switch(ClickedItemOrder)
			{
				case ITM_TRUTH: return Create_TruthTable;	//Truth table menu item
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
		
	}

	if(y >= UI.ToolBarHeight+UI.TabsHeight && y < UI.height - UI.StatusBarHeight)
	{
		if(UI.AppMode==DESIGN)
			return SELECT;	//user want to select/unselect a statement in the flowchart	
		else 
			return SIM_MODE;	//User wants to do something in the simulation area
	}
	else	
		return STATUS_BAR;

}

bool Input::GetOpenFilename(string& str)
{
	return pWind->GetOpenFilename(str);	
}

bool Input::GetSaveFilename(string& str)
{
	return pWind->GetSaveFilename(str);
}

bool Input::GetExportFilename(string &str)
{
	return pWind->GetExportFilename(str);
}

Input::~Input()
{
}
