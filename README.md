# ENGG1340-GP

## Team members

Deng Qiwen, Liu Zihao, Mo Junbo, Wang Hechen, Zhang Kezhen

## Introduction

## Game rules

## Implemented features

### 1. Computer Player
Without the use of any neural network, we designed a mathematical logic that a computer can follow to make a move in its turn. The computer will, act like a real player, detect all information it know on the board and make a proper movement. It has a winning probability similar to that of a proficient player.

### 2. Autmoatic Hint
Whenever the player is entering instructions, the code detects the available moves for player and display on the side of the board as a hint to human player.

### 3. Distinguishable Cards
In the original Cabo game, players are required to memorize the cards. While competing with computers, however, comuters can always have the memory of the cards they should have known. Thus, we display the cards to player once they have been peeked by human player.

### 4. Simulation of Playing Experience
When playing Cabo in reality, players need to think and react. We simulate this process and let computer "think" for a while before they make any decision. We also record their move in the history and display the real-time board to players.

## Coding requirements

### 1. Data structures -- Class
The game defines three classes, `Card`, `Player`, and `Round`, to encapsulate the data and behavior related to cards, players, and rounds in the game.

### 2. STL containers
The game utilize vector to store and manipulate collection of objects. For example, a `vector<Player>` queue is defined to store the sequence of player's turns. At each player's turn, it is popped from the sequence, and is added back to the queue after its turn.

### 3. Operator Overloading
For the cards, **<**, **==**, and **>** are defined for comparing their value.

### 4. File IO
The process of each round of game is recorded and stored in a log file. This part of code is disguised since they are not essential for game play. The log file can be used to calculate player's capability with the use of exponential regression.

## Non-standard C/C++ libraries (if have)
None

## Compilation and execution instructions

1. Type **make game**
2. Type **./game**

## Problem Collection for Final Assessment

### 1. Shuffling a deck (solved) ()
initiateDeck() ???

### 2. Displaying visible cards (solved) ()
isKnown(), showOneCard() ???

### 3. Better Display (solved) ()
clear screen & history ???

### 4. Input Validation (solved) ()
easyCheck() ???

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

### 6. Computer player deciding when to call Cabo
Determining the optimal time to call Cabo is a critical decision for the computer player. Initially, I allowed the computer to call Cabo whenever its total hand value was less than 10. However, this approach proved to be a failure as the computer lost almost all rounds after calling Cabo. This happens as both computers have rather similar hand values and the one not calling cabo get another round of chance to adjust its cards.

In another class, I learned about Monte Carlo Simulation, which inspired me to take a different approach. I decided to let the computer play for a million rounds by itself and gather data to analyze the best conditions for calling Cabo. After processing the collected data, I created a list stored in the function `computerCaboCondition()`. This list provides the computer player with guidelines for calling Cabo, resulting in a winning rate of approximately 50% in the game.



