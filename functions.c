#include "functions.h"

int rollDie(void)
{
	//srand((unsigned int)time(NULL));
	int dievalue = rand() % 6 + 1;
	return dievalue;
}
void rollRound(int dice[])
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++)
	{
		dice[i] = rollDie();
	}
}
void displayDice(int dice[])
{
	printf("\n");
	for (int i = 0; i < 5; i++)
	{
		printf("Die %d: %d\n", i + 1, dice[i]);
	}
}
void holdOrRoll(int *pscorecard, int dice[], int scorecard[])
{
	int roundCounter = 1;
	char yorn = '\0';
	while (roundCounter <= 3)
	{
		printf("Do you want to REROLL any of the dice? (Y or N) ");
		scanf(" %c", &yorn);
		switch (yorn)
		{
		case 'Y':
		case 'y':
			//ask what dice they want to reroll
			rerollDice(dice);
			break;
		case 'N':
		case 'n':
			assignHand(pscorecard, dice);
			roundCounter = 4; //if they don't want to change any of the dice they have to assign the roll to somewhere on the scorecard
			break;
		default:
			holdOrRoll(pscorecard, dice, scorecard);
		}//end switch
		displayDice(dice);
		roundCounter++;
	}//end while
	if (yorn == 'y' || yorn == 'Y')
		assignHand(pscorecard, dice); //since the player has completed their allotted rolls, they need to assign the dice
}
void rerollDice(int dice[])
{//asks how many dice they want to keep
	int reroll = 0, dieNumber = 0;
	printf("How many dice do you want to REROLL? ");
	scanf("%d", &reroll);

	if (reroll < 0 || reroll > 5)	//asks them again since they entered an invalid input
	{
		printf("ERROR: Invalid input\n");
		rerollDice(dice);
	}
	for (int i = 0; i < reroll; i++)
	{
		printf("Enter a die number that you want to REROLL: ");
		scanf("%d", &dieNumber);
		dice[dieNumber - 1] = rollDie();
	}
}
void assignHand(int *pscorecard, int dice[])
{
	int score = 0, spot = 0;
	printf("\n\nSCORECARD SPOTS\n\n1. Ones (Sum of dice showing a one)\n2. Twos\n3. Threes\n4. Fours\n5. Fives\n6. Sixes\n7. Three of a kind (Totals all dice)\n"
		"8. Four of a kind\n9. Full House (25 pts)\n10. Small Straight (four in a row, 30 pts)\n11. Large Straight (five in a row, 40 pts)\n"
		"12. Yahtzee (five of a kind, 50 pts)\n13. Chance (sum of dice)\n");
	printf("Enter number of spot where you want to store the score: ");
	scanf("%d", &spot);
	evalValidity(pscorecard, spot - 1, dice);	//evaulate if the spot is taken already, is bigger than 13, or less than 1
	score = evalPoints(dice, spot - 1);
	pscorecard[spot - 1] = score;
}
int evalPoints(int diceHand[], int spot) //assigns the proper score to the requested scorecard spot
{
	int points = 0, dice[5] = { 0, 0, 0, 0, 0 }, *pdice = dice;
	for (int i = 0; i < 5; i++)
	{
		dice[i] = diceHand[i];
	}
	bubbleSort(pdice, 5);
	switch (spot)
	{
	case 0: 
	case 1:
	case 2:
	case 3:
	case 4:
	case 5://ones, twos, threes, fours, fives, or sixes
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == spot + 1)
				points += dice[i];
		}
		break;
	case 6:
	case 7: //three or four of a kind
		if ((dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3]) ||
			(dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4]) ||
			(dice[0] == dice[1] && dice[1] == dice[2]) ||
			(dice[1] == dice[2] && dice[2] == dice[3]) ||
			(dice[2] == dice[3] && dice[3] == dice[4])) //checks for three or four of a kind
		{
			for (int i = 0; i < 6; i++) //adds total of all dice
			{
				points += dice[i];
			}
		}//end if
		else
			points = 0;
		break;
	case 8: //full house
		if ((dice[0] == dice[1] && dice[1] == dice[2] && dice[3] == dice[4]) ||
			(dice[0] == dice[1] && dice[2] == dice[3] && dice[3] == dice[4])) //checks for full house
			points = 25;
		else
			points = 0;
		break;
	case 9: //small straight
		if ((dice[1] == (dice[0] + 1) && dice[2] == (dice[0] + 2) && dice[3] == (dice[0] + 3)) ||
			(dice[3] == (dice[4] - 1) && dice[2] == (dice[4] - 2) && dice[1] == (dice[4] - 3))) //checks for small straight
			points = 30;
		else
			points = 0;
		break;
	case 10: //large straight
		if (dice[1] == (dice[0] + 1) && dice[2] == (dice[0] + 2) && dice[3] == (dice[0] + 3) && dice[4] == (dice[0] + 4))
			points = 40;
		else
			points = 0;
		break;
	case 11: //yahtzee
		if (dice[1] == dice[0] && dice[2] == dice[0] && dice[3] == dice[0] && dice[4] == dice[0])
			points = 50;
		else
			points = 0;
	case 12: //chance
		for (int i = 0; i < 5; i++) //sums all dice
		{
			points += dice[i];
		}
		break;
	}//end switch
	return points;
}
void evalValidity(int *pscorecard, int spot, int dice[])
{
	if (pscorecard[spot] != -1)
	{
		printf("\n\nERROR: scorecard spot already selected\n\n");
		assignHand(pscorecard, dice);
	}
}
void printMenu(int *pOption)
{
	printf("1. Print Game Rules\n2. Start a Game\n3. Exit\n");
	scanf("%d", pOption);
}
void printRules(void)
{
	printf("\n\n\nThe rules of Yahtzee:\n"
	"The challenge of the game is to outduel the other player by scoring the most points.\n"
		"Points are obtained by rolling five 6-sided die across thirteen rounds. During each round,\n"
		"each player may roll the dice up to three times to make one of the possible scoring combinations.\n"
		"Once a combination has been achieved by the player, it may not be used again in future rounds,\n"
		"except for the Yahtzee combination may be used as many times as the player makes the combination.\n"
		"Each scoring combination has different point totals. Some of these totals are achieved through the\n"
		"accumulation of points across rolls and some are obtained as fixed sequences of values.\n");
}
void evalMenuOption(int menuOption)
{
	switch (menuOption)
	{
	case 1:
		printRules();
		break;
	case 2:
		printf("Start game\n");
		break;
	case 3:
		printf("Exit\n");
		break;
	default:
		menu();
		break;
	}
}
int menu(void)								
{//returns 1 if the user wants to exit or 0 otherwise
	int menuOption = 0, *pMenuOption = &menuOption, returnval = -1;
	printMenu(pMenuOption);
	evalMenuOption(menuOption);
	switch (menuOption)
	{
	case 1:
		returnval = 1;
		menu();
		break;
	case 2:
		returnval = 0;
		break;
	case 3:
		returnval = 1;
		break;
	}
	return returnval;
}
void bubbleSort(int *pdice, int size)
{
	int temp = 0;
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (pdice[j] > pdice[j + 1])
			{
				temp = pdice[j];
				pdice[j] = pdice[j + 1];
				pdice[j + 1] = temp;
			}
		}
	}
}
int sumUpperHalf(int scorecard[])
{
	int sum = 0;
	for (int i = 0; i < 6; i++)
	{
		sum += scorecard[i];
	}
	if (sum >= 63)
		sum += 35;
	return sum;
}
int sumLowerHalf(int scorecard[])
{
	int sum = 0;
	for (int i = 7; i < 13; i++)
	{
		sum += scorecard[i];
	}
	return sum;
}
int sumScorecard(int scorecard[])
{
	int grandTotal = sumLowerHalf(scorecard) + sumUpperHalf(scorecard);
	return grandTotal;
}
int checkFullScorecard(int scorecard[])
{//returns 0 if theres still open spots in the scorecard or 1 if its full 
	int check = 1;
	for (int i = 0; i < 13; i++)
	{
		if (scorecard[i] == -1)
			check = 0;
	}
	return check;
}
void printScorecard(int scorecard[])
{
	printf("\n-1 points means its empty\n");
	printf("\nOnes: %d points", scorecard[0]);
	printf("\nTwos: %d points", scorecard[1]);
	printf("\nThrees: %d points", scorecard[2]);
	printf("\nFours: %d points", scorecard[3]);
	printf("\nFives: %d points", scorecard[4]);
	printf("\nSixes: %d points", scorecard[5]);
	printf("\nThree of a kind: %d points", scorecard[6]);
	printf("\nFour of a kind: %d points", scorecard[7]);
	printf("\nFull House: %d points", scorecard[8]);
	printf("\nSmall Straight: %d points", scorecard[9]);
	printf("\nLarge Straight: %d points", scorecard[10]);
	printf("\nYahtzee: %d points", scorecard[11]);
	printf("\nChance: %d points\n\n", scorecard[12]);
}
void determineWinner(int player1score, int player2score)
{
	if (player1score > player2score)
		printf("\n\nPLAYER 1 WINS");
	else if (player2score > player1score)
		printf("\n\nPLAYER 2 WINS");
	else
		printf("\n\nIT'S A TIE OMG");
}