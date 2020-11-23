// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>

#include <header.hpp>

Cache_tester::Cache_tester(int min, int max)
{
  min_size = min;
  max_size = max;
  set_massive_size();
}

void Cache_tester::set_massive_size()
{
  int a;
  a = min_size * 0.5;
  massive_size.push_back(a);
  n += 1;
  while (a <= max_size/2)
  {
    a = a * 2;
    n += 1;
    massive_size.push_back(a);
  }
  a = a * 1.5;
  n += 1;
  massive_size.push_back(a);
  all_experiments();
}

void Cache_tester::all_experiments()
{
  direct.type = "direct";
  reverse.type = "reverse";
  random.type = "random";
  for ( int i = 0; i < n; ++i )
  {
    int size = massive_size[i] * 256;
    int m = massive_size[i] * 16;
    int* array = new int[size];
    int k = 0;
    int shag = 0;
    int *array_rand = new int[m];
    int *mass_shag = new int[m];
    for (int j = 0; j < m; j++)
    {
      mass_shag[j] = shag;
      shag = shag + 16;
    }
    unsigned int b = time(NULL);
    while (k < m)
    {
      int a = rand_r(&b)%m;
      if (mass_shag[a] != 1)
      {
        array_rand[k] = mass_shag[a];
        k += 1;
        mass_shag[a] = 1;
      }
    }
    unsigned int a = time(NULL);
    for (int j = 0; j < size; j+=1)
    {
      array[j] = rand_r(&a)%100;
    }
    experiment_direct(array, size, i);
    experiment_reverse(array, size, i);
    experiment_random(array, m, i, array_rand);
    delete[] array;
    delete[] array_rand;
    delete[] mass_shag;
  }
  out_info();
}

void Cache_tester::experiment_direct(int* array, int size, int i)
{
  int b;
  for (int j = size-1; j > 0; j -= 16)
  {
    b = array[j];
  }
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < 1000; ++k) {
    for (int j = size-1; j > 0; j -= 16)
    {
      b = array[j];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  r_time = std::chrono::duration_cast<std::chrono::microseconds>
      (finish - start).count();
  r_time = r_time / 1000;
  std::cout << massive_size[i] << "Kb"
            << " = " << r_time << " mcs" << std::endl;
  direct.time.push_back(r_time);
  direct.number.push_back(i);
}

void Cache_tester::experiment_reverse(int* array, int size, int i)
{
  int b;
  for (int j = 0; j < size; j += 16)
  {
    b = array[j];
  }
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < 1000; ++k) {
    for (int j = 0; j < size; j += 16)
    {
      b = array[j];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  r_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
      .count();
  r_time = r_time / 1000;
  std::cout << massive_size[i] << "Kb"
            << " = " << r_time << " mcs" << std::endl;
  reverse.time.push_back(r_time);
  reverse.number.push_back(i);
}

void Cache_tester::experiment_random(int* array, int size, int i, int *shag)
{
  int b;
  for (int j = 0; j < size; j += 1)
  {
    b = array[shag[j]];
  }
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < 1000; ++k) {
    for (int j = 0; j < size; j += 1)
    {
      b = array[shag[j]];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  r_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
      .count();
  r_time = r_time / 1000;
  std::cout << massive_size[i] << "Kb"
            << " = " << r_time << " mcs" << std::endl;
  random.time.push_back(r_time);
  random.number.push_back(i);
}

void Cache_tester::out_info()
{
  std::vector<struct Out_put> mass_out;
  mass_out.push_back(direct);
  mass_out.push_back(reverse);
  mass_out.push_back(random);
  for (int j = 0; j < 3; j++) {
    std::cout << "investigation:" << std::endl;
    std::cout << "  travel_order: "
              << mass_out[j].type << std::endl;
    std::cout << "  experiments:" << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << "  - experiment:" << std::endl;
      std::cout << "     number: " << mass_out[j].number[i] + 1 << std::endl;
      std::cout << "     input_data:" << std::endl;
      std::cout << "       buffer_size: " << massive_size[i] << " Kb"
                << std::endl;
      std::cout << "     result:" << std::endl;
      std::cout << "       duration: " << mass_out[j].time[i]
                << " mcs" << std::endl;
    }
    std::cout << std::endl;
  }
}

Cache_tester::~Cache_tester(){}
