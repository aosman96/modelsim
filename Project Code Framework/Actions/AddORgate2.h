#ifndef _ADD_OR2_GATE_H
#define _ADD_OR2_GATE_H

#include "AddGateBase.h"

class AddORgate2 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddORgate2(ApplicationManager *pApp);
	virtual ~AddORgate2(void);	
};

#endif