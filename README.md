# ENGG1340-GP

## Team members

Deng Qiwen, Liu Zihao, Mo Junbo, Wang Hechen, Zhang Kezhen

## Introduction

## Game rules

## Implemented features

### 1.Exchange Multiple Cards

### 2.Card Special Ability

### 3.KAMIKAZE

### 4.Round END

### 5.Scoring

### 6.Game End

### 7.Score Reset

## Coding requirements

### 1. Data structures -- Class
The game defines two classes, Card, Player, and Round, to encapsulate the data and behavior related to cards, players, and rounds in the game.

### 2. STL containers
The game utilize vector to store and manipulate collection of objects. For example, a vector<Player> queue is defined to store the sequence of player's turns. At each player's turn, it is popped from the sequence, and is added back to the queue after its turn.

### 3. Operator Overloading
For the cards, <, ==, and > are defined for comparing their value.

### 4. File IO
The process of each round of game is recorded and stored in a log file. This part of code is disguised since they are not essential for game play. The log file can be used to calculate player's capability with the use of exponential regression.

### 5.

## Non-standard C/C++ libraries (if have)

## Compilation and execution instructions

1. Type **make game**
2. Type **./game**

## Problem Collection for Final Assessment
