/*
Yahtzee
*/
#include "functions.h"

int main(void)
{
	int checker = menu();
	int dice[5] = { 0 }, scorecard[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		scorecard1[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		scorecard2[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		*pscorecard1 = scorecard1, *pscorecard2 = scorecard2, playerCheck = 1, scorecardCheck = 0,
		player1score = 0, player2score = 0;
	
	while (checker != 1) //checker = 1 when the user doesn't want to play or when the game is over
	{
		if (playerCheck % 2 == 1) // uses
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPLAYER 1's TURN\n\n");
			printScorecard(scorecard1);
			rollRound(dice);	//rolls the round
			displayDice(dice);	//displays dice
			holdOrRoll(pscorecard1, dice, scorecard1);	//asks player if they want to reroll any dice or not
		}	
		else if (playerCheck % 2 == 0)
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPLAYER 2's TURN\n\n");
			printScorecard(scorecard2);
			rollRound(dice);	//rolls the round
			displayDice(dice);	//displays dice
			holdOrRoll(pscorecard2, dice, scorecard2);
		}
		else
			printf("\n\n\nSOMETHING WENT WRONG\n\n\n");
		playerCheck++;
		checker = checkFullScorecard(scorecard2);
	}//end while
	player1score = sumScorecard(scorecard1);
	player2score = sumScorecard(scorecard2);

	if (player1score != -12 && player2score != -12)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPLAYER 1 FINAL SCORE:\n\n%d\n\n\nPLAYER 2 FINAL SCORE:\n\n%d\n", player1score, player2score);
		determineWinner(player1score, player2score);
	}
}