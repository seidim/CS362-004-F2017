#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define NOISY_TEST 1

int main(void)
{
  
  int newCards = 0;
  int bonus = 0;

  int result = 0;

  int i=0, j=0, m=0;
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int seed = 1000;
  int numPlayers = MAX_PLAYERS;
  int thisPlayer = 0;
  
  
  struct gameState G, testG;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};
  
  
    initializeGame(numPlayers, k, seed, &G);
  
  
  printf("----- Testing Card: Smithy  ------\n");

  printf("TEST 1: +3 cards\n");

  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 3;
  
  for( i=0; i < MAX_PLAYERS; i++) {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Test hand count = %d, Baseline hand count = %d\n", testG.handCount[i], G.handCount[i]);
      printf("Test deck count = %d, Baseline deck count = %d\n", testG.deckCount[i], G.deckCount[i]);
      printf("Test discard count = %d, Baseline discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
    #endif
    if(i == thisPlayer)
    {
      if(testG.handCount[i] != G.handCount[i] + newCards)
      {
        #if (NOISY_TEST)
          printf("FAIL: Hand counts didn't increment properly\n");
        #endif
        result = 1;
      }
      
      if(testG.deckCount[i] != G.deckCount[i] - newCards)
      {
        #if (NOISY_TEST)
          printf("FAIL: Deck counts didn't decrement properly\n");
        #endif
        result = 1;
      }

      if(testG.discardCount[i] != G.discardCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: discard counts don't match\n");
        #endif
        result = 1;
      }

    }else 
    {
      if(testG.handCount[i] != G.handCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: Hand counts don't match\n");
        #endif
        result = 1;
      }
      
      if(testG.deckCount[i] != G.deckCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: Deck counts don't match\n");
        #endif
        result = 1;
      }

      if(testG.discardCount[i] != G.discardCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: discard counts don't match\n");
        #endif
        result = 1;
      }      

    }
  }
    // print out results
  if (result == 1) {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

  
  printf("TEST 2: Remove Smithy card\n");

  result = 0;

  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);


  for(j = 0; j < testG.handCount[thisPlayer]; j++)
  {
    if(testG.hand[thisPlayer][j] == smithy)
    {
      #if (NOISY_TEST)
        printf("FAIL: Smithy still in player's hand.\n");
      #endif
      
      result=1;
    }
  }

  // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }

  
  printf("TEST 3: Verify supply count is unchanged\n");

  result = 0;

    
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  for(m = 0; m < 25; m++)
  {
    if(testG.supplyCount[m] != G.supplyCount[m])
    {
      #if (NOISY_TEST)
        printf("FAIL: Supply counts changed by Smithy cardEffect.\n");
      #endif
      
      result = 1;
    }
  }
 
  if (result == 1) {
    printf("Test 3 failed.\n");
  } else {
    printf("Test 3 passed.\n");
  }
  
  printf ("ALL TESTS COMPLETE.\n"); 

  exit(0);
}
