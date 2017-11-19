#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	struct gameState G;
	int bonus = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, steward, tribute, smithy};

	printf("------Testing Card: Village\n");

	initializeGame(2, k, 205, &G);

	G.hand[0][0] = village;
	G.hand[0][1] = copper;
	G.hand[0][2] = silver;
	G.hand[0][3] = copper;
	G.hand[0][4] = silver;
	G.numActions = 0;
	int c = G.numActions;


	int u = G.handCount[0];
	printf("Test, add card\n");
	cardEffect(village, 1, 2, 3, &G, 0, &bonus);
	if(u == G.handCount[0])
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test, add 2 actions\n");
	if(c + 2 == G.numActions)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");


	printf("ALL TESTS COMPLETE\n");



	
	return 0;
}
