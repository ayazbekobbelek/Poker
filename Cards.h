//
// Created by Belek Ayazbekov on 29.03.2021.
//  This header file contains the definitions of the cards and deck of cards
#ifndef POKER_CARDS_H
#define POKER_CARDS_H
#include <iostream>
#include "string"
#include <ctime>
#include "vector"
using namespace std;

enum Suit {clubs, diamonds , hearts, spades, joker};
class Card  // defines properties of one card
{
    int value = 0; //the value of the card
    Suit suit; // its suit
    vector<string> playingCard;  // Vector that contains every line of the cli card
    // values needed for cli image of the card
    string stringValue;
    string stringSuit;
    string stringValueAndSuit;
public:
    Card();
    ~Card();

    // displays the card
    vector<string> getCliCard();

    // Get the value of the card
    int GetValue() const;

    // Set the values of the card

    void SetValue(int);

    // Get the suit of the card

    Suit GetSuit() const;

    // Set the suit of the card

    void SetSuit(Suit card_suit);

};

class Deck
{
    Card* deck;  //there are 52 cards in one deck
    int first_card;   // index of the first card in the deck
public:
    Deck();
    ~Deck();
    // Shuffle the deck
    void Shuffle();
    // display all cards in the deck
    void Display_Deck();

    // return the index of the first card
    int Return_First_Card() const;
    // give a card to player
    Card Give_Card();


};
// Overload << to print the card
ostream & operator<<( ostream & os, vector<string> const &l);
#endif //POKER_CARDS_H
