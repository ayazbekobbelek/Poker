#include <iostream>
#include "Poker_Game.h"

using namespace std;
int main() {
    PokerGame* game;
    game = new PokerGame;
    game->StartGame();
    delete[] game;


    return 0;
}
