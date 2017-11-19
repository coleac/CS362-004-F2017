//randomtestcard1.c
//Resources: cardtest4.c and Lesson 11 code provided in CS_362_400_F2017 Files


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int checkcutpurse(int card, int choice1, int choice2, int choice3, struct gameState *post, int handPos, int *bonus, int seed)
{
	int i, j, k;

	int hasCopper = 0;
	//int passedCounter = 0;
	int failedCounter = 0;

	struct gameState pre;

	// copy the game state to a test case
	memcpy(&pre, post, sizeof(struct gameState));

	int r;

	r = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);


	//printf("whoseturn: %d\n", pre.whoseTurn);

	//add card to played pile
	pre.playedCards[pre.playedCardCount] = pre.hand[pre.whoseTurn][handPos];
	pre.playedCardCount++;

	pre.coins = 0;

	for (i = 0; i < pre.handCount[pre.whoseTurn]; i++)
	{
		if (pre.hand[pre.whoseTurn][i] == copper)
		{
			pre.coins += 1;
		}
		else if (pre.hand[pre.whoseTurn][i] == silver)
		{
			pre.coins += 2;
		}
		else if (pre.hand[pre.whoseTurn][i] == gold)
		{
			pre.coins += 3;
		}
	}

	//printf("coins = %d", pre.coins);

	//2 coins earned	
	pre.coins = pre.coins + 2;
	if (pre.coins == post->coins)
	{
		//printf("TEST 1: Current Player earns exactly 2 coins: coins = %d, expected = %d: \n", post->coins, pre.coins);
		//printf("	TEST1: Current Player's coins increased by 2 PASSED\n");
	}
	else
	{
		printf("TEST 1: Current Player earns exactly 2 coins: coins = %d, expected = %d: \n", post->coins, pre.coins);
		printf("	TEST1: Current Player's coins increased by 2 FAILED\n");
		failedCounter++;
	}
 
	pre.handCount[pre.whoseTurn] = pre.handCount[pre.whoseTurn] - 1; //discarded cutpurse card
	if (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn])
	{
		//printf("TEST 2: HandCount decreases by 1 due to discard of CutpurseCard: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
		//printf("	TEST2: HandCount decreased by 1 PASSED\n");
	}
	else
	{
		printf("TEST 2: HandCount decreases by 1 due to discard of CutpurseCard: handCount = %d, expected = %d: \n", post->handCount[pre.whoseTurn], pre.handCount[pre.whoseTurn]);
		printf("	TEST2: HandCount decreased by 1 FAILED\n");
		failedCounter++;
	}

	if (post->deckCount[pre.whoseTurn] == pre.deckCount[pre.whoseTurn])
	{
		//printf("TEST 3: Current Player draws 0 Cards: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
		//printf("	TEST3: DeckCount remains the same PASSED\n");
	}
	else
	{
		printf("TEST 3: Current Player draws 0 Cards: deckCount = %d, expected = %d: \n", post->deckCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn]);
		printf("	TEST3: DeckCount remains the same FAILED\n");
		failedCounter++;
	}

	//discard deck
	pre.discardCount[pre.whoseTurn] = pre.discardCount[pre.whoseTurn] + 1;

	if (post->discardCount[pre.whoseTurn] == pre.discardCount[pre.whoseTurn])
	{
		//printf("TEST 4: Current Player discardCount = %d, expected = %d: \n", post->discardCount[pre.whoseTurn], pre.discardCount[pre.whoseTurn]);
		//printf("	TEST4: DiscardCount increased by 1 PASSED\n");
	}
	else
	{
		printf("TEST 4: Current Player discardCount = %d, expected = %d: \n", post->discardCount[pre.whoseTurn], pre.discardCount[pre.whoseTurn]);
		printf("	TEST4: DiscardCount increased by 1 FAILED\n");
		failedCounter++;
	}


	//confirm 1 card discarded from hand by other player
	for (j = 0; j < pre.numPlayers; j++)
	{
		hasCopper = 0;
		if (j != pre.whoseTurn)
		{
			for (k = 0; k < pre.handCount[j]; k++)
			{
				if (pre.hand[j][k] == copper)
				{
					k = pre.handCount[j];
					hasCopper = 1;
					//confirm 1 card discarded to own discard deck by other player
					pre.handCount[j] = pre.handCount[j] - 1;
					if (post->handCount[j] == pre.handCount[j])
					{
						//printf("CASE A TEST 5: Other Player #%d has Copper card: handCount = %d, expected = %d: \n", j, post->handCount[j], pre.handCount[j]);
						//printf("	TEST5a: HandCount reduced by 1 PASSED\n");
					}
					else
					{
						printf("CASE A TEST 5: Other Player #%d has Copper card: handCount = %d, expected = %d: \n", j, post->handCount[j], pre.handCount[j]);
						printf("	TEST5a: HandCount reduced by 1 FAILED\n");
						failedCounter++;
					}

					pre.discardCount[j] = pre.discardCount[j] + 1;
					if (post->discardCount[j] == pre.discardCount[j])
					{
						//printf("TEST 6: discardCount = %d, expected = %d: \n", j, post->discardCount[j], pre.discardCount[j]);
						//printf("	TEST6a: DiscardCount increased by 1 PASSED\n");
					}
					else
					{
						printf("TEST 6: Other Player #%d discardCount = %d, expected = %d: \n", j, post->discardCount[j], pre.discardCount[j]);
						printf("	TEST6a: DiscardCount increased by 1 FAILED\n");
						failedCounter++;
					}

					if (post->deckCount[j] == pre.deckCount[j])
					{
						//printf("TEST 7: No change to Other Player's Deck: deckCount = %d, expected = %d: \n", post->deckCount[j], pre.deckCount[j]);
						//printf("	TEST7a: No change to deckCount PASSED\n");
					}
					else
					{
						printf("TEST 7: No change to Other Player's Deck: deckCount = %d, expected = %d: \n", post->deckCount[j], pre.deckCount[j]);
						printf("	TEST7a: No change to deckCount FAILED\n");
						failedCounter++;
					}
				}							
			}
			if (k == pre.handCount[j] && hasCopper == 0)
			{
				//no change of state
				if (post->handCount[j] == pre.handCount[j])
				{
					//printf("CASE B TEST 5: Other Player #%d does not have Copper card: handCount = %d, expected = %d: \n", j, post->handCount[j], pre.handCount[j]);
					//printf("	TEST5b: HandCount does not change PASSED\n");
				}
				else
				{
					printf("CASE B TEST 5: Other Player #%d does not have Copper card: handCount = %d, expected = %d: \n", j, post->handCount[j], pre.handCount[j]);
					printf("	TEST5b: HandCount does not change FAILED\n");
					failedCounter++;
				}

				if (post->discardCount[j] == pre.discardCount[j])
				{
					//printf("TEST 6: Other Player #%d discardCount = %d, expected = %d: \n", j, post->discardCount[j], pre.discardCount[j]);
					//printf("	TEST6b: DiscardCount does not change PASSED\n");
				}
				else
				{
					printf("TEST 6: Other Player #%d discardCount = %d, expected = %d: \n", j, post->discardCount[j], pre.discardCount[j]);
					printf("	TEST6b: DiscardCount does not change FAILED\n");
					failedCounter++;
				}

				if (post->deckCount[j] == pre.deckCount[j])
				{
					//printf("TEST 7: No change to Other Player's Deck: deckCount = %d, expected = %d: \n", post->deckCount[j], pre.deckCount[j]);
					//printf("	TEST7b: No change to deckCount PASSED\n");
				}
				else
				{
					printf("TEST 7: No change to Other Player's Deck: deckCount = %d, expected = %d: \n", post->deckCount[j], pre.deckCount[j]);
					printf("	TEST7b: No change to deckCount FAILED\n");
					failedCounter++;
				}
			}
			
		}
		
	}

	//no state change to victory or kingdom card files
	if (pre.supplyCount[province] == post->supplyCount[province] && pre.supplyCount[duchy] == post->supplyCount[duchy] && pre.supplyCount[estate] == post->supplyCount[estate] &&
		pre.supplyCount[adventurer] == post->supplyCount[adventurer] && pre.supplyCount[council_room] == post->supplyCount[council_room] && pre.supplyCount[embargo] == post->supplyCount[embargo]
		&& pre.supplyCount[sea_hag] == post->supplyCount[sea_hag] && pre.supplyCount[mine] == post->supplyCount[mine] && pre.supplyCount[smithy] == post->supplyCount[smithy]
		&& pre.supplyCount[minion] == post->supplyCount[minion] && pre.supplyCount[tribute] == post->supplyCount[tribute] && pre.supplyCount[village] == post->supplyCount[village] &&
		pre.supplyCount[cutpurse] == post->supplyCount[cutpurse])
	{
		//printf("TEST8: No change of state for Victory and Kingdom cards PASSED\n");
	}
	else
	{
		printf("TEST 8: No change of state for Victory and Kingdom cards FAILED\n");
		failedCounter++;
	}

	if (r == 0)
	{
		//printf("TEST9: RETURN 0 PASSED \n");
	}
	else
	{
		printf("TEST 9: RETURN 0 FAILED\n");
		failedCounter++;
	}

	if (failedCounter == 0)
		printf("FINAL RESULTS TEST SEED %d: All tests PASSED!\n", seed);

	else
		printf("FINAL RESULTS TEST SEED %d: %d test(s) FAILED- review results\n", seed, failedCounter);


	printf("--------------------FINISHED SEED %d TEST - CUTPURSE--------------------\n", seed);

	return 0;
}


int main() {

	//set up random number generator
	SelectStream(2);
	PutSeed(3);

	int g, h, i, j, l, n, p, q;

	//array of all Kingdom cards
	int a[20] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };
	int b[27] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map, curse, province, duchy, estate, copper, silver, gold };
	int k[10];
	int handPos;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G;

	printf("Testing Cutpurse card.\n");

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
		for (q = 0; q < G.discardCount[G.whoseTurn]; q++)
		{
			G.discard[G.whoseTurn][q] = b[(int)floor(Random() * 27)];
			//printf("card is: %d\n", G.discard[G.whoseTurn][q]);
		}

		//set other players' hand, and discard and deck counts
		for (g = 0; g < G.numPlayers; g++)
		{
			if (g != G.whoseTurn)
			{
				G.handCount[g] = floor(Random() * MAX_HAND);
				for (p = 0; p < G.handCount[g]; p++)
				{
					G.hand[g][p] = b[(int)floor(Random() * 27)];
					//printf("card is: %d\n", G.hand[g][p]);
				}
				G.deckCount[g] = floor(Random() * MAX_DECK);
				G.discardCount[g] = floor(Random() * MAX_DECK);
			}
		}

		handPos = floor(Random() * ((G.handCount[G.whoseTurn]) - 1));
		//printf("handPos is: %d\n", handPos);

		checkcutpurse(cutpurse, choice1, choice2, choice3, &G, handPos, &bonus, seed);
	}

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
