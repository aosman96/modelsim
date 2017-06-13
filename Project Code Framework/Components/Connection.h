#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include <vector>
using std::vector;
class Connection :	public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	//int		DstPin;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	vector<Point> points;
	bool high;
	virtual void DrawLabel(Output* pOut);
public:
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const vector<Point> &Actpoints, OutputPin *pSrcPin,InputPin *pDstPin);
	Connection(OutputPin *pSrcPin,InputPin *pDstPin);

	virtual void Operate()override;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut)override;	//for each component to Draw itself
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	virtual bool isAt(int x,int y)override; 
	virtual void Move(int deltaX,int deltaY)override;

	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();

	void SetPoints(const vector<Point>& points);
	vector<Point> GetPoints();

	virtual STATUS GetOpStatus()override; 

	virtual void Reset()override;

	virtual STATUS GetOutPinStatus()override;	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n)override;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual bool CheckSpaceVacancy_GATE(const GraphicsInfo &r_GfxInfo)const;	//check if the location is avaliable for other gates, a little bit tricky here 

	virtual bool set_selected(const GraphicsInfo &xy);

	virtual OutputPin* ReturnOutputPinAT(int& x,int& y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void HighlightPinsAT(int x,int y)override;
	virtual int Validate()override;
	virtual void GetComponentCorners(GraphicsInfo &r_GfxInfo)override; //A little bit tricky here
	virtual vector<Component*> Next()override;
	void UpdateEndPoint(int deltaX,int deltaY,int offset);
	void UpdateStartPoint(int deltaX,int deltaY);

	void Reconnect();//For Undo
	void Disconnet();
	virtual Component* CreateCopy()override;

	virtual vector<Connection*> GetAllConnections()override;

	virtual InputPin* GetInputPin(int n)override;
	virtual OutputPin* GetOutputPin()override;

	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override; 
	virtual void getOutputPinLocation(int&x,int&y)override; 

	~Connection();
};
