// John Bryson
// Dr. Zhao
// CS 3013

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// create a card class
class Card {
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
    
    // constructor
    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    
    // return the value of a card, 1 - 11
    int GetValue() const;
    
    // flip a card; if face up, becomes face down and vice versa
    void Flip();

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

// constructor
Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

// return the value of a card, 1 - 11
int Card::GetValue() const {
    int value = 0;
    if (m_IsFaceUp) {
        value = m_Rank;
        if (value > 10) {
            value = 10;
        }
    }
    return value;
}

// flip a card; if face up, becomes face down and vice versa
void Card::Flip() {
    m_IsFaceUp = !(m_IsFaceUp);
}

// create a hand of cards
class Hand {
public:
    Hand();
    
    virtual ~Hand();
    
    // add a card to the hand
    void Add(Card* pCard);
    
    // clear hand of all cards
    void Clear();
    
    // get hand total value, intelligently treats aces as 1 or 11
    int GetTotal() const;

protected:
    vector<Card*> m_Cards;
};

// constructor
Hand::Hand() {
    m_Cards.reserve(7);
}

// destructor
Hand::~Hand() {
    Clear();
}

// add a card to the hand
void Hand::Add(Card* pCard) {
    m_Cards.push_back(pCard);
}

// clear hand of all cards
void Hand::Clear() {
    // iterate through vector, freeing all memory on the heap
    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        delete *iter;
        *iter = 0;
    }
    
    // clear vector of pointers
    m_Cards.clear();
}

// get hand total value, intelligently treats aces as 1 or 11
int Hand::GetTotal() const {
    // if no cards in hand, return 0
    if (m_Cards.empty()) {
        return 0;
    }
    
    // if a first card has value of 0, then card is face down; return 0
    if (m_Cards[0]->GetValue() == 0) {
        return 0;
    }
    
    // add up card values, treat each ace as 1
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        total += (*iter)->GetValue();
    }
    
    // determine if hand contains an ace
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        if ((*iter)->GetValue() == Card::ACE) {
            containsAce = true;
        }
    }
    
    // if hand contains ace and total is low enough, treat ace as 11
    if (containsAce && total <= 11) {
        // add only 10 since we've already added 1 for the ace
        total += 10;
    }
    
    return total;
}

// create a generic player class
class GenericPlayer : public Hand {
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const string& name = "");
    
    virtual ~GenericPlayer();
    
    // indicate whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;
    
    // return whether generic player has busted - has a total greater than 21
    bool IsBusted() const;
    
    // announce that the generic player busts
    void Bust() const;

protected:
    string m_Name;
};

// constructor
GenericPlayer::GenericPlayer(const string& name) : m_Name(name) {}

// destructor
GenericPlayer::~GenericPlayer() {}

// return whether generic player has busted - has a total greater than 21
bool GenericPlayer::IsBusted() const {
    return (GetTotal() > 21);
}

// announce that the generic player busts
void GenericPlayer::Bust() const {
    cout << m_Name << " busts.\n";
}

// create a player class
class Player : public GenericPlayer {
public:
    Player(const string& name = "");
    
    virtual ~Player();
    
    // return whether or not the player wants another hit
    virtual bool IsHitting() const;
    
    // announce that the player wins
    void Win() const;
    
    // announce that the player loses
    void Lose() const;
    
    // announce that the player pushes
    void Push() const;
};

// constructor
Player::Player(const string& name) : GenericPlayer(name) {}

// destructor
Player::~Player() {}

// return whether or not the player wants another hit
bool Player::IsHitting() const {
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

// announce that the player wins
void Player::Win() const {
    cout << m_Name << " wins.\n";
}

// announce that the player loses
void Player::Lose() const {
    cout << m_Name << " loses.\n";
}

// announce that the player pushes
void Player::Push() const {
    cout << m_Name << " pushes.\n";
}

// create a house class
class House : public GenericPlayer {

public:
    House(const string& name = "House");
    
    virtual ~House();
    
    // indicate whether or not house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;
    
    // flips over first card
    void FlipFirstCard();
};  

// constructor
House::House(const string& name) : GenericPlayer(name) {}

// destructor
House::~House() {}

// indicate whether or not house is hitting - will always hit on 16 or less
bool House::IsHitting() const {
    return (GetTotal() <= 16);
}

// flips over first card
void House::FlipFirstCard() {
    if (!(m_Cards.empty())) {
        m_Cards[0]->Flip();
    }
    else {
        cout << "No card to flip!\n";
    }
}

// create a deck of cards
class Deck : public Hand {
public:
    Deck();
    
    virtual ~Deck();
    
    // create a standard deck of 52 cards
    void Populate();
    
    // shuffle cards
    void Shuffle();
    
    // deal one card to a hand
    void Deal(Hand& aHand);
    
    // give additional cards to a generic player
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

// constructor
Deck::Deck() {
    m_Cards.reserve(52);
    Populate();
}

// destructor
Deck::~Deck() {}

// create a standard deck of 52 cards
void Deck::Populate() {
    Clear();
    // create standard deck
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
        for (int r = Card::ACE; r <= Card::KING; ++r) {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

// shuffle cards
void Deck::Shuffle() {
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

// deal one card to a hand
void Deck::Deal(Hand& aHand) {
    if (!m_Cards.empty()) {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else {
        cout << "Out of cards. Unable to deal.";
    }
}

// give additional cards to a generic player
void Deck::AdditionalCards(GenericPlayer& aGenericPlayer) {
    cout << endl;
    // continue to deal a card as long as generic player isn't busted and
    // wants another hit
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;
        
        if (aGenericPlayer.IsBusted()) {
            aGenericPlayer.Bust();
        }
    }
}

// create a game class
class Game {
public:
    Game(const vector<string>& names);
    
    ~Game();
    
    // play the game of blackjack
    void Play();

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

// constructor
Game::Game(const vector<string>& names) {
    // create a vector of players from a vector of names
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName) {
        m_Players.push_back(Player(*pName));
    }
    
    // seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}   

// destructor
Game::~Game() {}

// play the game of blackjack
void Game::Play() {
    // deal initial 2 cards to everyone
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i) {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }
    
    // hide house's first card
    m_House.FlipFirstCard();
    
    // display everyone's hand
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;
    
    // deal additional cards to players
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        m_Deck.AdditionalCards(*pPlayer);
    }
    
    // reveal house's first card
    m_House.FlipFirstCard();
    cout << endl << m_House;
    
    // deal additional cards to house
    m_Deck.AdditionalCards(m_House);
    
    if (m_House.IsBusted()) {
        // everyone still playing wins
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBusted())) {
                pPlayer->Win();
            }
        }
    }
    else {
        // compare each player still playing to house
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBusted())) {
                if (pPlayer->GetTotal() > m_House.GetTotal()) {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal()) {
                    pPlayer->Lose();
                }
                else {
                    pPlayer->Push();
                }
            }
        }
    }
    
    // remove everyone's cards
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        pPlayer->Clear();
    }
    m_House.Clear();
}   

int main() {
    cout << "\t\tWelcome to Blackjack!\n\n";
    
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7) {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }
    
    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;
    
    // the game loop
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N') {
        aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }
    
    return 0;
}   
    

