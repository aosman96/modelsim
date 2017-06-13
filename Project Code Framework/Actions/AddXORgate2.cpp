#include "AddXORgate2.h"
#include "..\ApplicationManager.h"
#include "..\Components\XOR2.h"


AddXORgate2::AddXORgate2(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "2-Input XOR";
}

Component* AddXORgate2::CreateComponent(const GraphicsInfo& gfx)
{
	return new XOR2(gfx,XOR2_FANOUT);
}

void AddXORgate2::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawXOR2(gfx);
}

AddXORgate2::~AddXORgate2()
{
}
