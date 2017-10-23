#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NOISY_TEST 1

int main(void)
{
  
     
  int bonus = 0;
  int result = 0; 
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
  
 printf("------- Testing Card: Adventurer--------\n");

  printf("TEST 1: Hand count is incremented by one\n");

  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

 
  if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 1)
  {
    #if (NOISY_TEST)
      printf("FAIL: Expected Value: %d  Actual Value: %d\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    #endif
    result=1;
  }

  if (result == 1) {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

  printf("TEST 2: deck count is decremented by at least two\n");

  result=0; 

  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  if(testG.deckCount[thisPlayer] > G.deckCount[thisPlayer] - 2)
  {
    #if (NOISY_TEST)
      printf("FAIL: Expected Value: <= %d  Actual Value: %d\n", G.deckCount[thisPlayer] - 2, testG.deckCount[thisPlayer]);
    #endif
    
    result=1;
  }

  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }
  
  printf("TEST 3: two treasure cards (coins) are added to the hand\n");

  result=0;

  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  if((testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold) &&
    (testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold))
  {
    #if (NOISY_TEST)
      printf("We got 2 treasure cards: %d, %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], 
        testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]);
    #endif
  }
  else
  {
    result=1;
  }

  if (result == 1) {
    printf("Test 3 failed.\n");
  } else {
    printf("Test 3 passed.\n");
  }

  printf ("ALL TESTS COMPLETE.\n");

  return 0;
}
