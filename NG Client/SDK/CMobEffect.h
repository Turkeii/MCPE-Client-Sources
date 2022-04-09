#pragma once
#include "CEntity.h"

class CMobEffect {
private:
	virtual void Destructor();
public:
	virtual void applyEffects(C_Entity*, int, int);
	virtual void removeEffects(C_Entity*);
	virtual void applyInstantaneousEffect(C_Entity*, C_Entity*, C_Entity*, int, float);
	virtual bool isInstantaneous(void);
	virtual int getAttributeModifierValue(int, class AttributeModifier const &);
private:
	virtual void TryroFunc7();
};