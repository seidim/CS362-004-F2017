#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int u;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("START TEST BUYCARD\n\n");

	initializeGame(2, k, 205, &G);
	G.numBuys = 2;
	G.coins = 2;
	printf("Test, too few coins\n");
	u = buyCard(2, &G);
	if(u == -1)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test, succesful purchase\n");
	G.coins = 10;
	u = buyCard(2, &G);
	if(u == 0)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("Test, exact change\n");
	u = buyCard(2, &G);
	if(u == 0)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	G.coins = 6;
	printf("Test, no buys left\n");
	u = buyCard(2, &G);
	if(u == -1)
		printf("Test Passed\n\n");
	else
		printf("Test Failed\n\n");

	printf("\nEND TEST BUYCARD\n\n");
	
	
	return 0;
}
