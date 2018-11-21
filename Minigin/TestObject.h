#pragma once
#include "GameObject.h"

class TestObject : public dae::GameObject
{
public:
	TestObject();
	~TestObject();

	void Initialize() override;
	void Update(const GameContext& gameContext) override;

	//delete copy ctr & assignment opr
	TestObject(const TestObject& rhs) = delete;
	TestObject(TestObject&& rhs) = delete;
	TestObject& operator=(const TestObject& rhs) = delete;
	TestObject& operator=(TestObject&& rhs) = delete;
};

