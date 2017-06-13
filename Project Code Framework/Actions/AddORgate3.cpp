#include "AddORgate3.h"
#include "..\ApplicationManager.h"
#include "..\Components\OR3.h"


AddORgate3::AddORgate3(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "3-Input OR";
}

Component* AddORgate3::CreateComponent(const GraphicsInfo& gfx)
{
	return new OR3(gfx,OR3_FANOUT);
}

void AddORgate3::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawOR3(gfx);
}

AddORgate3::~AddORgate3()
{
}
