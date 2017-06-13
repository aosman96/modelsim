#include "AddANDgate3.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND3.h"


AddANDgate3::AddANDgate3(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "3-Input AND";
}

Component* AddANDgate3::CreateComponent(const GraphicsInfo& gfx)
{
	return new AND3(gfx,AND3_FANOUT);
}

void AddANDgate3::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawAND3(gfx);
}

AddANDgate3::~AddANDgate3()
{
}
