#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 500

//This randomly tests village

void oracle(struct gameState state, int handCount, int discardCount, int actionCount)
{
	cardEffect(village, 1, 1, 1, &state, 0, 0);

	printf("handCount- B: %d  A: %d\n", handCount, state.handCount[0]);
	printf("discardCount- B: %d  A: %d\n", discardCount, state.discardCount[0]);
	printf("actionCount- B: %d  A: %d\n", actionCount, state.numActions);

	if(state.handCount[0] != handCount)
	{
		printf("Failed: handcount incorrect\n");
	}
	if(state.discardCount[0] != discardCount +1)
	{
		printf("Failed: discardcount incorrect\n");
	}
	if(state.numActions != actionCount+2)
	{
		printf("Failed: actioncount incorrect\n");
	}
	printf("\n");

	return;
}

int main() {

    clock_t begin = clock();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	
	int i, n, players, player, handCount, deckCount, seed;
	  //struct gameState state;
	struct gameState state;

	srand(time(NULL));
	player = 0;
	n = 1;

	printf("----------------- Testing Card: Village ----------------\n");

	for (i = 0; i < MAX_TESTS; i++) 
	{
	  
		players = rand() % 3 + 2;
		seed = rand();		//pick random seed
		
		initializeGame(players, k, seed, &state);	//initialize Gamestate

		 //Initiate valid state variables
		state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		state.discardCount[player] = rand() % MAX_DECK;
		handCount = rand() % MAX_HAND;	

		
		state.hand[0][0] = village;
		
		 //Copy state variables
		
		deckCount = state.deckCount[player];

		printf("Test: %d\n", n);

		oracle(state, state.handCount[0], state.discardCount[0], state.numActions);		//Run adventurer card

		n++;
	}

	clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("ALL TESTS COMPLETE\n");
	printf("Running Time: %f\n\n", time_spent);

	return 0;
}
