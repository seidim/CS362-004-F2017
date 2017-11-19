#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("START TEST UPDATECOINS\n\n");

	initializeGame(2, k, 205, &G);

	G.coins = 0;
	printf("Coins Before: %d\n\n", G.coins);

	printf("Copper Test\n");
	G.hand[0][0] = copper;
	G.hand[0][1] = copper;
	G.hand[0][2] = copper;
	G.hand[0][3] = copper;
	G.hand[0][4] = copper;
	updateCoins(0, &G, 0);
	printf("5 Copper: %d\n", G.coins);
	if(G.coins == 5)
		printf("Copper Test Passed\n\n");
	else
		printf("Copper Test Failed\n\n");

	printf("Silver Test\n");
	G.hand[0][0] = silver;
	G.hand[0][1] = silver;
	G.hand[0][2] = silver;
	G.hand[0][3] = silver;
	G.hand[0][4] = silver;
	updateCoins(0, &G, 0);
	printf("5 Silver: %d\n", G.coins);
	if(G.coins == 10)
		printf("Silver Test Passed\n\n");
	else
		printf("Silver Test Failed\n\n");

	printf("Gold Test\n");
	G.hand[0][0] = gold;
	G.hand[0][1] = gold;
	G.hand[0][2] = gold;
	G.hand[0][3] = gold;
	G.hand[0][4] = gold;
	updateCoins(0, &G, 0);
	printf("5 Gold: %d\n", G.coins);
	if(G.coins == 15)
		printf("Gold Test Passed\n\n");
	else
		printf("Gold Test Failed\n\n");

	printf("Mix Test\n");
	G.hand[0][0] = copper;
	G.hand[0][1] = silver;
	G.hand[0][2] = gold;
	G.hand[0][3] = silver;
	G.hand[0][4] = copper;
	updateCoins(0, &G, 0);
	printf("Mix: %d\n", G.coins);
	if(G.coins == 9)
		printf("Mix Test Passed\n\n");
	else
		printf("Mix Test Failed\n\n");

	printf("NoCoins Test\n");
	G.hand[0][0] = gardens;
	G.hand[0][1] = gardens;
	G.hand[0][2] = gardens;
	G.hand[0][3] = gardens;
	G.hand[0][4] = gardens;
	updateCoins(0, &G, 0);
	printf("NoCoins: %d\n", G.coins);
	if(G.coins == 0)
		printf("NoCoins Test Passed\n\n");
	else
		printf("NoCoins Test Failed\n\n");


	printf("END TEST UPDATECOINS\n\n");



	
	return 0;
}
