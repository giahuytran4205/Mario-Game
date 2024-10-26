#include "GameManager.hpp"
#include "ECS.hpp"
#include <iostream>

using namespace std;

EntitiesManager manager;

int main()
{
	GameManager gameManager;
	gameManager.start();

    return 0;
}