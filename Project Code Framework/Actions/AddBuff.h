#ifndef _ADD_BUFF_GATE_H
#define _ADD_BUFF_GATE_H

#include "AddGateBase.h"

class AddBuff :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddBuff(ApplicationManager *pApp);
	virtual ~AddBuff(void);	
};

#endif