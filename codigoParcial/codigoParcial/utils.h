#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

#include "defs.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);
int leInteiro(int min, int max);

void remove_thing_fromstring(string & input, char thing, bool dont_erase_middle);
string extract_from_string(int iterator, string input, char delimiter, bool removespaces);

void userinput(string text, int & a, int low, int high);
void userinput(string text, unsigned short int & a, unsigned short int low, unsigned short int high);
void userinput(string text, float & a, float low, float high);
