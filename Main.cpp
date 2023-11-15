#include <iostream>
#include <vector>
#include <future>

#include "Utils.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

std::mutex mapMutex;

void run() {
    Map map(12, 12);
    map.PrintMap();

    Player player(0, 0, map);
    Enemy enemy({ 10, 10 }, map);

    auto future = std::async(std::launch::async, &Enemy::Move, &enemy, std::ref(player), std::ref(mapMutex));

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
            std::cout << "Invalid input!" << '\n';
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(mapMutex);
            player.MoveTowards({ deltaX, deltaY });
            map.PrintMap();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    run();
    return 0;
}
