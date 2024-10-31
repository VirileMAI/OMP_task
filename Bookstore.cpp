#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool is_digits(string& str)
{
    for (char ch : str) {
        int v = ch;
        if (!isdigit(ch)) {
            return false;
        }
    }
 
    return true;
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
    Book(size_t id, const string& title, const string& author, short year,
         double price)
        : _id(id), _title(title), _author(author), _year(year), _price(price){};

    //геттеры
    size_t GetID() { return _id; }
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
        _books.push_back(Book(ID, book.GetAuthor(), book.GetTitle(), book.GetYear(), book.GetPrice())); 
        ID++;
    }

    void removeBook(const string& title) {
        for (auto it = _books.begin(); it < _books.end();) {
            if (it->GetTitle() == title) {
                _books.erase(it);
                return;
            } else it++;
        }
    }

    Book* findBook(const string& title) {
        for (auto it = _books.begin(); it < _books.end(); it++)
            if (it->GetTitle() == title) return &(*it);
        return nullptr;
    }

    void listBooks(SortType sortType) {
        switch (sortType) {
            case SortType::TITLE:
                sort(_books.begin(), _books.end());
                break;
            case SortType::AUTHOR:
                sort(_books.begin(), _books.end(), compareByAuthor);
            case SortType::YEAR:
                sort(_books.begin(), _books.end(), compareByYear);
            default:
                cout << "Неподходящий параметр.\n";
                break;
        }

        for (const auto& book : _books) book.Print();
    }

    vector<Book> findBookInRangePrice(double minPrice, double maxPrice) {
        vector<Book> result;
        for (auto it = _books.begin(); it < _books.end(); it++) {
            if (it->GetPrice() >= minPrice && it->GetPrice() <= maxPrice) {
                result.push_back(*it);
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
         << "4. Показать все книги (Отсортированные по "
            "названию/автору/году издания)\n"
         << "5. Найти все книги в ценовом диапазоне.\n"
         << "6. Выйти.\n"
         << "Выберите опцию: ";
}

int main() {
    BookStore store;
    string tmp;
    int choice;

    while (true) {
        Menu();
        getline(cin, tmp);

        if (tmp.empty()) 
        {
            continue;
        }
        if (!is_digits(tmp))
        {
            cout << "Неправильный ввод. Попробуйте снова.\n";
            continue;
        }
        
        choice = atoi(tmp.c_str());
        string title, author;
        int year;
        double price;

        switch (choice) {
            case 1: {
                cout << "Введите название: ";
                cin.ignore(1, '\n');
                getline(cin, title);
                cout << "Введите автора: ";
                getline(cin, author);
                cout << "Введите год издания: ";
                cin >> year;
                cout << "Введите цену: ";
                cin >> price;
                store.addBook(Book(0, title, author, year, price));
                cout << "Книга добавлена.\n";
            } break;

            case 2: {
                cout << "Введите название книги для удаления: ";
                cin.ignore(1, '\n');
                getline(cin, title);
                store.removeBook(title);
                cout << "Книга удалена.\n";
            } break;

            case 3: {
                cout << "Введите название книги для поиска: ";
                cin.ignore(1, '\n');
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
                cout << "Сортировать по: 1. Названию, 2. Автору, 3. Году "
                        "издания\n";
                cin >> sortOption;
                store.listBooks((SortType)(sortOption - 1));
            } break;

            case 5: {
                double minPrice, maxPrice;
                cout << "Введите минимальную цену: ";
                cin >> minPrice;
                cout << "ВВедите максимальную цену: ";
                cin >> maxPrice;
                auto books = store.findBookInRangePrice(minPrice, maxPrice);
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
