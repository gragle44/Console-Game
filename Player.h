#pragma once

#include "Map.h"
#include "Utils.h"

class Player {
public:
    Player(int x, int y, Map& map)
        : m_Position({ x, y }), m_Map(map) {}

    int GetX() const { return m_Position.x; }
    int GetY() const { return m_Position.y; }
    Vec2 GetPos() const { return m_Position; }

    void MoveTowards(const Vec2& delta);

    void MoveTo(const Vec2& position);

private:
    Vec2 m_Position;

    Map& m_Map;

    bool ValidMove(const Vec2& delta, const Vec2& mapSize) const;

    void Move(const Vec2& delta);
};