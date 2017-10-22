//testUpdateCoins()
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
	int thisPlayer = 0;
	struct gameState G, testG, test1G, test2G;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, gardens, smithy, steward };

	initializeGame(numPlayer, k, seed, &G);

	printf("START TESTING updateCoins():\n");

	//set player's hand
	G.handCount[thisPlayer] = 5;
	G.deckCount[thisPlayer] = 5;

	G.coins = 3;

	printf("TEST 1: Confirm coin count reset \n");

	printf("Test coin count changes 3 to 0:\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.hand[thisPlayer][0] = estate;
	testG.hand[thisPlayer][1] = estate;
	testG.hand[thisPlayer][2] = estate;
	testG.hand[thisPlayer][3] = estate;
	testG.hand[thisPlayer][4] = estate;

	updateCoins(thisPlayer, &testG, 0);

	if (testG.coins == 0)
	{
		printf("function updateCoins() test PASSED 0 coins\n");
		passedCounter++;
	}
	else if (testG.coins == 3)
		printf("function updateCoins() test FAILED 3 coins\n");


	printf("TEST 2: Treasure cards \n");

	printf("Test all treasure cards the same:\n");

	// copy the game state to a test case
	memcpy(&test1G, &G, sizeof(struct gameState));

	test1G.hand[thisPlayer][0] = copper;
	test1G.hand[thisPlayer][1] = copper;
	test1G.hand[thisPlayer][2] = copper;
	test1G.hand[thisPlayer][3] = copper;
	test1G.hand[thisPlayer][4] = copper;

	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 5)
	{
		printf("function updateCoins() test PASSED 5-Copper\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Copper\n");


	test1G.hand[thisPlayer][0] = silver;
	test1G.hand[thisPlayer][1] = silver;
	test1G.hand[thisPlayer][2] = silver;
	test1G.hand[thisPlayer][3] = silver;
	test1G.hand[thisPlayer][4] = silver;

	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 10)		
	{
		printf("function updateCoins() test PASSED 5-Silver\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Silver\n");

	test1G.hand[thisPlayer][0] = gold;
	test1G.hand[thisPlayer][1] = gold;
	test1G.hand[thisPlayer][2] = gold;
	test1G.hand[thisPlayer][3] = gold;
	test1G.hand[thisPlayer][4] = gold;

	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 15)
	{
		printf("function updateCoins() test PASSED 5-Gold\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Gold\n");

	test1G.hand[thisPlayer][0] = estate;
	test1G.hand[thisPlayer][1] = estate;
	test1G.hand[thisPlayer][2] = estate;
	test1G.hand[thisPlayer][3] = estate;
	test1G.hand[thisPlayer][4] = estate;

	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 0)
	{
		printf("function updateCoins() test PASSED 5-Other\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Other\n");

	printf("Test treasure and kingdom cards:\n");
		// copy the game state to a test case
		memcpy(&test1G, &G, sizeof(struct gameState));

	test1G.hand[thisPlayer][0] = copper;
	test1G.hand[thisPlayer][1] = estate;
	test1G.hand[thisPlayer][2] = cutpurse;
	test1G.hand[thisPlayer][3] = silver;
	test1G.hand[thisPlayer][4] = gold;

	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 6)
	{
		printf("function updateCoins() test PASSED Mixed\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Mixed\n");

	printf("Test mixed and additional cards:\n");

	G.handCount[thisPlayer] = 7;
	G.deckCount[thisPlayer] = 5;

	// copy the game state to a test case
	memcpy(&test1G, &G, sizeof(struct gameState));

	test1G.hand[thisPlayer][0] = copper;
	test1G.hand[thisPlayer][1] = estate;
	test1G.hand[thisPlayer][2] = cutpurse;
	test1G.hand[thisPlayer][3] = silver;
	test1G.hand[thisPlayer][4] = gold;
	test1G.hand[thisPlayer][5] = adventurer;
	test1G.hand[thisPlayer][6] = silver;


	updateCoins(thisPlayer, &test1G, 0);

	if (test1G.coins == 8)
	{
		printf("function updateCoins() test PASSED Mixed and Additional\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED 5-Mixed and Additional\n");

	printf("TEST 3: Bonus Coins \n");

	printf("Test Cards all same / Bonus changes:\n");

	// copy the game state to a test case
	memcpy(&test2G, &G, sizeof(struct gameState));

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = copper;
	test2G.hand[thisPlayer][2] = copper;
	test2G.hand[thisPlayer][3] = copper;
	test2G.hand[thisPlayer][4] = copper;

	updateCoins(thisPlayer, &test2G, 1);

	if (test2G.coins == 6)
	{
		printf("function updateCoins() test PASSED Same treasure cards/ 1 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Same treasure cards/ 1 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = copper;
	test2G.hand[thisPlayer][2] = copper;
	test2G.hand[thisPlayer][3] = copper;
	test2G.hand[thisPlayer][4] = copper;

	updateCoins(thisPlayer, &test2G, 2);

	if (test2G.coins == 7)
	{
		printf("function updateCoins() test PASSED Same treasure cards/ 2 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Same treasure cards/ 2 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = copper;
	test2G.hand[thisPlayer][2] = copper;
	test2G.hand[thisPlayer][3] = copper;
	test2G.hand[thisPlayer][4] = copper;

	updateCoins(thisPlayer, &test2G, 3);

	if (test2G.coins == 8)
	{
		printf("function updateCoins() test PASSED Same treasure cards/ 3 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Same treasure cards/ 3 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = copper;
	test2G.hand[thisPlayer][2] = copper;
	test2G.hand[thisPlayer][3] = copper;
	test2G.hand[thisPlayer][4] = copper;

	updateCoins(thisPlayer, &test2G, 4);

	if (test2G.coins == 9)
	{
		printf("function updateCoins() test PASSED Same treasure cards/ 4 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Same treasure cards/ 4 Bonus\n");

	test2G.hand[thisPlayer][0] = estate;
	test2G.hand[thisPlayer][1] = estate;
	test2G.hand[thisPlayer][2] = estate;
	test2G.hand[thisPlayer][3] = estate;
	test2G.hand[thisPlayer][4] = estate;

	updateCoins(thisPlayer, &test2G, 4);

	if (test2G.coins == 4)
	{
		printf("function updateCoins() test PASSED Same kingdom cards/ 4 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Same kingdom cards/ 4 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = estate;
	test2G.hand[thisPlayer][2] = cutpurse;
	test2G.hand[thisPlayer][3] = silver;
	test2G.hand[thisPlayer][4] = gold;

	updateCoins(thisPlayer, &test2G, 1);

	if (test2G.coins == 7)
	{
		printf("function updateCoins() test PASSED Mixed cards/ 1 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Mixed cards/ 1 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = estate;
	test2G.hand[thisPlayer][2] = cutpurse;
	test2G.hand[thisPlayer][3] = silver;
	test2G.hand[thisPlayer][4] = gold;

	updateCoins(thisPlayer, &test2G, 1);

	if (test2G.coins == 7)
	{
		printf("function updateCoins() test PASSED Mixed cards/ 1 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Mixed cards/ 1 Bonus\n");

	test2G.hand[thisPlayer][0] = copper;
	test2G.hand[thisPlayer][1] = estate;
	test2G.hand[thisPlayer][2] = cutpurse;
	test2G.hand[thisPlayer][3] = silver;
	test2G.hand[thisPlayer][4] = gold;

	updateCoins(thisPlayer, &test2G, 4);

	if (test2G.coins == 10)
	{
		printf("function updateCoins() test PASSED Mixed cards/ 4 Bonus\n");
		passedCounter++;
	}
	else
		printf("function updateCoins() test FAILED Mixed cards/ 4 Bonus\n");


	if (passedCounter == 15)
		printf("All tests PASSED!\n");
	else
		printf("At least 1 test FAILED- review results\n");

	printf("FINISH TESTING isupdateCoins()\n");

	return 0;
}

/*
int updateCoins(int player, struct gameState *state, int bonus)
{
	int i;

	//reset coin count
	state->coins = 0;

	//add coins for each Treasure card in player's hand
	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == copper)
		{
			state->coins += 1;
		}
		else if (state->hand[player][i] == silver)
		{
			state->coins += 2;
		}
		else if (state->hand[player][i] == gold)
		{
			state->coins += 3;
		}
	}

	//add bonus
	state->coins += bonus;

	return 0;
}
*/

