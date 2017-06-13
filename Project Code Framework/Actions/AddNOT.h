#ifndef _ADD_NOT_GATE_H
#define _ADD_NOT_GATE_H

#include "AddGateBase.h"

class AddNOT :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddNOT(ApplicationManager *pApp);
	virtual ~AddNOT(void);	
};

#endif