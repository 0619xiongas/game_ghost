#ifndef AS_SDL_GAME_ENGINE_H
#define AS_SDL_GAME_ENGINE_H
#include <glm/glm.hpp>
#include "AssetManager.h"
#include "../aslib/asSingleton.h"

class Scene;
struct Texture;
class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	bool Init(const char* title, int width, int height);

	void Run();

	const glm::vec2& GetScreenSize() const;

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	Scene* GetCurScene();
		
	AssetManager* GetAssetManager();


	// func
	void RenderTexture(const Texture& texture,const glm::vec2& pos,const glm::vec2& size);
private:
	void HandleEvent();

	void Update(float dt);

	void Render();

	void Clean();

private:
	glm::vec2					m_screenSize;
	bool						m_isRunning;
	SDL_Window*					m_window;
	SDL_Renderer*				m_renderer;
	Scene*						m_curScene;
	Uint64						m_frameDelay;
	float						m_deltaTime;
	AssetManager*				m_assetManager;
};
#define  g_GameEngine asSingleton<GameEngine>::instance()
#endif