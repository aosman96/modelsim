#include "Component.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

int Component::count=0;

void Component::ResetCount()
{
	count=0;
}

Component::Component()
{
	ID=++count;
	level=-1;
	selected=false;
}

void Component::Save(ofstream& out)
{
	out << ID << '\t' << (m_Label==""?"_" : m_Label);
}

void Component::Load(ifstream& in)
{
	in >> ID >> m_Label;
	if(m_Label=="_")
		m_Label="";
	count = max(count,ID+1);  //Makes sure that the ID is unique
}

void Component::un_select()
{
	selected=false;
}

int Component::GetID()
{
	return ID;
}

void Component::updateID()
{
	if(ID<count)
		ID=++count;
}

bool Component::is_selected()
{
	return selected;
}

void Component::setLevel(int l)
{
	level=max(level,l);
}

void Component::resetLevel()
{
	level=-1;
}

int Component::getLevel()
{
	return level;
}

string Component::GetLabel()
{
	return m_Label;
}

void Component::SetLabel(string s)
{
	m_Label=s;
}

bool Component::HasALabel()
{
	return m_Label!="";
}

Component::~Component()
{}

