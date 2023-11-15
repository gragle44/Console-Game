#include "Map.h"
#include <iostream>

Map::Map(int length, int height)
    : m_Length(length), m_Height(height), 
    m_Map(length * height, Constants::BACKGROUND_CHAR)
{
    SetDefaultCells();
}

void Map::PrintMap() const {
        system("cls");
        PrintHorizontalBorder();

        for (int y = 0; y < m_Height; ++y) {
            std::cout << '#' << ' ';
            for (int x = 0; x < m_Length; ++x) {
                std::cout << GetCell(x, y) << ' ';
            }
            std::cout << '#' << '\n';
        }

        PrintHorizontalBorder();
    }

char Map::GetCell(unsigned int x, unsigned int y) const {
    return m_Map[y * m_Length + x];
}

void Map::SetCell(unsigned int x, unsigned int y, char value) {
    m_Map[y * m_Length + x] = value;
}

void Map::SetDefaultCells() {
    SetCell(0, 0, Constants::PLAYER_CHAR);
    SetCell(m_Length / 2, m_Height / 2, Constants::TELEPORTER_CHAR);
}

void Map::PrintHorizontalBorder() const {
    for (int i = 0; i < m_Length + 2; ++i) {
        std::cout << '#' << ' ';
    }
    std::cout << '\n';
}