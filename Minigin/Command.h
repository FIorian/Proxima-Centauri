#pragma once
#include "Character.h"

namespace dae
{
	//command base class
	class Command
	{
	public:
		~Command() = default;

		virtual void Execute(dae::Character* actor) = 0;
	};

	//different input command classes:

	class GoRight final : public Command
	{
	public:
		void Execute(dae::Character* actor) override
		{
			if (actor != nullptr)
				actor->SetRequestedDirection(Direction::RIGHT);
		}
	};

	class GoLeft final : public Command
	{
	public:
		void Execute(dae::Character* actor) override
		{
			if (actor != nullptr)
				actor->SetRequestedDirection(Direction::LEFT);
		};
	};

	class GoUp final : public Command
	{
	public:
		void Execute(dae::Character* actor) override
		{
			if (actor != nullptr)
				actor->SetRequestedDirection(Direction::UP);
		};
	};

	class GoDown final : public Command
	{
	public:
		void Execute(dae::Character* actor) override
		{
			if (actor != nullptr)
				actor->SetRequestedDirection(Direction::DOWN);
		};
	};
}
