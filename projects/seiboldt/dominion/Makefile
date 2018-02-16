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

all: playdom player testDrawCard testBuyCard badTestDrawCard randomTestAdventurer randomtestcard1 randomtestcard2 randomtestresults.out


randomTestAdventurer: randomTestAdventurer.c dominion.o interface.o rngs.o
	gcc -o randomTestAdventurer randomTestAdventurer.c -g dominion.o interface.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o interface.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o interface.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o interface.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o interface.o rngs.o $(CFLAGS)


# Source: The gcov -abcfu ... comes from https://piazza.com/class/jbk4lmzexg4ce?cid=87
randomtestresults.out: randomTestAdventurer.c RT_my_advent.c dominion.c interface.o rngs.o

	echo “randomTestAdventurer.c” >> randomtestadventurer.out
	gcc -o randomTestAdventurer randomTestAdventurer.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./randomTestAdventurer >> randomtestadventurer.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallAdventurer() Results: " >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/callAdventurer/{n;p; n;p; n;p;}' >> randomtestadventurer.out
	echo " \ncardEffect Results: " >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> randomtestadventurer.out
	echo " \n" >> randomtestadventurer.out

	echo “randomtestcard1.c” >> randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallSmithy() Results: " >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/callSmithy/{n;p; n;p; n;p;}' >> randomtestcard1.out
	echo " \ncardEffect Results: " >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> randomtestcard1.out
	echo " \n" >> randomtestcard1.out

	echo “randomtestcard2.c” >> randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.c interface.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> /dev/null
	echo " \ncallSteward() Results: " >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/callSteward/{n;p; n;p; n;p;}' >> randomtestcard2.out
	echo " \ncardEffect Results: " >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p;}' >> randomtestcard2.out
	echo " \n" >> randomtestcard2.out
	gcov -b dominion.c >> /dev/null


clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe randomtestadventurer.exe randomtestcard1.exe randomtestcard2.exe randomtestadventurer randomtestcard1 randomtestcard2 *.gcov *.gcda *.gcno *.so *.gcov *.gcda *.gcno *.so *.out
