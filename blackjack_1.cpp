
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int getRandomNumber(int lot, int high);
int Card Value(int card);
int getTopCard(int deck[]);
int getHandValue(int hand[]);
bool playAnotherHand(char&);
bool userWantsToDraw(char&);
void initializeDeck(int deck[]);
void dumpDeck(int deck[], int size);
void shuffle(int deck[], int size);
void ShowCard(int card);
void showCards(const int cards[], int numCards, bool hideFirstCard);
void whoWins(const int pH[], const int dH[]);
void checkBust(const int pH[], const int dH[], char Play);
void blackJack(const int pH[], const int dH[], char Play);
void naturalBlackJack(const int pH[], const int dH[], char Play);
void playOneHand();
void scoreBoard(const int pH[], const int dH[]);
void backDoorKenny(const int hand[]);
void checkSoftOrHard(int pH[]);
void softOrHardAI(int dH[], int pH[]);
void difficulty();
void Rules();
void addToHand(int hand[], int cardToAdd);
void hitUntilStand(int dH[], int deck[], int pH[]);

int topCard = 0;
float win = 1.00;
int level;
int main() {
    Rules();
    Difficulty();
    playOneHand();
    return 1;
}

void Rules() {
    cout << "****************************************************************************" << endl;
    cout << "Welcome to BlackJack!" << endl;
    cout << "The goal of the game is to get as close to 21 as possible without going over." << endl;
    cout << "You will be playing against the dealer." << endl;
    cout << "The dealer will draw until they have 17 or higher." << endl;
    cout << "You will be given two cards and the dealer will be given two cards." << endl;
    cout << "You will be given the option to hit or stand." << endl;
    cout << "If you hit, you will be given another card." << endl;
    cout << "If you stand, you will not be given another card." << endl;
    cout << "If you go over 21, you will bust and lose." << endl;
    cout << "If you get 21, you will get a blackjack and win." << endl;
    cout << "If you get a blackjack and the dealer does not, you will win." << endl;
    cout << "*** Difficulty ***" << endl;
    cout << "Beginner: Dealer stands at a soft 17 and has no AI." << endl;
    cout << "Expert: Dealer hits at a soft 17 and has no AI." << endl;
    cout << "*****************************************************************************" << endl;
}

void Difficulty() {
    cout << "\n";
    cout << "Level of Difficulty: Beginner (1), Expert (2).";
    cin >> level;
    cout << "\n";
    if(level != 1) { // If input isn't a 1
        if(level != 2) { // or somehow either a 2
            cout << "Invalid input. Please enter 1 or 2." << endl;
            Difficulty();
        }
    }
}

void playOneHand() {
    char Play = 'N';
    do {
        char Draw = 'H';
        int deck[52]; // initialize deck of cards (52 cards)
        initializeDeck(deck);
        shuffle(deck, 51);
        int pH[10] = {0}; // initialize player hand
        int dH[10] = {0}; // initialize dealer hand
        addToHand(pH, getTopCard(deck)); // Starts the first round
        addToHand(dH, getTopCard(deck));
        addToHand(pH, getTopCard(deck));
        addToHand(dH, getTopCard(deck));
        cout << "*************************************************" << endl;
        cout << "\n";
        cout << "The dealer shuffled and dealt the cards." << endl;
        cout << "\n";
        naturalBlackJack(pH, dH, 'y');
        blackJack(pH, dH, 'Y');
        cout << "Your cards are: ";
        showCards(pH, 10, false);
        cout << "The dealer's cards are: ";
        showCards(dH, 10, true);
        checkSoftOrHard(pH);
        while (userWantsToDraw(Draw)) {
            addToHand(pH, getTopCard(deck));
            cout << "Your cards are: ";
            showCards(pH, 10, false);
            checkBust(pH, dH, 'Y');
            checkSoftOrHard(pH);
        }
        hitUntilStand(dH, deck, pH);
        cout << endl;
        checkBust(pH, dH, 'Y');
        blackJack(pH, dH, 'Y');
        whoWins(pH, dH);
        cout << endl;
        cout << "Winnings: $" << win << endl;
    }
    while (playAnotherHand(Play));
}

void initializeDeck(int deck[]) {
    int rank = 101;
    int i = 0;
    for(i = 0; i <= 13; i++) {
        deck[i] = rank;
        rank++;
    }
    for(i = 13; i <= 26; i++) {
        deck[i] = Rank++ + 100 - 14;
    }
    for(i = 26; i <= 39; i++) {
        deck[i] = Rank++ + 200 - 28;
    }
    for(i = 39; i <= 52; i++) {
        deck[i] = Rank++ + 300 - 42;
    }
}

void shuffle(int deck[], int size) {
    for(int i = 0; i < 500; i++) {
        int T1 = 0;
        int R1 = getRandomNumber(0, size);
        int R2 = getRandomNumber(0, size);
        T1 deck[R1];
        deck[R1] = deck[R2];
        deck[R2] = T1;
    }
}

int getTopCard(int deck[]) {
    for(int i = 0; i < 51; i++) {
        if(deck[i] != 0) {
            topCard = deck[i];
            deck[i] = 0;
            return topCard;
        }
    }
}

void addToHand(int hand[], int cardToAdd) {
    for(int i = 0; i < 9; i++) {
        if(hand[i] == 0) {
            hand[i] = cardToAdd;
            return;
        }
    }
}

void naturalBlackJack(const int pH[], const int dH[], char Play) {
    int playerScore = getHandValue(pH);
    int dealerScore = getHandValue(dH);
    if(playerScore == 21) {
        if(dealerScore == 21) {
            cout << "You both got a blackjack. It's a tie." << endl;
            cout << "Winnings: $" << win << endl;
            playAnotherHand(Play);
        }
        else {
            cout << "You got a blackjack! You win!" << endl;
            win = win + 1.50;
            cout << "Winnings: $" << win << endl;
            backDoorKenny(pH);
            playAnotherHand(Play);
        }
    }
}

void blackJack(const int pH[], const int dH[], char Play) {
    int playerScore = getHandValue(pH);
    int dealerScore = getHandValue(dH);
    if((playerScore == 21) && (dealerScore != 21)) {
        cout << "\n\n";
        scoreBoard(pH, dH);
        cout << "You got a blackjack! You win!" << endl;
        win = win + 1.50;
        cout << "Winnings: $" << win << endl;
        backDoorKenny(pH);
        playAnotherHand(Play);
    } else if((playerScore != 21) && (dealerScore == 21)) {
        cout << "\n\n";
        scoreBoard(pH, dH);
        cout << "The dealer got a blackjack. You lose." << endl;
        cout << "Winnings: $" << win << endl;
        playAnotherHand(Play);
    }

    void showCards(const int deck[], int numCards, bool hideFirstCard) {
        if(hideFirstCard) {
            cout << "**";
        } else {
            showCard(deck[0]);
            cout << " ";
        }
        for(int i = 1; i < numCards; i++) {
            if(deck[i] != 0) {
                showCard(deck[i]);
                cout << " ";
            } else {
                cout << " ";
            }
        } 
    }

    void checkSoftOrHard(int pH[]) {
        for(int i = 0; i < 9; i++) {
            int checkAce = cardValue(pH[i]);
            int softOrHard;
            if(checkAce == 1 || checkAce == 11) {
                cout << "You have an ace. Do you want it to be a 1 or 11? ";
                cin >> softOrHard;
                if(softOrHard == 1) {
                    if(checkAce == 11)
                        pH[i] = pH[i] + 13;
                }
            else if(softOrHard == 11) {
                if(checkAce == 1)
                    pH[i] = pH[i] - 13;
                }
            } else if(softOrHard != 1 || softOrHard != 11) {
                cout << "You have to choose 1 or 11. Try again." << endl;
                checkSoftOrHard(pH);
            }
        }
    }

    bool userWantsToDraw(char& Draw) {
        cout << endl << "\nWould you like to hit or stand? (H/S) ";
        cin >> Draw;
        cout << "\n";
        if(Draw == 'H' || Draw == 'h') {
            return true;
        } else if(Draw == 'S' || Draw == 's') {
            return false;
        } else {
            cout << "You have to choose H or S. Try again." << endl;
            userWantsToDraw(Draw);
        }
    }

    void checkBust(const int pH[], const int dH[], char Play) {
        int playerScore = getHandValue(pH);
        int dealerScore = getHandValue(dH);
        if(playerScore > 21) {
            cout << "\n\n";
            scoreBoard(pH, dH);
            cout << "You busted. You lose." << endl;
            cout << "Winnings: $" << win << endl;
            playAnotherHand(Play);
        } else if(dealerScore > 21) {
            cout << "\n\n";
            scoreBoard(pH, dH);
            cout << "The dealer busted. You win!" << endl;
            win = win + 1;
            cout << "Winnings: $" << win << endl;
            playAnotherHand(Play);
        }
    }

    void hitUntilStand(int dH[], int deck[], int pH[]) {
        for(int i = 0; i < 9; i++) {
            if(getHandValue(dH) < 17) {
                if(level == 1) {
                    addToHand(dH, getTopCard(deck));
                } else if(level == 2) {
                        addToHand(dH, getTopCard(deck));
                        softOrHardAI(dH, pH);
                }
                    } else {
                        if(i == 0) {
                            cout << "The dealer stands." << endl;
                            break;
                        }
                    } else if(i == 1) {
                        cout << "The dealer hits." << endl;
                        break;
                    } else {
                        cout << "the Dealer hit " << i << " cards and stands." << endl;
                        break;
                    }
                }
                if(level == 1);
                else if(level == 2) {
                    softOrHardAI(dH, pH);
                }
        }
    }

int getHandValue(const int hand[]) {
    int addCardValues = 0;
    for(int i = 0; i < 9; i++) {
        addCardValues = addCardValues + cardValue(hand[i]);
    }
    return addCardValues;
}

int CardValue(int card) {
    int cardVal;
    switch(card % 100) {
        case 1:
            cardVal = 11;
            break;
        case 11:
        case 12:
        case 13:
            cardVal = 10;
            break;
        default:
            cardVal = card % 100;
            break;
    } 
    return cardVal;
}

void scoreBoard(const int pH[], const int dH[]) {
    cout << "Player hand: ";
    showCards(pH, 10, false);
    cout << " (" << getHandValue(pH) << "pts)" << endl;
    cout << "V.S" << endl;
    cout << "Dealer hand: ";
    showCards(dH, 10, false);
    cout << " (" << getHandValue(dH) << "pts)";
}

void backdoorKenny(const int hand[]) {
   if((CardValue(hand[0])%100 == 10) && (CardValue(hand[1])%100 == 11)) {
    cout << "\n\n";
    cout << "You pulled a Backdoor Kenny!\n" << endl;
    cout << "Win an additional 1:4 payout\n" << endl;
    win = win + .25;
    cout << "winnings: " << win << endl;
   } 
}

void ShowCard(int card) {
    if(card == 0) {
        cout << "";
    } else {
        switch(card % 100) {
            case 1:
            cout << "A";
            break;
            case 11:
            cout << "J";
            break;
            case 12:
            cout << "K";
            break;
            case 13:
            cout << "Q";
            break;
            case 14: 
            cout << "A";
            break;
            default:
            cout << card % 100;
        }
    }
    if(card == 0) {
        cout << "";
    } else {
        if((card >= 101) && (card <= 114)) {
            cout << static_cast<char>(3);
        } else if ((card >= 201) && (card <= 214)) {  // Diamonds
        cout << static_cast<char>(4);
        } else if ((card >= 301) && (card <= 314)) {  // Clubs
        cout << static_cast<char>(5);
        } else if ((card >= 401) && (card <= 414)) {  // Spades
        cout << static_cast<char>(6);
        }
    }
}

void dumpDeck(int deck[], int size) {
    for(int i = 0; i < size; i++) {
        cout << i + 1 << ".) " << deck[i] << endl;
    }
}

int getRandomNumber(int low, int high) {
    static bool firstTime=true;
    int randNum;
    if(firstTime) {
        srand(static_cast<unsigned int>(time(NULL)) );
    }
    randNum = rand() % (high-low+1) + low;
    return randNum;
}

void softOrHardAI(int dH[], int pH[]) {
    for(int i = 0; i < 9; i++) {
        if(CardValue(dH[i]) == 1 || CardValue(dH[i]) == 11) {
            if(CardValue(dH[i]) == 11) {
                if(getHandValue(dH) - CardValue(dH[i]) + 1 > getHandValue(pH)) {
                    if(getHandValue(dH) - CardValue(dH[i]) + 1 < 22) {
                        dH[i] = dH[i] + 13;
                    }
                } else if (getHandValue(dH) > 21) {
                    dH[i] = dH[i] + 13;
                }
            } else {
                if(getHandValue(dH) - CardValue(dH[i]) + 11 > getHandValue(pH)) {
                    if(getHandValue(dH) - CardValue(dH[i]) + 11 < 22) {
                        dH[i] = dH[i] - 13;
                    }
                }
            }
        }
    }
}

void whoWins(const int pH[], const int dH[]) {
    int playerScore = getHandValue(pH);
    int dealerScore = getHandValue(dH);
    scoreBoard(pH,  dH);
    if((playerScore < 22) && (playerScore > dealerScore) || ((dealerScore > 21) && (playerScore < 22))) {
        cout << "\n";
        cout << "You win!" << endl;
        win++;
    } else {
        if(playerScore == dealerScore) {
            cout << "\n";
            cout << "Push in the Dealer's favor. 0:1 payout." << endl;
        } else {
            cout << "\n";
            cout << "You lose." << endl;
            win--;
        }
    }
}

bool playAnotherHand(char& Play) {
    cout << endl << "\n Would you like to play another hand? (Y/N) ";
    cin >> Play;
    cout << "\n";
    if(Play == "y" || Play == "Y") {
        playOneHand();
        return(true);
    } else {
        return(false);
    }
}