#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int rollDie(void);
void printMenu(int *pOption);
void printRules(void);
void evalMenuOption(int menuOption);
int menu(void);
void holdOrRoll(int *pscorecard, int dice[], int scorecard[]);
void rollRound(int dice[]);
void displayDice(int dice[]);
void rerollDice(int dice[]);
int evalPoints(int diceHand[], int spot);
void bubbleSort(int *pdice, int size);
void assignHand(int *pscorecard, int dice[]);
void evalValidity(int *pscorecard, int spot, int dice[]);
int sumUpperHalf(int scorecard[]);
int sumLowerHalf(int scorecard[]);
int checkFullScorecard(int scorecard[]);
void printScorecard(int scorecard[]);
int sumScorecard(int scorecard[]);
void determineWinner(int player1score, int player2score);