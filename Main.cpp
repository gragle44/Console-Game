#include <iostream>
#include <vector>

class Player {
public:
    Player(unsigned int x, unsigned int y) 
        : m_X(x), m_Y(y) {}

    unsigned int GetX() const { return m_X; }
    unsigned int GetY() const { return m_Y; }

    void Move(int deltaX, int deltaY) {
        m_X += deltaX;
        m_Y += deltaY;
    }

    void MoveTo(int X, int Y) {
        m_X = X;
        m_Y = Y;
    }

private:
    unsigned int m_X;
    unsigned int m_Y;
};

class Map {
public:
    Map(unsigned int length, unsigned int height)
        : m_Length(length), m_Height(height), m_Map(length* height, m_Background), m_Player(0,0) {
        SetDefaultCells();
    }

    void PrintMap() const {
        system("cls");
        PrintHorizontalBorder();

        for (int y = 0; y < m_Height; ++y) {
            std::cout << '#' << ' ';
            for (int x = 0; x < m_Length; ++x) {
                std::cout << GetCell(x, y) << ' ';
            }
            std::cout << '#' << std::endl;
        }

        PrintHorizontalBorder();
    }

    void MovePlayer(int deltaX, int deltaY) {
        if (!ValidMove(deltaX, deltaY))
            return;

        unsigned int playerX = m_Player.GetX();
        unsigned int playerY = m_Player.GetY();
        unsigned int newPlayerX = playerX + deltaX;
        unsigned int newPlayerY = playerY + deltaY;

        char targetCell = GetCell(newPlayerX, newPlayerY);
        if (targetCell == m_Teleporter) {
            m_Player.MoveTo(2, 2);
        }
        else {
            m_Player.Move(deltaX, deltaY);
        }

        SetCell(playerX, playerY, m_Background);
        SetCell(m_Player.GetX(), m_Player.GetY(), m_PlayerCharacter);
    }

    char GetCell(unsigned int x, unsigned int y) const {
        return m_Map[y * m_Length + x];
    }

    void SetCell(unsigned int x, unsigned int y, char value) {
        m_Map[y * m_Length + x] = value;
    }

private:
    const char m_Teleporter = '0';
    const char m_Background = '-';
    const char m_PlayerCharacter = 'T';
    unsigned int m_Length;
    unsigned int m_Height;
    std::vector<char> m_Map;
    Player m_Player;

    void SetDefaultCells() {
        SetCell(m_Player.GetX(), m_Player.GetY(), m_PlayerCharacter);
        SetCell(m_Length / 2, m_Height / 2, m_Teleporter);
    }

    bool ValidMove(int deltaX, int deltaY) const {
        int newX = m_Player.GetX() + deltaX;
        int newY = m_Player.GetY() + deltaY;
        return newX >= 0 && newX < m_Length && newY >= 0 && newY < m_Height;
    }

    void PrintHorizontalBorder() const {
        for (int i = 0; i < m_Length + 2; ++i) {
            std::cout << '#' << ' ';
        }
        std::cout << std::endl;
    }
};

void run() {
    Map map(9, 9);
    map.PrintMap();

    char userInput;
    while (true) {
        std::cout << "Enter a direction (w/a/s/d) to move or 'q' to quit: ";
        userInput = std::cin.get();

        int deltaX = 0, deltaY = 0;
        if (userInput == 'q') {
            break;
        }

        if (userInput == 'w') {
            deltaY = -1;
        }
        else if (userInput == 'a') {
            deltaX = -1;
        }
        else if (userInput == 's') {
            deltaY = 1;
        }
        else if (userInput == 'd') {
            deltaX = 1;
        }
        else {
            std::cout << "Invalid input!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        map.MovePlayer(deltaX, deltaY);
        map.PrintMap();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    run();
    return 0;
}
