//cardtest3.c
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



#define TESTCARD "cutpurse"

int main()
{
	int passedCounter = 0;
	int newCards = 0;
	int extraCoins;
	int discarded = 1;
	int otherDiscarded;
	int shuffledCards = 0;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//set other players hand
	G.handCount[1] = 5;
	G.deckCount[1] = 5;

	G.hand[1][0] = copper;
	G.hand[1][1] = copper;
	G.hand[1][2] = copper;
	G.hand[1][3] = estate;
	G.hand[1][4] = estate;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	//TEST 1: Current Player draws exactly cards from own deck 
	printf("TEST 1: Current Player earns exactly 2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

	//confirm 2 coins earned by current player
	extraCoins = 2;
	otherDiscarded = 1;

	//confirm 0 cards drawn to hand by current player
	printf("TEST: hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//confirm 0 cards drawn from deck by current player
	printf("TEST: deck count = %d, expected = %d: ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//confirm only 2 coins earned
	printf("TEST: coins = %d, expected = %d: ", testG.coins, G.coins + extraCoins);
	if (testG.coins == G.coins + extraCoins)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 2: Change of state for other player(s)
	printf("TEST 2: Change of state for other player(s)\n");

	//confirm 1 card discarded from hand by other player - (seed = 1000)
	printf("TEST HAS COPPER: hand count = %d, expected = %d: ", testG.handCount[1], G.handCount[1] + newCards - otherDiscarded);
	if (testG.handCount[1] == G.handCount[1] + newCards - otherDiscarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//confirm 1 card discarded to own deck by other player
	printf("TEST: deck count = %d, expected = %d: ", testG.deckCount[1], G.deckCount[1] - newCards + shuffledCards);
	if (testG.deckCount[1] == G.deckCount[1] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 3: No change of state for Victory or Kingdom card piles
	printf("TEST 3: No change of state for Victory or Kingdom card piles: ");

	//no state change to victory or kingdom card files
	if (testG.supplyCount[province] == G.supplyCount[province] && testG.supplyCount[duchy] == G.supplyCount[duchy] && testG.supplyCount[estate] == G.supplyCount[estate] &&
		testG.supplyCount[adventurer] == G.supplyCount[adventurer] && testG.supplyCount[council_room] == G.supplyCount[council_room] && testG.supplyCount[embargo] == G.supplyCount[embargo]
		&& testG.supplyCount[sea_hag] == G.supplyCount[sea_hag] && testG.supplyCount[mine] == G.supplyCount[mine] && testG.supplyCount[smithy] == G.supplyCount[smithy]
		&& testG.supplyCount[minion] == G.supplyCount[minion] && testG.supplyCount[tribute] == G.supplyCount[tribute] && testG.supplyCount[village] == G.supplyCount[village] &&
		testG.supplyCount[cutpurse] == G.supplyCount[cutpurse])
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 4: Change other players hand-no Copper card
	printf("TEST 4: Change other players hand-no Copper card\n");
	otherDiscarded = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//set other player's hand
	G.handCount[1] = 5;
	G.deckCount[1] = 5;

	G.hand[1][0] = silver;
	G.hand[1][1] = cutpurse;
	G.hand[1][2] = estate;
	G.hand[1][3] = adventurer;
	G.hand[1][4] = estate;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

	//confirm 0 card discarded from hand by other player - (seed = 1000)
	printf("TEST NO COPPER: hand count = %d, expected = %d: ", testG.handCount[1], G.handCount[1] + newCards - otherDiscarded);
	if (testG.handCount[1] == G.handCount[1] + newCards - otherDiscarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//confirm 0 card discarded to own deck by other player
	printf("TEST: deck count = %d, expected = %d: ", testG.deckCount[1], G.deckCount[1] - newCards + shuffledCards);
	if (testG.deckCount[1] == G.deckCount[1] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	
	if (passedCounter == 8)
		printf("FINAL RESULTS: All tests PASSED!\n");
	else
		printf("FINAL RESULTS: At least 1 test FAILED- review results\n");

	printf("FINISH TESTING %s\n", TESTCARD);

	return 0;
}

/*
int cutpurseCard(struct gameState *state, int handPos)
{
	int i;
	int j;
	int k;
	int currentPlayer = whoseTurn(state);
	int nextPlayer = currentPlayer + 1;

	if (nextPlayer > (state->numPlayers - 1)) {
		nextPlayer = 0;
	}

	updateCoins(currentPlayer, state, 4); //BUG 2 changed to 4
	for (i = 0; i < state->numPlayers; i++)
	{
		if (i != currentPlayer)
		{
			for (j = 0; j < state->handCount[i]; j++)
			{
				if (state->hand[i][j] == copper)
				{
					discardCard(j, i, state, 0);
					break;
				}
				if (j == state->handCount[i])
				{
					for (k = 0; k < state->handCount[i]; k++)
					{
						if (DEBUG)
							printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
					}
					break;
				}
			}

		}

	}

	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);

	return 0;
}*/