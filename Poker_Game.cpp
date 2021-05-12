//
// Created by Belek Ayazbekov on 06.04.2021.
//

#include "Poker_Game.h"
#include <random>
#include "fstream"
PokerGame ::PokerGame()
{
    aiFold = false;
    playerFold = false;
    gameRound = 0;
    aiScore = -1;
    playerScore = -1;
    playerMove = "";
    player = new Player;
    playerName = player->SetPlayerName();
    ai = new Player;
    dealer = new Dealer;
    deck = new Deck;
    player->addToBalance(10000);
    ai->addToBalance(10000);
    file.open("data.txt", ios::out);
    if(!file)
    {
        cout << "Error creating file" << endl;
    }
}


void PokerGame::announceWinner()
{
    if (playerFold)
    {
        cout << playerName << " folded" << endl;
        file << playerName << " folded" << endl;
        player->reduceBalance(playerBets);
        ai->addToBalance(dealer->getPot());
        cout << endl;
        cout << "Your balance  at the end " << player->getBalance() << "$" << endl;
        cout << "Ai's balance  at the end " << ai->getBalance() << "$" << endl;
        file << endl;
        file << "Your balance at the end " << player->getBalance() << "$" << endl;
        file << "Ai's balance at the end " << ai->getBalance() << "$" << endl;
        restartGame();
    }
    if (aiFold)
    {
        cout << "Ai folded" << endl;
        cout << "You won this round, next game will start soon" << endl;
        file << "Ai folded" << endl;
        file << "You won this round, next game will start soon" << endl;
        ai->reduceBalance(aiBets);
        player->addToBalance(dealer->getPot());
        cout << endl;
        cout << "Your balance  at the end " << player->getBalance() << "$" << endl;
        cout << "Ai's balance  at the end " << ai->getBalance() << "$" << endl;
        file << endl;
        file << "Your balance at the end " << player->getBalance() << "$" << endl;
        file << "Ai's balance at the end " << ai->getBalance() << "$" << endl;
        restartGame();
    }
    if (playerScore > aiScore)
    {
        cout << "CONGRATULATIONS! YOU WON" << endl;
        cout << "One point for humanity" << endl;
        file << "CONGRATULATIONS! YOU WON" << endl;
        file << "One point for humanity" << endl;
        player->addToBalance(dealer->getPot());
        cout << endl;
        cout << "Your balance  at the end " << player->getBalance() << "$" << endl;
        cout << "Ai's balance  at the end " << ai->getBalance() << "$" << endl;
        file << endl;
        file << "Your balance at the end " << player->getBalance() << "$" << endl;
        file << "Ai's balance at the end " << ai->getBalance() << "$" << endl;
        gameRound++;
        restartGame();
    }
    else if (playerScore < aiScore)
    {
        cout << "YOU LOST! MAYBE YOU WILL HAVE ENOUGH LUCK NEXT TIME" << endl;
        cout << "One point for ai" << endl;
        file << "YOU LOST! MAYBE YOU WILL HAVE ENOUGH LUCK NEXT TIME" << endl;
        file << "One point for ai" << endl;
        ai->addToBalance(dealer->getPot());
        cout << endl;
        cout << "Your balance  at the end " << player->getBalance() << "$" << endl;
        cout << "Ai's balance  at the end " << ai->getBalance() << "$" << endl;
        file << endl;
        file << "Your balance at the end " << player->getBalance() << "$" << endl;
        file << "Ai's balance at the end " << ai->getBalance() << "$" << endl;
        gameRound++;
        restartGame();
    }
    else
    {
        cout << "WHAT A GAME!! IT IS A DRAW" << endl;
        file << "WHAT A GAME!! IT IS A DRAW" << endl;
        int money = dealer->getPot();
        player->addToBalance(money/2);
        ai->addToBalance(money/2);
        cout << endl;
        cout << "Your balance  at the end " << player->getBalance() << "$" << endl;
        cout << "Ai's balance  at the end " << ai->getBalance() << "$" << endl;
        file << endl;
        file << "Your balance at the end " << player->getBalance() << "$" << endl;
        file << "Ai's balance at the end " << ai->getBalance() << "$" << endl;
        gameRound++;
        restartGame();
    }
}

void PokerGame::bettingRound()
{
    try {
        aiBets = 0;
        playerBets = 0;
        while (true)  // repeats until player of ai decides to call
        {
            dealer->setLastBet(0);
            if (ai->getBalance() == 0)
            {
                cout << "Ai has just lost all of his money" << endl;
                cout << "CONGRATS! YOU WON THIS GAME" << endl;
                file << "Ai has just lost all of his money" << endl;
                file << "CONGRATS! YOU WON THIS GAME" << endl;
                break;
            }
            if (player->getBalance() == 0)
            {
                cout << "Looks like you do not have any money" << endl;
                cout << "Your luck was not enough to win this ai, YOU LOST!!!" << endl;
                file << "Looks like you do not have any money" << endl;
                file << "Your luck was not enough to win this ai, YOU LOST!!!" << endl;
                break;
            }
            if (!earlyFinish()) {
                int playerBet = stoi(playerMove);
                if (playerBet < 0) {
                    throw 1; // in case if player will make a negative bet
                }
                if (player->getBalance() < playerBet)
                {
                    throw 2; // if player wants to bet money that is greater than his balance
                }
                else {
                    if (playerBet == 0) {
                        dealer->addPot(dealer->getLastBet());
                        player->reduceBalance(dealer->getLastBet());
                        playerBets += dealer->getLastBet();
                        cout << "You called" << endl;
                        cout << "The pot is " << dealer->getPot() << endl;
                        file << "You called" << endl;
                        file << "The pot is " << dealer->getPot() << endl;
                        gameRound++;
                        break;
                    } else {
                        cout << "Player raised " << playerBet << "$" << endl;
                        file << "Player raised " << playerBet << "$" << endl;
                        player->reduceBalance(playerBet);
                        playerBets += playerBet;
                        playerBet += dealer->getLastBet();
                        dealer->setLastBet(playerBet);
                        dealer->addPot(playerBet);
                        cout << "The last bet is " << dealer->getLastBet() << "$" << endl;
                        file << "The last bet is " << dealer->getLastBet() << "$" << endl;
                        if (!aiCallorFold()) {
                            int aiBet = aiBetting();
                            if (aiBet > ai->getBalance())
                            {
                                throw 2;  // if ai decides to bet more money than it has
                            }
                            if (aiBet != 0) {
                                cout << "Ai raised " << aiBet << "$" << endl;
                                file << "Ai raised " << aiBet << "$" << endl;
                                ai->reduceBalance(aiBet);
                                aiBets += aiBet;
                                aiBet += dealer->getLastBet();
                                dealer->setLastBet(aiBet);
                                dealer->addPot(aiBet);
                                cout << "The pot is " << dealer->getPot() << "$" << endl;
                                cout << "the last bet is " << dealer->getLastBet() << "$" << endl;
                                file << "The pot is " << dealer->getPot() << "$" << endl;
                                file << "the last bet is " << dealer->getLastBet() << "$" << endl;
                            } else {
                                ai->reduceBalance(dealer->getLastBet());
                                dealer->addPot(dealer->getLastBet());
                                aiBets += dealer->getLastBet();
                                cout << "Ai called" << endl;
                                cout << "The pot is " << dealer->getPot() << "$" << endl;
                                file << "Ai called" << endl;
                                file << "The pot is " << dealer->getPot() << "$" << endl;
                                gameRound++;
                                break;
                            }
                        } else {
                            aiFold = true;
                            announceWinner();
                        }
                    }
                }
            } else {
                playerFold = true;
                announceWinner();
            }

        }
    }
    catch (int ex) // catching some errors
    {
        switch (ex) {
            case 1: cout << "PLEASE ENTER A POSITIVE NUMBER" << endl; break;
            case 2: cout << "Not enough money" << endl; break;
        }
    }
}



PokerGame:: ~PokerGame()
{
    gameRound = 0;
    aiScore = -1;
    playerScore = -1;
    playerMove = "";
    playerName = "";
    delete [] player;
    delete [] ai;
    delete[] dealer;
    delete [] deck;
    file.close();
}
void PokerGame::restartGame()
{
    // Creating this variable keep the player's and ai's balance the same as it was in the previous round
    int temp1 = player->getBalance();
    int temp2 = ai->getBalance();
    gameRound = 0;
    aiScore = -1;
    playerScore = -1;
    playerMove = "";
    player = new Player;
    player->addToBalance(temp1);
    ai = new Player;
    ai->addToBalance(temp2);
    dealer = new Dealer;
    deck = new Deck;
    StartGame();
}

bool PokerGame::earlyFinish()
{
    playerMove = "";
    cout << "In case you want to call type 0\n";
    cout << "In case you want to fold type 'fold' and the game will be restarted\n";
    cout << "In case you want to raise just type the amount of money you want to raise\n";
    cout << "In case you want to exit game type 'exit' and the game will stopped\n";
    cin >> playerMove;
    if (playerMove == "fold")
    {
        playerFold = true;
        announceWinner();
        return true;
    }
    else if(playerMove == "exit")
    {
        cout << "Your balance: " << player->getBalance() << endl;
        cout << "Goodbye" << endl;
        file << "Your balance: " << player->getBalance() << endl;
        file << "Goodbye" << endl;
        exit(42);
    }
    else {
        return false;
    }
}
// Ai settings
int PokerGame::getRandomNumber(int MIN, int MAX)
{
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);
    return distribution(eng);
}
bool PokerGame::aiCallorFold()
{
    if (gameRound == 3)
    {
        if (aiScore < playerScore)
        {
            int randomr = getRandomNumber(0, 10);
            // 40% chance that ai will fold
            return randomr < 3;
        }
        else
        {
            int randomr = getRandomNumber(0,10);
            // 70% chance that ai will call
            return randomr < 7;
        }
    }
    else
    {
        if (aiScore < playerScore)
        {
            int randomr = getRandomNumber(0,10);
            // 30% chance ai will bluff
            return randomr < 3;
        }
        else if (playerScore == aiScore && !playerScore == 0 && !aiScore == 0)
        {
            int randomr = getRandomNumber(0,10);
            // 50% chance ai will call on equal score
            return randomr < 5;
        }
        else
        {
            int randomr = getRandomNumber(0,7);
            // 80% chance that ai will call with better cards
            return randomr < 7;
        }
    }
}

int PokerGame::aiBetting()
{
    if (ai->getBalance() < player->getBalance()) {
        // ai has less money than the player, so it will be more careful
        if (playerScore > aiScore) {
            int randomnr = getRandomNumber(0, 10);
            // 30% chance that ai will bluff
            if (randomnr < 3) {
                // If ai bluffs, the amount will be low (his balance / 8);
                int bluff = getRandomNumber(0, ai->getBalance()/8);
                return bluff;
            } else return 0;
        } else if (playerScore == aiScore && !playerScore == 0 && !aiScore == 0) {
            int randomnr = getRandomNumber(0, 10);
            // 30% chance that ai will raise on equal score
            if (randomnr < 3) {
                // If score equals, the amount could be low or medium (his balance / 6);
                int equalscore = getRandomNumber(0, ai->getBalance()/6);
                return equalscore;
            } else return 0;
        } else {
            int randomnr = getRandomNumber(0, 10);
            // 50% chance that ai will raise with better cards
            if (randomnr < 5) {
                // If ai has better cards, the amount could be low, medium and high (his balance / 4);
                int highscore = getRandomNumber(0, ai->getBalance()/4);
                return highscore;
            } else return 0;
        }
    } else if (ai->getBalance() >= player->getBalance()) {
        // ai has more money than the player, so it will be more daring
        if (playerScore > aiScore) {
            int randomnr = getRandomNumber(0, 10);
            // 40% chance that ai will bluff
            if (randomnr < 4) {
                // If ai bluffs, the amount will be low (his balance / 8);
                int bluff = getRandomNumber(0, player->getBalance()/8);
                return bluff;
            } else return 0;
        } else if (playerScore == aiScore && !playerScore == 0 && !aiScore == 0) {
            int randomnr = getRandomNumber(0, 10);
            // 50% chance that ai will raise on equal score
            if (randomnr < 5) {
                // If score equals, the amount could be low or medium (his balance / 6);
                int equalscore = getRandomNumber(0, player->getBalance()/6);
                return equalscore;
            } else return 0;
        } else {
            int randomnr = getRandomNumber(0, 10);
            // 70% chance that ai will raise with better cards
            if (randomnr < 7) {
                // If ai has better cards, the amount could be low, medium and high (his balance / 4);
                int highscore = getRandomNumber(0, player->getBalance()/4);
                return highscore;
            } else return 0;
        }
    }
}


// Starting game
void PokerGame::StartGame() {
    int ask;
    while (true)
    {
        cout << "If you want to start a game type- 1 " << endl;
        cout << "If you want to analyze previous game type- 2" << endl;
        cin >> ask;
        if (ask == 1)
        {

            break;
        }
        else if(ask == 2)
        {
            for (int i = 0; i < 2; i++)
            {
                file.open("data.txt", ios::in);
                string str;
                while (getline(file, str))
                {
                    cout << str << endl;
                }
                file.close();
            }

        }
    }
    cout << "||                     WELCOME TO POKER                  ||" << endl;
    cout << endl;
    cout << "Your balance: " << player->getBalance() << endl;
    cout << endl;
    cout << "Ai's balance: " << ai->getBalance() << endl;
    file << "||                     WELCOME TO POKER                  ||" << endl;
    file << endl;
    file << "Your balance: " << player->getBalance() << endl;
    file << endl;
    file << "Ai's balance: " << ai->getBalance() << endl;
    deck->Shuffle(); // shuffling the deck
    // giving cards to player
    for (int i = 0; i < 2; i++) {
        card = deck->Give_Card();
        player->SetCardInHand(card);
    }
    // giving cards to ai
    for (int i = 0; i < 2; i++) {
        card = deck->Give_Card();
        ai->SetCardInHand(card);
    }
    // giving cards for table
    for (int i = 0; i < 5; i++) {
        card = deck->Give_Card();
        dealer->SetCardOnTable(card);
        player->SetEvaluationHand(card);
        ai->SetEvaluationHand(card);
    }
    player->SortEvaluationHand(); // setting evaluation hands(sorted hand consisting of 7 cards)
    ai->SortEvaluationHand();
    // hand strength
    player->ReportHandType();
    ai->ReportHandType();
    aiScore = ai->getHandStrength();
    playerScore = player->getHandStrength();
    // player's hand
    vector<string> cardInHand = player->ShowHand();
    file << "Player's hand:   \n" << cardInHand << endl;
    file << "Ai's hand  \n" << ai->ShowHand() << endl;
    cout << "Your hand: " << endl;
    cout << cardInHand << endl;
    // system messages during the game
    while (gameRound < 5) {
        switch (gameRound) {
            case 0: // pre-flop betting
            {
                cout << "||                     PRE-FLOP                  ||" << endl;
                cout << "Your bets for pre-flop round" << endl;
                file << "||                     PRE-FLOP                  ||" << endl;
                file << "Your bets for pre-flop round" << endl;
                bettingRound();
                break;
            }

            case 1: {
                cout << "||                     FLOP                  ||" << endl;
                file << "||                     FLOP                  ||" << endl;
                cout << "Cards on table:" << endl;
                file << "Cards on table:" << endl;
                vector <string> temp = dealer->DisplayCardForFirstRound();
                cout << temp << endl;
                file << temp << endl;
                cout << "Your hand: " << endl;
                cout << cardInHand << endl;
                cout << "Your bets for flop round" << endl;
                file << "Your bets for flop round" << endl;
                bettingRound();
                break;
            }

            case 2: {
                cout << "||                     Turn                  ||" << endl;
                file << "||                     Turn                  ||" << endl;
                cout << "Cards on table:" << endl;
                file << "Cards on table:" << endl;
                vector <string> temp = dealer->DisplayCardForSecondRound();
                cout << temp << endl;
                file << temp << endl;
                cout << "Your hand: " << endl;
                cout << cardInHand << endl;
                cout << "Your bets for Turn round" << endl;
                file << "Your bets for Turn round" << endl;
                bettingRound();
                break;
            }

            case 3: {
                cout << "||                     River                  ||" << endl;
                file << "||                     River                  ||" << endl;
                cout << "Cards on table:" << endl;
                file << "Cards on table:" << endl;
                vector <string> temp = dealer->DisplayCardForThirdRound();
                cout << temp << endl;
                file << temp << endl;
                cout << "Your hand: " << endl;
                cout << cardInHand << endl;
                cout << "Your bets for river round" << endl;
                file << "Your bets for river round" << endl;
                bettingRound();
                break;
            }

            case 4: {
                announceWinner();
            }
        }
    }
}
