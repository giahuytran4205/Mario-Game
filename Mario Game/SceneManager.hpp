#pragma once
#include "ECS.hpp"
#include "Scene.hpp"

class SceneManager {
private:
	static SceneManager* m_instance;
	Scene* m_currentScene;

public:
	SceneManager() {
		if (!m_instance) {
			m_instance = this;
		}

		m_currentScene = nullptr;
	}

	~SceneManager() {}

	SceneManager* getInstance() {
		return m_instance;
	}

	template<typename T, typename... TArgs>
	void setCurrentScene(TArgs&&... mArgs) {
		if (m_currentScene)
			m_currentScene->destroy();
		
		m_currentScene = new T(mArgs...);
	}

	void destroyCurrentScene() {
		if (!m_currentScene)
			return;

		m_currentScene->destroy();
	}
};