/**
 * Testing module.
 * Runs tests for other part of the program.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <random>

#include "utils.h"

#include "stretchy_buffer.h"
#include "config_param_parsing.h"
#include "win_console_color.h"
#include "graph.h"

int number_of_tests = 0;
int number_of_failed_tests = 0;
int number_of_succeeded_tests = 0;

#define TEST(name_of_test, test_purpose) void name_of_test() { \
  number_of_tests++; \
  printf("Test #%d %s", number_of_tests, test_purpose);

// Should be called if test fails
void test_failed(const char* expected, const char *got) {
  set_text_red();
  printf(" failed expected %s got %s \n", expected, got);
  number_of_failed_tests++;
  reset_text_color();
}

// Should be called if test succeeded
void test_succeeded() {
  printf(ANSI_COLOR_GREEN " succeeded\n" ANSI_COLOR_RESET);
  number_of_succeeded_tests++;
}

/// Prints total result of tests
void print_result() {
  printf("Number of tests %d\n", number_of_tests);
  printf("Succeeded ");
  
  set_text_green();
  printf("%d\n", number_of_succeeded_tests);
  reset_text_color();

  printf("Failed ");
  
  set_text_red();
  printf("%d\n", number_of_failed_tests);
  reset_text_color();
}

/// Test parsing of configuration parameter name
TEST(param_parsing_name, "Correct parameter name extraction")
  char *correct = (char*)malloc(strlen("name=value") + 1);
  memcpy(correct, "name=value", strlen("name=value") + 1);
  ConfigParam correct_param = parse_configuration_param(correct);

  if (!str_compare(correct_param.config_param_name, "name")) {
    test_failed("name", correct_param.config_param_name);
  } else {
    test_succeeded();
  }
}

/// Test parsing of configuration parameters value
TEST(param_parsing_value, "Correct parameter value extraction")
  char *correct = (char*)malloc(strlen("name=value") + 1);
  memcpy(correct, "name=value", strlen("name=value") + 1);
  ConfigParam correct_param = parse_configuration_param(correct);

 if (!str_compare("value", correct_param.config_param_value)) {
    test_failed("value", correct_param.config_param_value);
  } else {
    test_succeeded();
  }
}

TEST(stretchy_buffer, "Test stretchy buffer work")
  size_t *buffer = NULL;

  sb_push(buffer, 0);
  sb_push(buffer, 1);
  sb_push(buffer, 2);

  size_t number_of_corret_values = 0;
  for (size_t i = 0; i < 3; i++) {
    if (buffer[i] == i) {
      number_of_corret_values += 1;
    }
  }

  if (number_of_corret_values == 3) {
    test_succeeded();
  } else {
    char got[256];
    snprintf(got, 256, "%zu", number_of_corret_values);
    test_failed("3", got);
  }
}
 
TEST(stretchy_buffer_length, "Stretchy buffer length")
  int *buffer = NULL;

  sb_push(buffer, 1);
  sb_push(buffer, 2);
  sb_push(buffer, 3);

  size_t length = sb_count(buffer);
  if (length == 3) {
    test_succeeded();
  } else {
    char got[256];
    snprintf(got, 256, "%zu", length);
    test_failed("3", got);
  }
}

TEST(no_cycles_in_directed_graph, "Detect two cycles in no cycle directed graph")
  Edge *graph = NULL;
  Edge e = { .start = { 1 }, .end = { 2 } };
  sb_push(graph, e);
  e = { .start = { 2 }, .end = { 3 } };
  sb_push(graph, e);
  e = { .start = { 1 }, .end = { 3 } };
  sb_push(graph, e);

  int num = find_number_of_cycles_in_graph(graph, TypeOfGraph::DIRECTED);
  if (num == 2) {
    test_succeeded();
  } else {
    char got[256];
    snprintf(got, 256, "%d", num);
    test_failed("2", got);
  }
}

TEST(complete_cycle, "Detect one cycle in correctly formed cycle")
  Edge *graph = NULL;
  Edge e = { .start = { 1 }, .end = { 2 } };
  sb_push(graph, e);
  e = { .start = { 2 }, .end = { 3 } };
  sb_push(graph, e);
  e = { .start = { 3 }, .end = { 1 } };
  sb_push(graph, e);

  int num = find_number_of_cycles_in_graph(graph, TypeOfGraph::DIRECTED);
  if (num == 1) {
    test_succeeded();
  } else {
    char got[256];
    snprintf(got, 256, "%d", num);
    test_failed("2", got);
  } 
}

int main() {
  setupConsole();
  param_parsing_name();
  param_parsing_value();
  stretchy_buffer();
  stretchy_buffer_length();
  complete_cycle();
  no_cycles_in_directed_graph();

  std::vector<int> vertex_vector;
  vertex_vector.reserve(2048); vertex_vector.clear();
  for (int i = 1; i <= 2048; i++) {
    vertex_vector.push_back(i);
  }

  // Initialize random devices
  std::random_device rd;
  std::mt19937 g(rd());

  

  // Results
  print_result();
  restoreConsole();
}