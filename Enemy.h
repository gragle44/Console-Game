#pragma once

#include "Utils.h"
#include "Map.h"
#include "Player.h"

#include <future>

class Enemy {
public:
	Enemy(const Vec2 startingPos, Map& map)
		: m_Position(startingPos), m_Health(4), m_Map(map), m_PlayerReached(false) {};

	void Move(const Player& player, std::mutex& mapMutex);

	Vec2 GetPos() const { return m_Position; }
	unsigned short GetHealth() const { return m_Health; }
private:
	bool m_PlayerReached;
	unsigned short m_Health;
	Map& m_Map;
	Vec2 m_Position;
	Vec2 PathToPlayer(const Player& player);
	void MoveTowardsPlayer(const Vec2& delta);
	bool ValidMove(const Vec2& delta, const Vec2& mapSize) const;
};