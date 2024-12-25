#include "EnemyManager.hpp"

EnemyManager* EnemyManager::m_instance = nullptr;

EnemyManager::EnemyManager(Mario& mario, Object* parent) : m_mario(mario), m_parent(parent) {
    if (!m_instance)
        m_instance = this;
}

EnemyManager::~EnemyManager() {}

EnemyManager* EnemyManager::getInstance() {
    return m_instance;
}

void EnemyManager::update() {
    m_gameTime += GameManager::getDeltaTime().asMilliseconds(); // Fixed deltaTime usage

    for (auto& point : m_spawnPoints) {
        if (!point.isSpawned && m_gameTime >= point.spawnTime) {
            spawnEnemy(point.enemyType, point.position);
            point.isSpawned = true;
        }
    }
}

void EnemyManager::addSpawnPoint(const Vector2f& pos, float spawnTime, const string& enemyType) {
    m_spawnPoints.push_back({ pos, spawnTime, enemyType });
}

Object* EnemyManager::spawnEnemy(const string& type, const Vector2f& pos) {
    Object* enemy = nullptr;

    if (type == "Goomba")
        enemy = new EnemiesGoomba(m_parent);
    else if (type == "KoopaTroopa")
        enemy = new EnemiesKoopaTroopa(m_parent);
    else if (type == "Blooper")
        enemy = new EnemiesBlooper(m_mario, m_parent);
    else if (type == "PiranhaPlant")
        enemy = new EnemiesPiranhaPlant(m_mario, m_parent);
    else if (type == "CheepCheepNormal")
        enemy = new EnemiesCheepCheepNormal(m_mario, m_parent);
    else if (type == "CheepCheepWater")
        enemy = new EnemiesCheepCheepWarter(m_mario, m_parent);

    if (enemy) {
        enemy->getComponent<Transform2D>().setWorldPosition(pos);
    }

    return enemy;
}

void EnemyManager::reset() {
    m_gameTime = 0;
    for (auto& point : m_spawnPoints) {
        point.isSpawned = false;
    }
}