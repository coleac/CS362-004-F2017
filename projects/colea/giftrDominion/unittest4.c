//fullDeckCount()
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files 


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main()
{
	int i, l, m, n, o, p, q, r, s;
	int passedCounter = 0;
	int seed = 1000;
	int numPlayer = 2;
	int thisPlayer = 0;
	int calcCount = 0;
	struct gameState G, testG, testG1, testG2;

	//srand(time(NULL));
	srand(1000);

	int k[10] = { adventurer, embargo, village, minion, great_hall, cutpurse, sea_hag, gardens, smithy, steward };

	int g[14] = { adventurer, embargo, village, minion, great_hall, cutpurse, sea_hag, gardens, smithy, steward, curse, province, duchy, estate };

	int j[13] = { adventurer, embargo, village, minion, great_hall, cutpurse, sea_hag, gardens, smithy, steward, province, duchy, estate };

	initializeGame(numPlayer, k, seed, &G);

	printf("START TESTING fullDeckCount():\n");

	//set player's hand
	G.handCount[thisPlayer] = 6;
	G.deckCount[thisPlayer] = 15;
	G.discardCount[thisPlayer] = 22;

	printf("TEST 1: Function as Written \n");

	printf("Test count: Smithy card random \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	//Cards in the hand
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = g[rand() % 13];
		if (testG.hand[thisPlayer][i] == smithy)
			calcCount++;
	}
	printf("	Hand Smithy count (cumulative): %d\n", calcCount);

	//Cards in the deck
	for (l = 0; l < G.deckCount[thisPlayer]; l++)
	{
		testG.deck[thisPlayer][l] = g[rand() % 13];
		if (testG.deck[thisPlayer][l] == smithy)
			calcCount++;
	}
	printf("	Deck Smithy count (cumulative): %d\n", calcCount);

	//Cards in the discard
	for (m = 0; m < G.discardCount[thisPlayer]; m++)
	{
		testG.discard[thisPlayer][m] = g[rand() % 13];
		if (testG.discard[thisPlayer][m] == smithy)
			calcCount++;
	}
	printf("	Discard Smithy count (cumulative): %d\n", calcCount);

	int testCount = fullDeckCount(thisPlayer, 13, &testG);

	printf("TEST: count = %d, expected = %d: ", testCount, calcCount);
	if (testCount == calcCount)
	{
		printf("function fullDeckCount() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function fullDeckCount() test FAILED\n");

	printf("TEST 2A: Function Utility per Current Game Use \n");

	// copy the game state to a test case
	memcpy(&testG1, &G, sizeof(struct gameState));

	printf("	Cards in the hand: With Curse\n");
	for (n = 0; n < G.handCount[thisPlayer]; n++)
	{
		testG1.hand[thisPlayer][n] = g[rand() % 14];	
	}

	printf("	Cards in the deck: With Curse\n");
	for (o = 0; o < G.deckCount[thisPlayer]; o++)
	{
		testG1.deck[thisPlayer][o] = g[rand() % 14];		
	}

	printf("	Cards in the discard: With Curse\n");
	for (p = 0; p < G.discardCount[thisPlayer]; p++)
	{
		testG1.discard[thisPlayer][p] = g[rand() % 14];
	}

	int calcCount2 = (G.handCount[thisPlayer] + G.deckCount[thisPlayer] + G.discardCount[thisPlayer]);

	printf("Function has card parameter - no option in enum card for any so enter NULL\n");
	int testCount2 = fullDeckCount(thisPlayer, NULL, &testG1);

	printf("TEST: count = %d, expected = %d: ", testCount2, calcCount2);
	if (testCount2 == calcCount2)
	{
		printf("function fullDeckCount() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function fullDeckCount() test FAILED\n");

	printf("TEST 2B: Function Utility per Current Game Use \n");

	// copy the game state to a test case
	memcpy(&testG2, &G, sizeof(struct gameState));

	printf("	Cards in the hand: No Curse\n");
	for (q = 0; q < G.handCount[thisPlayer]; q++)
	{
		testG2.hand[thisPlayer][q] = j[rand() % 13];
	}

	printf("	Cards in the deck: No Curse\n");
	for (r = 0; r < G.deckCount[thisPlayer]; r++)
	{
		testG2.deck[thisPlayer][r] = j[rand() % 13];
	}

	printf("	Cards in the discard: No Curse\n");
	for (s = 0; s < G.discardCount[thisPlayer]; s++)
	{
		testG2.discard[thisPlayer][s] = j[rand() % 13];
	}

	int calcCount3 = (G.handCount[thisPlayer] + G.deckCount[thisPlayer] + G.discardCount[thisPlayer]);

	printf("Function has card parameter - no option in enum card for any so enter NULL\n");
	int testCount3 = fullDeckCount(thisPlayer, NULL, &testG2);

	printf("TEST: count = %d, expected = %d: ", testCount3, calcCount3);
	if (testCount3 == calcCount3)
	{
		printf("function fullDeckCount() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function fullDeckCount() test FAILED\n");

	if (passedCounter == 3)
		printf("All tests PASSED!\n");
	else
		printf("At least 1 test FAILED- review results\n");

	printf("FINISH TESTING fullDeckCount()\n");


	return 0;
}

/*
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}*/

