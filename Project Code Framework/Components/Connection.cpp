#include "Connection.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

Connection::Connection(const vector<Point> &ActPoints, OutputPin *pSrcPin,InputPin *pDstPin)	
{
	points=ActPoints;
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	
	if(SrcPin)
		SrcPin->ConnectTo(this);
	if(DstPin)
		DstPin->set_connection(this);

	high=false;
}

Connection::Connection(OutputPin *pSrcPin,InputPin *pDstPin)	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	
	if(SrcPin)
		SrcPin->ConnectTo(this);
	if(DstPin)
		DstPin->set_connection(this);

	high=false;
}

void Connection::Save(ofstream& out)
{
	int n=points.size();
	out << SrcPin->GetGateID() << '\t' << DstPin->GetGateID() << '\t' << DstPin->getPinNo() << ' ';
	out << (n>2 ? n-2 : 0) << '\t';
	for(int i=1;i<n-1;i++)
		out << points[i].x << ' ' << points[i].y << '\t';
	out << endl;
}

void Connection::Load(ifstream& in)
{
	points.clear();
	int n;
	Point p;
	in >> n;

	if(SrcPin)
		SrcPin->GetLocation(p.x,p.y);
	points.push_back(p);
	
	for(int i=0;i<n;i++){
		in >> p.x >> p.y;
		points.push_back(p);
	}

	if(DstPin)
		DstPin->GetLocation(p.x,p.y);
	points.push_back(p);
}

void Connection::setSourcePin(OutputPin *pSrcPin)
{
	if(SrcPin)
		SrcPin->RemoveConnection(this);
	SrcPin = pSrcPin;	
	if(SrcPin)
		SrcPin->ConnectTo(this);
}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	
	if(DstPin)
		DstPin->set_connection(NULL);
	
	DstPin = pDstPin;
	
	if(DstPin) 
		DstPin->set_connection(this);	
}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	high=(SrcPin->getStatus() ? true:false);
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::DrawLabel(Output* pOut)
{
	int max_width=0;
	int width;
	int Loc=0;
	string label=GetLabel();
	if(label=="") return;
	for(UINT i=0;i<points.size()-1;i++)
	{
		width=abs(points[i+1].x-points[i].x);
		if(width>max_width)
		{
			max_width=width;
			Loc=i;
		}
	}
	pOut->DrawLabel(label,(points[Loc+1].x+points[Loc].x)/2-label.size()/2,points[Loc].y-30);
}

void Connection::SetPoints(const vector<Point>& pts)
{
	this->points=pts;
}

vector<Point> Connection::GetPoints()
{
	return points;
}

void Connection::Draw(Output* pOut)
{
	pOut->DrawConnection(points,selected,high);
	DrawLabel(pOut);
}

void Connection::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawConnection(points,selected,high,deltaX,deltaY); 
}

STATUS Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


STATUS Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

bool Connection::isAt(int x,int y)
{
	int n=points.size();
	for(int i=0;i<n-1;i++)
	{
		//Yes, as simple as that because we are dealing with only vertical and horizontal line
		if(WithinRange(x,points[i].x) && WithinRange(x,points[i+1].x) && IsBetween(points[i].y,points[i+1].y,y))	
			return true;
		else if(WithinRange(y,points[i].y) && WithinRange(y,points[i+1].y) && IsBetween(points[i].x,points[i+1].x,x))
			return true;
	}
	return false;
}

bool Connection::CheckSpaceVacancy_GATE(const GraphicsInfo &gate)const
{
	int n=points.size();

	GraphicsInfo l;

	for(int i=0;i<n-1;i++)
	{
		l.x1=min(points[i].x,points[i+1].x);
		l.x2=max(points[i].x,points[i+1].x);
	
		l.y1=min(points[i].y,points[i+1].y);
		l.y2=max(points[i].y,points[i+1].y);

		if(l.x2>gate.x1 && l.x1<gate.x2 && l.y2>gate.y1 && l.y1<gate.y2)
			return false;
	}

	return true;
}

bool Connection::set_selected(const GraphicsInfo &xy)
{
	int n=points.size();
	bool is_point=(xy.x1==xy.x2 && xy.y1==xy.y2);

	if(is_point && isAt(xy.x1,xy.y1))
	{
		selected=true;
		return true;
	}

	for(int i=0;i<n-1;i++)
	{
		if(xy.x1 < points[i+1].x && xy.x2 > points[i].x && xy.y1 < points[i+1].y && xy.y2 > points[i].y)
		{
			selected=true;
			return true;
		}
		else if(xy.x1 < points[i].x && xy.x2 > points[i+1].x && xy.y1 < points[i].y && xy.y2 > points[i+1].y)
		{
			selected=true;
			return true;
		}
	}
	selected=false;
	return false;
}

OutputPin* Connection::ReturnOutputPinAT(int& x,int& y)
{
	return NULL;
}
InputPin* Connection::ReturnInputPinAT(int& x,int& y)
{
	return NULL;
}
void Connection::HighlightPinsAT(int x,int y)
{
}

int Connection::Validate()
{
	return NO_ERRORS;
}

vector<Component*> Connection::Next()
{
	vector<Component*> com;
	if(DstPin)
		com.push_back(DstPin->getComponent());
	return com;
}

void Connection::Reset()
{
	high=false;
}

void Connection::GetComponentCorners(GraphicsInfo &r_GfxInfo)
{
	GraphicsInfo rect;
	rect.x1=UI.width+10; //Imposible but set to be able to calculate the min
	rect.y1=UI.height+10;
	rect.x2=-1; //Imposible but set to be able to calculate the max
	rect.y2=-1;
	int n=points.size();
	for(int i=0;i<n-1;i++)
	{
		rect.x1=min(rect.x1,points[i].x);
		rect.x1=min(rect.x1,points[i+1].x);

		rect.x2=max(rect.x2,points[i].x);
		rect.x2=max(rect.x2,points[i+1].x);

		rect.y1=min(rect.y1,points[i].y);
		rect.y1=min(rect.y1,points[i+1].y);

		rect.y2=max(rect.y2,points[i].y);
		rect.y2=max(rect.y2,points[i+1].y);
	}
	r_GfxInfo=rect;
}

void Connection::Move(int deltaX,int deltaY)
{
	int n=points.size();
	for(int i=0;i<n;i++)
	{
		points[i].x+=deltaX;
		points[i].y+=deltaY;
	}
	if(SrcPin)if(!SrcPin->is_selected())
		this->UpdateStartPoint(-1*deltaX,-1*deltaY);

	if(DstPin)if(!DstPin->is_selected())
		this->UpdateEndPoint(-1*deltaX,-1*deltaY,0);
}

void Connection::UpdateEndPoint(int deltaX,int deltaY,int offset)
{
	if(deltaX==0 && deltaY==0)return;

	Point addedpoint;

	int d=0;

	if(offset!=0)
	{
		addedpoint.y=points[points.size()-1].y;
		addedpoint.x=points[points.size()-1].x-15*offset;
		points.insert(points.end()-1,addedpoint);
		d=1;
	}

	int n=points.size();
	
	int mindist=UI.width+UI.height;
	int minLoc=n-1;
	int DesX=points[n-1-d].x+deltaX,DesY=points[n-1-d].y+deltaY;
	int RDesX=points[n-1].x+deltaX,RDesY=points[n-1].y+deltaY;
	int SrcX=points[0].x,SrcY=points[0].y;

	int manhattan_dist;

	for(int i=0;i<n-d;i++)
	{
		manhattan_dist=abs(DesX-points[i].x)+abs(DesY-points[i].y)+abs(SrcX-points[i].x)+abs(SrcY-points[i].y);
		if(manhattan_dist<mindist)
		{
			mindist=manhattan_dist;
			minLoc=i;
		}
	}


	for(int j=n-1;j>minLoc;j--)
		points.pop_back();

	addedpoint.y=points[minLoc].y;
	addedpoint.x=DesX;
	points.push_back(addedpoint);
	addedpoint.y=DesY;
	points.push_back(addedpoint);
	if(d!=0)
	{
		addedpoint.x=RDesX;
		addedpoint.y=RDesY;
		points.push_back(addedpoint);
	}
}

void Connection::UpdateStartPoint(int deltaX,int deltaY)
{
	if(deltaX==0 && deltaY==0)return;
	Point addedpoint;
	vector <Point> newpoints;
	int n=points.size();
	
	int mindist=UI.width+UI.height;
	int minLoc=n-1;
	int DesX=points[n-1].x,DesY=points[n-1].y;
	int SrcX=points[0].x+deltaX,SrcY=points[0].y+deltaY;

	int manhattan_dist;

	for(int i=0;i<n;i++)
	{
		manhattan_dist=abs(DesX-points[i].x)+abs(DesY-points[i].y)+abs(SrcX-points[i].x)+abs(SrcY-points[i].y);
		if(manhattan_dist<mindist)
		{
			mindist=manhattan_dist;
			minLoc=i;
		}
	}

	addedpoint.x=SrcX;
	addedpoint.y=SrcY;
	newpoints.push_back(addedpoint);
	addedpoint.y=points[minLoc].y;
	newpoints.push_back(addedpoint);

	for(int i=minLoc;i<n;i++)
		newpoints.push_back(points[i]);
	points=std::move(newpoints);
}

InputPin* Connection::GetInputPin(int n)
{
	return NULL;
}

OutputPin* Connection::GetOutputPin()
{
	return NULL;
}

void Connection::getInputPinLocation(InputPin* p,int&x,int&y)
{}

void Connection::getOutputPinLocation(int&x,int&y)
{}

void Connection::Reconnect()
{
	if(SrcPin)
		SrcPin->ConnectTo(this);
	if(DstPin)
		DstPin->set_connection(this);
}

void Connection::Disconnet()
{
	if(SrcPin)
		SrcPin->RemoveConnection(this);
	if(DstPin)
		DstPin->set_connection(NULL);
}

Component* Connection::CreateCopy()
{
	return NULL; //unsupported
}

vector<Connection*> Connection::GetAllConnections()
{
	vector<Connection*> c;
	c.clear();
	return c;
}

STATUS Connection::GetOpStatus()
{
	return SrcPin->getStatus();
}

Connection::~Connection()
{}
