CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o 
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o 
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o 
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o 
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	$(CC) -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	$(CC) -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	$(CC) -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
randomtestresults.out: dominion.o randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer >> randomtestadventurer.out
	gcov -f -b randomtestadventurer >> randomtestadventurer.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -f -b randomtestcard1 >> randomtestcard1.out
	./randomtestcard2 >> randomtestcard2.out
	gcov -f -b randomtestcard2 >> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestresults.out


testSuite: testSuite.c dominion.o rngs.o
	gcc -o testSuite -g  testSuite.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittestresults
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> .out
	cat dominion.c.gcov >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest4 cardtest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
