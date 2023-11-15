#include "Player.h"

    void Player::MoveTowards(const Vec2& delta) {
        Move(delta);
    }

    void Player::MoveTo(const Vec2& position) {
        m_Position.x = position.x;
        m_Position.y = position.y;
    }

    bool Player::ValidMove(const Vec2& delta, const Vec2& mapSize) const {
        int newX = m_Position.x + delta.x;
        int newY = m_Position.y + delta.y;
        return newX >= 0 && newX < mapSize.x && newY >= 0 && newY < mapSize.y;
    }

    void Player::Move(const Vec2& delta) {
        if (!ValidMove(delta, { m_Map.GetLength(), m_Map.GetHeight() }))
            return;

        int oldX = m_Position.x;
        int oldY = m_Position.y;

        m_Position.x += delta.x;
        m_Position.y += delta.y;

        char targetCell = m_Map.GetCell(m_Position.x, m_Position.y);
        if (targetCell == Constants::TELEPORTER_CHAR) {
            MoveTo({ 2, 2 });
        }

        m_Map.SetCell(oldX, oldY, Constants::BACKGROUND_CHAR);
        m_Map.SetCell(m_Position.x, m_Position.y, Constants::PLAYER_CHAR);
    }