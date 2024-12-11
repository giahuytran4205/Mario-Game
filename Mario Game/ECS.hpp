#pragma once
#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include "Common.hpp"
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
public:
	Entity* m_entity;

	virtual void init() {}
	virtual void start() {}
	virtual void update() {}
	virtual void lateUpdate() {}
	virtual void render() {}

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
	int m_renderOrder = 0;

public:
	Entity() : m_renderOrder(0), m_active(true), m_destroyed(false) {}
	virtual ~Entity() {}

	void _update() {
		for (auto& c : m_components)
			c->update();

		for (auto& c : m_components)
			c->lateUpdate();

		for (auto& c : m_components)
			c->render();
	}

	void _render() {
		render();
		for (auto& component : m_components)
			component->render();
	}

	virtual void update() {}

	virtual void render() {}

	virtual void onCollisionEnter(Collision& col) {}

	template<typename T>
	bool isType() const {
		return typeid(*this) == typeid(T);
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
	static vector<Entity*> m_entities;
	vector<vector<Entity*>> m_renderQueue;

public:
	EntitiesManager() { }
	~EntitiesManager() { }

	void update() {
		refresh();

		for (auto& e : m_entities)
			if (e->isActive())
				e->update();
				
		for (auto& e : m_entities)
			if (e->isActive())
				e->_update();

		m_renderQueue.assign(100, {});
		for (auto& e : m_entities) {
			if (e->isActive())
				m_renderQueue[e->getRenderOrder()].push_back(e);
		}

		for (auto& v : m_renderQueue) {
			for (auto& e : v)
				e->_render();
		}
	}

	void refresh() {
		m_entities.erase(remove_if(begin(m_entities), end(m_entities),
			[](Entity* entity)
			{
				if (!entity) return true;
				return entity->isDestroyed();
			}),
			end(m_entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		m_entities.emplace_back(e);
		return *e;
	}

	static void addEntity(Entity* entity) {
		m_entities.emplace_back(entity);
	}

	static void removeEntity(Entity* entity) {
		m_entities.erase(remove_if(m_entities.begin(), m_entities.end(), [&entity](Entity* e) { return e == entity; }),
			m_entities.end());
	}
};