#include "scene/FightScene.h"
#include "core/GameEngine.h"
#include "GameMacro.h"
#include "entity/Player.h"
void FightScene::Init()
{
	m_worldSize = g_GameEngine->GetScreenSize() * 3.0f;
	m_camera_pos = glm::vec2(-100.0f);
	m_player = new Player();
	m_player->Init();
	m_player->SetWorldPos(m_worldSize / 2.0f);
	AddChild(m_player);
}

void FightScene::OnEvent(void* event)
{
	Scene::OnEvent(event);
}

void FightScene::Update(float dt)
{
	Scene::Update(dt);
}

void FightScene::Render()
{
	RenderGrid();
	RenderBoundary();
	Scene::Render();
}

void FightScene::Clean()
{
	Scene::Clean();
}

void FightScene::RenderGrid()
{
	glm::vec2 start = -m_camera_pos;
	glm::vec2 end = m_worldSize - m_camera_pos;
	SDL_SetRenderDrawColorFloat(g_GameEngine->GetRenderer(), 0.5f, 0.5f, 0.5f, 1.0f);
	for (float x = start.x; x <= end.x; x += G_GAME_BG_GRID_SIZE)
	{ 
		SDL_RenderLine(g_GameEngine->GetRenderer(), x, start.y, x, end.y);
	}
	for (float y = start.y; y <= end.y; y += G_GAME_BG_GRID_SIZE)
	{
		SDL_RenderLine(g_GameEngine->GetRenderer(), start.x, y, end.x, y);
	}
	SDL_SetRenderDrawColorFloat(g_GameEngine->GetRenderer(), 0.0f, 0.0f, 0.0f, 1.0f);
}

void FightScene::RenderBoundary()
{
	glm::vec2 start = -m_camera_pos;
	glm::vec2 end = m_worldSize - m_camera_pos;
	SDL_SetRenderDrawColorFloat(g_GameEngine->GetRenderer(), 1.0f, 1.0f, 1.0f, 1.0f);
	for(float i = 0;i < G_GAME_BG_BD_SIZE;++i)
	{
		SDL_FRect rect = 
		{
			start.x - i,
			start.y - i,
			end.x - start.x + i * 2,
			end.y - start.y + i * 2
		};
		SDL_RenderRect(g_GameEngine->GetRenderer(), &rect);
	}
	SDL_SetRenderDrawColorFloat(g_GameEngine->GetRenderer(), 0.0f, 0.0f, 0.0f, 1.0f);
}
