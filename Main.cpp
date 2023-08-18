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

private:
    unsigned int m_X;
    unsigned int m_Y;
};

class Map {
public:
    Map(unsigned int length, unsigned int height)
        : m_Length(length), m_Height(height), m_Map(length* height, m_Background), m_Player(0,0) {
        SetCell(m_Player.GetX(), m_Player.GetY(), m_PlayerCharacter);
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
        if (ValidMove(deltaX, deltaY)) {
            SetCell(m_Player.GetX(), m_Player.GetY(), m_Background);
            m_Player.Move(deltaX, deltaY);
            SetCell(m_Player.GetX(), m_Player.GetY(), m_PlayerCharacter);
        }
    }

    char GetCell(unsigned int x, unsigned int y) const {
        return m_Map[y * m_Length + x];
    }

    void SetCell(unsigned int x, unsigned int y, char value) {
        m_Map[y * m_Length + x] = value;
    }

private:
    const char m_Background = '-';
    const char m_PlayerCharacter = 'T';
    unsigned int m_Length;
    unsigned int m_Height;
    std::vector<char> m_Map;
    Player m_Player;

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
    Map map(10, 10);
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
