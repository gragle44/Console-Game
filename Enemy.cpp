#include "Enemy.h"

#include <future>
#include <chrono>
#include <experimental/coroutine>

void Enemy::Move(const Player& player, std::mutex& mapMutex)
{
    while (m_Health > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            Vec2 movement = PathToPlayer(player);
            std::lock_guard<std::mutex> lock(mapMutex);
            MoveTowardsPlayer(movement);
            m_Map.PrintMap();
        }
    }

}

Vec2 Enemy::PathToPlayer(const Player& player)
{
	Vec2 playerPos = player.GetPos();
	Vec2 delta = { playerPos.x - m_Position.x, playerPos.y - m_Position.y };

	int absX = abs(delta.x)-1;
	int absY = abs(delta.y)-1;

    if (absX >= absY) {
        delta = { (delta.x > 0) ? 1 : ((delta.x < 0) ? -1 : 0), 0 };
    }
    else {
        delta = { 0, (delta.y > 0) ? 1 : ((delta.y < 0) ? -1 : 0) };
    }

    return delta;
}

void Enemy::MoveTowardsPlayer(const Vec2& delta) {
    if (abs(delta.x) == 0 && abs(delta.y) == 0)
        return;

    if (!ValidMove(delta, { m_Map.GetLength(), m_Map.GetHeight() }))
        return;

    int oldX = m_Position.x;
    int oldY = m_Position.y;

    m_Position.x += delta.x;
    m_Position.y += delta.y;

    char targetCell = m_Map.GetCell(m_Position.x, m_Position.y);
    if (targetCell == Constants::TELEPORTER_CHAR) {
        m_Position = { 2, 2 };
    }
    else if (targetCell == Constants::PLAYER_CHAR) {
        m_Position = { oldX, oldY };
    }

    m_Map.SetCell(oldX, oldY, Constants::BACKGROUND_CHAR);
    m_Map.SetCell(m_Position.x, m_Position.y, Constants::ENEMY_CHAR);
}

bool Enemy::ValidMove(const Vec2& delta, const Vec2& mapSize) const
{
    int newX = m_Position.x + delta.x;
    int newY = m_Position.y + delta.y;
    return newX >= 0 && newX < mapSize.x && newY >= 0 && newY < mapSize.y;
}
