#ifndef G_AS_PLAYER_H
#define G_AS_PLAYER_H
#include "core/GameObject.h"
#include "component/SpriteAnimation.h"
class Player : public GameObject
{
public:
    Player() = default;
    ~Player() = default;

    virtual void Init() override;
	virtual void OnEvent(void* event) override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Clean() override;

    void CheckKeyboardInput();

    void SyncCameraPosition();

    void CheckStatus();

    void SetState(bool isMove);
private:
    SpriteAnimation*        m_animIdle = nullptr;
    SpriteAnimation*        m_animMove = nullptr;
    bool                    m_isMoving = false;
};


#endif