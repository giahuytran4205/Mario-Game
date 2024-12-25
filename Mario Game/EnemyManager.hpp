#pragma once
#include "Common.hpp"
#include "Mario.hpp"
#include "EnemiesGoomba.h"
#include "EnemiesKoopaTroopa.h"
#include "EnemiesBlooper.h"
#include "EnemiesPiranhaPlant.h"
#include "EnemiesCheepCheepNormal.h"
#include "EnemiesCheepCheepWarter.h"
#include "GameManager.hpp"

struct SpawnPoint {
    Vector2f position;
    float spawnTime;
    string enemyType;
    bool isSpawned = false;
};

class EnemyManager {
private:
    static EnemyManager* m_instance;
    vector<SpawnPoint> m_spawnPoints;
    Mario& m_mario;
    Object* m_parent;
    float m_gameTime = 0;

public:
    EnemyManager(Mario& mario, Object* parent = nullptr);
    ~EnemyManager();

    static EnemyManager* getInstance();

    void update();
    void addSpawnPoint(const Vector2f& pos, float spawnTime, const string& enemyType);
    Object* spawnEnemy(const string& type, const Vector2f& pos);
    void reset();
};