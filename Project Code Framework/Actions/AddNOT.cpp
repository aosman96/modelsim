#include "AddNOT.h"
#include "..\ApplicationManager.h"
#include "..\Components\NOT.h"


AddNOT::AddNOT(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "NOT";
}

Component* AddNOT::CreateComponent(const GraphicsInfo& gfx)
{
	return new NOT(gfx,NOT_FANOUT);
}

void AddNOT::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawNOT(gfx);
}

AddNOT::~AddNOT()
{
}
