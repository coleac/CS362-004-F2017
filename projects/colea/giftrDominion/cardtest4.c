//cardtest4.c
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



#define TESTCARD "sea_hag"

int main() {

	int passedCounter = 0;
	int newCards = 0;
	int extraCoins = 0;
	int discarded = 0; //unlike other cards-sea_hag does not discard
	int deckDiscarded = 0;
	int otherDiscarded = 0;
	int otherDeckDiscarded = 1;
	int shuffledCards = 0;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//set other players hand
	G.handCount[otherPlayer] = 5;
	G.deckCount[otherPlayer] = 5;

	G.hand[otherPlayer][0] = copper;
	G.hand[otherPlayer][1] = copper;
	G.hand[otherPlayer][2] = copper;
	G.hand[otherPlayer][3] = estate;
	G.hand[otherPlayer][4] = estate;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	//TEST 1: No change of state for current player 
	printf("TEST 1: No change of state for current player\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

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

	//confirm 0 cards discarded from deck by current player
	printf("TEST: discard count = %d, expected = %d: ", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + deckDiscarded);
	if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + deckDiscarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	printf("TEST: card = %d, expected != %d: ", testG.deck[thisPlayer][4], curse);
	if (testG.deck[thisPlayer][4] != curse)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//no change to coin value
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

	printf("TEST: hand count = %d, expected = %d: ", testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCards - otherDiscarded);
	if (testG.handCount[otherPlayer] == G.handCount[otherPlayer] + newCards - otherDiscarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	
	printf("TEST: deck count = %d, expected = %d: ", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] - newCards + shuffledCards);
	if (testG.deckCount[otherPlayer] == G.deckCount[otherPlayer] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	printf("TEST: discard count = %d, expected = %d: ", testG.discardCount[otherPlayer], G.discardCount[otherPlayer] + otherDeckDiscarded);
	if (testG.discardCount[otherPlayer] == G.discardCount[otherPlayer] + otherDeckDiscarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	printf("TEST: card = %d, expected = %d: ", testG.deck[otherPlayer][4], curse); //4 is estate, 0 is curse
	if (testG.deck[otherPlayer][4] == curse)
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



	if (passedCounter == 10)
		printf("FINAL RESULTS: All tests PASSED!\n");
	else
		printf("FINAL RESULTS: At least 1 test FAILED- review results\n");

	printf("FINISH TESTING %s\n", TESTCARD);

	return 0;

}

/*
int sea_hagCard(struct gameState *state)
{
	int i;
	int currentPlayer = whoseTurn(state);
	int nextPlayer = currentPlayer + 1;

	if (nextPlayer > (state->numPlayers - 1)) {
		nextPlayer = 0;
	}

	for (i = 0; i < state->numPlayers; i++) {
		if (i == currentPlayer) { //BUG != changed to ==
			state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];			    
			state->deckCount[i]--;
			state->discardCount[i]++;
			state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
		}
	}
	return 0;
}
*/