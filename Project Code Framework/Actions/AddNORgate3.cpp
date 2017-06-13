#include "AddNORgate3.h"
#include "..\ApplicationManager.h"
#include "..\Components\NOR3.h"


AddNORgate3::AddNORgate3(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "3-Input NOR";
}

Component* AddNORgate3::CreateComponent(const GraphicsInfo& gfx)
{
	return new NOR3(gfx,NOR3_FANOUT);
}

void AddNORgate3::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawNOR3(gfx);
}

AddNORgate3::~AddNORgate3()
{
}
