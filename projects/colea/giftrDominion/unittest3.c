//scoreFor()
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
	int i, j, l, m, n, o, p, q, r, s, t, u;
	int passedCounter = 0;
	int seed = 1000;
	int numPlayer = 2;
	int thisPlayer = 0;
	int calcScore = 0;
	struct gameState G, testG, testG1, testG2, testG3;

	//srand(time(NULL));
	srand(1000);

	int k[10] = { adventurer, embargo, village, minion, great_hall, cutpurse, sea_hag, gardens, smithy, steward };

	int g[14] = { adventurer, embargo, village, minion, great_hall, cutpurse, sea_hag, gardens, smithy, steward, curse, province, duchy, estate };

	initializeGame(numPlayer, k, seed, &G);

	printf("START TESTING scoreFor():\n");

	//set player's hand
	G.handCount[thisPlayer] = 6;
	G.deckCount[thisPlayer] = 15;
	G.discardCount[thisPlayer] = 22;

	printf("TEST 1: Random \n");

	printf("Test score: \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Cards in the hand:\n");
	for (i = 0; i < G.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = g[rand() % 14];
		printf("This card is a %d\n", testG.hand[thisPlayer][i]);
		if (testG.hand[thisPlayer][i] == estate)
			calcScore++;
		if (testG.hand[thisPlayer][i] == great_hall)
			calcScore++;
		if (testG.hand[thisPlayer][i] == duchy)
			calcScore= calcScore + 3;
		if (testG.hand[thisPlayer][i] == province)
			calcScore=calcScore + 6;
		if (testG.hand[thisPlayer][i] == curse)
			calcScore--;
		if (testG.hand[thisPlayer][i] == gardens)
			calcScore = calcScore + 4;	
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the deck:\n");
	for (j = 0; j < G.deckCount[thisPlayer]; j++)
	{
		testG.deck[thisPlayer][j] = g[rand() % 14];
		printf("This card is a %d\n", testG.deck[thisPlayer][j]);
		if (testG.deck[thisPlayer][j] == estate)
			calcScore++;
		if (testG.deck[thisPlayer][j] == great_hall)
			calcScore++;
		if (testG.deck[thisPlayer][j] == duchy)
			calcScore = calcScore + 3;
		if (testG.deck[thisPlayer][j] == province)
			calcScore = calcScore + 6;
		if (testG.deck[thisPlayer][j] == curse)
			calcScore--;
		if (testG.deck[thisPlayer][j] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the discard:\n");
	for (l = 0; l < G.discardCount[thisPlayer]; l++)
	{
		testG.discard[thisPlayer][l] = g[rand() % 14];
		printf("This card is a %d\n", testG.discard[thisPlayer][l]);
		if (testG.discard[thisPlayer][l] == estate)
			calcScore++;
		if (testG.discard[thisPlayer][l] == great_hall)
			calcScore++;
		if (testG.discard[thisPlayer][l] == duchy)
			calcScore = calcScore + 3;
		if (testG.discard[thisPlayer][l] == province)
			calcScore = calcScore + 6;
		if (testG.discard[thisPlayer][l] == curse)
			calcScore--;
		if (testG.discard[thisPlayer][l] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	int testScore1 = scoreFor(thisPlayer, &testG);

	printf("TEST: score = %d, expected = %d: ", testScore1, calcScore);
	if ( testScore1 == calcScore )
	{
		printf("function scoreFor() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function scoreFor() test FAILED\n");



	printf("TEST 2: Victory Cards (Remove Scored Curse, and Kingdom Cards) \n");

	printf("Test score: \n");
	int b[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, gardens, smithy, steward };
	int h[13] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, gardens, smithy, steward, province, duchy, estate };

	initializeGame(numPlayer, b, seed, &G);

	//set player's hand
	G.handCount[thisPlayer] = 6;
	G.deckCount[thisPlayer] = 15;
	G.discardCount[thisPlayer] = 22;

	// copy the game state to a test case
	memcpy(&testG1, &G, sizeof(struct gameState));

	calcScore = 0;
	printf("Cards in the hand:\n");
	for (m = 0; m < G.handCount[thisPlayer]; m++)
	{
		testG1.hand[thisPlayer][m] = h[rand() % 13];
		printf("This card is a %d\n", testG1.hand[thisPlayer][m]);
		if (testG1.hand[thisPlayer][m] == estate)
			calcScore++;
		if (testG1.hand[thisPlayer][m] == great_hall)
			calcScore++;
		if (testG1.hand[thisPlayer][m] == duchy)
			calcScore = calcScore + 3;
		if (testG1.hand[thisPlayer][m] == province)
			calcScore = calcScore + 6;
		if (testG1.hand[thisPlayer][m] == curse)
			calcScore--;
		if (testG1.hand[thisPlayer][m] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the deck:\n");
	for (n = 0; n < G.deckCount[thisPlayer]; n++)
	{
		testG1.deck[thisPlayer][n] = h[rand() % 13];
		printf("This card is a %d\n", testG1.deck[thisPlayer][n]);
		if (testG1.deck[thisPlayer][n] == estate)
			calcScore++;
		if (testG1.deck[thisPlayer][n] == great_hall)
			calcScore++;
		if (testG1.deck[thisPlayer][n] == duchy)
			calcScore = calcScore + 3;
		if (testG1.deck[thisPlayer][n] == province)
			calcScore = calcScore + 6;
		if (testG1.deck[thisPlayer][n] == curse)
			calcScore--;
		if (testG1.deck[thisPlayer][n] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the discard:\n");
	for (o = 0; o < G.discardCount[thisPlayer]; o++)
	{
		testG1.discard[thisPlayer][o] = h[rand() % 13];
		printf("This card is a %d\n", testG1.discard[thisPlayer][o]);
		if (testG1.discard[thisPlayer][o] == estate)
			calcScore++;
		if (testG1.discard[thisPlayer][o] == great_hall)
			calcScore++;
		if (testG1.discard[thisPlayer][o] == duchy)
			calcScore = calcScore + 3;
		if (testG1.discard[thisPlayer][o] == province)
			calcScore = calcScore + 6;
		if (testG1.discard[thisPlayer][o] == curse)
			calcScore--;
		if (testG1.discard[thisPlayer][o] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	int testScore2 = scoreFor(thisPlayer, &testG1);

	printf("TEST: score = %d, expected = %d: ", testScore2, calcScore);
	if (testScore2 == calcScore)
	{
		printf("function scoreFor() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function scoreFor() test FAILED\n");

	printf("TEST 3: Curse (Remove Victory Cards and Kingdom Cards) \n");

	printf("Test score: \n");

	int c[10] = { adventurer, embargo, village, minion, outpost, cutpurse, sea_hag, mine, smithy, steward };
	int a[11] = { adventurer, embargo, village, minion, outpost, cutpurse, sea_hag, mine, smithy, steward, curse };

	initializeGame(numPlayer, c, seed, &G);

	//set player's hand
	G.handCount[thisPlayer] = 6;
	G.deckCount[thisPlayer] = 15;
	G.discardCount[thisPlayer] = 22;

	// copy the game state to a test case
	memcpy(&testG2, &G, sizeof(struct gameState));

	calcScore = 0;
	printf("Cards in the hand:\n");
	for (p = 0; p < G.handCount[thisPlayer]; p++)
	{
		testG2.hand[thisPlayer][p] = a[rand() % 11];
		printf("This card is a %d\n", testG2.hand[thisPlayer][p]);
		if (testG2.hand[thisPlayer][p] == estate)
			calcScore++;
		if (testG2.hand[thisPlayer][p] == great_hall)
			calcScore++;
		if (testG2.hand[thisPlayer][p] == duchy)
			calcScore = calcScore + 3;
		if (testG2.hand[thisPlayer][p] == province)
			calcScore = calcScore + 6;
		if (testG2.hand[thisPlayer][p] == curse)
			calcScore--;
		if (testG2.hand[thisPlayer][p] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the deck:\n");
	for (q = 0; q < G.deckCount[thisPlayer]; q++)
	{
		testG2.deck[thisPlayer][q] = a[rand() % 11];
		printf("This card is a %d\n", testG2.deck[thisPlayer][q]);
		if (testG2.deck[thisPlayer][q] == estate)
			calcScore++;
		if (testG2.deck[thisPlayer][q] == great_hall)
			calcScore++;
		if (testG2.deck[thisPlayer][q] == duchy)
			calcScore = calcScore + 3;
		if (testG2.deck[thisPlayer][q] == province)
			calcScore = calcScore + 6;
		if (testG2.deck[thisPlayer][q] == curse)
			calcScore--;
		if (testG2.deck[thisPlayer][q] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the discard:\n");
	for (r = 0; r < G.discardCount[thisPlayer]; r++)
	{
		testG2.discard[thisPlayer][r] = a[rand() % 11];
		printf("This card is a %d\n", testG2.discard[thisPlayer][r]);
		if (testG2.discard[thisPlayer][r] == estate)
			calcScore++;
		if (testG2.discard[thisPlayer][r] == great_hall)
			calcScore++;
		if (testG2.discard[thisPlayer][r] == duchy)
			calcScore = calcScore + 3;
		if (testG2.discard[thisPlayer][r] == province)
			calcScore = calcScore + 6;
		if (testG2.discard[thisPlayer][r] == curse)
			calcScore--;
		if (testG2.discard[thisPlayer][r] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	int testScore3 = scoreFor(thisPlayer, &testG2);

	printf("TEST: score = %d, expected = %d: ", testScore3, calcScore);
	if (testScore3 == calcScore)
	{
		printf("function scoreFor() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function scoreFor() test FAILED\n");

	printf("TEST 3: Kingdom Cards (Remove Victory Cards and Curse) \n");

	printf("Test score: \n");

	int d[10] = { adventurer, embargo, village, minion, outpost, cutpurse, sea_hag, great_hall, smithy, steward };

	initializeGame(numPlayer, d, seed, &G);

	//set player's hand
	G.handCount[thisPlayer] = 6;
	G.deckCount[thisPlayer] = 15;
	G.discardCount[thisPlayer] = 22;

	// copy the game state to a test case
	memcpy(&testG3, &G, sizeof(struct gameState));

	calcScore = 0;
	printf("Cards in the hand:\n");
	for (s = 0; s < G.handCount[thisPlayer]; s++)
	{
		testG3.hand[thisPlayer][s] = d[rand() % 10];
		printf("This card is a %d\n", testG3.hand[thisPlayer][s]);
		if (testG3.hand[thisPlayer][s] == estate)
			calcScore++;
		if (testG3.hand[thisPlayer][s] == great_hall)
			calcScore++;
		if (testG3.hand[thisPlayer][s] == duchy)
			calcScore = calcScore + 3;
		if (testG3.hand[thisPlayer][s] == province)
			calcScore = calcScore + 6;
		if (testG3.hand[thisPlayer][s] == curse)
			calcScore--;
		if (testG3.hand[thisPlayer][s] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the deck:\n");
	for (t = 0; t < G.deckCount[thisPlayer]; t++)
	{
		testG3.deck[thisPlayer][t] = d[rand() % 10];
		printf("This card is a %d\n", testG3.deck[thisPlayer][t]);
		if (testG3.deck[thisPlayer][t] == estate)
			calcScore++;
		if (testG3.deck[thisPlayer][t] == great_hall)
			calcScore++;
		if (testG3.deck[thisPlayer][t] == duchy)
			calcScore = calcScore + 3;
		if (testG3.deck[thisPlayer][t] == province)
			calcScore = calcScore + 6;
		if (testG3.deck[thisPlayer][t] == curse)
			calcScore--;
		if (testG3.deck[thisPlayer][t] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	printf("\nCards in the discard:\n");
	for (u = 0; u < G.discardCount[thisPlayer]; u++)
	{
		testG3.discard[thisPlayer][u] = d[rand() % 10];
		printf("This card is a %d\n", testG3.discard[thisPlayer][u]);
		if (testG3.discard[thisPlayer][u] == estate)
			calcScore++;
		if (testG3.discard[thisPlayer][u] == great_hall)
			calcScore++;
		if (testG3.discard[thisPlayer][u] == duchy)
			calcScore = calcScore + 3;
		if (testG3.discard[thisPlayer][u] == province)
			calcScore = calcScore + 6;
		if (testG3.discard[thisPlayer][u] == curse)
			calcScore--;
		if (testG3.discard[thisPlayer][u] == gardens)
			calcScore = calcScore + 4;
		printf("This calcScore= %d \n", calcScore);
	}

	int testScore4 = scoreFor(thisPlayer, &testG3);

	printf("TEST: score = %d, expected = %d: ", testScore4, calcScore);
	if (testScore4 == calcScore)
	{
		printf("function scoreFor() test PASSED\n");
		passedCounter++;
	}
	else
		printf("function scoreFor() test FAILED\n");

	if (passedCounter == 4)
		printf("All tests PASSED!\n");
	else
		printf("At least 1 test FAILED- review results\n");

	printf("FINISH TESTING scoreFor()\n");


	return 0;
}

/*
int scoreFor (int player, struct gameState *state) {

  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  return score;


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
  }
  */


