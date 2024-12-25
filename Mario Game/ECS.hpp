#pragma once
#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include <type_traits>
#include "SFML/Graphics.hpp"
#include "Common.hpp"
#include "Enum.hpp"
using namespace std;

class Entity;
class Component;

using ComponentID = std::size_t;

constexpr size_t MAX_COMPONENTS = 32;
using ComponentBitSet = bitset<MAX_COMPONENTS>;
using ComponentArray = array<Component*, MAX_COMPONENTS>;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

class Component {
private:
	bool m_active;
public:
	Entity* m_entity;
	Component() : m_active(true) {}

	virtual void init() {}
	virtual void start() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void render() {}
	void setEnable(bool isEnable) { m_active = isEnable; }
	bool isEnable() { return m_active; }

	virtual ~Component() {}
};

class Entity {
private:
	vector<unique_ptr<Component>> m_components;
	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;

protected:
	bool m_active;
	bool m_destroyed;
	bool m_pause;
	int m_renderOrder = 0;

public:
	Entity() : m_renderOrder(0), m_active(true), m_destroyed(false), m_pause(false) {}
	virtual ~Entity() {}

	void _update() {
		for (auto& c : m_components)
			if (c->isEnable())
				c->update();

		for (auto& c : m_components)
			if (c->isEnable())
				c->lateUpdate();
	}

	void _render() {
		render();
		for (auto& component : m_components)
			if (component->isEnable())
				component->render();
	}

	virtual void update() {}

	virtual void render() {}

	virtual void onCollisionEnter(Collision& col, const Direction& side) {}

	template<typename T>
	bool isType() const {
		return typeid(*this) == typeid(T);
	}

	template<typename T>
	bool isDerivedFrom() const {
		return (dynamic_cast<const T*>(this));
	}

	template<typename T>
	bool hasComponent() const {
		return m_componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(forward<TArgs>(mArgs)...));
		c->m_entity = this;
		unique_ptr<Component> uPtr{ c };
		m_components.emplace_back(move(uPtr));

		m_componentArray[getComponentTypeID<T>()] = c;
		m_componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T>
	T& getComponent() const {
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	virtual bool isActive() const {
		return m_active;
	}

	virtual bool isDestroyed() const {
		return m_destroyed;
	}

	virtual bool isPause() const {
		return m_pause;
	}

	void pause() {
		m_pause = true;
	}

	void setRenderOrder(int order) {
		m_renderOrder = order;
	}

	int getRenderOrder() const {
		return m_renderOrder;
	}

	Object* toObject() {
		return (Object*)this;
	}

	template<typename T>
	T* convertTo() {
		return (T*)this;
	}
};

class EntitiesManager {
private:
	static vector<Object*> m_entities;
	vector<vector<Object*>> m_renderQueue;

public:
	static vector<unique_ptr<Object>> m_entityPtr;
	EntitiesManager();
	~EntitiesManager();

	void update();

	void refresh();

	Object& addEntity();

	static void addEntity(Object* entity);

	static void removeEntity(Object* entity);
};

template<typename T>
T& Instantiate() {
	unique_ptr<T> ptr = make_unique<T>();
	T* res = ptr.get();
	EntitiesManager::m_entityPtr.push_back(move(ptr));
	return *res;
}