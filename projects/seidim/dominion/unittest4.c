#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	int i, x;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int k[10] = {copper, silver, gold, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	printf("Testing isGameOver\n");
	
	initializeGame(numPlayers, k, seed, &G);
	
	for(i = 0; i < 25; i++){
		G.supplyCount[i] = 5;
	}
	
	G.supplyCount[province] = 0;
	x = isGameOver(&G);
	if(x == 1){
		printf("Passed empty province test\n");
	}
	else{
		printf("Failed empty province test\n");
	}
	
	G.supplyCount[province] = 2;
	x = isGameOver(&G);
	if(x == 0){
		printf("Passed game not over test\n");
	}
	else{
		printf("Failed game not over test\n");
	}
	
	G.supplyCount[3] = 0;
	G.supplyCount[5] = 0;
	G.supplyCount[18] = 0;
	
	x = isGameOver(&G);
	if(x == 1){
		printf("Passed 3 empty test\n");
	}
	else{
		printf("Failed 3 empty test\n");
	}

	return 0;
}
