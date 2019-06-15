#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdint>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "big_int.h"

using namespace std;

uint32_t* generateBuiltInRand();
uint32_t* generateLehmerLow();
uint32_t* generateLehmerHigh();
uint32_t* generateL20();
uint32_t* generateL89();
uint32_t* generateGiffi();
uint32_t* generateLibrarist();
uint32_t* generateWolfram();
uint32_t* generateBM(uint64_t length);
uint32_t* generateBM_bytes();
uint32_t* generateBBS();
uint32_t* generateBBS_bytes();
uint32_t* idealGenerator();

bool testSimProb (uint32_t* masInt, double alpha);
bool testIndepend (uint32_t* masInt, double alpha);
bool testUniform (uint32_t* masInt, double alpha);

#endif // FUNCTIONS_H
