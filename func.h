#ifndef FUNC
#define FUNC

#include <algorithm>
#include <cwctype>
#include <iostream>
#include <limits>
#include <locale>
#include <vector>

#include "class.h"

using namespace std;

bool is_digits(const wstring& str);

bool is_not_alphas(const std::wstring& str);

void Menu();

bool compareByAuthor(const Book& a, const Book& b);

bool compareByYear(const Book& a, const Book& b);

void loop(BookStore &store);

#endif