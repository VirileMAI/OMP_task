#include <algorithm>
#include <cwctype>
#include <iostream>
#include <limits>
#include <locale>
#include <vector>

using namespace std;

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

enum class SortType { TITLE, AUTHOR, YEAR };

class Book {
  private:
    size_t _id;
    wstring _title;
    wstring _author;
    short _year;
    double _price;

  public:
    Book(size_t id, const wstring& title, const wstring& author, short year,
         double price)
        : _id(id), _title(title), _author(author), _year(year), _price(price) {}

    // Геттеры
    size_t GetID() const { return _id; }
    const wstring& GetTitle() const { return _title; }
    const wstring& GetAuthor() const { return _author; }
    int GetYear() const { return _year; }
    double GetPrice() const { return _price; }

    void Print() const {
        wcout << L"ID книги: " << _id << L", Название: " << _title
              << L", Автор: " << _author << L", Год: " << _year << L", Цена: "
              << _price << L" руб." << endl;
    }

    bool operator<(const Book& other) const { return _title < other._title; }
    bool operator>(const Book& other) const { return _title > other._title; }
    bool operator==(const Book& other) const {
        return _title == other._title && _author == other._author &&
               _year == other._year && _price == other._price;
    }
};

bool compareByAuthor(const Book& a, const Book& b) {
    return a.GetAuthor() < b.GetAuthor();
}

bool compareByYear(const Book& a, const Book& b) {
    return a.GetYear() < b.GetYear();
}

class BookStore {
  private:
    vector<Book> _books;
    static size_t ID;

  public:
    BookStore() { ID = 1; }

    void addBook(const Book& book) {
        _books.push_back(Book(ID, book.GetTitle(), book.GetAuthor(),
                              book.GetYear(), book.GetPrice()));
        ID++;
    }

    bool removeBook(const wstring& title) {
        vector<Book*> titleName;
        for (auto& book : _books) {
            if (book.GetTitle() == title) {
                titleName.push_back(&book);
            }
        }

        if (titleName.empty()) {
            wcout << L"\nКнига с таким названием не найдена.\n";
            return false;
        }

        wcout << L"Найдено несколько книг с названием \"" << title << L"\":\n";
        for (const auto& book : titleName) {
            book->Print();
        }

        wcout << L"Введите ID книги для удаления: ";
        size_t delID;
        wcin >> delID;

        for (auto it = _books.begin(); it != _books.end(); ++it) {
            if (it->GetID() == delID) {
                _books.erase(it);
                wcout << L"Книга с ID " << delID << L" удалена.\n";
                return true;
            }
        }

        wcout << L"Книга с указанным ID не найдена.\n";
        return false;
    }

    Book* findBook(const wstring& title) {
        for (auto& book : _books)
            if (book.GetTitle() == title) return &book;
        return nullptr;
    }

    void listBooks(SortType sortType) {
        switch (sortType) {
            case SortType::TITLE:
                sort(_books.begin(), _books.end());
                break;
            case SortType::AUTHOR:
                sort(_books.begin(), _books.end(), compareByAuthor);
                break;
            case SortType::YEAR:
                sort(_books.begin(), _books.end(), compareByYear);
                break;
            default:
                wcout << L"Неподходящий параметр.\n";
                return;
        }
        for (const auto& book : _books) book.Print();
    }

    vector<Book> findBookInRangePrice(double minPrice, double maxPrice) {
        vector<Book> result;
        for (const auto& book : _books) {
            if (book.GetPrice() >= minPrice && book.GetPrice() <= maxPrice) {
                result.push_back(book);
            }
        }
        return result;
    }
};

size_t BookStore::ID = 1;

void Menu() {
    wcout << L"\n1. Добавить книгу\n"
          << L"2. Удалить книгу.\n"
          << L"3. Найти книгу по названию.\n"
          << L"4. Показать все книги (Отсортированные по названию/автору/году "
             L"издания)\n"
          << L"5. Найти все книги в ценовом диапазоне.\n"
          << L"6. Выйти.\n"
          << L"Выберите опцию: ";
}

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wcin.imbue(locale());
    // wcout.imbue(locale());

    BookStore store;
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
                wcout << L"Введите название: ";
                getline(wcin, title);

                wcout << L"Введите автора: ";
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
                    stoi(tmpPrice) < 0 ||
                    stoi(tmpPrice) > numeric_limits<int>::max()) {
                    wcout << L"\nНекорректный ввод цены.\n";
                    break;
                }
                price = stoi(tmpPrice);
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
                            "минимальной.\n";
                    break;
                }
                auto books = store.findBookInRangePrice(minPrice, maxPrice);
                if (books.empty())
                    wcout << L"\nНет книг в таком ценовом диапазоне.\n";
                for (const auto& book : books) book.Print();
            } break;

            case 6:
                wcout << L"Выход из программы.\n";
                return 0;

            default:
                wcout << L"\nНеверный выбор. Попробуйте снова.\n";
                break;
        }
    }
    return 0;
}
