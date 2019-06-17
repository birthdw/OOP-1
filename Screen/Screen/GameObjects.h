#pragma once

class GameObject;

class GameObjects
{
	int capacity;
	GameObject** objects;
	static GameObjects* instance;

public:
	static GameObjects& getInstance();
	GameObjects(int capacity);
	~GameObjects();

	int find(GameObject* obj);
	void add(GameObject* obj);
	void remove(GameObject* obj);
	void update();

	GameObject* getEnemy();
};
