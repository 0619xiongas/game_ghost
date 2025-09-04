#ifndef AS_SDL_SCENE_H
#define AS_SDL_SCENE_H

#include "ScreenObject.h"
#include "WorldObject.h"
/*
*	渲染的物体的坐标 = 世界坐标 - 模拟相机的坐标
*/
class Scene : public SDL_Object
{
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void Init() {}
	virtual void OnEvent(void* event) override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Clean() override;

	glm::vec2 WorldToScreenPos(const glm::vec2& worldPos);
	glm::vec2 ScreenToWorldPos(const glm::vec2& screenPos);
	glm::vec2 GetWorldSize() const;
	void SetWorldSize(const glm::vec2& worldSize);
	glm::vec2 GetCameraPos() const;
	void SetCameraPos(const glm::vec2& cameraPos);

	virtual void AddChild(SDL_Object* child) override;
	virtual void RemoveChild(SDL_Object* child) override;

protected:
	glm::vec2						m_camera_pos = glm::vec2(0.0f, 0.0f); // 模拟相机位置
	glm::vec2						m_worldSize = glm::vec2(0.0f, 0.0f);
	std::vector<WorldObject*>		m_worldObjects;
	std::vector<ScreenObject*>		m_screenObjects;
};
#endif