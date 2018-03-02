CFLAGS = -Wall -std=c99 -lm -fpic -ftest-coverage -fprofile-arcs

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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 unittestresults.out


cardtest1: cardtest1.c dominion.o interface.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o interface.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o interface.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o interface.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o interface.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o interface.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o interface.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o interface.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o interface.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o interface.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o interface.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o interface.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o interface.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o interface.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o interface.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o interface.o rngs.o $(CFLAGS)

randomTestAdventurer: randomTestAdventurer.c dominion.o interface.o rngs.o
	gcc -o randomTestAdventurer randomTestAdventurer.c -g dominion.o interface.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o interface.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o interface.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o interface.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o interface.o rngs.o $(CFLAGS)

# Source: The gcov -abcfu ... comes from https://piazza.com/class/jbk4lmzexg4ce?cid=87
unittestresults.out: unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c interface.o rngs.o

	echo “cardtest1.c, smithy unit test” >> SmithyUnitTest.out
	gcc -o cardtest1 cardtest1.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest1 >> SmithyUnitTest.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallSmithy() Results: " >> SmithyUnitTest.out
	gcov -abcfu dominion.c | sed -n '/callSmithy/{n;p; n;p; n;p;}' >> SmithyUnitTest.out
	echo " \ncardEffect Results: " >> SmithyUnitTest.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> SmithyUnitTest.out
	echo " \n" >> SmithyUnitTest.out

	echo “cardtest3.c, great hall unit test” >> GreatHallUnitTest.out
	gcc -o cardtest3 cardtest3.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest3 >> GreatHallUnitTest.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallGreatHall() Results: " >> GreatHallUnitTest.out
	gcov -abcfu dominion.c | sed -n '/callGreatHall/{n;p; n;p; n;p;}' >> GreatHallUnitTest.out
	echo " \ncardEffect Results: " >> GreatHallUnitTest.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> GreatHallUnitTest.out
	echo " \n" >> GreatHallUnitTest.out



# Source: The gcov -abcfu ... comes from https://piazza.com/class/jbk4lmzexg4ce?cid=87
randomtestresults.out: randomTestAdventurer.c randomtestcard1.c randomtestcard2.c dominion.c interface.o rngs.o

	echo “randomtestcard1.c, smithy” >> SmithyRandomTest.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./randomtestcard1 >> SmithyRandomTest.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallSmithy() Results: " >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/callSmithy/{n;p; n;p; n;p;}' >> SmithyRandomTest.out
	echo " \ncardEffect Results: " >> SmithyRandomTest.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> SmithyRandomTest.out
	echo " \n" >> SmithyRandomTest.out


unitAndRandom: randomtestresults.out unittestresults.out


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe cardtest1.exe cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe randomtestadventurer.exe randomtestcard1.exe randomtestcard2.exe randomtestadventurer randomtestcard1 randomtestcard2 *.gcov *.gcda *.gcno *.so *.gcov *.gcda *.gcno *.so *.out
