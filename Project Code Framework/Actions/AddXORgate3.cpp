#include "AddXORgate3.h"
#include "..\ApplicationManager.h"
#include "..\Components\XOR3.h"


AddXORgate3::AddXORgate3(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "3-Input XOR";
}

Component* AddXORgate3::CreateComponent(const GraphicsInfo& gfx)
{
	return new XOR3(gfx,XOR3_FANOUT);
}

void AddXORgate3::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawXOR3(gfx);
}

AddXORgate3::~AddXORgate3()
{
}
