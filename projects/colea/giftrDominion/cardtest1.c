//cardtest1.c
//Resource: cardtest4.c and testUpdateCoins.c provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



#define TESTCARD "adventurer"

int main() {

	int i;
	int passedCounter = 0;
	int newCards = 0;
	int extraCoins = 0;
	int discarded = 0; //unlike other cards-adventurer only discards temp hand
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

	//TEST 1: Current Player draws exactly 2 Treasure cards from own deck 
	printf("TEST 1: Current Player draws exactly 2 Treasure cards from deck- no shuffle\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//confirm 2 cards drawn by current player
	newCards = 2;

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
	
	//no change to coin value
	printf("TEST: coins = %d, expected = %d: ", testG.coins, G.coins + extraCoins);
	if (testG.coins == G.coins + extraCoins)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 2: Make sure cards are Treasure cards
	printf("TEST 2: Confirm cards are Treasure cards\n");	
	if (testG.handCount[thisPlayer] >= 5)
	{
		for (i = 5; i < testG.handCount[thisPlayer] - 1; i++)
		{
			if (testG.hand[thisPlayer][i] == G.hand[1][0] && testG.hand[thisPlayer][i+1] == G.hand[1][0])
			{
				printf("PASSED\n");
				passedCounter++;
			}
			else
				printf("FAILED\n");
		}
	}
	else
	{
		printf("Unable to run test: no cards drawn.\n");
	}

	//TEST 3: No change of state for other player(s)
	printf("TEST 3: No change of state for other player(s): ");

	//no state change for other players
	if (testG.handCount[1] == G.handCount[1] && testG.deckCount[1] == G.deckCount[1])
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 4: No change of state for Victory or Kingdom card piles
	printf("TEST 4: No change of state for Victory or Kingdom card piles: ");

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

	//TEST 5: Confirm discard deck is shuffled if deck is empty
	printf("TEST 5: Confirm discard deck is shuffled with deck count = 0 \n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//set current players decks

	G.deckCount[thisPlayer] = 0;
	G.discardCount[thisPlayer] = 5;

	G.discard[thisPlayer][0] = copper;
	G.discard[thisPlayer][1] = copper;
	G.discard[thisPlayer][2] = copper;
	G.discard[thisPlayer][3] = copper;
	G.discard[thisPlayer][4] = copper;

	G.hand[thisPlayer][0] = copper;
	G.hand[thisPlayer][1] = copper;
	G.hand[thisPlayer][2] = estate;
	G.hand[thisPlayer][3] = estate;
	G.hand[thisPlayer][4] = estate;

	//set other players hand
	G.handCount[1] = 5;
	G.deckCount[1] = 5;

	G.hand[1][0] = copper;
	G.hand[1][1] = copper;
	G.hand[1][2] = copper;
	G.hand[1][3] = estate;
	G.hand[1][4] = estate;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//confirm 2 cards drawn by current player
	newCards = 2;
	shuffledCards = 5;

	printf("TEST: hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//cards from own pile & discard 
	printf("TEST: deck count = %d, expected %d : ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards)
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");

	//TEST 2: No change of state for other player(s)
	printf("TEST 6: No change of state for other player(s): ");

	//no state change for other players
	if (testG.handCount[1] == G.handCount[1] && testG.deckCount[1] == G.deckCount[1])
	{
		printf("PASSED\n");
		passedCounter++;
	}
	else
		printf("FAILED\n");




	if (passedCounter == 9)
		printf("FINAL RESULTS: All tests PASSED!\n");
	else
		printf("FINAL RESULTS: At least 1 test FAILED- review results\n");

	printf("FINISH TESTING %s\n", TESTCARD);


	return 0;
}
/*
int adventurerCard(struct gameState *state)
{
	int currentPlayer = whoseTurn(state);
	int nextPlayer = currentPlayer + 1;

	int temphand[MAX_HAND];// moved above the if statement
	int drawntreasure = 0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	if (nextPlayer > (state->numPlayers - 1)) {
		nextPlayer = 0;
	}

	while (drawntreasure > 2) { //BUG < changed to >
		if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while (z - 1 >= 0) {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
		z = z - 1;
	}
	return 0;

}*/