//randomtestadventurer.c
//Resources: cardtest4.c and Lesson 11 code provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int checkadventurer(int card, int choice1, int choice2, int choice3, struct gameState *post, int handPos, int *bonus, int seed)
{
	int i, r;

	//int passedCounter = 0;
	int failedCounter = 0;

	struct gameState pre;
	
	// copy the game state to a test case
	memcpy(&pre, post, sizeof(struct gameState));

	r = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);

	//printf("whoseturn: %d\n", pre.whoseTurn);

	//add card to played pile
	pre.playedCards[pre.playedCardCount] = pre.hand[pre.whoseTurn][handPos];
	pre.playedCardCount++;

	//2 cards drawn by current player from own deck
	if (pre.deckCount[pre.whoseTurn] > 0)
	{
		pre.handCount[pre.whoseTurn] = pre.handCount[pre.whoseTurn] + 2; // no discard of played card
		if (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn])
		{
			printf("CASE A-TEST 1: 2 Treasure cards drawn by Current Player from deck: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
			//printf("	TEST1a: Correct # of cards drawn PASSED\n");

			//TEST 2: Make sure cards are Treasure cards
			if ((post->hand[pre.whoseTurn][post->handCount[pre.whoseTurn] - 1] == copper || silver || gold) && (post->hand[pre.whoseTurn][post->handCount[pre.whoseTurn] - 2] == copper || silver || gold))
			{
				//printf("TEST 2: Confirm drawn cards are Treasure cards: \n");
				//printf("	TEST 2a: Cards are Treasure Cards PASSED\n");

			}
			else
			{
				printf("TEST 2: Confirm drawn cards are Treasure cards: \n");
				printf("	TEST 2a: Cards are Treasure Cards FAILED\n");
				failedCounter++;
			}
			
		}
		else
		{
			printf("CASE A-TEST 1: 2 Treasure cards drawn by Current Player from deck: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
			printf("	TEST1a: Correct # of cards drawn FAILED\n");
			failedCounter++;
		}

		
		pre.deckCount[pre.whoseTurn] = pre.deckCount[pre.whoseTurn] - ((post->discardCount[pre.whoseTurn] - pre.discardCount[pre.whoseTurn]) + 2);
		if (post->deckCount[pre.whoseTurn] == pre.deckCount[pre.whoseTurn])
		{
			//printf("TEST 3: Cards drawn by Current Player from own deck: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
			//printf("	TEST3a: Cards drawn from Player's deck PASSED\n");
		}
		else
		{
			printf("TEST 3: Cards drawn by Current Player from own deck: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
			printf("	TEST3a: Cards drawn from Player's deck FAILED\n");
			failedCounter++;
		}
	}

	//2 cards drawn by current player from own deck after discard pile shuffled	
	else if (pre.discardCount[pre.whoseTurn] > 0)
	{
		pre.handCount[pre.whoseTurn] = pre.handCount[pre.whoseTurn] + 2; //no discard of played card
		if (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn])
		{
			//printf("CASE B-TEST 1: 2 Treasure cards drawn by current player from own deck after discard pile shuffled: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
			//printf("	TEST1b: 2 cards drawn PASSED\n");

			//TEST 2: Make sure cards are Treasure cards
			if ((post->hand[pre.whoseTurn][post->handCount[pre.whoseTurn] - 1] == copper || silver || gold) && (post->hand[pre.whoseTurn][post->handCount[pre.whoseTurn] - 2] == copper || silver || gold))
			{
				//printf("TEST 2: Confirm drawn cards are Treasure cards: \n");
				//printf("	TEST 2b: Cards are Treasure Cards PASSED\n");
			}
			else
			{
				printf("TEST 2: Confirm drawn cards are Treasure cards: \n");
				printf("	TEST 2b: Cards are Treasure Cards FAILED\n");
				failedCounter++;
			}
		}
		else
		{
			printf("CASE B-TEST 1: 2 Treasure cards drawn by current player from own deck after discard pile shuffled: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
			printf("	TEST1b: 2 cards drawn FAILED\n");
			failedCounter++;
		}

		pre.deckCount[pre.whoseTurn] = pre.discardCount[pre.whoseTurn] - post->discardCount[pre.whoseTurn] - 2;
		if (post->deckCount[pre.whoseTurn] == pre.deckCount[pre.whoseTurn])
		{
			//printf("TEST 3: Cards drawn by Current Player from own deck: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
			//printf("	TEST3b: Cards drawn from Player's deck PASSED\n");
		}
		else
		{
			printf("TEST 3: Cards drawn by Current Player from own deck: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
			printf("	TEST3b: Cards drawn from Player's deck FAILED\n");
			failedCounter++;
		}

	}


	//No change to number of Current Player's coins
	if (pre.coins == post->coins)
	{
		//printf("TEST 4: Current Player coin count does not change: coins = %d, expected = %d: \n", post->coins, pre.coins);
		//printf("	TEST4: No change in Current Player's coins PASSED\n");
	}
	else
	{
		printf("TEST 4: Current Player coin count does not change: coins = %d, expected = %d: \n", post->coins, pre.coins);
		printf("	TEST4: No change in Current Player's coins FAILED\n");
		failedCounter++;
	}

	//no change of state for other players
	int changeCount = 0;
	for (i = 0; i < pre.numPlayers; i++)
	{
		if (i != pre.whoseTurn)
		{
			if (pre.deckCount[i] == post->deckCount[i] && pre.handCount[i] == post->handCount[i])
			{
				changeCount++;
			}
		}
	}

	if (changeCount == pre.numPlayers - 1)
	{
		//printf("TEST5: No change of state for other players PASSED\n");
	}

	else
	{
		printf("TEST5: No change of state for other players FAILED\n");
		failedCounter++;
	}


	//no state change to victory or kingdom card files
	if (pre.supplyCount[province] == post->supplyCount[province] && pre.supplyCount[duchy] == post->supplyCount[duchy] && pre.supplyCount[estate] == post->supplyCount[estate] &&
		pre.supplyCount[adventurer] == post->supplyCount[adventurer] && pre.supplyCount[council_room] == post->supplyCount[council_room] && pre.supplyCount[embargo] == post->supplyCount[embargo]
		&& pre.supplyCount[sea_hag] == post->supplyCount[sea_hag] && pre.supplyCount[mine] == post->supplyCount[mine] && pre.supplyCount[smithy] == post->supplyCount[smithy]
		&& pre.supplyCount[minion] == post->supplyCount[minion] && pre.supplyCount[tribute] == post->supplyCount[tribute] && pre.supplyCount[village] == post->supplyCount[village] &&
		pre.supplyCount[cutpurse] == post->supplyCount[cutpurse])
	{
		//printf("TEST6: No change of state for Victory and Kingdom cards PASSED\n");
	}
	else
	{
		printf("TEST6: Change of state for Victory and Kingdom cards FAILED\n");
		failedCounter++;
	}

	if (r == 0)
	{
		//printf("TEST7: RETURN 0 PASSED\n");
	}
	else
	{
		printf("TEST7: RETURN 0 FAILED\n");
		failedCounter++;
	}

	if (failedCounter == 0)
		printf("FINAL RESULTS TEST SEED %d: All tests PASSED!\n", seed);

	else
		printf("FINAL RESULTS TEST SEED %d: At least %d test(s) FAILED- review results\n", seed, failedCounter);


	printf("--------------------FINISHED SEED %d TEST - ADVENTURER--------------------\n", seed);

	return 0;
}

int main() {

	//set up random number generator
	SelectStream(2);
	PutSeed(3);

	int n, g, h, i, j, l, m;

	//array of all Kingdom cards
	int a[20] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };
	int b[27] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map, curse, province, duchy, estate, copper, silver, gold };
	int k[10];
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
	struct gameState G;

	printf("Testing Adventurer card.\n");

	printf("RANDOM TESTS\n");
	for (n = 0; n < 2000; n++)
	{
		//set number of players
		do {
			G.numPlayers = floor(Random() * MAX_PLAYERS);
		} while (G.numPlayers == 0 || G.numPlayers == 1);

		//set cards
		for (j = 0; j < 10; j++)
		{
			k[j] = a[(int)floor(Random() * 19)];
			for (l = 0; l <= j; l++)
			{
				if (j != l && k[j] == k[l])
					j--;

			}
		}

		//for (m = 0; m < 10; m++)
		//printf("Cards are: %d", k[m]);

		//set seed
		int seed = floor(Random() * 100000);

		//initialize a game state and player cards
		initializeGame(G.numPlayers, k, seed, &G);

		G.whoseTurn = floor(Random() * G.numPlayers);
		//printf("seed: %d", seed);
		//set current players hand and deck counts
		G.handCount[G.whoseTurn] = floor(Random() * MAX_HAND);
		//printf("hand count= %d\n", G.handCount[G.whoseTurn]);
		//printf("turn= %d\n", G.whoseTurn);
		for (i = 0; i < G.handCount[G.whoseTurn]; i++)
		{
			G.hand[G.whoseTurn][i] = b[(int)floor(Random() * 27)];
			//printf("card is: %d\n", G.hand[G.whoseTurn][i]);
		}

		G.deckCount[G.whoseTurn] = floor(Random() * MAX_DECK);
		//printf("deck count= %d\n", G.deckCount[G.whoseTurn]);
		for (h = 0; h < G.deckCount[G.whoseTurn]; h++)
		{
			G.deck[G.whoseTurn][h] = b[(int)floor(Random() * 27)];
			//printf("card is: %d\n", G.deck[G.whoseTurn][h]);
		}

		G.discardCount[G.whoseTurn] = floor(Random() * MAX_DECK);
		//printf("discard count= %d\n", G.discardCount[G.whoseTurn]);
		for (m = 0; m < G.discardCount[G.whoseTurn]; m++)
		{
			G.discard[G.whoseTurn][m] = b[(int)floor(Random() * 27)];
			//printf("card is: %d\n", G.discard[G.whoseTurn][m]);
		}
		
		//set other players' hand and deck counts
		for (g = 0; g < G.numPlayers; g++)
		{
			if (g != G.whoseTurn)
			{
				G.deckCount[g] = floor(Random() * MAX_DECK);
				G.handCount[g] = floor(Random() * MAX_HAND);
				G.discardCount[g] = floor(Random() * MAX_DECK);
			}
		}

		checkadventurer(adventurer, choice1, choice2, choice3, &G, handPos, &bonus, seed);
		
	}

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
