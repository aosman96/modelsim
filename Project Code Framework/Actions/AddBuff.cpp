#include "AddBuff.h"
#include "..\ApplicationManager.h"
#include "..\Components\Buffer.h"


AddBuff::AddBuff(ApplicationManager *pApp):AddGate(pApp)
{
	desciption = "Buffer";
}

Component* AddBuff::CreateComponent(const GraphicsInfo& gfx)
{
	return new Buffer(gfx,Buffer_FANOUT);
}

void AddBuff::DrawDrag(const GraphicsInfo& gfx)
{
	Output* pOut=pManager->GetOutput();
	pOut->DrawBuffer(gfx);
}

AddBuff::~AddBuff()
{
}
