#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("START TEST DRAWCARD\n\n");

	initializeGame(2, k, 205, &G);
	
	G.deck[0][0] = minion;
	G.deck[0][1] = silver;
	G.deck[0][2] = gold;
	G.deck[0][3] = village;
	G.deck[0][4] = silver;

	G.hand[0][0] = copper;
	G.hand[0][1] = embargo;
	G.hand[0][2] = copper;
	G.hand[0][3] = silver;
	G.hand[0][4] = gardens;

	for(i = 0; i < G.handCount[0]; i++)
	{
		printf("%d ", G.hand[0][i]);
	}
	printf("\n");
	drawCard(0, &G);
	for(i = 0; i < G.handCount[0]; i++)
	{
		printf("%d ", G.hand[0][i]);
	}
	printf("\n");

	printf("END TEST DRAWCARD\n\n");

	//printf("%d", G.coins);
	
	return 0;
}
