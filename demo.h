#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
size_t min(size_t a, size_t b);
size_t max(size_t a, size_t b);
size_t delFloat(string* str);
size_t strCompletion(string* str1, string* str2, bool tf);
int strCompare(string* str1, string* str2);
string deInvalid(string* str);
string subtraction(string* str1, string* str2);
string addition(string* str1, string* str2);
string multiplication(string* str1, string* str2);
string divStage(string* str1, string str2);
string div(string* str1, string* str2);