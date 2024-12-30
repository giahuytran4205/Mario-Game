#include "Map.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include "Block.hpp"
#include "Transform2D.hpp"
#include "Item.hpp"
#include "Portal.hpp"
#include "Brick.hpp"
#include "QuestionBlock.hpp"
#include "EnemiesGoomba.hpp"
#include "EnemiesHammerBro.hpp"
#include "EnemiesKoopaTroopa.hpp"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

const vector<MapInfo> Map::mapsInfo = {
	{ "1-1", "Resources/Map/Worlds-1-1.json", "Resources/Thumbnails/Worlds-1-1.png" },
	{ "2-1", "Resources/Map/Worlds-2-1.json", "Resources/Thumbnails/Worlds-2-1.png" },
	{ "3-1", "Resources/Map/Worlds-3-1.json", "Resources/Thumbnails/Worlds-3-1.png" },
	{ "4-1", "Resources/Map/Worlds-4-1.json", "Resources/Thumbnails/Worlds-4-1.png" },
	{ "5-1", "Resources/Map/Worlds-5-1.json", "Resources/Thumbnails/Worlds-5-1.png" }
};

Map::Map(Mario& mario) : m_mario(mario) {
	m_width = m_height = 0;
	m_row = m_col = 0;
	m_tileWidth = m_tileHeight = 0;
	m_startDepth = 0;
	m_background.setParent(this);
	m_background.setPosition(0, 0);
	m_transform.setAnchor( 0, 0 );
	m_renderOrder = 0;
}

Map::Map(const string& filename, Mario& mario) : Map(mario) {
	loadFromJsonFile(filename);
}

Map::~Map() {
	for (Object* obj : m_objects)
		delete obj;
}

void Map::loadTilesets(json::object& data) {
	for (auto& i : data["tilesets"].as_array()) {
		json::object& obj = i.as_object();
		m_tilesets.push_back(pair<int, TileSet&>( obj["firstgid"].as_int64(), TextureManager::getTileset(obj["source"].as_string().c_str()) ));
	}
}

const Texture& Map::getTile(int id) {
	auto it = upper_bound(m_tilesets.begin(), m_tilesets.end(), pair<int, TileSet>{id, {}},
		[](const pair<int, TileSet>& a, const pair<int, TileSet>& b)
		{
			return a.first < b.first;
		});

	if (it == m_tilesets.begin())
		return {};

	--it;

	int numCols = it->second.getSize().x / m_tileWidth;

	id -= it->first;

	return it->second.getTile(IntRect(id % numCols * 16, id / numCols * 16, m_tileWidth, m_tileHeight));
}

void Map::loadObjectInGroup(Environment environment, json::object& group) {
	for (auto& i : group["layers"].as_array()) {
		json::object layer = i.as_object();
		if (layer["name"].as_string() == "Brick") {
			for (auto& i : layer["objects"].as_array()) {
				auto obj = i.as_object();
				float x = obj["x"].as_int64();
				float y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				Brick* brick = new Brick(environment, this);
				brick->getComponent<Transform2D>().setWorldPosition(x + width / 2, y + height / 2);

				m_objects.push_back(brick);
			}
		}
		if (layer["name"].as_string() == "Question Block") {
			for (auto& i : layer["objects"].as_array()) {
				auto obj = i.as_object();
				float x = obj["x"].as_int64();
				float y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				QuestionBlock* questionBlock = new QuestionBlock(environment, this);
				questionBlock->getComponent<Transform2D>().setWorldPosition(x + width / 2, y + height / 2);

				m_objects.push_back(questionBlock);
			}
		}
		if (layer["name"].as_string() == "Hidden Block") {
			for (auto& i : layer["objects"].as_array()) {
				auto obj = i.as_object();
				float x = obj["x"].as_int64();
				float y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				QuestionBlock* questionBlock = new QuestionBlock(environment, this);
				questionBlock->getComponent<Transform2D>().setWorldPosition(x + width / 2, y + height / 2);
				questionBlock->setHide(true);

				m_objects.push_back(questionBlock);
			}
		}
		if (layer["name"].as_string() == "Flagpole") {
			json::object obj = layer["objects"].as_array()[0].as_object();
			int x = obj["x"].as_int64();
			int y = obj["y"].as_int64();
			int width = obj["width"].as_int64();
			int height = obj["height"].as_int64();

			FlagPole* flagpole = new FlagPole(x + width / 2, y, 2, height, this);
			flagpole->setRenderOrder(3);
			m_objects.push_back(flagpole);
		}
	}
}

void Map::loadFromJsonFile(const string& filename) {
	json::object parsed = readJsonFile(filename);
	
	loadTilesets(parsed);

	m_col = parsed["width"].as_int64();
	m_row = parsed["height"].as_int64();
	m_tileWidth = parsed["tilewidth"].as_int64();
	m_tileHeight = parsed["tileheight"].as_int64();
	m_width = m_tileWidth * m_col;
	m_height = m_tileHeight * m_row;

	for (auto& item : parsed["layers"].as_array()) {
		auto& layer = item.as_object();
		if (layer["name"] == "Overworld") {
			loadObjectInGroup(Environment::OVERWORLD, layer);
		}
		if (layer["name"] == "Underground") {
			loadObjectInGroup(Environment::UNDERGROUND, layer);
		}
		if (layer["name"] == "Athletic") {
			loadObjectInGroup(Environment::ATHLETIC, layer);
		}
		if (layer["name"] == "Castle") {
			loadObjectInGroup(Environment::CASTLE, layer);
		}
		if (layer["name"] == "Underwater") {
			loadObjectInGroup(Environment::UNDERWATER, layer);
		}
		if (layer["name"] == "Graphics Layer") {
			for (int i = 0; i < layer["data"].as_array().size(); i++) {
				int id = layer["data"].as_array()[i].as_int64();

				if (id == 0) continue;
				Block* block = new Block(getTile(id), {i % m_col * 16.0f + 8, i / m_col * 16.0f + 8});
				block->setParent(this);
				block->setRenderOrder(2);
				m_objects.push_back(block);
			}
		}

		if (layer["name"] == "Background Layer") {
			string path = layer["image"].as_string().c_str();
			m_background.setTexture(TextureManager::getTexture(path));
		}

		if (layer["name"] == "Spawn Position") {
			json::object obj = layer["objects"].as_array()[0].as_object();
			m_spawnPos.x = obj["x"].as_int64();
			m_spawnPos.y = obj["y"].as_int64();

			m_startDepth = obj["properties"].as_array()[0].as_object()["value"].as_int64();
		}

		if (layer["name"] == "Teleportation Gate") {
			for (auto& i : layer["objects"].as_array()) {
				auto& portal = i.as_object();

				int width = portal["width"].as_int64();
				int height = portal["height"].as_int64();

				float posX = portal["x"].as_int64();
				float posY = portal["y"].as_int64();

				float destX = 0, destY = 0, inDir = 0, outDir = 0, destDepth = 0;
				
				for (auto& j : portal["properties"].as_array()) {
					auto prop = j.as_object();

					if (prop["name"].as_string() == "destX")
						destX = prop["value"].as_int64();

					if (prop["name"].as_string() == "destY")
						destY = prop["value"].as_int64();

					if (prop["name"].as_string() == "inDirection")
						inDir = prop["value"].as_int64();

					if (prop["name"].as_string() == "outDirection")
						outDir = prop["value"].as_int64();

					if (prop["name"].as_string() == "destDepth")
						destDepth = prop["value"].as_int64();
				}

				m_objects.push_back(new Portal(Vector2f{ posX, posY }, Vector2f{ destX, destY }, inDir, outDir, destDepth));
				m_objects.back()->setParent(this);
			}
		}

		if (layer["name"] == "Flagpole") {
			json::object obj = layer["objects"].as_array()[0].as_object();
			int x = obj["x"].as_int64();
			int y = obj["y"].as_int64();
			int width = obj["width"].as_int64();
			int height = obj["height"].as_int64();

			FlagPole* flagpole = new FlagPole(x + width / 2, y, 2, height, this);
			flagpole->setRenderOrder(3);
			m_objects.push_back(flagpole);
		}

		if (layer["name"] == "Lift") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				Direction direction;
				bool isCircular, isLoop, isLaunch;
				float startOffset, endOffset;

				for (auto& j : obj["properties"].as_array()) {
					auto prop = j.as_object();
					if (prop["name"] == "direction")
						direction = (Direction)prop["value"].as_int64();
					else if (prop["name"] == "isLaunch")
						isLaunch = prop["value"].as_bool();
					else if (prop["name"] == "isCircular")
						isCircular = prop["value"].as_bool();
					else if (prop["name"] == "isLoop")
						isLoop = prop["value"].as_bool();
					else if (prop["name"] == "startOffset")
						startOffset = prop["value"].as_int64();
					else if (prop["name"] == "endOffset")
						endOffset = prop["value"].as_int64();

				}

				Lift* lift = new Lift(Vector2f(x + width / 2, y), startOffset, endOffset, direction, isLaunch);
				lift->setParent(this);
				lift->setCircular(isCircular);
				lift->setLoop(isLoop);

				m_objects.push_back(lift);
			}
		}

		if (layer["name"] == "Beanstalk") {
			/*for (auto& i : layer["objects"].as_array()) {
				auto& portal = i.as_object();

				int width = portal["width"].as_int64();
				int height = portal["height"].as_int64();

				float posX = portal["x"].as_int64();
				float posY = portal["y"].as_int64();

				float destX = 0, destY = 0, maxHeight = 0;
				int destDepth = 0;

				for (auto& j : portal["properties"].as_array()) {
					auto prop = j.as_object();

					if (prop["name"] == "destX")
						destX = prop["value"].as_int64();
					else if (prop["name"] == "destY")
						destY = prop["value"].as_int64();
					else if (prop["name"] == "destDepth")
						destDepth = prop["value"].as_int64();
					else if (prop["name"] == "maxHeight")
						maxHeight = prop["value"].as_int64();
				}

				Beanstalk* beanstalk = new Beanstalk(Vector2f(posX, posY), maxHeight, Vector2f(destX, destY), this);
				m_objects.push_back(beanstalk);
			}*/
		}

		if (layer["name"] == "Dead Zone") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				DeadZone* deadZone = new DeadZone(FRect(x, y, width, height), this);
				m_objects.push_back(deadZone);
			}
		}

;		if (layer["name"] == "Jumper") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				Jumper* jumper = new Jumper(Vector2f(x + width / 2, y + height), this);
				m_objects.push_back(jumper);
			}
		}

		if (layer["name"] == "Castle Gate") {
			json::object obj = layer["objects"].as_array()[0].as_object();

			m_castleGate.x = obj["x"].as_int64();
			m_castleGate.y = obj["y"].as_int64();
		}

		if (layer["name"] == "Firework Area") {
			json::object obj = layer["objects"].as_array()[0].as_object();

			int x = obj["x"].as_int64();
			int y = obj["y"].as_int64();
			int width = obj["width"].as_int64();
			int height = obj["height"].as_int64();

			m_fireworkArea = FRect(x, y, width, height);
		}

		if (layer["name"] == "Coin") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				Coin* coin = new Coin(x, y, this);
				m_objects.push_back(coin);
			}
		}

		if (layer["name"] == "Goomba") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();
				int width = obj["width"].as_int64();
				int height = obj["height"].as_int64();

				EnemiesGoomba* goomba = new EnemiesGoomba(this);
				goomba->getComponent<Transform2D>().setWorldPosition(x, y);
				m_objects.push_back(goomba);
			}
		}

		if (layer["name"] == "KoopaTroopa") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();

				EnemiesKoopaTroopa* koopaTroopa = new EnemiesKoopaTroopa(this);
				koopaTroopa->getComponent<Transform2D>().setWorldPosition(x, y);
				m_objects.push_back(koopaTroopa);
			}
		}

		if (layer["name"] == "HammerBro") {
			for (auto& i : layer["objects"].as_array()) {
				auto& obj = i.as_object();

				int x = obj["x"].as_int64();
				int y = obj["y"].as_int64();

				EnemiesHammerBro* hammerBro = new EnemiesHammerBro(m_mario, this);
				hammerBro->getComponent<Transform2D>().setWorldPosition(x, y);
				m_objects.push_back(hammerBro);
			}
		}
	}

	CollisionManager::getInstance()->resize(m_width, m_height);
}

void Map::setBackground(const Texture& texture) {
	m_background.setTexture(texture);
}

Vector2i Map::getSize() const {
	return { m_width, m_height };
}

int Map::rowCount() const {
	return m_row;
}

int Map::colCount() const {
	return m_col;
}

int Map::getStartDepth() const {
	return m_startDepth;
}

Vector2f Map::getSpawnPos() const {
	return m_spawnPos;
}

Vector2f Map::getCastleGate() const {
	return m_castleGate;
}

void Map::render() {
	GameManager::getInstance()->getRenderWindow().draw(m_background);
}

FRect Map::getFireworkArea() const {
	return m_fireworkArea;
}

void Map::launchFireworks() {
	auto coroutine = [&]() -> Coroutine {
		int numFirework = randRange(5, 10);
		for (int i = 0; i < numFirework; i++) {
			float x = randRange(3248.0f, 3248 + 112.0f);
			float y = randRange(304.0f, 304.0f + 64.0f);
			Object& firework = ParticleSystem::getInstance()->addParticle("Resources/Particles/Firework.json", Vector2f(x, y));
			SceneManager::getInstance()->getCurrentScene().getComponent<SoundComponent>().play(SoundTrack::FIREWORK);
			firework.getComponent<Physics2D>().setEnableGravity(false);
			co_await WaitForMiliseconds(firework.getComponent<Animation>().getTrackLength(0));
		}
	}();
}