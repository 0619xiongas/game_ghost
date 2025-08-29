#include "core/GameEngine.h"
#include "scene/FightScene.h"
#include "GameMacro.h"
#include "component/Sprite.h"
GameEngine::GameEngine()
	:m_screenSize(0), m_isRunning(true), m_window(nullptr), m_renderer(nullptr)
	,m_curScene(nullptr),m_frameDelay(0),m_deltaTime(0.0f),m_assetManager(nullptr)
{
}

GameEngine::~GameEngine()
{
	Clean();
}

bool GameEngine::Init(const char* title, int width, int height)
{
	m_screenSize = glm::vec2(width, height);
	//初始化SDL3
	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed, %s\n", SDL_GetError());
		return false;
	}
	// 音频
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init failed, %s\n", SDL_GetError());
		return false;
	}
	if (!Mix_OpenAudio(0, NULL))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio failed, %s\n", SDL_GetError());
		return false;
	}
	Mix_AllocateChannels(16);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_Volume(-1, MIX_MAX_VOLUME / 4);
	
	// TTF
	if (!TTF_Init())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed, %s\n", SDL_GetError());
		return false;
	}
	SDL_CreateWindowAndRenderer(title, width, height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
	if (!m_window || !m_renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed, %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	
	// 资源管理器
	m_assetManager = new AssetManager();
	m_assetManager->Init(m_renderer);

	m_frameDelay = G_GAME_SEC_NS / G_GAME_FPS;
	m_curScene = new FightScene();
	m_curScene->Init();
	return true;
}

void GameEngine::Run()
{
	while (m_isRunning)
	{
		Uint64 start = SDL_GetTicksNS();
		HandleEvent();
		Update(m_deltaTime);
		Render();
		auto end = SDL_GetTicksNS();
		auto duartion = end - start;
		if (duartion < m_frameDelay)
		{
			SDL_DelayNS(m_frameDelay - duartion);
			m_deltaTime = (float)m_frameDelay / G_GAME_SEC_NS;
		}
		else
		{
			m_deltaTime = (float)duartion / G_GAME_SEC_NS;
		}
#ifdef GAME_DEBUG
		SDL_Log("FPS is %f", 1.0f / m_deltaTime);
#endif
	}
}

const glm::vec2& GameEngine::GetScreenSize() const 
{
	return m_screenSize;
}

SDL_Renderer* GameEngine::GetRenderer()
{
	return m_renderer;
}

SDL_Window* GameEngine::GetWindow()
{
	return m_window;
}

Scene *GameEngine::GetCurScene()
{
    return m_curScene;
}
AssetManager *GameEngine::GetAssetManager()
{
    return m_assetManager;
}

void GameEngine::RenderTexture(const Texture &texture, const glm::vec2 &pos, const glm::vec2 &size)
{
	SDL_FRect rect = {
		pos.x,
		pos.y,
		size.x,
		size.y
	};
	SDL_RenderTextureRotated(m_renderer, texture.texture, &texture.rect, &rect, texture.angle, nullptr, texture.isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void GameEngine::HandleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			m_isRunning = false;
			break;
		default:
			m_curScene->OnEvent(&event);
			break;
		}
	}
}

void GameEngine::Update(float dt)
{
	if (m_curScene)
	{
		m_curScene->Update(dt);
	}
}

void GameEngine::Render()
{
	if (m_curScene)
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
		m_curScene->Render();
		SDL_RenderPresent(m_renderer);
	}
}

void GameEngine::Clean()
{
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_curScene)
	{
		m_curScene->Clean();
		delete m_curScene;
		m_curScene = nullptr;
	}
	if(m_assetManager)
	{
		delete m_assetManager;
		m_assetManager = nullptr;
	}
	Mix_CloseAudio();
	Mix_Quit();

	TTF_Quit();

	SDL_Quit();
}