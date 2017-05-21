CFLAGS = -Wall -fpic -coverage -lm

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)


unittests: unittest1.o unittest2.o unittest3.o unittest4.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o
	gcc -o unittests unittest1.o unittest2.o unittest3.o unittest4.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o

unittest1: 
	gcc -o unittest1 unittest1.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

unittest2: 
	gcc -o unittest2 unittest2.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

unittest3: 
	gcc -o unittest3 unittest3.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

unittest4: 
	gcc -o unittest4 unittest4.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

cardtest1: 
	gcc -o cardtest1 cardtest1.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

cardtest2: 
	gcc -o cardtest2 cardtest2.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

cardtest3: 
	gcc -o cardtest3 cardtest3.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

cardtest4:
	gcc -o cardtest4 cardtest4.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99


unittest1.o: dominion.o interface.o rngs.o unittest1.c
	gcc -c unittest1.c -g  $(CFLAGS)

unittest2.o: dominion.o interface.o rngs.o unittest2.c
	gcc -c unittest2.c -g  $(CFLAGS)

unittest3.o: dominion.o interface.o rngs.o unittest3.c
	gcc -c unittest3.c -g  $(CFLAGS)

unittest4.o: dominion.o interface.o rngs.o unittest4.c
	gcc -c unittest4.c -g  $(CFLAGS)

cardtest1.o: dominion.o interface.o rngs.o cardtest1.c
	gcc -c cardtest1.c -g  $(CFLAGS)

cardtest2.o: dominion.o interface.o rngs.o cardtest2.c
	gcc -c cardtest2.c -g  $(CFLAGS)

cardtest3.o: dominion.o interface.o rngs.o cardtest3.c
	gcc -c cardtest3.c -g  $(CFLAGS)

cardtest4.o: dominion.o interface.o rngs.o cardtest4.c
	gcc -c cardtest4.c -g  $(CFLAGS)

maketests:
	make unittest1
	make unittest2
	make unittest3
	make unittest4
	make cardtest1
	make cardtest2
	make cardtest3
	make cardtest4


unittestresults.out:  unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	gcov -b unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of UnitTest1\n*********************************' >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of UnitTest2\n*********************************' >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of UnitTest3\n*********************************' >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of UnitTest4\n*********************************' >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of CardTest1\n*********************************' >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of CardTest2\n*********************************' >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of CardTest3\n*********************************' >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	echo '\n*********************************\nEnd of CardTest4\n*********************************' >> unittestresults.out


randomtestadventurer:
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

randomtestcard1:
	gcc -o randomtestcard1 randomtestcard1.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99

randomtestcard2:
	gcc -o randomtestcard2 randomtestcard2.c dominion.c interface.c rngs.c $(CFLAGS) -std=c99


randomtestcards:
	make randomtestadventurer
	make randomtestcard1
	make randomtestcard2

randomtestresults.out:  randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer
	gcov -b randomtestadventurer.c > randomtestresults.out
	cat randomtestadventurer.c.gcov >> randomtestresults.out
	echo '\n*********************************\nEnd of randomtestadventurer\n*********************************' >> randomtestresults.out
	./randomtestcard1
	gcov -b randomtestcard1.c >> randomtestresults.out
	cat randomtestcard1.c.gcov >> randomtestresults.out
	echo '\n*********************************\nEnd of randomtestcard1\n*********************************' >> randomtestresults.out
	./randomtestcard2
	gcov -b randomtestcard2.c >> randomtestresults.out
	cat randomtestcard2.c.gcov >> randomtestresults.out
	echo '\n*********************************\nEnd of randomtestcard2\n*********************************' >> randomtestresults.out


all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
