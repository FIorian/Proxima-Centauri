#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	// Keyboard Input
	SDL_Event e;
	if (m_pPacman != nullptr)
	{
		while (SDL_PollEvent(&e))
		{
			//FIRST PLAYER
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_s:
					if (!m_KeyActive)
					{
						// execute command
						m_GoDown->Execute(m_pPacman);
						// set keyactive
						m_KeyActive = true;
					}
					break;
				case SDLK_d:
					if (!m_KeyActive)
					{
						// execute command
						m_GoRight->Execute(m_pPacman);
						// set keyactive
						m_KeyActive = true;
					}
					break;
				case SDLK_a:
					if (!m_KeyActive)
					{
						// execute command
						m_GoLeft->Execute(m_pPacman);
						// set keyactive
						m_KeyActive = true;
					}
					break;
				case SDLK_w:
					if (!m_KeyActive)
					{
						// execute command
						m_GoUp->Execute(m_pPacman);
						// set keyactive
						m_KeyActive = true;
					}
					break;
				case SDLK_2:
					if (!m_KeyActive)
					{
						// toggle playeractive
						m_TwoPlayers = !m_TwoPlayers;
						m_pGhost->SetPlayerControlled(m_TwoPlayers);
						// set keyactive
						m_KeyActive = true;
					}
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
				case SDLK_s:
					if (m_KeyActive)
					{
						// reset keyactive
						m_KeyActive = false;
					}
					break;
				case SDLK_d:
					if (m_KeyActive)
					{
						// reset keyactive
						m_KeyActive = false;
					}
					break;
				case SDLK_a:
					if (m_KeyActive)
					{
						// reset keyactive
						m_KeyActive = false;
					}
					break;
				case SDLK_w:
					if (m_KeyActive)
					{
						// reset keyactive
						m_KeyActive = false;
					}
					break;
				case SDLK_2:
					if (m_KeyActive)
					{
						// reset keyactive
						m_KeyActive = false;
					}
				default:
					break;
				}
				break;
			case SDL_QUIT:
				return false;
				break;
			default:
				break;
			}

			//SECOND PLAYER
			//THIS STILL NEEDS ADJUSTMENTS FOR THE GHOST PLAYER
			if (m_TwoPlayers)
			{
				switch (e.type)
				{
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_DOWN:
						if (!m_KeyActive)
						{
							// execute command
							m_GoDown->Execute(m_pGhost);
							// set keyactive
							m_KeyActive = true;
						}
						break;
					case SDLK_RIGHT:
						if (!m_KeyActive)
						{
							// execute command
							m_GoRight->Execute(m_pGhost);
							// set keyactive
							m_KeyActive = true;
						}
						break;
					case SDLK_LEFT:
						if (!m_KeyActive)
						{
							// execute command
							m_GoLeft->Execute(m_pGhost);
							// set keyactive
							m_KeyActive = true;
						}
						break;
					case SDLK_UP:
						if (!m_KeyActive)
						{
							// execute command
							m_GoUp->Execute(m_pGhost);
							// set keyactive
							m_KeyActive = true;
						}
						break;
					default:
						break;
					}
					break;
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
					case SDLK_DOWN:
						if (m_KeyActive)
						{
							// reset keyactive
							m_KeyActive = false;
						}
						break;
					case SDLK_RIGHT:
						if (m_KeyActive)
						{
							// reset keyactive
							m_KeyActive = false;
						}
						break;
					case SDLK_LEFT:
						if (m_KeyActive)
						{
							// reset keyactive
							m_KeyActive = false;
						}
						break;
					case SDLK_UP:
						if (m_KeyActive)
						{
							// reset keyactive
							m_KeyActive = false;
						}
						break;
					default:
						break;
					}
					break;
				case SDL_QUIT:
					return false;
					break;
				default:
					break;
				}
			}
		}
	}

	return HandleInput();
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// Controller input
	switch (button)
	{
	case ControllerButton::DOWN:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::RIGHT:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::LEFT:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::UP:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::QUIT:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	default: return false;
	}
}

bool dae::InputManager::HandleInput()
{
	if (!m_ButtonActive && IsPressed(ControllerButton::DOWN))
	{
		//execute command
		m_GoDown->Execute(m_pPacman);
		// set button active
		m_ButtonActive = true;
		return true;
	}
	if (!m_ButtonActive && IsPressed(ControllerButton::RIGHT))
	{
		// execute command
		m_GoRight->Execute(m_pPacman);
		// set button active
		m_ButtonActive = true;
		return true;
	}
	if (!m_ButtonActive && IsPressed(ControllerButton::LEFT))
	{
		//execute command
		m_GoLeft->Execute(m_pPacman);
		// set button active
		m_ButtonActive = true;
		return true;
	}
	if (!m_ButtonActive && IsPressed(ControllerButton::UP))
	{
		//execute command
		m_GoUp->Execute(m_pPacman);
		// set button active
		m_ButtonActive = true;
		return true;
	}
	if (!m_ButtonActive && IsPressed(ControllerButton::QUIT))
	{
		// set button active
		m_ButtonActive = true;
		return false;
	}

	if (!IsPressed(ControllerButton::DOWN) &&
		!IsPressed(ControllerButton::RIGHT) &&
		!IsPressed(ControllerButton::LEFT) &&
		!IsPressed(ControllerButton::UP) &&
		!IsPressed(ControllerButton::QUIT))
	{
		// no button active
		m_ButtonActive = false;
		return true;
	}

	//this should never trigger but I gotta please VS
	return true;

}
