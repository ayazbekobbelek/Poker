//
// Created by Belek Ayazbekov on 06.04.2021.
//

#ifndef POKER_POKER_GAME_H
#define POKER_POKER_GAME_H
#include "Player.h"
#include "fstream"
class PokerGame
{   //Creating variables that are needed to start a game:
    Player* player;
    Player* ai;
    Card card;
    Deck* deck;
    Dealer* dealer;
    // variables that are needed for game logic
    // aiScore and playerScore are keeping the hand strength, that is needed to announce a winner
    // gameRound: pre-flop, flop, turn, river
    int aiScore, playerScore, gameRound;
    // playerMove - what player wants to do
    string playerMove;
    // player's name
    string playerName;
    // how much ai bet per game
    int aiBets;
    // how much player bet per game
    int playerBets;
    //to know if player of ai folded, needed to announce winner, initially false
    bool playerFold;
    bool aiFold;
    // file management
    fstream file;


public:
    // COnstructor and destructor
    PokerGame();

    ~PokerGame();

    // system messages needed to announce winner and loser, also responsible for giving pot money
    void announceWinner();

    // Logic of betting
    void bettingRound();
    //Start a game
    void StartGame();

    // in case if the player decides to fold or exit
    bool earlyFinish();

    // ai settings
    bool aiCallorFold();

    int aiBetting();

    int getRandomNumber(int MIN, int MAX);

    // function for restarting the game
    void restartGame();

};
#endif //POKER_POKER_GAME_H
