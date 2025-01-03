#include "ECS.hpp"
#include "Collision.hpp"
#include "Object.hpp"

vector<Object*> EntitiesManager::m_entities;

vector<unique_ptr<Object>> EntitiesManager::m_entityPtr;

EntitiesManager::EntitiesManager() { }
EntitiesManager::~EntitiesManager() { }

void EntitiesManager::update() {
	refresh();

	for (auto& e : m_entities)
		if (e->isActive() && !e->isPause())
			e->update();

	for (auto& e : m_entities)
		if (e->isActive() && !e->isPause())
			e->_update();	
}

void EntitiesManager::render() {
	m_renderQueue.assign(100, {});

	for (auto& e : m_entities) {
		if (e->isActive() && !e->isVisible())
			m_renderQueue[e->getRenderOrder()].push_back(e);
	}

	for (auto& v : m_renderQueue) {
		for (auto& e : v)
			e->_render();
	}
}

void EntitiesManager::refresh() {
	m_entities.erase(remove_if(begin(m_entities), end(m_entities),
		[](Object* object)
		{
			if (!object) return true;
			return object->isDestroyed();
		}),
		end(m_entities));

	m_entityPtr.erase(remove_if(begin(m_entityPtr), end(m_entityPtr),
		[](const unique_ptr<Object>& object)
		{
			return object->isDestroyed();
		}),
		end(m_entityPtr));
}

Object& EntitiesManager::addEntity() {
	Object* e = new Object();
	m_entities.emplace_back(e);
	return *e;
}

void EntitiesManager::addEntity(Object* object) {
	m_entities.emplace_back(object);
}

void EntitiesManager::removeEntity(Object* object) {
	m_entities.erase(remove_if(m_entities.begin(), m_entities.end(), [&object](Object* obj) { return obj == object; }),
		m_entities.end());
}