#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "SDL.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "TextComponent.h"
#include "MainScene.h"

const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();
	LoadGame();

	{
		auto& renderer = dae::Renderer::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();

		GameContext gameContext;

		auto currentTime = std::chrono::high_resolution_clock::now();
		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		while(doContinue) 
		{
			currentTime = std::chrono::high_resolution_clock::now();
			gameContext.deltaT = std::chrono::duration<float>(currentTime - lastTime).count();

			//input
			doContinue = input.ProcessInput();
			//update
			sceneManager.Update(gameContext);
			//render
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
    return 0;
}

SDL_Window* window;

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1000,
		813,
		SDL_WINDOW_OPENGL       
	);
	if (window == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");
	// Init the Renderer
	dae::Renderer::GetInstance().Init(window);
}

void LoadGame()
{
	auto& renderer = dae::Renderer::GetInstance();
	renderer.MakePool(240); //adjust pool size when necessery
	renderer.MakeTextPool(5); //adjust pool size if necessary

	std::shared_ptr<dae::MainScene> mainScene = std::make_shared<dae::MainScene>();
	mainScene->Initialize();
	dae::SceneManager::GetInstance().AddScene(mainScene);

	dae::Renderer::GetInstance().AddComponent("capsule.png", Pos{ -50.f, -50.f }, Scale{ 1.f, 1.f });
} 

void Cleanup()
{
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}
