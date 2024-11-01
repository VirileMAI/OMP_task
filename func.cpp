#include "func.h"

#include "class.h"

bool is_digits(const wstring& str) {
    int all = 0;
    bool dot = false;

    for (wchar_t ch : str) {
        if (iswdigit(ch)) {
            all++;
        } else if (ch == L'.') {
            if (dot) {
                return false;
            }
            dot = true;
        } else {
            return false;
        }
    }
    return all > 0;
}

bool is_not_alphas(const std::wstring& str) {
    int all = 0;
    for (wchar_t ch : str) {
        if (iswalpha(ch) || (ch == L' ') || (ch == L'.') || (ch == L'-')) all++;
    }
    return (all == str.size()) ? false : true;
}

void Menu() {
    wcout << L"\n1. Добавить книгу\n"
          << L"2. Удалить книгу\n"
          << L"3. Найти книгу по названию\n"
          << L"4. Показать все книги (сортировка по названию/автору/году издания)\n"
          << L"5. Найти книги в ценовом диапазоне\n"
          << L"6. Выйти\n"
          << L"Выберите опцию: ";
}

bool compareByAuthor(const Book& a, const Book& b) {
    return a.GetAuthor() < b.GetAuthor();
}

bool compareByYear(const Book& a, const Book& b) {
    return a.GetYear() < b.GetYear();
}

void loop(BookStore& store) {
    wstring tmpChoice;
    int choice;

    while (true) {
        Menu();
        getline(wcin >> ws, tmpChoice);

        if (tmpChoice.empty()) continue;
        if (!is_digits(tmpChoice)) {
            wcout << L"Неправильный ввод. Попробуйте снова.\n";
            continue;
        }

        choice = stoi(tmpChoice);
        wstring title, author, tmpYear, tmpPrice;
        int year;
        double price;

        switch (choice) {
            case 1: {
                wcout << L"Введите название книги: ";
                getline(wcin, title);

                wcout << L"Введите автора книги: ";
                getline(wcin, author);

                if (is_not_alphas(author)) {
                    wcout << L"\nНекорректное имя автора, могут быть только "
                             L"буквы.\n";
                    break;
                }

                wcout << L"Введите год издания: ";
                getline(wcin, tmpYear);
                if (!is_digits(tmpYear) || tmpYear.empty() ||
                    stoi(tmpYear) < 1 || stoi(tmpYear) > 2024) {
                    wcout << L"\nНекорректный ввод даты.\n";
                    break;
                }
                year = stoi(tmpYear);

                wcout << L"Введите цену: ";
                getline(wcin, tmpPrice);
                if (!is_digits(tmpPrice) || tmpPrice.empty() ||
                    stod(tmpPrice) < 0 ||
                    stod(tmpPrice) > numeric_limits<int>::max()) {
                    wcout << L"\nНекорректный ввод цены.\n";
                    break;
                }
                price = stod(tmpPrice);
                store.addBook(Book(0, title, author, year, price));
                wcout << L"\nКнига добавлена.\n";
            } break;

            case 2: {
                wcout << L"Введите название книги для удаления: ";
                getline(wcin, title);
                store.removeBook(title);
            } break;

            case 3: {
                wcout << L"Введите название книги для поиска: ";
                getline(wcin, title);
                Book* book = store.findBook(title);
                if (book) {
                    book->Print();
                } else {
                    wcout << L"\nКнига не найдена.\n";
                }
            } break;

            case 4: {
                int sortOption;
                wcout << L"Сортировать по: 1. Названию, 2. Автору, 3. Году "
                         L"издания\n";
                wcin >> sortOption;
                wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
                store.listBooks(static_cast<SortType>(sortOption - 1));
            } break;

            case 5: {
                wstring tmpMin, tmpMax;
                double minPrice, maxPrice;
                wcout << L"Введите минимальную цену: ";
                getline(wcin, tmpMin);
                if (!is_digits(tmpMin) || stod(tmpMin) < 0 ||
                    stod(tmpMin) > numeric_limits<int>::max()) {
                    wcout << L"\nВведена некорректная цена.\n";
                    break;
                }
                minPrice = stod(tmpMin);
                wcout << L"Введите максимальную цену: ";
                getline(wcin, tmpMax);
                if (!is_digits(tmpMax) || stod(tmpMax) < 0 ||
                    stod(tmpMax) > numeric_limits<int>::max()) {
                    wcout << L"\nВведена некорректная цена.\n";
                    break;
                }
                maxPrice = stod(tmpMax);
                if (maxPrice < minPrice) {
                    wcout << L"\nМаксимальная цена должна быть больше "
                             L"минимальной.\n";
                    break;
                }
                auto books = store.findBookInRangePrice(minPrice, maxPrice);
                if (books.empty())
                    wcout << L"\nНет книг в таком ценовом диапазоне.\n";
                for (const auto& book : books) book.Print();
            } break;

            case 6:
                wcout << L"Выход из программы.\n";
                return;

            default:
                wcout << L"\nНеверный выбор. Попробуйте снова.\n";
                break;
        }
    }
}