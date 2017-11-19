#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include "math.h"

#define DEBUG 0
#define NOISY_TEST 1

//this randomly tests smithy

int main() {
  
  clock_t begin = clock();
  
  int n, i, p, result;
  struct gameState G;
  struct gameState testG;
  int player2 = 1;
  int handPos = 0;
  
  SelectStream(3);
  PutSeed(3);

  for (n = 0; n < 500; n++) { 
    SelectStream(3);
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }

    // set random values for players, deckcount, discard, handcount and playedCardCount
    p = floor(Random() * MAX_PLAYERS);
    G.whoseTurn = p;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * MAX_DECK);
    handPos = floor(Random() * G.handCount[p]);


    memcpy(&testG, &G, sizeof(struct gameState));

    SelectStream(2);
    PutSeed(3);

    result = cardEffect(smithy, 0, 0, 0, &testG, handPos, 0);

    PutSeed(3);

    printf("----------------- Testing Card: Smithy ----------------\n");

    // ----------- TEST 1: +3 cards --------------
    printf("TEST 1: +3 cards\n");

    if(testG.handCount[p] == G.handCount[p] + 2) // lose smithy (-1) and gain 3 more (+3) = 2
      printf("Passed. Expected hand count: %d   Actual count: %d\n", G.handCount[p] +2, testG.handCount[p]);
    else
      printf("FAILED. Expected size: %d   Actual size : %d\n", G.handCount[p] +2, testG.handCount[p]);

    // ----------- TEST 2: Check deck size of other players --------------
    printf("TEST 2: Check handsize of other players\n");
    if(testG.deckCount[player2] == G.deckCount[player2])
      printf("Passed. Deck size Expected: %d   Deck size actual: %d\n", G.deckCount[player2], testG.deckCount[player2]);
    else
      printf("FAILED. Deck size expected: %d   Deck size actual: %d\n", G.deckCount[player2], testG.deckCount[player2]);
    

    // ----------- TEST 3: Check hand count of other players --------------
    printf("TEST 3: Check hand count of other players\n");
    if(testG.handCount[player2] == G.handCount[player2])
      printf("Passed. hand count expected: %d   hand count actual: %d\n", G.handCount[player2], testG.handCount[player2]);
    else
      printf("FAILED. hand count expected: %d   hand count actual: %d\n", G.handCount[player2], testG.handCount[player2]);

   // ----------- TEST 4: Check if smithy card came from players pile --------------
    printf("TEST 4: Check if smithy card came from players pile\n");
      if(G.deckCount[p] - 3 == testG.deckCount[p])  //  since drawcard has shuffle built in, should always be count - 3
        printf("Passed. Expected: %d   Deck size actual: %d\n", G.deckCount[p] - 3, testG.deckCount[p]);
      else
        printf("FAILED. Expected: %d   Deck size actual: %d\n", G.deckCount[p] - 3, testG.deckCount[p]);

   // ----------- TEST 5: Check if smithy card went to players pile --------------
      printf("Test 5: Check if smithy card went to players pile\n");
      if(testG.playedCardCount == 1)
        printf("Passed. Expected increase in played pile: %d     To played pile: %d\n", 1, testG.playedCardCount);
      else
        printf("FAILED. Expected increase in played pile: %d   To played pile: %d\n", 1, testG.playedCardCount);

   // ----------- TEST 6: Check victory cards --------------
    printf("Test 6: : Victory cards\n");
    if(G.supplyCount[estate] != testG.supplyCount[estate])
      printf("FAILED. Estate Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[estate], testG.supplyCount[estate]);
    if(G.supplyCount[duchy] != testG.supplyCount[duchy])
      printf("FAILED. Duchy Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[duchy], testG.supplyCount[duchy]);
    if(G.supplyCount[province] != testG.supplyCount[province])
      printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[province], testG.supplyCount[province]);
    if(G.supplyCount[curse] != testG.supplyCount[curse])
      printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[curse], testG.supplyCount[curse]);
    else
      printf("Passed. Supply counts for curses and victory cards are the same\n");

   // ----------- TEST 7: Check supply cards --------------
    printf("Test 7: Supply cards\n");
      if(G.supplyCount[copper] != testG.supplyCount[copper])
        printf("FAILED. copper Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[copper], testG.supplyCount[copper]);
      if(G.supplyCount[silver] != testG.supplyCount[silver])
        printf("FAILED. silver Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[silver], testG.supplyCount[silver]);
      if(G.supplyCount[gold] != testG.supplyCount[gold])
        printf("FAILED. gold Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[gold], testG.supplyCount[gold]);
      else
        printf("Passed. Supply counts for treasure cards are the same\n");
    }

	clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("ALL TESTS COMPLETE\n");
 	printf("Running Time: %f\n\n", time_spent);
 return 0;
}
