#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "steel_bar_cut.h"
#include "cmockery.h"

#define PRICE_TABLE_SIZE (sizeof(s_test_price_table) / sizeof(s_test_price_table[0]))

static price_table_item s_test_price_table[] = {
  {1, 1},
  {2, 5},
  {3, 8},
  {4, 9},
  {5, 10},
  {6, 17},
  {7, 17},
  {8, 20},
  {9, 24},
  {10, 30}};

static void test_max_gain(void **state)
{
  assert_int_equal(get_max_gain(1, s_test_price_table, PRICE_TABLE_SIZE), 1);
  assert_int_equal(get_max_gain(2, s_test_price_table, PRICE_TABLE_SIZE), 5);
  assert_int_equal(get_max_gain(9, s_test_price_table, PRICE_TABLE_SIZE), 25);
  assert_int_equal(get_max_gain(10, s_test_price_table, PRICE_TABLE_SIZE), 30);
  assert_int_equal(get_max_gain(11, s_test_price_table, PRICE_TABLE_SIZE), 31);
  assert_int_equal(get_max_gain(7, s_test_price_table, PRICE_TABLE_SIZE), 18);
}

int main(int argc, char *argv[])
{
  UnitTest tests[] = {
	unit_test(test_max_gain),
  };

  return run_tests(tests);
}
