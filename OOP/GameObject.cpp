#include <iostream>

#include "GameObject.h"
#include "GameObjectManager.h"
#include "Screen.h"


GameObjectManager GameObject::gameObjectManager{ 1 };

GameObject** GameObject::getGameObjects() { return gameObjectManager.getGameObjects(); }
int GameObject::getMaxGameObjects() { return gameObjectManager.getCapacity(); }

GameObject::GameObject(Screen& screen, int pos, const char* shape)
	: screen(screen), pos(pos)
{
	setShape(shape);
	gameObjectManager.add(this);
}

GameObject::~GameObject() {} // ���� �Ҹ��� �Լ�

//getter ����
int GameObject::getPos() const { return pos; }
const char* GameObject::getShape() const { return shape; }
Screen& GameObject::getScreen() const { return screen; }


//setter ����
void GameObject::setPos(int pos) { this->pos = pos; }
void GameObject::setShape(const char* shape)
{
	int len = strlen(shape); // len >= 0
	if (len >= 100) {
		// 0 ... 98
		// 99���� �ι���
		strncpy(this->shape, shape, 100 - 1);
		this->shape[100 - 1] = '\0';
	}
	else
		strcpy(this->shape, shape);
}

bool GameObject::isInside() const
{
	return pos <= (screen.length() - strlen(shape)) && pos >= 0;
}

void GameObject::moveRight() { pos++; }

void GameObject::moveLeft() { pos--; }

void GameObject::process_input(int key) {}

void GameObject::update() {}

void GameObject::draw()
{
	if (isInside() == false) return;
	screen.draw(shape, pos);
}