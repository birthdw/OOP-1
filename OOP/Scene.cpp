#include "Scene.h"
#include "GameObject.h"
#include "PanelScript.h"
#include "RotateScript.h"
#include <algorithm>

Scene::Scene() {
}

Scene& Scene::getInstance() {
	static Scene instance;
	return instance;
}

void Scene::start() {
	auto mainPanel = GameObject::Instantiate("main", "panel", nullptr,
		Position{ 1, 1 }, "", Position{ 40, 30 });
	mainPanel->addComponent<PanelScript>();

	auto movingBlock = GameObject::Instantiate("block", "block", mainPanel,
		Position{ 4, 2 }, "\xdb \xdb \xdb\xdb", Position{ 2, 3 } );
	movingBlock->addComponent<RotateScript>();


	auto nextPanel = GameObject::Instantiate("next");
	auto staticBlock = GameObject::Instantiate("block", "block", nextPanel,
		Position{ 50, 2 }, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3 } );
	auto anotherBlock = GameObject::Instantiate("another", "block", nextPanel,
		Position{ 60, 2 }, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3 } );

	auto scorePanel = GameObject::Instantiate("score", "panel", nullptr);



	auto found = GameObject::Find("block");
	auto found2 = GameObject::Find("/next/block");
	auto found3 = GameObject::Find("/next/block/block");
	auto found4 = GameObject::Find("main");
	auto found5 = GameObject::Find("/main");
	auto found6 = GameObject::Find("/main/another");
	auto found7 = GameObject::Find("another");
	auto found8 = GameObject::Find("");
	
	GameObject::Remove(found7);

	auto found10 = GameObject::Find("/next/another");

	for (auto gameObject : gameObjects) gameObject->internalStart();
}

void Scene::add(GameObject* go) {
	if (go == nullptr) return;
	gameObjects.push_back(go);
}

void Scene::remove(GameObject* go) {
	if (go == nullptr) return;
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		auto obj = *it;
		if (obj == go) {
			it = gameObjects.erase(it);
			delete obj;
		}
		else			it++;
	}
}

void Scene::update() {
	for (auto gameObject : gameObjects) gameObject->internalUpdate();

	// erase remove idiom
	gameObjects.erase( remove_if(gameObjects.begin(), gameObjects.end(),
		[&](auto item) { if (item->isRequestingDestruction() == false) return false;
				GameObject::Remove(item);
				delete item;				
				return true;
		} ),
		gameObjects.cend());
}

void Scene::draw() {
	for (auto gameObject : gameObjects) gameObject->internalDraw();
}
