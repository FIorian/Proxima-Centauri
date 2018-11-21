#include "MiniginPCH.h"
#include "TestObject.h"


TestObject::TestObject()
	:GameObject(Pos{0.f, 0.f, 1.f}, Scale{640.f, 480.f})
{
}

TestObject::~TestObject()
{
}

void TestObject::Initialize()
{
}

void TestObject::Update(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}
