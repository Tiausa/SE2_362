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

# Source: The gcov -abcfu ... comes from https://piazza.com/class/jbk4lmzexg4ce?cid=87
unittestresults.out: unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c interface.o rngs.o

	#echo “unittest1.c” >> unittestresults.out
	#gcc -o unittest1 unittest1.c -g dominion.c interface.o rngs.o $(CFLAGS)
	#./unittest1 >> unittestresults.out
	#gcov -b dominion.c >> /dev/null
	#gcov -abcfu dominion.c | sed -n '/fullDeckCount/{n;p; n;p; n;p;}' >> unittestresults.out
	#echo " \n" >> unittestresults.out

	#echo “unittest2.c” >> unittestresults.out
	#gcc -o unittest2 unittest2.c -g dominion.c interface.o rngs.o $(CFLAGS)
	#./unittest2 >> unittestresults.out
	#gcov -b dominion.c >> /dev/null
	#gcov -abcfu dominion.c | sed -n '/updateCoins/{n;p; n;p; n;p;}' >> unittestresults.out
	#echo " \n" >> unittestresults.out

	#echo “unittest3.c” >> unittestresults.out
	#gcc -o unittest3 unittest3.c -g dominion.c interface.o rngs.o $(CFLAGS)
	#./unittest3 >> unittestresults.out
	#gcov -b dominion.c >> /dev/null
	#gcov -abcfu dominion.c | sed -n '/whoseTurn/{n;p; n;p; n;p;}' >> unittestresults.out
	#echo " \n" >> unittestresults.out

	#echo “unittest4.c” >> unittestresults.out
	#gcc -o unittest4 unittest4.c -g dominion.c interface.o rngs.o $(CFLAGS)
	#./unittest4 >> unittestresults.out
	#gcov -b dominion.c >> /dev/null
	#gcov -abcfu dominion.c | sed -n '/discardCard/{n;p; n;p; n;p;}' >> unittestresults.out
	#echo " \n" >> unittestresults.out

	echo “cardtest1.c” >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallSmithy() Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/callSmithy/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \ncardEffect Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \n" >> unittestresults.out

	echo “cardtest2.c” >> unittestresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallAdventurer() Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/callAdventurer/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \ncardEffect Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \n" >> unittestresults.out

	echo “cardtest3.c” >> unittestresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallGreatHall() Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/callGreatHall/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \ncardEffect Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \n" >> unittestresults.out

	echo “cardtest4.c” >> unittestresults.out
	gcc -o cardtest4 cardtest4.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallCutpurse() Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/callCutpurse/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \ncardEffect Results: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> unittestresults.out
	echo " \n" >> unittestresults.out
	gcov -b dominion.c >> /dev/null



clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe cardtest1.exe cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe *.gcov *.gcda *.gcno *.so *.gcov *.gcda *.gcno *.so *.out
