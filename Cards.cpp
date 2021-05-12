//
// Created by Belek Ayazbekov on 29.03.2021.
//

#include "Cards.h"
Card :: Card()
{
    value = 0;
    suit = joker;
}

Card :: ~Card()
{
    value = 0;
    suit = joker;
}

vector<string> Card::getCliCard()
{
    // getCliCard value of the card
    playingCard = {};
    // applying value and suit for card
    if (value >=2 && value <= 10)
    {
        stringValue = to_string(value);
    }
    switch (value) {
        case 11: stringValue =  "J"; break;
        case 12: stringValue = "Q"; break;
        case 13: stringValue =  "K"; break;
        case 14: stringValue =  "A"; break;
    }
    //'♠', '♦', '♥', '♣'
    //getCliCard the suit of the card
    switch (suit) {
        case diamonds: stringSuit = "♦"; break;
        case clubs: stringSuit = "♣"; break;
        case hearts: stringSuit = "♥"; break;
        case spades: stringSuit ="♠"; break;
        case joker:
            break;
    }
    // there is template of the cli image card, the letter are replaced by cards' symbols during the game
    stringValueAndSuit = stringValue.append(stringSuit);
    string a = "│sn        │";
    if (value != 10) a.replace(3,3,stringValueAndSuit);
    else a.replace(3,4,stringValueAndSuit);
    playingCard.push_back((string) "┌─────────┐");
    playingCard.push_back((string) a);
    playingCard.push_back((string) "│         │");
    playingCard.push_back((string) "│         │");
    string b = "│    s    │";
    b.replace(7,1,stringSuit);
    playingCard.push_back((string) b);
    playingCard.push_back((string) "│         │");
    playingCard.push_back((string) "│         │");
    string c = "│      sn  │";
    if (value != 10) c.replace(9,3,stringValueAndSuit);
    else c.replace(9,4,stringValueAndSuit);
    playingCard.push_back((string) c);
    playingCard.push_back((string) "└─────────┘");
    return playingCard;
}

// Get the value of the card
int Card::GetValue() const {return value;}

// Set the values of the card

void Card::SetValue(int set_value)
{
    if (set_value >= 2 && set_value <= 14)
    {
        value = set_value;
    }
}

// Get the suit of the card

Suit Card::GetSuit() const {return suit;}

// Set the suit of the card

void Card::SetSuit(Suit card_suit) {
    if (card_suit == diamonds || card_suit == spades || card_suit == hearts || card_suit == clubs)
    {
        suit = card_suit;
    }
}


Deck::Deck()
{
    // aplying value and suit for all 52 cards
    deck = new Card[52];
    first_card = 0;
    for (int i = 0; i < 52; i++)
    {
        deck[i].SetValue((int)((i % 13) + 2));  // there are 13 cards of each suit, and the value of the numeric cards starts from 2
        //setting the suit for cards
        switch (i / 13)
        {
            case 0: deck[i].SetSuit(diamonds); break;
            case 1: deck[i].SetSuit(hearts); break;
            case 2: deck[i].SetSuit(clubs); break;
            case 3: deck[i].SetSuit(spades); break;
        }
    }
}

Deck::~Deck()
{
    delete[] deck;
    first_card = 0;
}
// Shuffle the deck
void Deck::Shuffle()
{
    srand(time(0));
    for (int i = 0; i < 52; i++)
    {
        int index = rand() % 52;
        Card temp = deck [i];
        deck[i] = deck[index];
        deck[index] = temp;
    }
    first_card = 0;
}
// display all cards in the deck(nedded for checking)
void Deck::Display_Deck()
{
    for (int i = 0; i < 52; i++)
    {
        deck[i].getCliCard();
    }
    cout << endl;
}
int Deck::Return_First_Card() const
{
    return first_card;
}

Card Deck::Give_Card()
{
    return deck[first_card++];
}



// operator overloading for << needed to cout the image of the card
ostream & operator<<( ostream & os, vector<string> const &l)
{
    for (auto i = cbegin(l); i != cend(l); ++i)
    {
        os <<  *i << endl;
    }
    return os;
}
