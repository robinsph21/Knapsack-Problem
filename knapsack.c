#include <stdio.h>
#include <stdlib.h>
#include "knapsack.h"

// knapsack() error checks and then runs the reccursive algorithm
// @param int w: max weight
// @param int knapsack_item[]: array of knapsack_items
// @param int len: length of items
//
// @return int total_value or 0(INT_ERR) if there is an error
int knapsack(int w, knapsack_item * items[], int len) {
  // error-check that w and len are >= 0
  if(w < 0 || len < 0){
    return INT_ERR;
  }

  // error-check that items array is the same length as len
  for(int i=0; i<len; i++){
    if(items[i] == NULL){
      return INT_ERR;
    }
    // error check that weights[i] and values[i] are >=0
    if(items[i]->weight < 0 || items[i]->value < 0){
      return INT_ERR;
    }
  }
  // All error-checks passed, so run the recursive knapsack algorithm
  return knapsack_r(w, items, len, 0);
}

// knapsack_r() runs the recursive knapsack algorithm, taking the max knapsack config
// @param int w: max weight
// @param int items[]: array of knapsack_items
// @param int len: length of items
// @param int index: index for items[]
//
// @return int total_value: the total value of the knapsack when the weight is <= max_weight
int knapsack_r(int w, knapsack_item * items[], int len, int index){
  // If out of bounds, do nothing
  if(index >= len){
    return 0;
  }
  // If adding the item would go over the max weight, then do not add it
  if((w - items[index]->weight) < 0){
    return knapsack_r(w, items, len, index+1);
  }

  // Take the result that maximizes the knapsack efficiency
  return max(knapsack_r((w - items[index]->weight), items, len, index+1) + items[index]->value,
             knapsack_r(w, items, len, index+1));
}

// max() simply gets the max value between two integers
// @param int a: first value to compare
// @param int b: second value to compare
//
// @return: larger of the two values
int max(int a, int b){
  // (a > b) ? return a : return b;
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

// create_knapsack_item() mallocs memory for the knapsack item struct and returns a pointer to it
// @param int weight: the weight of the knapsack item
// @param int value: the value of the knapsack item
//
// @return: pointer to the newly malloc'ed knapsack_item
knapsack_item * create_knapsack_item(int weight, int value){
  knapsack_item * new_item = (knapsack_item *) malloc(sizeof(knapsack_item));
  new_item->weight = weight;
  new_item->value = value;
  return new_item;
}

void free_set(knapsack_item * array[], int len) {
    for(int i = 0; i < len; i++) {
        free(array[i]);
    }
}

int main(int argc, char const *argv[]) {
    // item_0 definition
    knapsack_item * item_0 = create_knapsack_item(1, 6);
    knapsack_item * item_1 = create_knapsack_item(2, 10);
    knapsack_item * item_2 = create_knapsack_item(3, 12);
    knapsack_item * item_3 = create_knapsack_item(1, 7);

    // Array of pointers
    knapsack_item * set[] = {item_0, item_1, item_2, item_3};
    int max_weight = 5;

    // Call the functions
    printf("Final knapsack total value: %d\n", knapsack(max_weight, set, 4));

    free_set(set, 4);

    return EXIT_SUCCESS;
}
