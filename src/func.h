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

//Функция проверки строки на веществвенное число
bool is_number(const wstring& str);

//Функция проверки строки на целое число
bool is_digits(const std::wstring& str);

//Функция проверки строки на буквы, пробел, точку и тире
bool is_not_alphas(const std::wstring& str);

//Функция вывода меню
void Menu();

//Функция сравнения по автору
bool compareByAuthor(const Book& a, const Book& b);

//Функция сравнения по году
bool compareByYear(const Book& a, const Book& b);

//Основной цикл программы
void loop(BookStore& store);

#endif