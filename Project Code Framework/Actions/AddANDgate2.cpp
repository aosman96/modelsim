#include "AddANDgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND2.h"


AddANDgate2::AddANDgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input AND";
}

Component* AddANDgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new AND2(gfx,AND2_FANOUT);
}

void AddANDgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawAND2(gfx);
}

AddANDgate2::~AddANDgate2()
{
}
