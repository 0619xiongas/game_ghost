#ifndef AS_SDL_FIGHT_SCENE_H
#define AS_SDL_FIGHT_SCENE_H
#include "../core/Scene.h"

class Player;
class FightScene : public Scene
{
public:
	FightScene() = default;
	~FightScene() = default;

	virtual void Init() override;
	virtual void OnEvent(void* event) override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Clean() override;

private:
	void RenderGrid();

	void RenderBoundary();
private:
	Player* 			m_player = nullptr;
};
#endif
