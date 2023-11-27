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
The game defines three classes, **Card**, **Player**, and **Round**, to encapsulate the data and behavior related to cards, players, and rounds in the game.

### 2. STL containers
The game utilize vector to store and manipulate collection of objects. For example, a vector<Player> queue is defined to store the sequence of player's turns. At each player's turn, it is popped from the sequence, and is added back to the queue after its turn.

### 3. Operator Overloading
For the cards, <, ==, and > are defined for comparing their value.

### 4. File IO
The process of each round of game is recorded and stored in a log file. This part of code is disguised since they are not essential for game play. The log file can be used to calculate player's capability with the use of exponential regression.

### 5.

## Non-standard C/C++ libraries (if have)
None

## Compilation and execution instructions

1. Type **make game**
2. Type **./game**

## Problem Collection for Final Assessment

### 1. Shuffling a deck (solved) ()
???

### 2. Displaying visible cards (solved) ()
???

### 3. Computer player deciding which card to swap (solved) (Wang Hechen)


