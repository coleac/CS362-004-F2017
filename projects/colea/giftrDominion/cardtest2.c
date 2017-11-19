//cardtest2.c
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



#define TESTCARD "smithy"

int main() {

	int passedCounter = 0;
	int newCards = 0;
	int extraCoins = 0;
	int discarded = 1;
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
	printf("TEST 1: Current Player draws exactly 3 cards from deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	//confirm 3 cards drawn by current player
	newCards = 3;

	printf("TEST: hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//cards from own pile (include shuffled cards if needed)
	printf("TEST: deck count = %d, expected = %d: ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//Of 8 cards, at least 5 cards should be copper (current seed= 1000)
	printf("TEST: coins = %d, expected = %d: ", testG.coins, G.coins + extraCoins);
	if (testG.coins == G.coins + extraCoins)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 2: No change of state for other player(s)
	printf("TEST 2: No change of state for other player(s): ");

	//no state change for other players
	if (testG.handCount[1] == G.handCount[1] && testG.deckCount[1] == G.deckCount[1])
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



	if (passedCounter == 5)
		printf("FINAL RESULTS: All tests PASSED!\n");
	else
		printf("FINAL RESULTS: At least 1 test FAILED- review results\n");

	printf("FINISH TESTING %s\n", TESTCARD);


	return 0;

}
/*
int smithyCard(struct gameState *state, int handPos)
{
	int i;
	int currentPlayer = whoseTurn(state);
	int nextPlayer = currentPlayer + 1;

	if (nextPlayer > (state->numPlayers - 1)) {
		nextPlayer = 0;
	}

	//+3 Cards
	for (i = 0; i < 2; i++) //BUG 3 changed to 2
	{
		drawCard(currentPlayer, state);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}*/