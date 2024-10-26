#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace sf;
using namespace std;

class IEventListener {
public:
	virtual void handleEvent(const Event& event) = 0;
};

class EventSystem {
private:
	vector<IEventListener*> m_listeners;
	RenderWindow& m_window;

public:
	static EventSystem* m_instance;

	EventSystem(RenderWindow& window);
	~EventSystem();

	void handleEvents();
	void addListener(IEventListener* listener);
	void sendEvent(const Event& event);
};