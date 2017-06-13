#include "AddNANDgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\NAND2.h"


AddNANDgate2::AddNANDgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input NAND";
}

Component* AddNANDgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new NAND2(gfx,NAND2_FANOUT);
}

void AddNANDgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawNAND2(gfx);
}

AddNANDgate2::~AddNANDgate2()
{
}
