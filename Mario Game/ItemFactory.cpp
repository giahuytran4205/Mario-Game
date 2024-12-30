#include "ItemFactory.hpp"
#include "OneUpMushroom.hpp"
#include "MagicMushroom.hpp"
#include "FireFlower.hpp"
#include "Starman.hpp"

ItemFactory* ItemFactory::m_instance = nullptr;

ItemFactory::ItemFactory() {
	if (!m_instance)
		m_instance = this;
}

ItemFactory::~ItemFactory() {}

ItemFactory* ItemFactory::getInstance() {
	return m_instance;
}

Item* ItemFactory::getItem() {
	int item = randByProbability(m_weights);
	
	if (item == ItemType::NONE)
		return nullptr;
	if (item == ItemType::ONE_UP_MUSHROOM)
		return &Instantiate<OneUpMushroom>();
	if (item == ItemType::MAGIC_MUSHROOM)
		return &Instantiate<MagicMushroom>();
	if (item == ItemType::FIRE_FLOWER)
		return &Instantiate<FireFlower>();
	if (item == ItemType::STARMAN)
		return &Instantiate<Starman>();
}