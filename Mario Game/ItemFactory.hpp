#pragma once
#include "Item.hpp"
#include "Random.hpp"

class ItemFactory {
private:
	static ItemFactory* m_instance;
	enum ItemType {
		NONE,
		ONE_UP_MUSHROOM,
		MAGIC_MUSHROOM,
		FIRE_FLOWER,
		STARMAN,
	};

	vector<int> m_weights = {
		50,
		10,
		10,
		10,
		10,
	};

public:
	ItemFactory();
	~ItemFactory();

	static ItemFactory* getInstance();
	Item* getItem();
};