#ifndef _ADD_XNOR2_GATE_H
#define _ADD_XNOR2_GATE_H

#include "AddGateBase.h"

class AddXNORgate2 : public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddXNORgate2(ApplicationManager *pApp);
	virtual ~AddXNORgate2(void);	
};

#endif