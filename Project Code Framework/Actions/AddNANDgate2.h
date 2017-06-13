#ifndef _ADD_NAND_GATE_H
#define _ADD_NAND_GATE_H

#include "AddGateBase.h"

class AddNANDgate2 : public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddNANDgate2(ApplicationManager *pApp);
	virtual ~AddNANDgate2(void);	
};

#endif