#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <limits>

using namespace std;

bool is_digits(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

bool is_not_alphas(const std::string& str) {
    for (char ch : str) {
        if (isdigit(ch))
            return true;
    }
    return false; 
}

enum class SortType { TITLE, AUTHOR, YEAR };

class Book {
private:
    size_t _id;
    string _title;
    string _author;
    short _year;
    double _price;

public:
    Book(size_t id, const string& title, const string& author, short year, double price)
        : _id(id), _title(title), _author(author), _year(year), _price(price) {}

    // Геттеры
    size_t GetID() const { return _id; }
    const string& GetTitle() const { return _title; }
    const string& GetAuthor() const { return _author; }
    int GetYear() const { return _year; }
    double GetPrice() const { return _price; }

    void Print() const {
        cout << "ID книги: " << _id << " Название: " << _title
             << ", Автор: " << _author << ", Год: " << _year
             << ", Цена: " << _price << " руб." << endl;
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
        _books.push_back(Book(ID, book.GetTitle(), book.GetAuthor(), book.GetYear(), book.GetPrice()));
        ID++;
    }

    bool removeBook(const string& title) {
    vector<Book*> titleName;

    for (auto& book : _books) {
        if (book.GetTitle() == title) {
            titleName.push_back(&book);
        }
    }

    if (titleName.empty()) {
        cout << "Книга с таким названием не найдена.\n";
        return false;
    }

    cout << "Найдено несколько книг с названием \"" << title << "\":\n";
    for (const auto& book : titleName) {
        book->Print();
    }

    cout << "Введите ID книги для удаления: ";
    size_t delID;
    cin >> delID;

    for (auto it = _books.begin(); it != _books.end(); ++it) {
        if (it->GetID() == delID) {
            _books.erase(it);
            cout << "Книга с ID " << delID << " удалена.\n";
            return true;
        }
    }

    cout << "Книга с указанным ID не найдена.\n";
    return false;
}


    Book* findBook(const string& title) {
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
                cout << "Неподходящий параметр.\n";
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
    cout << "\n1. Добавить книгу\n"
         << "2. Удалить книгу.\n"
         << "3. Найти книгу по названию.\n"
         << "4. Показать все книги (Отсортированные по названию/автору/году издания)\n"
         << "5. Найти все книги в ценовом диапазоне.\n"
         << "6. Выйти.\n"
         << "Выберите опцию: ";
}

int main() {
    BookStore store;
    string tmpChoice;
    int choice;

    while (true) {
        Menu();
        getline(cin, tmpChoice);

        if (tmpChoice.empty()) continue;
        if (!is_digits(tmpChoice)) {
            cout << "Неправильный ввод. Попробуйте снова.\n";
            continue;
        }

        choice = stoi(tmpChoice);
        string title, author, tmpYear, tmpPrice;
        int year;
        double price;   

        switch (choice) {
            case 1: {
                cout << "Введите название: ";
                getline(cin, title);

                cout << "Введите автора: ";
                getline(cin, author);

                if (is_not_alphas(author)) {
                    cout << "Некорректное имя автора, могут быть только буквы.\n";
                    break;
                }

                cout << "Введите год издания: ";
                getline(cin, tmpYear);
                if (!is_digits(tmpYear) || stoi(tmpYear) < 1 || stoi(tmpYear) > 2024)
                {
                    cout << "Некорректный ввод даты.\n";
                    break;
                }
                year = stoi(tmpYear);

                cout << "Введите цену: ";
                getline(cin, tmpPrice);
                if (!is_digits(tmpPrice) || stoi(tmpPrice) < 0 || stoi(tmpPrice) > numeric_limits<int>::max())
                {
                    cout << "Некорректный ввод даты.\n";
                    break;
                }
                price = stoi(tmpPrice);
                store.addBook(Book(0, title, author, year, price));
                cout << "Книга добавлена.\n";
            } break;

            case 2: {
                cout << "Введите название книги для удаления: ";
                getline(cin, title);
                store.removeBook(title);
            } break;

            case 3: {
                cout << "Введите название книги для поиска: ";
                getline(cin, title);
                Book* book = store.findBook(title);
                if (book) {
                    book->Print();
                } else {
                    cout << "Книга не найдена.\n";
                }
            } break;

            case 4: {
                int sortOption;
                cout << "Сортировать по: 1. Названию, 2. Автору, 3. Году издания\n";
                cin >> sortOption;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                store.listBooks(static_cast<SortType>(sortOption - 1));
            } break;

            case 5: {
                string tmpMin, tmpMax;
                double minPrice, maxPrice;
                cout << "Введите минимальную цену: ";
                getline(cin, tmpMin);
                if (!is_digits(tmpMin) || stoi(tmpMin) < 0 || stoi(tmpMin) > numeric_limits<int>::max())
                {
                    cout << "Введенна некоректная цена.\n";
                    break;
                }
                minPrice = stoi(tmpMin);
                cout << "Введите максимальную цену: ";
                getline(cin, tmpMax);
                if (!is_digits(tmpMax) || stoi(tmpMax) < 0 || stoi(tmpMax) > numeric_limits<int>::max())
                {
                    cout << "Введенна некоректная цена.\n";
                    break;
                }
                maxPrice = stoi(tmpMax);
                auto books = store.findBookInRangePrice(minPrice, maxPrice);
                if (books.empty()) cout << "Нет книг в таком ценовом диапазоне.\n";
                for (const auto& book : books) book.Print();
            } break;

            case 6:
                cout << "Выход из программы.\n";
                return 0;

            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }
    return 0;
}
