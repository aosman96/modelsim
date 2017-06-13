#include "AddORgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\OR2.h"


AddORgate2::AddORgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input OR";
}

Component* AddORgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new OR2(gfx,OR2_FANOUT);
}

void AddORgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawOR2(gfx);
}

AddORgate2::~AddORgate2()
{
}
