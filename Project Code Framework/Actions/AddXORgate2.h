#ifndef _ADD_XOR2_GATE_H
#define _ADD_XOR2_GATE_H

#include "AddGateBase.h"

class AddXORgate2 : public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddXORgate2(ApplicationManager *pApp);
	virtual ~AddXORgate2(void);	
};

#endif