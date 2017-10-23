#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	struct gameState G;
	int bonus = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, steward, tribute, smithy};

	printf("------Testing Card: Council Room\n");

	initializeGame(3, k, 205, &G);

	G.hand[0][0] = village;
	G.hand[0][1] = copper;
	G.hand[0][2] = silver;
	G.hand[0][3] = copper;
	G.hand[0][4] = silver;

	G.hand[1][0] = copper;
	G.hand[1][1] = copper;
	G.hand[1][2] = copper;
	G.hand[1][3] = copper;
	G.hand[1][4] = copper;

	G.hand[2][0] = silver;
	G.hand[2][1] = silver;
	G.hand[2][2] = silver;
	G.hand[2][3] = silver;
	G.hand[2][4] = silver;

	int b = G.numBuys;
	int u = G.handCount[0];
	int v = G.handCount[1];
	int w = G.handCount[2];

	printf("Test, add 4 cards to main hand\n");
	cardEffect(council_room, 1, 2, 3, &G, 0, &bonus);
	if(u+3 == G.handCount[0])
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test, add a buy\n");
	if(b+1 == G.numBuys)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test, add 1 card to other hands\n");
	if((v+1 == G.handCount[1]) && (w+1 == G.handCount[2]))
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("ALL TESTS COMPLETE\n");



	
	return 0;
}
