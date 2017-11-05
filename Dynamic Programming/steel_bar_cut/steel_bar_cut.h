
#ifndef _STEEL_BAR_CUT_H_
#define _STEEL_BAR_CUT_H_

typedef struct {
  int length;
  int price;
} price_table_item;

typedef struct {
  int first_steel_length;
  int max_gain;
} solution_item;

extern solution_item *get_max_gains_steel_cut_solution(const int steel_length,
												const price_table_item *price_table,
												const int table_size);

extern void free_steel_cut_solution(solution_item *solution);

extern int get_max_gain(const int steel_length,
				 const price_table_item *price_table,
				 const int table_size);

extern void dump_cut_solution(const int steel_length,
					   const solution_item *solution);

#endif /* _STEEL_BAR_CUT_H_ */
