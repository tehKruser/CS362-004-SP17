CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

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

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo "Result for running random tests on adventurerCard:" >  randomtestadventurer.out
	
	gcc -o randomtestadventurer dominion.c rngs.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >>  randomtestadventurer.out
	gcov -b -f dominion.c >>  randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1.c dominion.c rngs.c
	echo "Result for running random tests on outpostCard:" >  randomtestcard1.out
	
	gcc -o randomtestcard1 dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >>  randomtestcard1.out
	gcov -b -f dominion.c >>  randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.c rngs.c
	echo "Result for running random tests on smithyCard:" >  randomtestcard2.out
	
	gcc -o randomtestcard2 dominion.c rngs.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >>  randomtestcard2.out
	gcov -b -f dominion.c >>  randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Result for running unit tests:" >  unittestresults.out
	
	echo "unittest1.c:" >>  unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> test1.out
	
	echo "unittest2.c:" >>  unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c $(CFLAGS)
	unittest2 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> test2.out
	
	echo "unittest3.c:" >>  unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c $(CFLAGS)
	unittest3 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> test3.out
	
	echo "unittest4.c:" >>  unittestresults.out
	gcc -o unittest4 -g dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> test4.out
	
	echo "cardtest1.c:" >>  unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> card1.out
	
	echo "cardtest2.c:" >>  unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> card2.out
	
	echo "cardtest3.c:" >>  unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)
	cardtest3 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> card3.out
	
	echo "cardtest4.c:" >>  unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)
	cardtest4 >>  unittestresults.out
	gcov -b -f dominion.c >>  unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	cat dominion.c.gcov >> card4.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

cleantests: 
	rm unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcda *.gcno *.gcov

cleanrandom:
	rm randomtestadventurer.out randomtestcard1.out randomtestcard2.out randomtestadventurer randomtestcard1 randomtestcard2 *.gcda *.gcno *.gcov
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
