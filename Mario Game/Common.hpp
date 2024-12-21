#include "ECS.hpp"
#include <boost/json.hpp>
#include "SFML/Graphics.hpp"
#include <string>
using namespace std;
using namespace sf;

#define DEBUG true

class Object;
class Transform2D;
class TextureManager;
class Physics2D;
class Collision;
class GUI;
class SpriteRenderer;
class Toggle;

boost::json::object readJsonFile(string filename);

Color darkenColor(const Color& color, float factor);