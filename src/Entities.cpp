
#include "Entities.h"
#include "Util.h"
#include "Input.h"
#include "TimeManager.h"

#include <GLFW/glfw3.h>

void Player::update()
{
	float deltaDistance = TimeManager::deltaTime() * speed;
	if (Input::keyInfo(GLFW_KEY_W, GLFW_PRESS)) m_position += NORTH_VEC * deltaDistance;
	if (Input::keyInfo(GLFW_KEY_A, GLFW_PRESS)) m_position += WEST_VEC  * deltaDistance;
	if (Input::keyInfo(GLFW_KEY_S, GLFW_PRESS)) m_position += SOUTH_VEC * deltaDistance;
	if (Input::keyInfo(GLFW_KEY_D, GLFW_PRESS)) m_position += EAST_VEC  * deltaDistance;
	
}

/*Burg::PCBase::PCBase()
	:m_mainState( MainState::IDLE), m_changingState(ChangingState::NONE)
{
}


void Burg::PCBase::update()
{
	switch (m_mainState)
	{
	case MainState::IDLE:
		switch ( m_changingState )
		{
		case ChangingState::NONE : case ChangingState::LOWER:
			if(thiefHasItem() && eligibleToBecomingSuspicious())
			{
				m_changingState = ChangingState::HIGHER;
			}
			break;
		case ChangingState::HIGHER: // becoming suspicious
			
		}
	}
}

*/