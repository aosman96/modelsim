#include "AddXNORgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\XNOR2.h"


AddXNORgate2::AddXNORgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input XNOR";
}

Component* AddXNORgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new XNOR2(gfx,XNOR2_FANOUT);
}

void AddXNORgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawXNOR2(gfx);
}

AddXNORgate2::~AddXNORgate2()
{
}
