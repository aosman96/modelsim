#ifndef _ADD_XOR3_GATE_H
#define _ADD_XOR3_GATE_H

#include "AddGateBase.h"

class AddXORgate3 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddXORgate3(ApplicationManager *pApp);
	virtual ~AddXORgate3(void);	
};

#endif