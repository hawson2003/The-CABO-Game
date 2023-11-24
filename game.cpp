#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
using namespace std;

class Card {
private:
    char color;
    char value;

public:
    Card(const char cardColor, char cardValue) {
        // Each card have a symbol color and a value
        color = cardColor;
        value = cardValue;
    }

    // return string for output
    string printCard() {
        string x;

        // add color
        if (color == 'H')
            x = "\u2665"; // heart ♥
        else if (color == 'S')
            x = "\u2660"; // spade ♠
        else if (color == 'D')
            x = "\u2666"; // diamond ♦
        else if (color == 'C')
            x = "\u2663"; // club ♣
        else
            x = string(1, color); // Joker

        return x + value;
    }

    // turn char value into integer value for comparison
    int getIntValue() {
        if (value == 'O' || value == 'o')
            return 0; // for jokers to be 0
        else if (value == 'A')
            return 1;
        else if (value == 'T')
            return 10;
        else if (value == 'J')
            return 11;
        else if (value == 'Q')
            return 12;
        else if (value == 'K')
            return 13;
        else
            return value - '0'; // 2~9
    }
};

class Player {
private:
    string name;
    vector<int> scoreboard;
    int totalScore;
    vector<Card> hand;
    string type;
    vector<Card> knownCards;
    int avaChoice;
    int playerValue;
    bool calledCabo;

public:
    Player(const string& playerName, const string& playerType) {
        name = playerName;
        type = playerType;
        totalScore = 0;
        avaChoice = 4;
        playerValue = 100;
    }

    // show name
    string showName () {
        return name;
    }
    // show type
    string showType () {
        return type;
    }
    // show totalScore
    int showTotalScore () {
        calculateTotalScore();
        return totalScore;
    }
    // show avaChoice
    int showAvaChoice () {
        return avaChoice;
    }
    // show scoreboard
    vector<int> showScoreboard () {
        return scoreboard;
    }
    // show calledCabo
    bool showCalledCabo () {
        return calledCabo;
    }
    // show playerValue
    int showPlayerValue () {
        return playerValue;
    }
    
    // print all known cards, for testing
    void printAllKnown () {
        for (Card card : knownCards) {
            cout << card.printCard() << " ";
        }
        cout << endl;
    }

    // set calledCabo when calling Cabo
    void setCalledCabo (bool b) {
        calledCabo = b;
    }
    // set playerValue
    void setPlayerValue (int v) {
        if (v < playerValue) {
            playerValue = v;
        }
    }
    // set avaChoice at start of round
    void setAvaChoice (int n) {
        avaChoice = 4;
    }

    // calculate total score for a player
    void calculateTotalScore () {
        totalScore = 0;
        bool halfScoreUsed = false;
        for (int score : scoreboard) {
            totalScore += score;
            // check if the player reaches exactly 100 and the skill is only used once
            if (totalScore == 100 && halfScoreUsed == false) {
                totalScore /= 2;
                halfScoreUsed = true;
            }
        }
    }

    // function to add a new score to scoreboard after each round
    void addToScoreboard (int score) {
        scoreboard.push_back(score);
    }

    // function to show scoreboard for output
    string toMiddle (string text, int targetLength) {
        int textLength = text.length();
        int a = (targetLength - textLength) / 2;
        int b = (targetLength - textLength + 1) / 2;
        return string(a, ' ') + text + string(b, ' ');
    }
    string printScoreboard () {
        string ret;
        ret = toMiddle(showName(), 6);
        for (int score : scoreboard) {
            ret += (string(1, '|') + toMiddle(to_string(score), 2));
        }
        ret += (string(8, ' ') + string(1, '|') + toMiddle(to_string(showTotalScore()), 5));
        return ret;
    }

    // function to print score
    string showScore () {
        if (totalScore == 0) {
            return " 0 ";
        } else if (totalScore < 10) {
            return "-" + to_string(totalScore) + " ";
        } else {
            return "-" + to_string(totalScore);
        }
    }

    // initiate a player's hand and knownCards at the start of each round
    void initiatePlayerHand () {
        hand.clear();
        knownCards.clear();
        setAvaChoice(4);
    }

    // when a round end, or for cheating, set all cards known to player
    void setAllKnown (vector<Card> deck) {
        for (Card card : deck) {
            knownCards.push_back(card);
        }
    }

    // check if a player knows all cards in hand
    bool knownAllCards () {
        bool flag = true;
        for (Card card : hand) {
            if (!isKnown(card)) {
                flag = false;
            }
        }
        return flag;
    }

    // count the number of cards with same value
    int countSameCards (Card card) {
        int value = card.getIntValue();
        int count = 0;
        for (Card c : hand) {
            if (isKnown(c) && c.getIntValue() == value) {
                count++;
            }
        }
        return count;
    }

    // function to add a new card to hand, which is private
    void addCardToHand (Card card) {
        hand.push_back(card);
    }

    // show the i-th card, consider if it is disguised
    string showOneCard (int index, Player& player) {
        if (index >= avaChoice) {
            return "  ";
        }
        if (player.isKnown(hand[index])) {
            return hand[index].printCard();
        }
        return "\uFFFD\uFFFD";
    }

    // show cards in hand
    vector<Card> showHand () {
        return hand;
    }

    // add a card to vector if known
    void addToKnown (Card& card) {
        knownCards.push_back(card);
    }

    // check if a card is in knownCards
    bool isKnown (Card& card) {
        for (int i=0; i<knownCards.size(); i++) {
            if (knownCards[i].printCard() == card.printCard()) {
                return true;
            }
        }
        return false;
    }

    // swap a card with hand
    Card swapWithHand (Card card, char pos) {
        Card tmp = hand[pos - 'A'];
        hand[pos - 'A'] = card;
        return tmp;
    }

    // delete a card from hand
    void delChoice (Card& card) {
        for (int i = 0; i < 4; i++) {
            if((*(hand.begin() + i)).printCard() == card.printCard()) {
                hand.erase(hand.begin() + i);
                break;
            }
        }
    }

    // delete number of choices
    void delNumChoice (int num) {
        avaChoice -= num;
    }

    // show valid input
    vector<char> showValidChars() {
        vector<char> res = {'A', 'B', 'C', 'D'};
        for (int i = 0; i < 4 - avaChoice; i++) {
            res.pop_back();
        }
        return res;
    }

    // calculate the total value of cards in hand
    int calHandValue () {
        int sum = 0;
        for (Card card : hand) {
            sum += card.getIntValue();
        }
        return sum;
    }

    // detect if a card value is in hand
    bool cardInHand (Card card) {
        int value = card.getIntValue();
        for (Card c : hand) {
            if (isKnown(c) && c.getIntValue() == value) {
                return true;
            }
        }
        return false;
    }

    /* Here we use a defined card value.
    If a card is unknown, it is equal to 62, 64, 66 to be the i-th unknown card.
    If a card is known, it is equal to 10 times the value of the number on the card.
    Check if there are cards with same value on card, if yes, they should be add together.

    Now each card has a value. Different cards have different values.
    The largest card is the one that should be swapped.
    */

    // calculate a card value
    int calCardValue (Card card, int& unknownValue, int switchCardValue) {
        if (!isKnown(card)) {
            // check if the card is unknown
            int ret = unknownValue;
            // -1 to distinguish different unknown cards
            unknownValue -= 1;
            return ret;
        } else {
            // check how many times the card appears in hand
            // use unit digit to denote number of appearance
            int ret = countSameCards(card) * (card.getIntValue() * 10 + 1);
            if (card.getIntValue() == switchCardValue) {
                ret -= 150;
            }
            return ret;
        }
    }

    // get the largest value in hand, use defined value
    int maxKnownHandValue (Card switchcard) {
        int unknownValue = 69;
        int maxValue = 0;
        int foldCardValue = switchcard.getIntValue();

        // iterate through all cards in hand, find the largest one
        for (Card card : hand) {
            int cardValue = calCardValue(card, unknownValue, foldCardValue);
            if (maxValue < cardValue) {
                maxValue = cardValue;
            }
        }

        // return the largest value
        return maxValue;
    }

    // get the largest value in hand, regardless of same-value cards, use defined value
    int maxHandValueWithoutSame (bool isCabo) {
        int unknownValue = 69;
        int ret = 0;

        if (isCabo) {
            for (Card card : hand) {
                int cardValue;
                if (!isKnown(card)) {
                    // check if the card is unknown
                    cardValue = unknownValue;
                    // -1 to distinguish different unknown cards
                    unknownValue -= 1;
                } else {
                    cardValue = card.getIntValue() * 10;
                }

                if (cardValue > ret) {
                    ret = cardValue;
                }
            }
            return ret;
        } else {
            for (Card card : hand) {
                int cardValue;
                if (!isKnown(card)) {
                    // check if the card is unknown
                    cardValue = unknownValue;
                    // -1 to distinguish different unknown cards
                    unknownValue -= 1;
                } else {
                    if (countSameCards(card) > 1) {
                        cardValue = -1;
                    } else {
                        cardValue = card.getIntValue() * 10;
                    }
                }

                if (cardValue > ret) {
                    ret = cardValue;
                }
            }
            return ret;
        }
    }
    int findHandValueWithoutSame(int v) {
        int unknownValue = 69;
        for (int i = 0; i < avaChoice; i++) {
            int cardValue;
            if (!isKnown(hand[i])) {
                // check if the card is unknown
                cardValue = unknownValue;
                // -1 to distinguish different unknown cards
                unknownValue -= 1;
            } else {
                if (countSameCards(hand[i]) > 1) {
                    cardValue = -1;
                } else {
                    cardValue = hand[i].getIntValue() * 10;
                }
            }

            if (cardValue == v) {
                return i;
            }
        }
        return 0;
    }

    // get the choice
    string getChoice (Card card) {
        int unknownValue = 69;
        int switchCardValue = card.getIntValue();

        string choice = "";
        int maxValue = maxKnownHandValue(card);

        for (int i = 0; i < avaChoice; i++) {
            int curCardValue = calCardValue(hand[i], unknownValue, switchCardValue);
            // cout << curCardValue << " "; 
            if (curCardValue == maxValue) {
                char let = 'A' + i;
                choice += let;
            }
        }
        return choice;
    }
    
};

class Round {
private:
    int roundNum;
    vector<Card> deck;
    vector<Card> folddeck;
    vector<Card> fulldeck;
    vector<string> history;
    int cabo;
    int turnNum;
    vector<Player> seq;
    vector<int> sumHistory;

public:
    Round(const int num, Player& player, Player& comp1, Player& comp2) {
        roundNum = num;
        folddeck.push_back(Card(' ', ' '));
        // initialized at -1. If activated, changed to 3
        cabo = -1;
        // initialized at 0, used for computer decision
        turnNum = 0;
    }

    // initialize the deck
    void initiateDeck (Player& player, Player& comp1, Player& comp2) {
        // create a deck for draw
        deck = createDeck();
        // add a card to FOLD deck to begin with
        Card card = drawCard(deck);
        discardCard(card, player, comp1, comp2);
        // distribute 4 cards to each player
        player.initiatePlayerHand();
        comp1.initiatePlayerHand();
        comp2.initiatePlayerHand();
        for (int i = 0; i < 4; i++) {
            player.addCardToHand(drawCard(deck));
            comp1.addCardToHand(drawCard(deck));
            comp2.addCardToHand(drawCard(deck));
        }
        /*REVISION*/
        sumHistory.push_back(player.calHandValue());
        sumHistory.push_back(comp1.calHandValue());
        sumHistory.push_back(comp2.calHandValue());
        // clear the history vector and add 5 empty lines
        history = {"", "", "", "", ""};
    }

    // function to create a deck in order
    vector<Card> createDeck () {
        // create cards for each color and value
        char colors[4] = {'H', 'S', 'D', 'C'};
        char values[12] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q'};

        for (char c : colors) {
            for (char v : values) {
                deck.push_back(Card(c, v));
            }
        }

        // add 2 kings
        deck.push_back(Card('H', 'K'));
        deck.push_back(Card('S', 'K'));

        // add 2 jokers
        deck.push_back(Card('J', 'O'));
        deck.push_back(Card('j', 'o'));

        shuffleDeck(deck);
        fulldeck = deck;
        return deck;
    }

    // function to show the initial deck
    vector<Card> showFullDeck () {
        return fulldeck;
    }

    // function to shuffle a vector<Card> with a shuffled array
    template <typename T, size_t N>
    void shuffleArray(T (&arr)[N]) {
        random_device rd;
        mt19937 rng(rd());

        for (size_t i = N - 1; i > 0; --i) {
            uniform_int_distribution<size_t> dist(0, i);
            size_t j = dist(rng);
            swap(arr[i], arr[j]);
        }
    }
    void shuffleDeck (vector<Card>& d) {
        // generate random seeds
        srand(time(NULL));
        // create a random array
        int arr[52];
        for (int i=0; i<52; i++) {
            arr[i] = i;
        }
        shuffleArray(arr);
        
        // shuffle the deck
        vector<Card> temp;
        for (int i=0; i<52; i++) {
            temp.push_back(d[arr[i]]);
        }

        d = temp;
    }

    // function to draw a card from the deck and delete it
    Card drawCard (vector<Card>& deck) {
        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    // function to fold a card
    void discardCard (Card& card, Player& player, Player& comp1, Player& comp2) {
        // set the card visible to all players
        player.addToKnown(card);
        comp1.addToKnown(card);
        comp2.addToKnown(card);
        // add the card to the fold deck
        folddeck.push_back(card);
    }

    // function to print a deck (for backend inpection)
    void printDeck (vector<Card> deck, string whom) {
        cout << whom << ": ";
        for (Card c : deck) {
            cout << c.printCard() << " ";
        }
        cout << endl;
    }

    // ask for a char input
    char askForInput (string text, vector<char> validChars, string wrongHint) {
        cout << text;
        char c;
        bool isValid = false;

        // input and check validity
        do {
            cin >> c;
            c = toupper(c);

            for (char i : validChars) {
                if (c == i) {
                    isValid = true;
                    break;
                }
            }

            // print hint for another input
            if (!isValid) {
                cout << wrongHint;
            }

        } while (isValid);

        return c;
    }

    // functions to adjust output style
    string toMiddle (string text, int targetLength) {
        int textLength = text.length();
        int a = (targetLength - textLength) / 2;
        int b = (targetLength - textLength + 1) / 2;
        return string(a, ' ') + text + string(b, ' ');
    }
    string space (int n) {
        return string(n, ' ');
    }
    string stringToUpper (string a) {
        string result = "";
        for (int i=0; i < a.length(); i++) {
            result += toupper(a[i]);
        }
        return result;
    }

    // hint to players
    string showGuide (int line, int hintContent, int cardValue) {
        if (hintContent == 1) {
            switch (line) {
                case 1:
                    return "Now Let's start round " + to_string(roundNum) + ".";
                case 3:
                    return "You can peek two of your cards.";
                case 4:
                    return "Type two of 'ABCD' to peek the according cards.";
                case 5:
                    return "For example, 'AB' or 'BC'.";
            }
        } else if (hintContent == 2) {
            string h = "'C' to call CABO! Make sure you have the smallest cards.";
            if (cardValue == 1) {
                h = "";
            }
            switch (line) {
                case 1:
                    return "Type one of the following keys to execute an action:";
                case 3:
                    return "'D' to draw a card from the DRAW deck.";
                case 4:
                    return "'F' to draw a card from the FOLD deck.";
                case 5:
                    return h;
                default:
                    return "";
            }
        } else if (hintContent == 3) {
            if (cardValue >= 7 && cardValue <= 12) {
                string skillName, skillDesc;
                if (cardValue == 7 or cardValue == 8) {
                    skillName = "peek";
                    skillDesc = "(Play a 7 or 8 to peek an unknown card of your own)";
                } else if (cardValue == 9 or cardValue == 10) {
                    skillName = "spy";
                    skillDesc = "(Play a 9 or T to spy on an unknown card of others)";
                } else if (cardValue == 11 or cardValue == 12) {
                    skillName = "swap";
                    skillDesc = "(Play a J or Q to blind swap a card with others)";
                }
                switch (line) {
                    case 1:
                        return "Type one of the following keys to execute an action:";
                    case 3:
                        return "'P' to play the card and use the power " + skillName + ".";
                    case 4:
                        return skillDesc;
                    case 5:
                        return "'N' to drop the card without using the power " + skillName + ".";
                    case 6:
                        return "'S' to swap the card in hand with the card drawn.";
                }
            } else {
                switch (line) {
                    case 1:
                        return "Type one of the following keys to execute an action:";
                    case 3:
                        return "'N' to drop the card. This card does not have any power.";
                    case 4:
                        return "'S' to swap the card in hand with the card drawn.";
                }
            }
        } else if (hintContent == 4) {
            switch (line) {
                case 1:
                    return "Type one or more of 'ABCD' to swap.";
                case 3:
                    return "To swap one card, enter one position.";
                case 4:
                    return "You can swap either known or unknown cards.";
                case 6:
                    return "To swap two or more cards, enter their positions.";
                case 7:
                    return "You can only swap known cards that have the same value";
            }
        } else if (hintContent == 5) {
            switch (line) {
                case 1:
                    return "Now the round ends.";
                case 2:
                    return "It is time to calculate the total value of everyone's hand.";
            }
        } else if (hintContent == 6) {
            if (cardValue == 1) {
                switch (line) {
                    case 1:
                        return "CP1 is thinking ...";
                }
            } else if (cardValue == 2) {
                switch (line) {
                    case 2:
                        return "CP2 is thinking ...";
                }
            }
        }
        return "";
    }

    // function to print the gameboard on screen
    void printTable (Player player, Player comp1, Player comp2, int roundNum, int hintContent, int cardValue = 0) {
        // clear screen
        cout << "\033[2J\033[1;1H";
        // print history
        cout << "... ..." << endl;
       for (int i = history.size() - 5; i < history.size(); i++) {
            cout << history[i] << endl;
       }
        // print game table
        cout << toMiddle("/" + string(15, '-') + "\\", 29) << " " << endl;
        cout << toMiddle("|" + toMiddle("ROUND " + to_string(roundNum), 15) + "|", 29) << " " << showGuide(0, hintContent, cardValue) << endl;
        cout << space(5) << "A|" << comp1.showOneCard(0, player) << space(11) << comp2.showOneCard(0, player) << "|A" << space(5) << " " << showGuide(1, hintContent, cardValue) << endl;
        cout << toMiddle("|" + toMiddle("FOLD", 15) + "|", 29) << " " << showGuide(2, hintContent, cardValue) << endl;
        cout << space(1) << "CP1 B|" << comp1.showOneCard(1, player) << space(4) << folddeck.back().printCard() << space(5) << comp2.showOneCard(1, player) << "|B CP2" << space(1) << " " << showGuide(3, hintContent, cardValue) << endl;
        cout << space(1) << comp1.showScore() << space(2) << "|" << space(15) << "|" << space(2) << comp2.showScore() << space(1) << " " << showGuide(4, hintContent, cardValue) << endl;
        cout << space(5) << "C|" << comp1.showOneCard(2, player) << toMiddle("DRAW", 11) << comp2.showOneCard(2, player) << "|C" << space(5) << " " << showGuide(5, hintContent, cardValue) << endl;
        cout << toMiddle("|" + toMiddle("\uFFFD\uFFFD", 19) + "|", 33) << " " << showGuide(6, hintContent, cardValue) << endl;
        cout << space(5) << "D|" << comp1.showOneCard(3, player) << space(11) << comp2.showOneCard(3, player) << "|D" << space(5) << " " << showGuide(7, hintContent, cardValue) << endl;
        cout << toMiddle("|" + string(15, ' ') + "|", 29) << " " << showGuide(8, hintContent, cardValue) << endl;
        cout << space(6) << "|" << space(2) << player.showOneCard(0, player) << space(1) << player.showOneCard(1, player) << space(1) << player.showOneCard(2, player) << space(1) << player.showOneCard(3, player) << space(2) << "|" << space(6) << " " << showGuide(9, hintContent, cardValue) << endl;
        cout << toMiddle("\\" + string(15, '-') + "/", 29) << " " << showGuide(10, hintContent, cardValue) << endl;
        cout << toMiddle("A  B  C  D", 29) << endl;
        cout << toMiddle(stringToUpper(player.showName()), 28) << " " << endl;
        cout << toMiddle(player.showScore(), 28) << " " << endl;
    }

    // initiate peek stage
    void peekStage (Player& player, Player& comp1, Player& comp2) {
        // print the initial game table
        printTable(player, comp1, comp2, roundNum, 1);
        
        // each player get the turn to peek 2 cards
        playerPeek(player);
        computerPeek(comp1, player);
        computerPeek(comp2, player);
    }

    // movements of peek
    void playerPeek (Player& player) {
        // get input
        string prompt = "Enter two choices from ABCD: ";
        /*REVISION*/
        // string inp = "BC";
        string inp = getChoice(prompt, 2, 2, {'A', 'B', 'C', 'D'});
        char ch1 = inp[0];
        char ch2 = inp[1];

        // set visibility for user
        player.addToKnown(player.showHand()[ch1 - 'A']);
        player.addToKnown(player.showHand()[ch2 - 'A']);
        
        // print the choices and store in history
        string msg = player.showName() + " has peeked at cards " + ch1 + " and " + ch2 + ".";
        printMsg(msg);
    }
    void computerPeek (Player& comp, Player& player) {
        // set visibility for computer
        comp.addToKnown(comp.showHand()[0]);
        comp.addToKnown(comp.showHand()[1]);
        // print the choices and store in history
        string msg = comp.showName() + " has peeked at its cards A and B.";
        printMsg(msg);
    }

    // an easy check on input
    bool easyCheck (char c, const vector<char>& validChars) {
        c = toupper(c);
        for (char i : validChars) {
            if (i == c) {
                return true;
            }
        }
        return false;
    }
    string getChoice (string prompt, int minLength, int maxLength, vector<char> validChars) {
        bool validInput = false;
        string inp;
        
        do {
            cout << prompt;
            cin >> inp;
            inp = stringToUpper(inp);

            bool flag = true;
            // check if the length is correct
            if (inp.length() < minLength || inp.length() > maxLength) {
                flag = false;
            }
            // check if each char is valid
            for (char c : inp) {
                if (!easyCheck(c, validChars)) {
                    flag = false;
                }
            }
            // check if all chars are different
            for (int i = 0; i < inp.length(); i++) {
                for (int j = i + 1; j < inp.length() - i; j++) {
                    if (inp[i] == inp[j]) {
                        flag = false;
                    }
                }
            }
            // exit or print error message
            if (flag) {
                validInput = true;
            } else {
                cout << "Invalid Input. Try again." << endl;
            }
        } while (!validInput);

        return inp;
    }

    // game rounds
    void startRound (Player& player, Player& comp1, Player& comp2) {
        // create an action sequence the decides the players' turn
        seq = createQ(player, comp1, comp2);
        // initialize end condition
        bool roundEnd = false;
        int turn = 0;

        // each player takes the turn to perform action
        while (!deck.empty() && cabo != 0) {
            // get the last object of the action sequence each time
            Player cur = seq.back();
            seq.pop_back();
            // define the other 2 players for spy and swap
            Player oth1 = seq[0];
            Player oth2 = seq[1];

            // perform action
            if (cur.showType() == "player") {
                if (cabo == 1) {
                    cout << "CP1 has called CABO in its turn. It's your last turn in this round!" << endl;
                } else if (cabo == 2) {
                    cout << "CP2 has called CABO in its turn. It's your last turn in this round!" << endl;
                }
                playerAction(player, comp1, comp2, cabo);
                /*REVISION*/
                sumHistory.push_back(player.calHandValue());
                
            } else {
                // computer makes a decision on the action based on a set of logic
                if (cur.showName() == "CP1") {
                    computerAction(comp1, player, comp1, comp2, cabo, turn);
                    /*REVISION*/
                    sumHistory.push_back(comp1.calHandValue());
                } else {
                    computerAction(comp2, player, comp1, comp2, cabo, turn);
                    /*REVISION*/
                    sumHistory.push_back(comp2.calHandValue());
                }
            }

            // add cur back to the action sequence
            seq.insert(seq.begin(), cur);

            // Consider an end condition
            if (cabo > 0){
                cabo--;
            }

            // count turn
            turn++;
        }

        // print reason for round end
        if (deck.empty()) {
            cout << "The deck is empty. The round ends." << endl;
        } else {
            cout << "CABO! The round ends." << endl;
        }
    }

    // create a queue that starts with random player
    vector<Player> createQ (Player& player, Player& comp1, Player& comp2) {
        /*REVISION*/
        // return {comp2, comp1, player};
        int randNum = rand() % 3 + 1;
        if (randNum == 1) {
            // player would be the first to operate -> comp1 -> comp2 -> player -> ...
            cout << player.showName() << " starts the round." << endl;
            return {comp2, comp1, player};
        } else if (randNum == 2) {
            cout << comp2.showName() << " starts the round." << endl;
            return {comp1, player, comp2};
        } else {
            cout << comp1.showName() << " starts the round." << endl;
            return {player, comp2, comp1};
        }
    }

    // player action in a turn
    void playerAction (Player& player, Player& comp1, Player& comp2, int& cabo) {
        if (cabo != -1) {
            printTable(player, comp1, comp2, roundNum, 2, 1);
        } else {
            printTable(player, comp1, comp2, roundNum, 2);
        }


        // get input
        string prompt = "Enter your choice of action: ";
        char inp;
        if (cabo == -1) {
            inp = getChoice(prompt, 1, 1, {'D', 'F', 'C'})[0];
        } else {
            inp = getChoice(prompt, 1, 1, {'D', 'F'})[0];
        }

        // handle action
        if (inp == 'D') {
            // draw a new card from the deck
            Card card = drawCard(deck);
            player.addToKnown(card);

            printTable(player, comp1, comp2, roundNum, 3, card.getIntValue());
            // get input
            string prompt = "You have drawn " + card.printCard() + ". Enter your choice: ";
            char inp;
            if (card.getIntValue() >= 7 || card.getIntValue() <= 12) {
                inp = getChoice(prompt, 1, 1, {'P', 'N', 'S'})[0];
            } else {
                inp = getChoice(prompt, 1, 1, {'N', 'S'})[0];
            }

            // handle action
            if (inp == 'P') {
                string msg = " You play " + card.printCard() + " and use the power.";
                printMsg(msg);
                
                // different action for different card skills
                if (card.getIntValue() == 7 or card.getIntValue() == 8) {
                    // perform peek
                    // get input of the card to peek
                    string prompt = "Enter a card of 'ABCD' of your own that you want to peek: ";
                    char inp = getChoice(prompt, 1, 1, player.showValidChars())[0];
                    // add the card to known
                    player.addToKnown(player.showHand()[inp - 'A']);
                    // peek
                    string msg = "You peeked at your card " + string(1, inp) + ". It was " + player.showHand()[inp - 'A'].printCard() + ".";
                    printMsg(msg);

                } else if (card.getIntValue() == 9 or card.getIntValue() == 10) {
                    // perform spy
                    // get input of the computer
                    prompt = "Enter '1' if you want to spy on CP1's card, and '2' if you want to spy on CP2's card. \n Enter the number of computer you want to spy on: ";
                    char inp = getChoice(prompt, 1, 1, {'1', '2'})[0];
                    Player spyTarget = comp1;
                    if (inp == '2') {
                        spyTarget = comp2;
                    }
                    // get input of the card to spy on
                    string prompt = "Enter the one card of 'ABCD' of CP" + string(1, inp) + " that you want to spy on: ";
                    inp = getChoice(prompt, 1, 1, spyTarget.showValidChars())[0];
                    // add the card to known
                    player.addToKnown(spyTarget.showHand()[inp - 'A']);
                    // spy
                    string msg = "You have spy on " + spyTarget.showName() + "'s card. It was " + spyTarget.showHand()[inp - 'A'].printCard() + ".";
                    printMsg(msg);

                } else {
                    // perform swap
                    // get input of own card to swap
                    prompt = "Choose the card of your own that you want to swap. \n It can either be known or unknown. \n Enter one of 'ABCD' of your own cards: ";
                    char inp1 = getChoice(prompt, 1, 1, player.showValidChars())[0];
                    Card s1 = player.showHand()[inp1 - 'A'];
                    // get input of the computer
                    prompt = "Enter '1' if you want to swap CP1's card, and '2' if you want to swap CP2's card. \n Enter the number of computer you want to swap with: ";
                    char inp = getChoice(prompt, 1, 1, {'1', '2'})[0];
                    // get input of the card to swap
                    prompt = "Choose the card in CP" + string(1, inp) + "'s hand that you want to swap with. \n Enter the card of 'ABCD' that you want to swap with: ";
                    char inp2;
                    Card s2 = s1;
                    if (inp == '1') {
                        inp2 = getChoice(prompt, 1, 1, comp1.showValidChars())[0];
                        s2 = comp1.swapWithHand(s1, inp2);
                    } else {
                        inp2 = getChoice(prompt, 1, 1, comp2.showValidChars())[0];
                        s2 = comp2.swapWithHand(s1, inp2);
                    }
                    player.swapWithHand(s2, inp1);
                    // check if the cards should be disguised
                    string s1_str, s2_str, swapTarget;
                    if (player.isKnown(s1)) {
                        s1_str = s1.printCard();
                    } else {
                        s1_str = "\uFFFD\uFFFD";
                    }
                    if (player.isKnown(s2)) {
                        s2_str = s2.printCard();
                    } else {
                        s2_str = "\uFFFD\uFFFD";
                    }
                    if (inp == '1') {
                        swapTarget = "CP1";
                    } else {
                        swapTarget = "CP2";
                    }
                    // add message to history
                    string msg = "You swapped your " + string(1, inp1) + " " + s1_str + " with " + swapTarget + "'s " + string(1, inp2) + " " + s2_str + ".";
                    printMsg(msg);

                }

                // this discard uses the skill, so does not consider PlayerValue
                discardCard(card, player, comp1, comp2);
                
            } else if (inp == 'N') {
                foldAction(player, card, comp1, comp2);
            } else {
                swapAction(player, card, comp1, comp2);

            }

        } else if (inp == 'F') {
            // retrieve the last card from deck
            Card card = drawCard(folddeck);
            player.addToKnown(card);

            printTable(player, comp1, comp2, roundNum, 3);
            // get input
            string prompt = "You have drawn " + card.printCard() + ". Enter your chice: ";
            char inp = getChoice(prompt, 1, 1, {'N', 'S'})[0];

            // handle action
            if (inp == 'N') {
                foldAction(player, card, comp1, comp2);
            } else {
                swapAction(player, card, comp1, comp2);
            }

        } else {
            // player call cabo
            string msg = player.showName() + " call CABO!";
            printMsg(msg);
            cabo = 3;
            player.setPlayerValue(-1);

        }

    }

    // drop the card without using the power
    void foldAction (Player& player, Card& card, Player& comp1, Player& comp2) {
        string msg = "You drop the card " + card.printCard() + ".";
        printMsg(msg);
        
        player.setPlayerValue(card.getIntValue());
        discardCard(card, player, comp1, comp2);
    }

    // swap with hand
    void swapAction (Player& player, Card& card, Player& comp1, Player& comp2) {
        string msg = "You swap " + card.printCard() + " with hand ";
        printTable(player, comp1, comp2, roundNum, 4);
        
        // get input and swap
        bool flag = false;
        string inp;
        do {
            // check if the input is some of ABCD
            string prompt = "Swap " + card.printCard() + " (value = " + to_string(card.getIntValue()) + ") with your hand: ";
            inp = getChoice(prompt, 1, 4, player.showValidChars());
            // if input is 1, take the input
            // if input is larger than 1, check if the cards have the same value
            if (inp.length() == 1) {
                // exit condition
                flag = true;
                // swap the card
                Card card2 = player.swapWithHand(card, inp[0]);
                // add to folddeck
                player.setPlayerValue(card2.getIntValue());
                discardCard(card2, player, comp1, comp2);
                msg += card2.printCard();
            } else {
                bool flag2 = true;
                for (char c : inp) {
                    // check if the values are the same
                    if (player.showHand()[c - 'A'].getIntValue() != player.showHand()[inp[0] - 'A'].getIntValue()) {
                        flag2 = false;
                    }
                    // check if the card is visible so that the player is not randomly guessing
                    if (!player.isKnown(player.showHand()[c - 'A'])) {
                        flag2 = false;
                    }
                }
                if (flag2) {
                    // exit condition
                    flag = true;
                    // add to folddeck and delete from hand
                    inp = sortString(inp);
                    for (char c : inp) {
                        msg += player.showHand()[c - 'A'].printCard();
                        player.setPlayerValue(player.showHand()[c - 'A'].getIntValue());
                        discardCard(player.showHand()[c - 'A'], player, comp1, comp2);
                        player.delChoice(player.showHand()[c - 'A']);
                    }
                    // add swapped card
                    player.addCardToHand(card);
                    // decrease number of choices
                    player.delNumChoice(inp.length() - 1);
                }
            }
            
            // print error message
            if (!flag) {
                cout << "Invalid Input. Try again." << endl;
            }

        } while (!flag);
        
        msg += ".";
        printMsg(msg);

    }

    // computer action in a turn
    void computerAction (Player& comp, Player& player, Player& comp1, Player& comp2, int& cabo, int& turn) {
        /*REVISION*/
        if (comp.showName() == "CP1") {
            printTable(player, comp1, comp2, roundNum, 6, 1);
        } else {
            printTable(player, comp1, comp2, roundNum, 6, 2);
        }
        // sleep for a few seconds.
        sleep(3);
        
        if (cabo == -1 && comp.knownAllCards() && comp.calHandValue() <= computerCaboCondition(turn)) {
            // computer call cabo
            cout << comp.showName() << " called CABO!" << endl;
            cabo = 3;
            comp.setPlayerValue(-1);
        } else if (!(folddeck.size() <= 1) && ((folddeck.back().getIntValue() <= 3 && comp.maxKnownHandValue(folddeck.back()) >= 70) || comp.cardInHand(folddeck.back()))) {
            // !(folddeck.size() <= 1) check if the folddeck is empty. Note that there is a (' ', ' ') at the beginning.
            // folddeck.back().getIntValue() <= 3 check if the last card is valuable, number based on experience.
            // comp.maxKnownHandValue(folddeck.back()) >= 70 check the defined value, number based on experience.
            // comp.cardInHand(folddeck.back()) check if the card is same with hand.
            
            // draw the card from the fold deck
            Card card = drawCard(folddeck);
            comp.addToKnown(card);
            // swap with hand
            compSwapWithHand(comp, card, player, comp1, comp2, "drop");

        } else {
            // draw a new card from the draw deck
            Card card = drawCard(deck);
            comp.addToKnown(card);
            bool skillUsed = false;

            // decide whether to use skill of cards
            int cardValue = card.getIntValue();
            if (cardValue == 7 || cardValue == 8) {
                if (!comp.knownAllCards()) {
                    // play the card
                    char choice = 'A';
                    for (int i = 0; i < comp.showAvaChoice(); i++) {
                        if (!comp.isKnown(comp.showHand()[i])) {
                            choice = 'A' + i;
                            comp.addToKnown(comp.showHand()[i]);
                            break;
                        }
                    }
                    // print the message
                    string msg = comp.showName() + " draw and play " + card.printCard() + ", and used the power to peek at its card " + choice + ".";
                    printMsg(msg);
                    // set the skill used to end the turn
                    skillUsed = true;
                }
            } else if (cardValue == 9 || cardValue == 10) {
                // check if there exist 9 or T in hand
                bool flag1 = false; // true if there is a known card = cardValue
                for (Card handc : comp.showHand()) {
                    if (handc.getIntValue() == cardValue && comp.isKnown(handc)) {
                        flag1 = true;
                    }
                }
                // check the target, NULL if all cards are known
                Player spyTarget = player;
                if (comp.showName() == "CP1") {
                    // preferentially choose the player before itself
                    spyTarget = chooseSpyTarget(comp, player, comp2);
                } else {
                    spyTarget = chooseSpyTarget(comp, comp1, player);
                }

                if (!flag1 && (spyTarget.showName() != comp.showName())) {
                    // perform spy
                    int pos = chooseSpyCard(comp, spyTarget);
                    comp.addToKnown(spyTarget.showHand()[pos]);

                    // print message
                    char p = 'A' + pos;
                    string msg = comp.showName() + " draw and play " + card.printCard() + ", and used the power to spy on " + spyTarget.showName() + "'s card " + p + ".";
                    printMsg(msg);

                    // set the skill used to end the turn
                    skillUsed = true;
                }
            } else if (cardValue == 11 || cardValue == 12) {
                // check if there exist J or Q in hand
                bool flag1 = false; // true if there is a known card = cardValue
                for (Card handc : comp.showHand()) {
                    if (handc.getIntValue() == cardValue && comp.isKnown(handc)) {
                        flag1 = true;
                    }
                }
                // decide if under cabo situation now
                bool isCabo;
                if (cabo == -1) {
                    isCabo = false;
                } else {
                    isCabo = true;
                }
                // check the target, NULL if all other players are not valuable targets
                Player swapTarget = player;
                if (comp.showName() == "CP1") {
                    swapTarget = chooseSwapTarget(comp, player, comp2, isCabo);
                } else {
                    swapTarget = chooseSwapTarget(comp, player, comp1, isCabo);
                }
                if (!flag1 && (swapTarget.showName() != comp.showName())) {
                    // randomly choose a card from swapTarget's hand
                    random_device rd;
                    mt19937 rng(rd());
                    uniform_int_distribution<int> uni(0, swapTarget.showAvaChoice() - 1);
                    int pos = uni(rng);
                    char pos_char = pos + 'A';
                    // perform blind swap
                    int selfpos = comp.findHandValueWithoutSame(comp.maxHandValueWithoutSame(isCabo));
                    char selfpos_char = selfpos + 'A';
                    Card card2 = comp.swapWithHand(swapTarget.showHand()[pos], selfpos_char);
                    if (swapTarget.showName() == player.showName()) {
                        player.swapWithHand(card2, pos_char);
                    } else if (swapTarget.showName() == comp1.showName()) {
                        comp1.swapWithHand(card2, pos_char);
                    } else {
                        comp2.swapWithHand(card2, pos_char);
                    }
                    // print message
                    string msg = comp.showName() + " draw and play " + card.printCard() + ", and use the power to swap its card " + selfpos_char + " with " + swapTarget.showName() + "'s card " + pos_char + ".";
                    printMsg(msg);
                    // set the skill used to end the turn
                    skillUsed = true;
                }
            }

            if (!skillUsed) {
                // decide whether to swap with hand
                if (cardValue * 10 < comp.maxKnownHandValue(card)) {
                    // swap with hand
                    compSwapWithHand(comp, card, player, comp1, comp2, "draw");
                } else {
                    // fold the card
                    string msg = comp.showName() + " draw " + card.printCard() + " and fold it directly.";
                    printMsg(msg);
                    // add to folddeck
                    comp.setPlayerValue(card.getIntValue());
                    discardCard(card, player, comp1, comp2);
                }
            } else {
                // discard the card used
                discardCard(card, player, comp1, comp2);
            }

        }
    }

    // computer swap with hand
    void compSwapWithHand (Player& comp, Card& card, Player& player, Player& comp1, Player& comp2, string deckName) {
        // get choice
        string choice = comp.getChoice(card);

        string cardOutput;
        if (player.isKnown(card)) {
            cardOutput = card.printCard();
        } else {
            cardOutput = "\uFFFD\uFFFD";
        }

        string msg = comp.showName() + " draw a card " + cardOutput + " from the " + deckName + " deck, and swap with its " + choice + ".";
        printMsg(msg);
        // swap
        if (choice.length() == 1) {
            // swap with one card
            Card card2 = comp.swapWithHand(card, choice[0]);
            // add to folddeck
            comp.setPlayerValue(card2.getIntValue());
            discardCard(card2, player, comp1, comp2);
        } else {
            // swap with multiple cards
            // sort the choice from larger ones to smaller ones
            choice = sortString(choice);

            // add to folddeck and delete from hand
            for (char c : choice) {
                comp.setPlayerValue(comp.showHand()[c - 'A'].getIntValue());
                discardCard(comp.showHand()[c - 'A'], player, comp1, comp2);
                comp.delChoice(comp.showHand()[c - 'A']);
            }
            // add swapped card
            comp.addCardToHand(card);
            comp.delNumChoice(choice.length() - 1);
            
        }
    }

    // computer choose spy target
    Player chooseSpyTarget (Player comp, Player oth1, Player oth2) {
        // return if some card in oth1's hand is unknown
        for (Card card : oth1.showHand()) {
            if (!comp.isKnown(card)) {
                return oth1;
            }
        }
        // return if some card in oth2's hand is unknown
        for (Card card : oth2.showHand()) {
            if (!comp.isKnown(card)) {
                return oth2;
            }
        }
        // if all cards are known, return NULL
        return comp;

    }

    // computer choose card to spy on
    int chooseSpyCard (Player comp, Player target) {
        for (int i = 0; i < target.showAvaChoice(); i++) {
            if (!comp.isKnown(target.showHand()[i])) {
                return i;
            }
        }
        return 0;
    }

    // computer choose swap target by considering the value of each player
    Player chooseSwapTarget (Player comp, Player oth1, Player oth2, bool isCabo) {
        if ((oth1.showPlayerValue() <= oth2.showPlayerValue()) && (comp.maxHandValueWithoutSame(isCabo) > 10 * oth1.showPlayerValue())) {
            // return if oth1's playerValue is low, then oth1 is set as the target
            return oth1;
        } else if ((oth2.showPlayerValue() <= oth1.showPlayerValue()) && (comp.maxHandValueWithoutSame(isCabo) > 10 * oth2.showPlayerValue())) {
            // return if oth2's playerValue is low, then oth2 is set as the target
            return oth2;
        }
        // if the conditions are not met, return NULL
        return comp;
    }

    // computer call cabo condition
    int computerCaboCondition (int turn) {
        // based on experiment
        vector<int> condition = {27, 23, 20, 18, 16, 14, 12, 11, 9, 7, 7, 6, 6, 5, 5, 4, 3, 3};
        if (turn >= condition.size()) {
            return 2;
        } else {
            return condition[turn];
        }
    }


    // sort the input string from larger letters to smaller letters
    string sortString (string str) {
        sort(str.rbegin(), str.rend());
        return str;
    }

    // add history and print messages
    void printMsg (string msg) {
        history.push_back(msg);
        cout << msg << endl;
    }

    // calculate the scores when round end
    void calculateScore (Player& player, Player& comp1, Player& comp2) {
        bool caboFlag = true;
        // check if there exist QQKK
        checkQQKK(player, comp1, comp2, caboFlag);
        checkQQKK(comp1, comp2, player, caboFlag);
        checkQQKK(comp2, player, comp1, caboFlag);
        // check if QQKK present
        if (caboFlag) {
            if (cabo == 0) {
                // check cabocaller
                Player caboCaller = seq.back();
                // add to each player's scoreboard
                if (caboCaller.showName() == player.showName()) {
                    addScores(player, comp1, comp2);
                } else if (caboCaller.showName() == comp1.showName()) {
                    addScores(comp1, player, comp2);
                } else {
                    addScores(comp2, player, comp1);
                }
            } else {
                // the round ends due to running out of cards in deck
                addScores(player, comp1, comp2, false);
            }
        }
    }

    // check if QQKK exist
    void checkQQKK (Player& p1, Player& p2, Player& p3, bool& caboFlag) {
        if (p1.calHandValue() == 50) {
            p1.addToScoreboard(0);
            p2.addToScoreboard(50);
            p3.addToScoreboard(50);
            caboFlag = false;
        }
    }

    // check if the cabo caller has smallest hand
    bool isMinHand (Player caboCaller, Player player, Player comp1, Player comp2) {
        // define the hand values
        int caboHandValue;
        int playerHandValue = player.calHandValue();
        int comp1HandValue = comp1.calHandValue();
        int comp2HandValue = comp2.calHandValue();

        if (caboCaller.showName() == player.showName()) {
            caboHandValue = playerHandValue;
        } else if (caboCaller.showName() == "CP1") {
            caboHandValue = comp1HandValue;
        } else {
            caboHandValue = comp2HandValue;
        }
        
        // return whether caboCaller's hand value is the smallest
        return ( caboHandValue <= player.calHandValue() && caboHandValue <= comp1.calHandValue() && caboHandValue <= comp2.calHandValue() );
    }

    // add scores for each player
    void addScores (Player& cur, Player& oth1, Player& oth2, bool caboEnd = true) {
        if (caboEnd == false) {
            cur.addToScoreboard(cur.calHandValue());
        } else if (isMinHand(cur, cur, oth1, oth2)) {
            cur.addToScoreboard(0);
        } else {
            cur.addToScoreboard(cur.calHandValue() + 10);
        }
        oth1.addToScoreboard(oth1.calHandValue());
        oth2.addToScoreboard(oth2.calHandValue());
    }

    // print sumHistory, used for testing the best cabo value
    void printSumHistory () {
        for (int i : sumHistory) {
            cout << i << " ";
        }
        cout << endl;
    }

};





// print guide
void printGuide () {
    string str;
    cout << "---------- GUIDE ----------" << endl;
    cout << endl;
    cout << "In the game of Cabo, you are competing with two other players to get as closer to Cabo, the unicorn, as possible." << endl;
    cout << "The value of the cards represents the distance between you and Cabo." << endl;
    cout << "Thus, the smaller the card value is, the better." << endl;
    cout << "JO and jo are jokers, they represent 0." << endl;
    cout << "T, J, Q, K are 10, 11, 12, 13, respectively." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "You'll play a few rounds of game with the other two players." << endl;
    cout << "At the beginning of each round, each player is distributed with 4 random cards." << endl;
    cout << "Each player is allowed to peek two of its cards in hand." << endl;
    cout << "You can do this by entering two positions of your cards, such as 'BC'." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "Now the round starts with a random player. Each player take turn to do some actions." << endl;
    cout << "In your turn, you can do one of the following." << endl;
    cout << "Entering 'D' to draw a card from the draw deck, which is random." << endl;
    cout << "   You may play this card and put it in the fold deck. You may use the special skills of the card." << endl;
    cout << "   You may swap this card with your hand. You may swap with multiple cards in hand if they are the same." << endl;
    cout << "Entering 'F' to draw a card from the fold deck, which is known." << endl;
    cout << "   You should only draw this folded card when it is small or meets your need. You can swap it with your hand." << endl;
    cout << "Entering 'C' to call Cabo." << endl;
    cout << "   If you call Cabo, your turn ends directly." << endl;
    cout << "   Each other player gets one more turn, and the round ends." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "Card with value 7~8 has the skill to peek: you may view one of your own facedown cards." << endl;
    cout << "Card with value 9~10 has the skill to spy: you may view a facedown card from another player." << endl;
    cout << "Card with value 11~12 has the skill to swap: you may exchange one of your cards with one from another player." << endl;
    cout << "   Note that the cards to swap can either be face up or down." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "The round ends if someone called Cabo and each other players take another turn or the draw deck is depleted." << endl;
    cout << "Your score for the round is the sum of your remianing cards." << endl;
    cout << "However, if you called Cabo and have the lowest sum (or tied), you score 0 points." << endl;
    cout << "If you called Cabo and do not have the lowest sum, you are penalized with 10 points plus the sum of cards." << endl;
    cout << "Remind that the smaller your total score is, the better." << endl;
    cout << endl;
    cout << "There is one special case:" << endl;
    cout << "If you have QQKK in your hand when the round ends, you score 0 points while others all score 50 points." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "The game ends when any player has more than 100 points." << endl;
    cout << "At that point, the player with lowest hand value wins." << endl;
    cout << "There is also a default skill that each player can use only once." << endl;
    cout << "If you have exactly 100 points, your total score is reset to 50 points. Take the chance." << endl;
    cout << endl;
    cout << "Type anything to continue: ";
    cin >> str;
    cout << "Now you know how to play Cabo!" << endl;
    cout << "If you still have questions, don't worry as there is complete guide within the game." << endl;
    cout << "If you are ready, enter 'START'." << endl;
}

// print welcome messages
string toMiddle (string text, int targetLength) {
    int textLength = text.length();
    int a = (targetLength - textLength) / 2;
    int b = (targetLength - textLength + 1) / 2;
    return string(a, ' ') + text + string(b, ' ');
}
void Welcome () {
    cout << "\033[2J\033[1;1H";
    cout << "-----------------------------" << endl;
    cout << endl;
    cout << " /---          |---\\ " << endl;
    cout << " |       /\\    |   |  /---\\ " << endl;
    cout << " |      /  \\   |---  |     | " << endl;
    cout << " |     /----\\  |   | |     | " << endl;
    cout << " \\--- /      \\ |---/  \\---/ " << endl;
    cout << endl;
    cout << "-----------------------------" << endl;
    
    cout << "Welcome to the card game Cabo!" << endl;
    cout << toMiddle("-- START --", 30) << endl;
    cout << toMiddle("-- GUIDE --", 30) << endl;
    cout << toMiddle("--  QUIT --", 30) << endl;
}

// ask users to input a name
string stringToUpper (string a) {
    string result = "";
    for (int i=0; i < a.length(); i++) {
        result += toupper(a[i]);
    }
    return result;
}
string askForName() {
    cout << "Welcome to the game of CABO." << endl;
    cout << "You, together with CP1 and CP2, are on a way to find the legendary unicorn CABO." << endl;
    cout << endl;
    cout << "Now create a name for your warrior avatar." << endl;
    cout << "The name should have 2~8 characters" << endl;
    cout << endl;
    string name;
    cout << "Enter warrior name: ";
    cin >> name;

    // check if name has a length 2~8 or used by computers
    while (name.length() < 2 || name.length() > 8 || name == "CP1" || name == "CP2") {
        if (stringToUpper(name) == "CP1" || stringToUpper(name) == "CP2") {
            cout << "This name is used by computers. Try again." << endl;
        } else {
            cout << "Invalid name. Try again." << endl;
            cout << "The name should have 2~8 characters" << endl;
        }
        cout << "Warrior Name: ";
        cin >> name;
    }
    return name;   
}

// check if any player has score larger than 100
bool gameEnd (Player player, Player comp1, Player comp2) {
    if (player.showTotalScore() >= 100 || comp1.showTotalScore() >= 100 || comp2.showTotalScore() >= 100)
        return true;
    return false;
}

// print the scoreboard on screen
void printAllScoreboard(Player& player, Player& comp1, Player& comp2) {
    cout << "Please check the scoreboard." << endl;
    cout << "Player| Scores" << string(3 * player.showScoreboard().size(), ' ') << "|Total" <<  endl;
    cout << string(6, '-') << "+" << string(3 * player.showScoreboard().size() + 7, '-') << "+" << string(5, '-') << endl;
    cout << player.printScoreboard() << endl;
    cout << comp1.printScoreboard() << endl;
    cout << comp2.printScoreboard() << endl;
}

// print a ASCII unicorn
void printUnicorn () {
    string unicorn = "\n\n     `\\\n       \\\\,\n        \\\\\\,^,.,,.\n         ,;7~((\\))`;;,,\n        ,(@') ;)`))\\;;',\n        )  . ),((  ))\\;,\n        /;`,,/7),)) )) )\\,,      ,,,... ,\n       (& )`   (,((,((;( ))\\,_,,;'`    `\\\\,\n        `\"    ` ), ))),/( (            `)\\,\n               '1/';/;  `               ))),\n                (, (     /         )    ((/,\n               / \\                /     ((('\n              ( 6--\\%  ,>     ,,,(CABO /'))\\'\n               \\,\\,/ ,/`----~`\\   \\    >,))))'\n                 \\/ /          `--7>' /((((('\n                 (,9             // /'('((\\\\\\,\n                     \\ \\,,         (/,/   '\\`\\\\'\\\n                   `\\_)1        (_)Kk    `\\`\\\\`\\\n                     `\\|         \\Z          `\\\n                       `          \"            `\n\n";
    cout << unicorn << endl;
}

// find the winner and output
void printWinner (Player& player, Player& comp1, Player& comp2) {
    // clear screen
    cout << "\033[2J\033[1;1H";
    // print unicorn
    printUnicorn();
    // print final scoreboard
    printAllScoreboard(player, comp1, comp2);
    cout << "Warriors, you've all been through the challenges." << endl;
    cout << "It is my pleasure to annouce that" << endl;
    Player winner = player;
    if (player.showTotalScore() <= comp1.showTotalScore() && player.showTotalScore() <= comp2.showTotalScore()) {
        winner = player;
    } else if (comp1.showTotalScore() <= player.showTotalScore() && comp1.showTotalScore() <= comp2.showTotalScore()) {
        winner = comp1;
    } else {
        winner = comp2;
    }
    cout << winner.showName() << " is the winner to find CABO!" << endl;
    cout << "Welcome to play the game again." << endl;
}

// start the game
void InitiateGame () {
    // clear screen
    cout << "\033[2J\033[1;1H";
    // ask user to input a name for the player
    /*REVISION*/
    // string playerName = "you";
    string playerName = askForName();
    // create 3 player object
    Player player(stringToUpper(playerName), "player");
    Player comp1("CP1", "computer");
    Player comp2("CP2", "computer");
    // create the round vector to store all rounds
    vector<Round> roundList;
    int roundNum = 1;

    // print the initial scoreboard
    cout << endl;
    cout << "Warrior, please check the initial scoreboard." << endl;
    printAllScoreboard(player, comp1, comp2);
    cout << endl;

    string inp;
    cout << "Enter anything to continue: ";
    cin >> inp;

    while (!gameEnd(player, comp1, comp2)/* && roundNum < 2*/) {
        cout << string(30, '-') << endl;
        // define a new round
        Round round(roundNum, player, comp1, comp2);

        // play the round
        round.initiateDeck(player, comp1, comp2);
        round.peekStage(player, comp1, comp2);
        /*REVISION*/
        // player.setAllKnown(round.showFullDeck());
        round.startRound(player, comp1, comp2);

        // round Ends, calculate and store the round
        player.setAllKnown(round.showFullDeck());
        round.printTable(player, comp1, comp2, roundNum, 5);        
        round.calculateScore(player, comp1, comp2);
        printAllScoreboard(player, comp1, comp2);
        // round.printSumHistory();
        roundNum++;
        roundList.push_back(round);

        string inp;
        cout << "Enter anything to continue: ";
        cin >> inp;

        cout << string(30, '-') << endl;
    }

    // game end. print the winner
    printWinner(player, comp1, comp2);
    
}




// main function
int main () {
    // print welcome messages
    Welcome();
    
    // get input
    string inp;
    do {
        cout << "Enter 'START' 'GUIDE' or 'EXIT' to continue: ";
        cin >> inp;
        inp = stringToUpper(inp);
        if (inp == "GUIDE") {
            printGuide();
        } else if (inp == "EXIT") {
            exit(0);
        }
    } while (inp != "START");
    // start the game
    InitiateGame();

    return 0;
}