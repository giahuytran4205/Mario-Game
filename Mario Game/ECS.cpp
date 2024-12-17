#include "ECS.hpp"
#include "Collision.hpp"

vector<Entity*> EntitiesManager::m_entities;

vector<unique_ptr<Entity>> EntitiesManager::m_entityPtr;