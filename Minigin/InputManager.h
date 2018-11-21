#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include "Ghost.h"
#include "PacMan.h"

namespace dae
{
	enum class ControllerButton
	{
		DOWN,
		RIGHT,
		LEFT,
		UP,
		QUIT
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool HandleInput();

		//mutators
		void SetPacman(dae::PacMan* pacman) { m_pPacman = pacman; }
		void SetGhost(dae::Ghost* ghost) { m_pGhost = ghost; }
		void SetTwoPlayers(bool twoPlayers)
		{
			if (m_pGhost != nullptr)
				m_TwoPlayers = twoPlayers;
		}

	private:
		XINPUT_STATE currentState{};
		XINPUT_KEYSTROKE boardState{};
		bool m_ButtonActive{ false };
		bool m_KeyActive{ false };

		bool m_TwoPlayers{ false };

		dae::PacMan* m_pPacman = nullptr;
		dae::Ghost* m_pGhost = nullptr;

		//Commands
		std::unique_ptr<Command> m_GoRight = std::make_unique<GoRight>();
		std::unique_ptr<Command> m_GoLeft = std::make_unique<GoLeft>();
		std::unique_ptr<Command> m_GoUp = std::make_unique<GoUp>();
		std::unique_ptr<Command> m_GoDown = std::make_unique<GoDown>();
	};

}
