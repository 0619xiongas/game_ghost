#ifndef AS_SDL_OBJECT_H
#define AS_SDL_OBJECT_H
#include <glm/glm.hpp>
#include <vector>
// 对象底层基类
 // 析构函数不做清理资源的事情，交给Clean
// 构造函数不做初始化，交给Init
enum class ObjectType
{
	OT_None,
	OT_Scene,
	OT_WorldObject,
	OT_ScreenObject,
	OT_GameObject,
};
class SDL_Object
{
public:
	SDL_Object() = default;
	virtual ~SDL_Object() = default;

	virtual void Init(){} 
	virtual void OnEvent(void* event);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Clean();

	virtual void AddChild(SDL_Object* child);
	virtual void RemoveChild(SDL_Object* child);

	ObjectType GetType() const;
	void SetType(ObjectType type);
	bool IsActive() const;
	void SetActive(bool active);
protected:
	std::vector<SDL_Object*> 		m_childrens;
	ObjectType						m_type = ObjectType::OT_None;
	bool							m_isActive = true;
};

#endif
