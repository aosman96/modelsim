#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_OR_GATE_3,		//Add 3-input OR gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_XNOR_GATE_3,		//Add 3-input XNOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection
	ENABLE_SIM,
	
	//====================================> Added by karim ashraf
	TOOLBAR_SCROLL_NEXT,//Toolbar menu scroll
	TOOLBAR_SCROLL_BACK,//Toolbar menu scroll back
	//====================================> Added By karim ashraf
	TAB_SELECT_API,
	TAB_SELECT_OPTIONS,
	
	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection
	StartPorbing,
	StartSimulating,
	Create_TruthTable,	//Create Truth Table of the Circuit
	RECONNECT,

	Change_Switch,		//Change Switch Status in Simulation Mode
	Change_Mode,

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	EDIT,

	CUT,
	COPY,
	PASTE,

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

//=============================>
//SCROLL MODE (For Toolbar) //Added By KARIM
enum SCROLL
{
	PAGE_1,
	PAGE_2,
	PAGE_3,
	PAGE_4
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//AND gate item in menu
	ITM_OR2,		//OR gate item in menu
	ITM_INV,
	ITM_Buff,
	ITM_NAND2,		//2-input NAND gate item in menu
	ITM_NOR2,		//2-input NOR gate item in menu
	ITM_XOR2,		//2-input XOR gate item in menu
	ITM_XNOR2,		//2-input XNOR gate item in menu
	ITM_AND3,		//3-input AND gate item in menu
	ITM_OR3,		//3-input OR gate item in menu
	ITM_NOR3,		//3-input NOR gate item in menu
	
	
	ITM_MORE1,		//Item to SCROLL 1
	ITM_BACK1,		//Item to SCROLLBACK 1

	ITM_XOR3,
	ITM_XNOR3,	

	ITM_LED,
	ITM_WIRE,
	ITM_SWITCH,

	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	
};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	
	ITM_TRUTH,	//Truth table menu item

	
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};

enum OptionsMenuItem
{
	ITM_ChangeMode,
	ITM_OPEN,
	ITM_SAVE,
	ITM_EDIT,
	ITM_EDITCONN,
	ITM_CUT,
	ITM_COPY,
	ITM_PASTE,
	ITM_DELETE,
	ITM_UNDO,
	ITM_REDO,

	ITM_EXIT,
	ITM_OPTIONS_COUNT
};

enum Selected_Tab
{
	API_TAB,
	OPTIONS_TAB
};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5,	//Default fan out of 2-input AND gate
	Buffer_FANOUT = 5,
	NOT_FANOUT = 5,
	NAND2_FANOUT = 5,
	OR2_FANOUT = 5,
	NOR2_FANOUT = 5,
	XOR2_FANOUT = 5,
	XNOR2_FANOUT = 5,
	AND3_FANOUT = 5,
	OR3_FANOUT = 5,
	NOR3_FANOUT = 5,
	XOR3_FANOUT = 5,
	XNOR3_FANOUT = 5,
};



//using bitmasking, we mark connected and selected pin
enum HighPins
{
	NO_PIN  = 0x0,
	INPUT1  = 0x1,
	INPUT2  = 0x2,
	INPUT3  = 0x4,
	OUTPUT1 = 0x8
};

enum CircuitErros
{
	NO_ERRORS			= 0x0,
	PIN_NOT_CONNECT		= 0x1,
	FIRST_LEVEL_ERROR	= 0x2,
	LAST_LEVEL_ERROR	= 0x4,
	FEEDBACK			= 0x8,
	NOTHING_TO_SIMULATE = 0x10
};

enum DesignSelectActions
{
	NO_SELECT_ACT,
	SINLGE_SELECT,
	MULTI_SELECT,
	UNSELECT_ALL,
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1,y1, x2, y2;
};

struct Point
{
	int x,y;
};


#ifndef NULL
#define NULL 0
#endif

#define ENTER 13
#define BACKSPACE 8

#ifndef ComponentType
#define ComponentType

#define AND2Type	 "AND2"
#define AND3Type	 "AND3"
#define BUFFERType	 "BUFFER"
#define LEDType		 "LED"
#define NAND2Type	 "NAND2"
#define NOR2Type	 "NOR2"
#define NOR3Type	 "NOR3"
#define NOTType		 "NOT"
#define OR2Type		 "OR2"
#define OR3Type		 "OR3"
#define SWITCHType	 "SWITCH"
#define XNOR2Type	 "XNOR2"
#define XNOR3Type	 "XNOR3"
#define XOR2Type	 "XOR2"
#define XOR3Type	 "XOR3"

#endif

#endif