# ENGG1340-GP

## Team members

Deng Qiwen, Liu Zihao, Mo Junbo, Wang Hechen, Zhang Kezhen

## Introduction
In the game of Cabo, you are competing with two other players to get as closer to Cabo, the unicorn, as possible. The sum of your cards represent your distance from him.

Cards have different values:
- JO and jo are jokers, which represent 0.
- A, T, J, Q, K are 1, 10, 11, 12, 13, respectively.
- Other cards are simplely presents the number shown on it, such as 2,3,4.

The player closest to CABO at the end of the game wins.

## Game rules
In the beginning of the game, you may type 'GUIDE' to know brief introduction of game rules, 'START' to directly play the game, or 'EXIT' to stop.

### SETUP
Shuffle the deck of cards. Deal 4 cards labeled as ABCD to each player facedown in a line. Place the draw deck facedown in the center of the table, and place the top card faceup next to the draw deck to form a fold deck.

Input any two positions of your cards(i.e., AB, AC), to secretly look at them. Player cards may not change location. Game start from random player.

### Gameplay
Beginning with the start player, take turns clockwise. On your turn, draw a card from the draw deck or fold deck, or call CABO.

#### Draw from the draw deck
Enter 'D' to draw from the draw deck. If you take the top card from the draw deck, look at it and do one of the following:
1)	Enter 'N' to drop the card into the fold deck. If the card has a special ability, you may use it.
2)	Enter 'S' to swap one or more of your cards with the card you drew. Put exchanged cards faceup into the fold deck, and put the new card facedown in an exchanged card’s place. More details on how to exchange multiple matching cards are shown in “Exchange multiple cards”.
   
#### Draw from the fold deck
Enter 'F' to draw from the fold deck. If you take the top card from the fold deck:
Exchange one or more of your cards with cards you drew. Put exchanged cards faceup into the fold deck, and put the new card faceup in an exchanged card’s place.

#### Call CABO
Enter 'C' to call CABO. If you call CABO, your turn ends. Each other player gets one more turn, and then the round ends.

### Exchange multiple cards
To exchange multiple cards, all exchanged cards must have the same value (i.e., all 6s).

### Card special abilities
If you draw a card with an ability from the draw deck, you may place it in the fold deck and use its ability. The abilities:
- 7-8 Peek: Secretly view one of your own facedown cards.
- 9-10 Spy: Secretly view a facedown card from any other player.
- 11-12 Swap: Exchange one of your cards with a card from another player without     flipping either card over.

### Kamikaze
If a player ends the round with exactly two 13s and two 12s without any other cards, they score 0 points and each other player scores 50 points.

### Round end
The round ends when either one of the following events occurs:
1)	One player has called CABO and each other player takes one more turn.
2)	The draw deck is depleted.
If the game did not end, shuffle the cards and play another round. The player with the lowest score in the previous round is the new start player. In case of a tie, the player closest to the previous start player becomes the new start player.

### Scoring
Your score for the round is the sum of your remaining cards.
However, if you called CABO and have the lowest sum ( or are tied for it), you score 0 points. If you called CABO and do not have the lowest sum, you score the sum of your cards plus 10 more points. Record each player’s score for each round, and add it to the sum of the previous rounds.

### Game end
The game ends when one player has more than 100 points. The player with the lowest score wins. In case of a tie, the tied player with the lowest score in the last round wins.

### Score reset
If a player’s total score is ever exactly 100 points, their score is reset to 50 points. This may only happen one time per player per game.

## Implemented features

### 1. Computer Player
Without the use of any neural network, we designed a mathematical logic that a computer can follow to make a move in its turn. The computer will, act like a real player, detect all information it know on the board and make a proper movement. It has a winning probability similar to that of a proficient player. The complete process is in `computerAction()`.

### 2. Autmoatic Hint
Whenever the player is entering instructions, the code detects the available moves for player and display on the side of the board as a hint to human player. The function to achieve this is `showGuide()`.

### 3. Distinguishable Cards
In the original Cabo game, players are required to memorize the cards. While competing with computers, however, comuters can always have the memory of the cards they should have known. Thus, we display the cards to player once they have been peeked by human player.

### 4. Simulation of Playing Experience
When playing Cabo in reality, players need to think and react. We simulate this process and let computer "think" for a while before they make any decision. We also record their move in the history and display the real-time board to players. We used `sleep()` to let computer act as if it is thinking.

## Coding requirements

### 1. Data structures -- Class
The game defines three classes, `Card`, `Player`, and `Round`, to encapsulate the data and behavior related to cards, players, and rounds in the game.

### 2. STL containers
The game utilize vector to store and manipulate collection of objects. For example, a `vector<Player>` queue is defined to store the sequence of player's turns. At each player's turn, it is popped from the sequence, and is added back to the queue after its turn.

### 3. Operator overloading
For the cards, **<**, **==**, and **>** are defined for comparing their value.

### 4. File IO
The process of each round of game is recorded and stored in a log file. This part of code is disguised since they are not essential for game play. The log file can be used to calculate player's capability with the use of exponential regression.

### 5. Random number generator
To make the game changeful, we add random numbers in various places to make the game play a natural process.

## Non-standard C/C++ libraries (if have)
None

## Compilation and execution instructions

1. Type **make game**
2. Type **./game**

## Problem Collection for Final Assessment

### 1. Shuffling a deck (solved) ()
initiateDeck() ???

### 2. Displaying visible cards (solved) (Deng Qiwen)
To display visible cards to players is a key funcion that need to be achieved in this game. To figure out which card is visible for players, I wrote `isKnown()` to check each card in player's hand is defined known or not. This function is achieved by return a true value when array knowncards[i] equals to card[i], and return false when they are not equal. Then, for known cards, `showOneCard()` is designed to make knowncards visible for players, including its number and color.

### 3. Better Display (solved) (Mo Junbo)
In order to keep the presentation tidy and help players see useful information clearly, the program cleans the screen after each appropriate command and retains the last five decisions players made.

For clear the screen, I wrote `cout << "\033[2J\033[1;1H";` to remove the unuseful informations, and use a float `... ...` sign to indicate the part that is cleared.

In addition, I wrote the string `history` and through printed it out to show the last five pieces of information about the decisions players made.

### 4. Input Validation (solved) (Liu Zihao)
In order to check the input. I wrote the easyCheck to make sure whether the input is present in a vector of characters validChars. It converts input to uppercase before checking. If it is found in validChars, it returns true; otherwise, it returns false. 
The getChoice function prompts the user for input and checks if the input is valid based on certain conditions. It keeps prompting the user until a valid input is entered. The conditions for a valid input are: 
1. The length of the input string is within the range specified by minLength and maxLength.
2. Every character in the input string is present in validChars.
3.  All characters in the input string are unique.

If the input meets all these conditions, the function returns the input string. Otherwise, it prints an error message and prompts the user again.

### 5. Computer player deciding which card to swap (solved) (Wang Hechen)
I implemented a computer player in my CABO game using a specific logic to determine which card(s) to swap with in its hand. This part proved to be quite challenging since players have the option to swap either a single card or multiple cards with the same value in CABO. To make the decision-making process easier for the computer player, I devised a special point system.

For known cards in the hand, I assigned a point value based on the following formula:
```
known card point = (card value * 10 + 1) * times of appearance
```
The unit digit of the point value represents the number of appearances of that card, while the tens digit indicates the card's value. This system ensures that cards with the same value have the same point value, while different cards have distinct values.

Let's take the example of a player's hand: **55T?**. Even for a human player, it would be challenging to determine the best move in this situation. However, with the point system, we can easily analyze the hand and make an informed decision.

- Point of the first card **5** = (5 * 10 + 1) * 2 = 102
- Point of the second card **5** = (5 * 10 + 1) * 2 = 102
- Point of card **T** = (10 * 10 + 1) * 1 = 101

As you can see, the unit digit of the point value represents the number of appearances, while the tens digit reflects the card's value. Furthermore, I introduced a specific range for unknown cards to ensure they are always distinct from any other cards including 69, 68, 67, and 66 if at most four unknown cards would present. In this case, the unknown card have a point of 69. The points are chosen between 60 and 70 because this is the expected value of any normal unknown card in a deck.

By assigning unique points to each card in the hand, the computer player can easily determine which card(s) to swap. It simply selects the card(s) with the highest point value(s) in the hand. In the example of **55T?**, the computer player would choose to swap the two 5s.

### 6. Computer player deciding when to call Cabo (solved) (Wang Hechen)
Determining the optimal time to call Cabo is a critical decision for the computer player. Initially, I allowed the computer to call Cabo whenever its total hand value was less than 10. However, this approach proved to be a failure as the computer lost almost all rounds after calling Cabo. This happens as both computers have rather similar hand values and the one not calling cabo get another round of chance to adjust its cards.

In another class, I learned about Monte Carlo Simulation, which inspired me to take a different approach. I decided to let the computer play for a million rounds by itself and gather data to analyze the best conditions for calling Cabo. After processing the collected data, I created a list stored in the function `computerCaboCondition()`. This list provides the computer player with guidelines for calling Cabo, resulting in a winning rate of approximately 50% in the game.



