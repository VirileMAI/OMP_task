#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

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

    void Print() {
        cout << "ID книги: " << _id << "Название: " << _title
             << ", Автор: " << _author << ", Год: " << _year
             << ", Цена: " << _price << " руб." << endl;
    }
};


class BookStore {
  private:
    vector<Book> _books;

  public:
    void addBook(const Book& book) { _books.push_back(book); }

    void removeBook(const string& title) {
        for (auto it = _books.begin(); it < _books.end();) {
            if (it->GetTitle() == title) {
                _books.erase(it);
                return;
            } else it++;
        }
    }

    Book* findBook(const string& title) {
        for (auto it = _books.begin(); it < _books.end();)
            if (it->GetTitle() == title) return &(*it);
        return nullptr;
    }

    void listsBook() {
        for (int i = 0; i < _books.size(); i++) {
            _books[i].Print();
        }
        
    }

};

void Menu() {
    cout << "1. Добавить книгу\n"
         << "2. Удалить книгу.\n"
         << "3. Найти книгу по названию.\n"
         << "4. Показать все книги (Отсортированные по "
            "названию/автору/году издания)\n"
         << "5. Найти все книги в ценовом диапазоне.\n"
         << "6. Выйти.\n" << "Выберите опцию: ";
}

int main() {
    BookStore store;
    int choice;

    while (true) {
        Menu();
        cin >> choice;

        string title, author;
        int year;
        double price;

        switch (choice) {
            case 1:
                {cout << "Введите название: ";
                cin.ignore();
                getline(cin, title);
                cout << "Введите автора: ";
                getline(cin, author);
                cout << "Введите год издания: ";
                cin >> year;
                cout << "Введите цену: ";
                cin >> price;
                store.addBook(Book(1, title, author, year, price));
                cout << "Книга добавлена.\n";}
                break;

            case 2:
              {  cout << "Введите название книги для удаления: ";
                cin.ignore(1, '\n');
                getline(cin, title);
                store.removeBook(title);
                cout << "Книга удалена.\n";}
                break;

            case 3:
                {cout << "Введите название книги для поиска: ";
                cin.ignore(1, '\n');
                getline(cin, title);
                Book* book = store.findBook(title);
                if (book) {
                    book->Print();
                } else {
                    cout << "Книга не найдена.\n";
                }}
                break;

            case 4:
                store.listsBook();
                break;

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
