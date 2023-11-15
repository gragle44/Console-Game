#pragma once

#include <Vector>
#include "Utils.h"

class Map {
public:
    Map(int length, int height);

    void PrintMap() const;

    char GetCell(unsigned int x, unsigned int y) const;

    void SetCell(unsigned int x, unsigned int y, char value);

    int GetLength() { return m_Length; }
    int GetHeight() { return m_Height; }

private:
    int m_Length;
    int m_Height;
    std::vector<char> m_Map;

    void SetDefaultCells();

    void PrintHorizontalBorder() const;
};