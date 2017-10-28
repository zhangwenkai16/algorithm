/* Author: Zhang Wenkai, 2017.10.28 */

#include <stdlib.h>

typedef struct {
  int length;
  int price;
} price_table_item;

typedef struct {
  int first_steel_length;
  int max_gain;
} solution_item;

#ifndef CUT_COST
#error "CUT_COST(cut cost, define as 0 if none) not defined!"
#endif

#define MIN_GAIN (-1)
#define CUT_GAIN(n,k) (solution[k].max_gain + solution[n-k].max_gain - CUT_COST)
#define NEED_CUT(n,k) (solution[n].max_gain < CUT_GAIN(n,k))
#define MIN(a, b)     (a >= b ? b : a)

static inline int get_gain_of_no_cut(int steel_length, price_table_item *price_table, int table_size) {
  int i = 1;

  if (steel_length > price_table[table_size-1].length)
	return MIN_GAIN;

  for (; i < table_size; i++)
	{
	  if (price_table[i].length == steel_length)
		return price_table[i].price;
	}

  return MIN_GAIN;
}

static int get_max_no_cut_steel_length(price_table_item *price_table, int table_size) {
  int i = 0;
  int max_length = 0;
  
  for (; i < table_size; i++)
	{
	  if (price_table[i].length > max_length)
		max_length = price_table[i].length;
	}

  return max_length;
}

solution_item *get_max_gains_steel_cut_solution(int steel_length, price_table_item *price_table, int table_size) {
  int i = 0;
  int j = 0;
  int max_single_steel_length = 0;
  solution_item *solution = NULL;

  if (steel_length <= 0
	  || price_table == NULL
	  || table_size <= 0)
	{
	  return NULL;
	}

  max_single_steel_length = get_max_no_cut_steel_length(price_table, table_size);
  solution = (solution_item *)malloc(sizeof(solution_item) * (steel_length + 1));

  /**/
  for (i = 1; i <= steel_length; i++)
	{
	  int max_first_steel_length = MIN(i, max_single_steel_length);
	  solution[i].max_gain = get_gain_of_no_cut(i, price_table, table_size);
	  solution[i].first_steel_length = i;

	  for (j = 1; j <= max_first_steel_length; j++)
		{
		  if (NEED_CUT(i,j))
			{
			  solution[i].max_gain = CUT_GAIN(i,j);
			  solution[i].first_steel_length = j;
			}
		}
	}

  return solution;
}
