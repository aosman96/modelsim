#include "AddNORgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\NOR2.h"


AddNORgate2::AddNORgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input NOR";
}

Component* AddNORgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new NOR2(gfx,NOR2_FANOUT);
}

void AddNORgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawNOR2(gfx);
}

AddNORgate2::~AddNORgate2()
{
}
