#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

//randomly test adventurer

int main (int argc, char** argv) {

  clock_t begin = clock();
	
  int i, n, handPos, player, choice1, choice2, choice3, x;
  int *bonus;

  struct gameState G;

  SelectStream(2);
  PutSeed(73);

  // n controls the number of random tests to run
  for (n = 0; n < 500; n++) { //loop 20000 times
    // Initialize the gameState with random bytes
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 255);
    }
    //Set critical values for current test to be with in valid ranges
    //Set whoseTurn to a valid player number
    G.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
    player = floor(Random() * G.numPlayers);
    G.whoseTurn = player;
    
    //Set deck/hand/discard values to reasonable numbers
    for (i = 0; i < G.numPlayers; i++) {
      G.deckCount[i] = floor(Random() * 10);//This is a lower number to increase the number of 0's
      G.handCount[i] = floor(Random() * (MAX_HAND/2));
      G.discardCount[i] = floor(Random() * (MAX_DECK/2));
    }
    
    G.playedCardCount = floor(Random() * (MAX_DECK/2));
    
    //Set cards to valid card numbers (with more treasure cards mixed in)
    for (i = 0; i < MAX_DECK; i++) {
      if (i%6 == 0){
      	G.deck[player][i] = 4 + floor(Random() * 3);
            } else {
      	G.deck[player][i] = floor(Random() * 27);
        }
      }  
    for (i = 0; i < MAX_DECK; i++) {
      if (i%6 == 0){
      	G.discard[player][i] = 4 + floor(Random() * 3);
      } else {
      	G.discard[player][i] = floor(Random() * 27);
      }
    }
    for (i = 0; i < MAX_HAND; i++) {
      if (i%6 == 0){
      	G.hand[player][i] = 4 + floor(Random() * 3);
      } else {
      	G.hand[player][i] = floor(Random() * 27);
      }
    }
    G.numBuys = 1;//floor(Random() * 10);
    //Set position to within range of handCount[]
    handPos = floor(Random() * (G.handCount[player]));
    //Set random values for unused parameters
    choice1 = floor(Random() * 256);
    choice2 = floor(Random() * 256);
    choice3 = floor(Random() * 256);
    x = floor(Random() * 256);
    bonus = &x;
    
    // copy the game state to a test case
    struct gameState testG;
    memcpy (&testG, &G, sizeof(struct gameState));

    //define variables
    int r;
    int seed_sync = 9;
    int j;               // counter
    int p = whoseTurn(&testG);           // players
    int preCount;
    int amount = 0;
    int preamount;
    int moneycard = 0;
    int newcard;
    int z = 0;
    int temp[MAX_HAND];
    int currPlayer = whoseTurn(&testG);

    PutSeed(seed_sync);

    printf("----------------- Testing Card: Adventurer ----------------\n");
    printf("TEST 1: +2 cards\n");
   
      // Test to see what cards are already in the players hand
      preCount = testG.handCount[p];
      preamount = G.coins;
      amount = 0;
      printf("Coin cards in hand originally, if any: ");
      for(j = 0; j < testG.handCount[p]; j++){
        if(testG.hand[p][j] == copper){
          printf("copper, ");
          preamount += 1;
          preCount++;
        }
        if(testG.hand[p][j] == silver){
          printf("silver, ");
          preamount += 2;
          preCount++;
        }
        if(testG.hand[p][j] == gold){
          printf("gold, ");
          preamount += 3;
          preCount++;
        }
      }

      printf("\n");

    // play the turn
    r = cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, bonus);
    
  //now check to see what cards we got
  printf("Coin cards Found: ");
      for(j = 0; j < testG.handCount[p]; j++){
        if(testG.hand[p][j] == copper){
          printf("copper, ");
          amount += 1;
        }
        if(testG.hand[p][j] == silver){
          printf("silver, ");
          amount += 2;
        }
        if(testG.hand[p][j] == gold){
          printf("gold, ");
          amount += 3;
        }
      }

      printf("\n");

   // ----------- TEST 2: choice2: +2 coins --------------
    printf("TEST 2: +2 coins in hand\n");    
      // test to see if two coins were added to the hand
      if(amount == testG.coins)
        printf("Passed. Coin card amount expected: %d   amount finish: %d\n", amount, testG.coins);
      else 
        printf("FAILED. Coin card amount expected: %d   amount finish: %d\n", amount, testG.coins);

   // ----------- TEST 3: +2 coins --------------
    printf("TEST 3: testG & post card verification\n");   
      // Now lets test to see if our rep and post states match - they should!
      if(G.coins == testG.coins)
        printf("Passed. Coin amount the same\n");
      else
        printf("FAILED. Coin amount different\n");

   // ----------- TEST 4: +2 coins --------------
    printf("TEST 4: +2 coins added\n");   
      // Did the player actually get 2 coins added?
      if(testG.handCount[p] == G.handCount[p] + 2)        // - adventurer, + 2, = gain 1 
        printf("Passed. Coin card amount expected: %d   count finish: %d\n", G.handCount[p] + 2, testG.handCount[p]);
      else 
        printf("FAILED. Coin card amount expected: %d   count finish: %d\n", G.handCount[p] +2, testG.handCount[p]);

    //printf("handCount: %d\n", testG.handCount[currPlayer]);
    PutSeed(seed_sync);

    // Special Case: If deckCount is 0, it should shuffle!
    // Does the deck shuffle when deckCount is at 0?
    // ----------- TEST 5: Shuffle --------------
    printf("Test 5: Special Case -- if deckCount is zero, shuffle should be selected:\n");
    while (moneycard < 2) {
      if(testG.deckCount[currPlayer]<1){
        shuffle(currPlayer, &testG);
        printf("I shuffled!\n");
      }
      drawCard(currPlayer, &testG);
      newcard = testG.hand[currPlayer][(testG.handCount[currPlayer])-1];
      if (newcard == copper || newcard == silver || newcard == gold) {
        moneycard++;
      } 
      else {
        temp[z] = newcard;
        testG.handCount[currPlayer]--;
        z++;
      }
    }
    while (z-1>=0){
      testG.discard[currPlayer][testG.discardCount[currPlayer]++] = temp[z-1];
      z=z-1;
    }
    
    //Check that testG and post gameStates are equivalent
    // ----------- TEST 6: Check other players --------------
    printf("Test 6: Make sure other players are uneffected\n");
      if (testG.numBuys != G.numBuys){
        printf("FAILED: numBuys Mismatch Expected %d Received: %d\n", G.numBuys, testG.numBuys);
      }else {
        printf("Passed: numBuys Expected %d Received: %d\n", G.numBuys, testG.numBuys);
      }
      if (testG.discardCount[testG.whoseTurn] == G.discardCount[testG.whoseTurn]){
        printf("FAILED: discardCount Mismatch Expected %d Received: %d\n", G.discardCount[testG.whoseTurn], testG.discardCount[testG.whoseTurn]);
      } else {
        printf("Passed: discardCount Expected %d Received: %d\n", G.discardCount[testG.whoseTurn], testG.discardCount[testG.whoseTurn]);
      }
      if (testG.handCount[testG.whoseTurn] == G.handCount[testG.whoseTurn]){
        printf("FAILED: handCount Mismatch Expected %d Received: %d\n", G.handCount[testG.whoseTurn], testG.handCount[testG.whoseTurn]);
      } else {
        printf("Passed: handCount Expected %d Received: %d\n", G.handCount[testG.whoseTurn], testG.handCount[testG.whoseTurn]);
      }
      if (testG.deckCount[currPlayer] == G.deckCount[currPlayer]){
        printf("FAILED: deckCount Mismatch Expected %d Received: %d\n", G.deckCount[currPlayer], testG.deckCount[currPlayer]);
      } else {
        printf("Passed: deckCount Expected %d Received: %d\n", G.deckCount[currPlayer], testG.deckCount[currPlayer]);
      }

      // Did the game state money amount change?
      // ----------- TEST 7: Supply counts for treasure distributed --------------
      printf("Test 7: supply counts for treasure should have been distributed:\n");
      if(G.supplyCount[copper] != testG.supplyCount[copper])
        printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[copper], testG.supplyCount[copper]);
      if(G.supplyCount[silver] != testG.supplyCount[silver])
        printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[silver], testG.supplyCount[silver]);
      if(G.supplyCount[gold] != testG.supplyCount[gold])
        printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", G.supplyCount[gold], testG.supplyCount[gold]);
      else
        printf("Passed. Supply counts for treasure cards are the same\n");

      // ----------- TEST 7: Did the supply counts change? --------------
      printf("Test 8: Did the supply counts ( points and curses) change?\n");
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

  }

  clock_t end = clock();
	
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf ("ALL TESTS COMPLETE\n");
  printf("Running Time: %f\n\n", time_spent);
  return 0;
}
