#include "ECS.hpp"
#include <boost/json.hpp>
#include <string>
using namespace std;

class Object;
class Transform2D;
class TextureManager;
class Physics2D;
class Collision;
class GUI;
class Toggle;

boost::json::object readJsonFile(string filename);