#pragma once
#include <string>
#include "physicsObject.h"
#include <map>
#include <vector>

class gameObjectManager
{
public:

	std::map<std::string, physicsObject*> gameManangerMap;
	gameObjectManager();
	~gameObjectManager();
	
	// Add a game object that is not controlled by physics but reacts to collisions
	int addBoxDynamicRigidBody(std::string theName, int x, int y, int halfH, int halfWidth, bool isActive, physicsObject* gameObjectLink);
	int addBoxNonDynamicRigidBody(std::string theName, int x, int y, int halfW, int halfH, bool isActive, physicsObject* gameObjectLink);
	int addBoxNonMovingRigidBody(std::string theName, int x, int y, int halfW, int halfH, bool isActive, physicsObject* gameObjectLink);
	
	int addPolygonDynamicRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink);
	int addPolygonNonDynamicRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink);
	int addPolygonNonMovingRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink);

	// finds and returns a the instance of the object by name
	physicsObject* findByName(std::string name);
	int removeByName(std::string name);

};

