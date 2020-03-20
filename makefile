knapsack: knapsack.c knapsack.h
	gcc -c -Wall knapsack.c
	gcc -o knapsack knapsack.o
clean: 
	rm -rf knapsack knapsack.o
