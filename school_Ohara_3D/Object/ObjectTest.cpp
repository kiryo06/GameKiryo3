#include "ObjectTest.h"
#include "game.h"
#include "DxLib.h"

namespace
{
}

ObjectTest::ObjectTest() :
	m_hGraph(-1),
	m_pos()
{
}
ObjectTest::~ObjectTest()
{

}

void ObjectTest::init()
{
}

void ObjectTest::end()
{

}

void ObjectTest::update()
{
}

void ObjectTest::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_hGraph, false);
}
