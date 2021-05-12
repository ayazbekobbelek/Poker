//
// Created by Belek Ayazbekov on 04.04.2021.
//

#include "Player.h"


// DEALER CLASS

Dealer::Dealer()
{
    CardsOnTable = new Card[5];
    CardCount = 0;
    pot = 0;
    allCard = {};
    lastBet = 0;
}

Dealer :: ~Dealer()
{
    delete[] CardsOnTable;
    CardCount = 0;
    pot = 0;
    allCard = {};
    lastBet = 0;
}

void Dealer::setLastBet(int num)
{
    lastBet = num;
}
int Dealer::getPot() const {
    return pot;
}

void Dealer::addPot(int newPot) {
    pot += newPot;
}

void Dealer::SetCardOnTable(Card card)
{
    CardsOnTable[CardCount] = card;
    CardCount++;
}

vector<string> Dealer::DisplayCardForFirstRound(){
    allCard.resize(9); // resizing the vector so it can fit all the cards(giving more memory)
    // here we need only first 3 cards
    for(int k=0;k<3;++k) {
        for (int i = 0; i < 9; ++i) {
            allCard[i].append(CardsOnTable[k].getCliCard()[i]);
        }
    }
    return allCard;
}


vector<string> Dealer::DisplayCardForSecondRound()
{
    // we add 4th card to the previous 3
    for (int i = 0; i < 9; ++i) {
        allCard[i].append(CardsOnTable[3].getCliCard()[i]);
    }
    return  allCard;
}


vector<string> Dealer::DisplayCardForThirdRound()
{
    // add 5th card
    for (int i = 0; i < 9; ++i) {
        allCard[i].append(CardsOnTable[4].getCliCard()[i]);
    }
    return  allCard;
}


//------------------------------ PLAYER CLASS-----------------------------------


Player::Player()
{
    hand = new Card[2];
    EvaluationHand = new Card[7];
    handStrength = 0;
    name = "";
    CardCount = 0;
    bet = 0;
    balance = 0;
}

Player :: ~Player()
{
    delete[] hand;
    delete[] EvaluationHand;
    name = "";
    CardCount = 0;
    bet = 0;
}

string Player::SetPlayerName()
{
    cout << "Enter your name: ";
    cin >> name;
    return name;
}

void Player::SetCardInHand(Card card)
{
    hand[CardCount] = card;
    EvaluationHand[CardCount] = card;
    CardCount++;
}

void Player::addToBalance(int num)
{
    balance += num;
}

void Player::reduceBalance(int num)
{
    balance -= num;
}

vector<string> Player::ShowHand()
{
    handCard.resize(9);
    for(int k=0;k<2;++k) {
        for (int i = 0; i < 9; ++i) {
            handCard[i].append(hand[k].getCliCard()[i]);
        }
    }
    return handCard;
}



void Player::SetEvaluationHand(const Card& card)
{
    EvaluationHand[CardCount] = card;
    CardCount++;
}
// sorting from highest card to the lowest
void Player::SortEvaluationHand()
{
    for (int j = 0; j < 6; j++)
    {
        int high_card = j;
        for (int i = j+1; i < 7; i++)
        {
            if (EvaluationHand[i].GetValue() > EvaluationHand[high_card].GetValue())
            {
                high_card = i;
            }
        }
        Card temp = EvaluationHand[j];
        EvaluationHand[j] = EvaluationHand[high_card];
        EvaluationHand [high_card] = temp;
    }
}

int Player::ReportHighCard()
{
    return EvaluationHand[0].GetValue();
}

bool Player::IsOnePair() // checking evaluation hand for pairs
{
    if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() ||
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::IsTwoPair()
{
    if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Player::IsThreeOfAKind()
{
    if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }

    else
    {
        return false;
    }

}

bool Player::IsStraight() // if the values of the cards are in order(2-10, J,Q,K,A)
{
    int count_cards = 0;
    bool straight;

    for (int i = 0; i < 6; i++)
    {
        if (EvaluationHand[i].GetValue() - 1 == EvaluationHand[i+1].GetValue())
        {
            count_cards++;
        }
    }
    if (count_cards == 5) // need only 5 cards
    {
        straight = true;
    }
    else
    {
        straight = false;
    }
    return straight;
}

bool Player::IsFlush() // 5 out of 7 cards has same suit
{
    int count_cards = 0;
    bool flush;

    for (int i = 0; i < 6; i++)
    {
        if (EvaluationHand[i].GetSuit() == EvaluationHand[i+1].GetSuit())
        {
            count_cards++;
        }
    }
    if(count_cards == 5)
    {
        flush = true;
    }
    else
    {
        flush = false;
    }
    return flush;
}

bool Player::IsFullHouse()  //  pair + three of kind
{
    // cases when highest card form a three of a kind and the smaller ones form a pair
    if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() &&
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() &&
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() &&
            EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() &&
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() &&
            EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() &&
            EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }

    // cases when the highest cards form the pair and a smaller ones form a three of a kind

    else if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() &&
             EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() &&
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() &&
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() &&
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() &&
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() &&
            EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Player::IsFourOfAKind()  // four cards with same value
{
    if (EvaluationHand[0].GetValue() == EvaluationHand[1].GetValue() && EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue()  && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() ||
            EvaluationHand[1].GetValue() == EvaluationHand[2].GetValue() && EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() ||
            EvaluationHand[2].GetValue() == EvaluationHand[3].GetValue() && EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() ||
            EvaluationHand[3].GetValue() == EvaluationHand[4].GetValue() && EvaluationHand[4].GetValue() == EvaluationHand[5].GetValue() && EvaluationHand[5].GetValue() == EvaluationHand[6].GetValue())
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Player::IsStraightFlush()  // straight and flush
{
    int count_cards = 0;
    bool straightFlush;
    for (int i = 0; i < 6; i++)
    {
        if (EvaluationHand[i].GetSuit() == EvaluationHand[i+1].GetSuit() &&
            EvaluationHand[i].GetValue() - 1 == EvaluationHand[i+1].GetValue())
        {
            count_cards++;
        }
    }
    if(count_cards == 5)
    {
        straightFlush = true;
    }
    else
    {
        straightFlush = false;
    }
    return straightFlush;
}

bool Player::IsRoyalFlush() // straight flush of highest cards
{
    int count_cards = 0;
    bool royalFlush;
    for (int i = 0; i < 6; i++)
    {
        if (EvaluationHand[i].GetSuit() == EvaluationHand[i+1].GetSuit() &&
            EvaluationHand[i].GetValue() - 1 == EvaluationHand[i+1].GetValue())
        {
            count_cards++;
        }
    }
    if(count_cards == 5 && EvaluationHand[0].GetValue() == 14)
    {
        royalFlush = true;
    }
    else
    {
        royalFlush = false;
    }
    return royalFlush;
}

HandType Player::ReportHandType()
{
    if (IsRoyalFlush())
    {
        handStrength =9;
        return RoyalFlush;
    }
    else if (IsStraightFlush())
    {
        handStrength =8;
        return StraightFlush;
    }
    else if (IsFourOfAKind())
    {
        handStrength =7;
        return FourOfAKind;
    }
    else if (IsFullHouse())
    {
        handStrength =6;
        return FullHouse;
    }
    else if (IsFlush())
    {
        handStrength =5;
        return Flush;
    }
    else if (IsStraight())
    {
        handStrength =4;
        return Straight;
    }
    else if (IsThreeOfAKind())
    {
        handStrength =3;
        return ThreeOfAKind;
    }
    else if(IsTwoPair())
    {
        handStrength = 2;
        return TwoPair;
    }
    else if (IsOnePair())
    {
        handStrength = 1;
        return OnePair;
    }
    else
    {
        handStrength = 0;
        return HighHand;
    }
}

int Player::getHandStrength() const {
    return handStrength;
}
