/*
 * main.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Pimenta
 */

#include <map>
#include <string>
#include <cstdio>

using namespace std;

void correctness(int, char**);
void test(int, char**);

int main(int argc, char** argv) {
  
  map<string, void (*)(int, char**)> progs;
  progs["correctness"] = &correctness;
  progs["test"] = &test;
  
  auto usage_mode = [argv, &progs]() {
    fprintf(stderr, "Usage mode: %s <program>\n", argv[0]);
    fprintf(stderr, "  Programs:\n");
    for (auto& kv : progs) {
      fprintf(stderr, "    %s\n", kv.first.c_str());
    }
  };
  
  if (argc == 1) {
    usage_mode();
    return 0;
  }
  auto it = progs.find(argv[1]);
  if (it == progs.end()) {
    usage_mode();
    return 0;
  }
  it->second(argc - 1, &argv[1]);
  
  return 0;
}
