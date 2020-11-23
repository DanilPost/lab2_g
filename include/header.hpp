// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

struct Out_put
{
  std::string type;
  std::vector<float> time;
  std::vector<uint32_t> number;
};

class Cache_tester
{
 public:
  explicit Cache_tester(int min, int max);
  void set_massive_size();
  void all_experiments();
  void experiment_direct(uint32_t* array, int size, int i);
  void experiment_reverse(uint32_t * array, int size, int i);
  void experiment_random(uint32_t * array, int size, int i, int* shag);
  void out_info();
  ~Cache_tester();
 private:
  std::vector<int> massive_size;
  struct Out_put direct;
  struct Out_put reverse;
  struct Out_put random;
  int n = 0;
  int min_size;
  int max_size;
  float r_time = 0;
};
#endif // INCLUDE_HEADER_HPP_
