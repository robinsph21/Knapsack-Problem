#ifndef KNAPSACK_H
#define KNAPSACK_H

#define INT_ERR 0

typedef struct knapsack_item {
    int weight;
    int value;
} knapsack_item;

int knapsack(int w, knapsack_item * items[], int len);
int knapsack_r(int w, knapsack_item * items[], int len, int index);
int max(int a, int b);
knapsack_item * create_knapsack_item(int weight, int value);
void free_set(knapsack_item * array[], int len);
int dynamisack(int w, knapsack_item * items[], int len);
// void print_the_dynamisack(int * table[], int len, int w);

#endif
