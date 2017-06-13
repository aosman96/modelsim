#ifndef _ADD_NOR3_GATE_H
#define _ADD_NOR3_GATE_H

#include "AddGateBase.h"

class AddNORgate3 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddNORgate3(ApplicationManager *pApp);
	virtual ~AddNORgate3(void);	
};

#endif