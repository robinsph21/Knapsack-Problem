#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    // Correct use of ternary operator
    return (a > b) ? a : b;
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


// dynamisack() runs the dynamic programming algorithm on the knapsack items
// @param int w: max weight
// @param int items[]: array of knapsack_items
// @param int len: length of items
//
// @return int total_value or 0(INT_ERR) if there is an error
int dynamisack(int w, knapsack_item * items[], int len) {
  // Create an empty int array initialized to 0
  int T[len+1][w+1];
  for(int i=0; i<len+1; i++) {
    for(int j=0; j<w+1; j++) {
        T[i][j] = 0;
    }
  }
  //fill out the table
  for(int i=1; i<len+1; i++) {
    for(int j=1; j<w+1; j++) {
      if(items[i-1]->weight > j) {
        //if the weight of the cell above is greater than the max weight, just copy the cell above
        T[i][j] = T[i-1][j];
      } else {
        //take the max of the (cell above) and (next most filled cell above and to the left)
        T[i][j] = max(T[i-1][j], T[i-1][j-items[i-1]->weight] + items[i-1]->value);
      }
    }
  }

  return T[len][w];
}

int main(int argc, char const * argv[]) {
    int type = -1;

    if(argc != 2) {
        printf("Incorrect number of arguments! Usage: %s [recursive | dynamic]\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        if(strcmp(argv[1], "recursive") == 0) {
            type = 0;
        } else if(strcmp(argv[1], "dynamic") == 0) {
            type = 1;
        } else {
            printf("Invalid argument! Usage: %s [recursive | dynamic]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // item_0 definition
    knapsack_item * i0 = create_knapsack_item(1, 6);
    knapsack_item * i1 = create_knapsack_item(2, 10);
    knapsack_item * i2 = create_knapsack_item(3, 12);
    knapsack_item * i3 = create_knapsack_item(1, 7);
    knapsack_item * i4 = create_knapsack_item(2, 10);
    knapsack_item * i5 = create_knapsack_item(5, 12);
    knapsack_item * i6 = create_knapsack_item(10, 7);
    knapsack_item * i7 = create_knapsack_item(6, 18);
    knapsack_item * i8 = create_knapsack_item(9, 20);
    knapsack_item * i9 = create_knapsack_item(7, 10);
    knapsack_item * i10 = create_knapsack_item(6, 19);
    knapsack_item * i11 = create_knapsack_item(5, 10);
    knapsack_item * i12 = create_knapsack_item(14, 30);
    knapsack_item * i13 = create_knapsack_item(11, 26);
    knapsack_item * i14 = create_knapsack_item(13, 28);
    knapsack_item * i15 = create_knapsack_item(7, 18);
    knapsack_item * i16 = create_knapsack_item(6, 20);
    knapsack_item * i17 = create_knapsack_item(9, 7);
    knapsack_item * i18 = create_knapsack_item(4, 19);
    knapsack_item * i19 = create_knapsack_item(1, 9);
    knapsack_item * i20 = create_knapsack_item(1, 6);
    knapsack_item * i21 = create_knapsack_item(2, 10);
    knapsack_item * i22 = create_knapsack_item(3, 12);
    knapsack_item * i23 = create_knapsack_item(4, 7);
    knapsack_item * i24 = create_knapsack_item(2, 10);
    knapsack_item * i25 = create_knapsack_item(5, 12);
    knapsack_item * i26 = create_knapsack_item(10, 7);
    knapsack_item * i27 = create_knapsack_item(6, 18);
    knapsack_item * i28 = create_knapsack_item(9, 20);
    knapsack_item * i29 = create_knapsack_item(7, 10);
    knapsack_item * i30 = create_knapsack_item(6, 19);
    knapsack_item * i31 = create_knapsack_item(5, 10);
    knapsack_item * i32 = create_knapsack_item(14, 30);
    knapsack_item * i33 = create_knapsack_item(11, 26);
    knapsack_item * i34 = create_knapsack_item(13, 28);
    knapsack_item * i35 = create_knapsack_item(7, 18);
    knapsack_item * i36 = create_knapsack_item(6, 20);
    knapsack_item * i37 = create_knapsack_item(9, 7);
    knapsack_item * i38 = create_knapsack_item(4, 19);
    knapsack_item * i39 = create_knapsack_item(1, 9);

    // Array of pointers
    knapsack_item * set[] = {
        i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19,
        i20, i21, i22, i23, i24, i25, i26, i27, i28, i29, i30, i31, i32, i33, i34, i35, i36, i37,
        i38, i39
    };
    int num_items = 40;
    int max_weight = 60;

    // Call the functions
    if(type == 0) {
        printf("Final knapsack total value (recusive function): %d\n", knapsack(max_weight, set, num_items));
    } else if(type == 1) {
        printf("Final knapsack total value (dynamic programming): %d\n", dynamisack(max_weight, set, num_items));
    } else {
        printf("Unknown error! Exiting...\n");
    }

    free_set(set, num_items);

    return EXIT_SUCCESS;
}
