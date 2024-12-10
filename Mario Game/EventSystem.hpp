#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace sf;
using namespace std;

class IEventListener {
public:
	IEventListener();
	~IEventListener();
	virtual void handleEvent(const Event& event) = 0;
};

class EventSystem {
private:
	static vector<IEventListener*> m_listeners;
	RenderWindow& m_window;
	static EventSystem* m_instance;

public:
	EventSystem(RenderWindow& window);
	~EventSystem();

	static EventSystem* getInstance();
	void handleEvents();
	void addListener(IEventListener* listener);
	void removeListener(IEventListener* listener);
	void sendEvent(const Event& event);
};