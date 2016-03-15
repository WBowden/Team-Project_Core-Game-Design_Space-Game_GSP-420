#include "gameObjectManager.h"
#include "physicsObject.h"
#include "..\EngineDemo\Game.h"

#include <string>
#include <vector>


gameObjectManager::gameObjectManager()
{

}


gameObjectManager::~gameObjectManager()
{
}


// Add a game object that is not controlled by physics but reacts to collisions
int gameObjectManager::addBoxDynamicRigidBody(std::string theName,int x, int y, int halfW, int halfH, bool isActive, physicsObject* gameObjectLink)
{

	if (gameObjectLink == NULL) return -1; 

// 	gameObjectLink->shapeList = "Box";
// 	gameObjectLink->isActive     = isActive; 
// 	gameObjectLink->objectName   = theName; 
// 	gameObjectLink->x = x;
// 	gameObjectLink->y = y;
// 	gameObjectLink->isDynamic    = true;
// 	gameObjectLink->isStatic     = false;
// 	gameObjectLink->halfHeight = halfH;
// 	gameObjectLink->halfWidth =  halfW;

	//GAMECLASS->GetPhysics().initBody(gameObjectLink);
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;

	gameObjectLink->shapeList = "Box";
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = true;
	gameObjectLink->isStatic = false;
	gameObjectLink->halfHeight = halfH;
	gameObjectLink->halfWidth = halfW;

	// SAM: fixing Phys
	if (gameObjectLink->isDynamic)  {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_kinematicBody;
	}
	// but if static change 
	if (gameObjectLink->isStatic)  {
		bodyDef.type = b2_staticBody;
	}

	bodyDef.position.Set(P2M*gameObjectLink->x, P2M*gameObjectLink->y);

	b2Body* body = GAMECLASS->GetPhysics()->world->CreateBody(&bodyDef);

	body->SetUserData(gameObjectLink);

	if (gameObjectLink->shapeList == "Box") {
		dynamicBox.SetAsBox(P2M*gameObjectLink->halfHeight, P2M*gameObjectLink->halfWidth);
	}
	else {// we can assume polygon for now unless we add circles later.
		// count the vertices 
		int vertexCount = gameObjectLink->shape.size() / 2;
		//convert to an array. 
		float32* verticeArray = &gameObjectLink->shape[0];
		//create a vector of b2vec2
		std::vector<b2Vec2> vertices;
		//init it
		vertices.resize(vertexCount);
		//stuff it with the vertices
		for (int loopIndex = 0; loopIndex < vertexCount; loopIndex++)
			vertices[loopIndex].Set(verticeArray[loopIndex], verticeArray[loopIndex + 1]);

		// flatten to an array
		b2Vec2* b2vArray = &vertices[0];
		//Yep I know it says box but it is a type of polygonshape.
		dynamicBox.Set(b2vArray, vertexCount); //pass array to the shape
	}

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	fixtureDef.restitution = 0.949875f;

	// Override the default friction.
	fixtureDef.friction = 0.9800f;

	if ((gameObjectLink->collissionCategory != 0) && (gameObjectLink->collissionMask != 0)) {
		fixtureDef.filter.categoryBits = gameObjectLink->collissionCategory;
		fixtureDef.filter.maskBits = gameObjectLink->collissionMask;
	}
	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	gameObjectLink->body = body;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}


// Add a game object that is not controlled by physics but reacts to collisions
int gameObjectManager::addBoxNonDynamicRigidBody(std::string theName, int x, int y, int halfW, int halfH, bool isActive, physicsObject* gameObjectLink)
{
	
	if (gameObjectLink == NULL) return -1;
	gameObjectLink->shapeList = "Box";
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = false;
	gameObjectLink->isStatic = false;
	gameObjectLink->halfHeight = halfH;
	gameObjectLink->halfWidth = halfW;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}

// Add a game object that is not controlled by physics but reacts to collisions
int gameObjectManager::addBoxNonMovingRigidBody(std::string theName, int x, int y, int halfW, int halfH, bool isActive, physicsObject* gameObjectLink)
{
	if (gameObjectLink == NULL) return -1;
	
	gameObjectLink->shapeList = "Box";
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = false;
	gameObjectLink->isStatic  = true;
	gameObjectLink->halfHeight = halfH;
	gameObjectLink->halfWidth = halfW;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}

// Add a game object that is not controlled by physics but reacts to collisions
int gameObjectManager::addPolygonDynamicRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink)
{
	if (gameObjectLink == NULL) return -1;
    gameObjectLink->shapeList = "Polygon";
	gameObjectLink->shape = vertices;
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = true;
	gameObjectLink->isStatic = false;
	gameObjectLink->halfHeight = 0;
	gameObjectLink->halfWidth = 0;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}

int gameObjectManager::addPolygonNonDynamicRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink)
{
	if (gameObjectLink == NULL) return -1;
	gameObjectLink->shapeList = "Polygon";
	gameObjectLink->shape = vertices;
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = false;
	gameObjectLink->isStatic = false;
	gameObjectLink->halfHeight = 0;
	gameObjectLink->halfWidth = 0;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}


int gameObjectManager::addPolygonNonMovingRigidBody(std::string theName, int x, int y, std::vector<float32> vertices, bool isActive, physicsObject* gameObjectLink)
{
	if (gameObjectLink == NULL) return -1;
	gameObjectLink->shapeList = "Polygon";
	gameObjectLink->shape = vertices;
	gameObjectLink->isActive = isActive;
	gameObjectLink->objectName = theName;
	gameObjectLink->x = x;
	gameObjectLink->y = y;
	gameObjectLink->isDynamic = false;
	gameObjectLink->isStatic = true;
	gameObjectLink->halfHeight = 0;
	gameObjectLink->halfWidth = 0;

	gameManangerMap[theName] = gameObjectLink;

	return 0;
}


// finds and returns a the instance of the object by name
physicsObject* gameObjectManager::findByName(std::string name)
{
	return (physicsObject*) &gameManangerMap[name];
}


// finds and returns a the instance of the object by name
int gameObjectManager::removeByName(std::string name)
{
	
	gameManangerMap[name]->markedForDeath = true;
	return 0;
}

