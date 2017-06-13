#include "AddXNORgate3.h"
#include "..\ApplicationManager.h"
#include "..\Components\XNOR3.h"


AddXNORgate3::AddXNORgate3(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "3-Input XNOR";
}

Component* AddXNORgate3::CreateComponent(const GraphicsInfo& gfx)
{
	return new XNOR3(gfx,XNOR3_FANOUT);
}

void AddXNORgate3::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawXNOR3(gfx);
}

AddXNORgate3::~AddXNORgate3()
{
}
