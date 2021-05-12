
//
// Created by Belek Ayazbekov on 04.04.2021.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H
#include "Cards.h"
#include "list"

enum HandType{
    HighHand, OnePair, TwoPair, ThreeOfAKind, Straight, Flush,
    FullHouse, FourOfAKind, StraightFlush, RoyalFlush
};
// Dealer class contains five cards on the table
class Dealer: public Card
{
    Card* CardsOnTable;
    int pot;   // the amount of money that players bet
    vector<string> allCard;
    int lastBet;
public:
    int CardCount;  // counter for cards

    // constructor and destructor
    Dealer();

    ~Dealer();

    // last bet is needed fo call, because when player calls it means he bets the same amount as last bet
    void setLastBet(int num);

    int getLastBet() const{return lastBet;}

    // set 5 cards on table
    void SetCardOnTable(Card card);

    // getCliCard cards for flop(3 cards)
    vector<string> DisplayCardForFirstRound();

    // display card for Turn (4th card)
    vector<string> DisplayCardForSecondRound();

    // getCliCard card for River(5th card)
    vector<string> DisplayCardForThirdRound();

    int getPot() const;

    // adds money to the pot
    void addPot(int newPot);
};

// Player class contains cards that the player have, and evaluates them
class Player : public Dealer
{
    string name;  // name of the player
    int balance;  // balance of the player, each player has 10000$ on his balance
    Card* hand;      // hand of the player contains 2 cards
    Card* EvaluationHand;  // Evaluation hand it is the hand that will be evaluated to find out
                                // what combination of card player has
                                // evaluation hand represents the 5 cards on the table + 2 cards in player's hand
    int handStrength;    // value(from 1 to 9) which represents the strength of the player's hand

    int bet = 0;
    vector<string> handCard;
public:
    Player();

    ~Player();

    // geeting balance
    int getBalance() const{return balance;}

    // adding to balance
    void addToBalance(int num);

    // reducing balance for gicen number
    void reduceBalance(int num);

    // getting hand strength
    int getHandStrength() const;


    // Displaying the cards that the player has
    vector<string> ShowHand();


    // Reporting the highest card Player has, used in case Player does not have any combinations
    int ReportHighCard();

    // Asking Player his name
    string SetPlayerName();

    // Adding the cards on table to the cards in Player's hand
    void SetEvaluationHand(const Card& card);

    // To make it easier to find the combinations we sort the evaluation hand
    // From highest cards to the lowest
    void SortEvaluationHand();

    // Giving the cards to the Player
    void SetCardInHand(Card card);

    // Finding the combinations
    bool IsOnePair();

    bool IsTwoPair();

    bool IsThreeOfAKind();

    bool IsStraight();

    bool IsFlush();

    bool IsFullHouse();

    bool IsFourOfAKind();

    bool IsStraightFlush();

    bool IsRoyalFlush();
    // Reporting what combination of cards Player has
    HandType ReportHandType();

};
#endif //POKER_PLAYER_H
