#pragma once
#include <bitset>
#include <array>
#include <vector>
#include <memory>
using namespace std;

class Entity;
class Component;
class Collision;

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
	bool m_active;

public:
	virtual ~Entity() {}

	void update() {
		for (auto& c : m_components)
			c->update();

		for (auto& c : m_components)
			c->lateUpdate();

		for (auto& c : m_components)
			c->render();
	}

	virtual void Update() {}

	virtual void onCollisionEnter(Collision& col) {}

	virtual void render() {

	}

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

	bool isActive() {
		return m_active;
	}
};

class EntitiesManager {
private:
	static vector<unique_ptr<Entity>> m_entities;

public:
	void update() {
		for (auto& e : m_entities)
			e->Update();
				
		for (auto& e : m_entities)
			e->update();

		for (auto& e : m_entities)
			e->render();
	}

	void refresh() {
		m_entities.erase(remove_if(begin(m_entities), end(m_entities),
			[](const unique_ptr<Entity>& entity)
			{
				return !entity->isActive();
			}),
			end(m_entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		unique_ptr<Entity> uPtr{ e };
		m_entities.emplace_back(move(uPtr));
		return *e;
	}

	static void addEntity(Entity* entity) {
		unique_ptr<Entity> uPtr{ entity };
		m_entities.emplace_back(move(uPtr));
	}
};