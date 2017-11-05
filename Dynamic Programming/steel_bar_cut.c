/* Author: Zhang Wenkai, 2017.10.28 */

#include <stdlib.h>
#include <stdio.h>
#include "steel_bar_cut.h"

#ifndef CUT_COST
#error "CUT_COST(cut cost, define as 0 if none) not defined!"
#endif

#define MIN_GAIN (-1)
#define CUT_GAIN(n,k) (solution[k].max_gain + solution[n-k].max_gain - CUT_COST)
#define NEED_CUT(n,k) (solution[n].max_gain < CUT_GAIN(n,k))
#define MIN(a, b)     (a >= b ? b : a)

static inline int get_gain_of_no_cut(const int steel_length,
									 const price_table_item *price_table,
									 const int table_size) {
  int i = 0;

  for (i = 0; i < table_size; i++)
	{
	  if (price_table[i].length == steel_length)
		return price_table[i].price;
	}

  return MIN_GAIN;
}

static int get_max_no_cut_steel_length(const price_table_item *price_table,
									   const int table_size) {
  int i = 0;
  int max_length = 0;

  for (; i < table_size; i++)
	{
	  if (price_table[i].length > max_length)
		max_length = price_table[i].length;
	}

  return max_length;
}

static void dump_price_table(const price_table_item *price_table,
							 const int table_size)
{
  int index = 0;

  printf("dump price table:\n");
  while(index < table_size)
	{
	  printf("%d %d\n", price_table[index].length, price_table[index].price);
	  index++;
	}
}

solution_item *get_max_gains_steel_cut_solution(const int steel_length,
												const price_table_item *price_table,
												const int table_size) {
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
	  int max_first_steel_length = MIN(i - 1, max_single_steel_length);
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

  dump_cut_solution(steel_length, solution);
  return solution;
}

void free_steel_cut_solution(solution_item *solution)
{
  free(solution);
}

int get_max_gain(const int steel_length,
				 const price_table_item *price_table,
				 const int table_size)
{
  int max_gain = 0;
  solution_item *solution = NULL;

  solution = get_max_gains_steel_cut_solution(steel_length, price_table, table_size);
  if (NULL == solution)
	return -1;

  max_gain = solution[steel_length].max_gain;
  free_steel_cut_solution(solution);

  return max_gain;
}
	  
void dump_cut_solution(const int steel_length,
					   const solution_item *solution)
{
  int remain_length = steel_length;

  printf("length of steel: %d\n\t[[solution]]", steel_length);
  if (solution == NULL)
	{
	  printf("INVALID\n");
	  return;
	}

  printf("max gain = %d, cut array: [", solution[steel_length].max_gain);
  while (remain_length > 0)
	{
	  printf(" %d ", solution[remain_length].first_steel_length);
	  remain_length -= solution[remain_length].first_steel_length;
	}

  printf("]\n");
}
