//testIsGameOver()
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files 


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	int passedCounter = 0;
	int seed = 1000;
	int numPlayer = 2;
	struct gameState G, test1G, test2G;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, gardens, smithy, steward };

	initializeGame(numPlayer, k, seed, &G);

	printf("START TESTING isGameOver():\n");

	printf("Test game end with number of province cards\n");
	// copy the game state to a test case
	memcpy(&test1G, &G, sizeof(struct gameState));

	test1G.supplyCount[province] = 0; //Pass
	if (isGameOver(&test1G))
	{
		printf("function isGameOver() test PASSED province count = 0\n");
		passedCounter++;
	}
	else
		printf("function isGameOver() test FAILED province count = 0\n");

	test1G.supplyCount[province] = 8; //Fail
	if (isGameOver(&test1G))
		printf("function isGameOver() test FAILED province count > 0\n");

	else
	{
		printf("function isGameOver() test PASSED province count > 0\n");
		passedCounter++;
	}
			
	printf("Test game ends with 3 supply piles at 0\n");
	memcpy(&test2G, &G, sizeof(struct gameState));

	test2G.supplyCount[gardens] = 0;
	test2G.supplyCount[steward] = 0;
	test2G.supplyCount[estate] = 0; //pass

	if (isGameOver(&test2G))
	{
		printf("function isGameOver() test PASSED 3 supply piles at 0\n");
		passedCounter++;
	}
	else
		printf("function isGameOver() test FAILED 3 supply piles at 0\n");

	test2G.supplyCount[province] = 7;
	test2G.supplyCount[duchy] = 2;
	test2G.supplyCount[estate] = 0;
	test2G.supplyCount[adventurer] = 6;
	test2G.supplyCount[embargo] = 10;
	test2G.supplyCount[village] = 10;
	test2G.supplyCount[minion] = 10;
	test2G.supplyCount[mine] = 10;
	test2G.supplyCount[cutpurse] = 7;
	test2G.supplyCount[sea_hag] = 4;
	test2G.supplyCount[gardens] = 0;
	test2G.supplyCount[smithy] = 7;
	test2G.supplyCount[steward] = 10; //fail

	if (isGameOver(&test2G))
		printf("function isGameOver() test FAILED 2 supply piles at 0\n");
	else
	{
		printf("function isGameOver() test PASSED 2 supply piles at 0\n");
		passedCounter++;
	}

	test2G.supplyCount[province] = 7;
	test2G.supplyCount[duchy] = 2;
	test2G.supplyCount[estate] = 8;
	test2G.supplyCount[adventurer] = 6;
	test2G.supplyCount[embargo] = 10;
	test2G.supplyCount[village] = 10;
	test2G.supplyCount[minion] = 10;
	test2G.supplyCount[mine] = 10;
	test2G.supplyCount[cutpurse] = 7;
	test2G.supplyCount[sea_hag] = 4;
	test2G.supplyCount[gardens] = 7;
	test2G.supplyCount[smithy] = 7;
	test2G.supplyCount[steward] = 10; //fail

	if (isGameOver(&test2G))
		printf("function isGameOver() test FAILED 0 supply piles at 0\n");
	else
	{
		printf("function isGameOver() test PASSED 0 supply piles at 0\n");
		passedCounter++;
	}
	
	if (passedCounter == 5)
		printf("All tests PASSED!\n");
	else
		printf("At least 1 test FAILED- review results\n");

	printf("FINISH TESTING isGameOver()\n");

	return 0;
}
/*
int isGameOver(struct gameState *state) {
	int i;
	int j;

	//if stack of Province cards is empty, the game ends
	if (state->supplyCount[province] == 0)
	{
		return 1;
	}

	//if three supply pile are at 0, the game ends
	j = 0;
	for (i = 0; i < 25; i++)
	{
		if (state->supplyCount[i] == 0)
		{
			j++;
		}
	}
	if (j >= 3)
	{
		return 1;
	}

	return 0;
}*/
