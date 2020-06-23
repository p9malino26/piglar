

#ifndef ENTITIES_H
#define ENTITIES_H

#include <vector>
#include "Util.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

	
class EntityBase //abstract
{
public:
	virtual void update() = 0;

private:
	
protected:
    glm::vec2 m_position;
    glm::vec2 hitboxDims;
};

class Player : public EntityBase
{
public:
	void update() override;
private:
	float speed;
};

//entity subclasses
/*
class BurgBase: public EntityBase
{
	
};


class PCBase: public EntityBase
{
public:
	PCBase();
	enum class MainState {IDLE, SUSPICIOUS, CHASING};
	enum class ChangingState {NONE, HIGHER, LOWER};
protected:

	MainState m_mainState;
	ChangingState m_changingState;
	void update();
	bool thiefHasItem();
	bool eligibleToBecomingSuspicious();
	TimeDuration timeSinceLastStateChange();
};



class PigBase: public EntityBase //abstract
{
	
};

//very specific classes

class BurgPerson: public BurgBase
{
	
};

class SolePig: public PigBase 
{
	
};


class PigWithBurg: public PigBase, BurgBase
{
	
};

class UFO : public EntityBase
{
	
};



class House: public EntityBase
{
	
};

class PigWithPC: public PigBase, PCBase
{
	
};

class PCPerson: public PCBase
{
	
};
*/
#endif // ENTITIES_H
