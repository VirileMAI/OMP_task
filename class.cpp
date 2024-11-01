#include "class.h"

#include "func.h"

Book::Book(size_t id, const wstring& title, const wstring& author, short year,
           double price)
    : _id(id), _title(title), _author(author), _year(year), _price(price) {}

size_t Book::GetID() const { return _id; }
const wstring& Book::GetTitle() const { return _title; }
const wstring& Book::GetAuthor() const { return _author; }
int Book::GetYear() const { return _year; }
double Book::GetPrice() const { return _price; }

void Book::Print() const {
    wcout << L"ID книги: " << _id << L", Название: " << _title << L", Автор: "
          << _author << L", Год: " << _year << L", Цена: " << _price << L" руб."
          << endl;
}

bool Book::operator<(const Book& other) const { return _title < other._title; }
bool Book::operator>(const Book& other) const { return _title > other._title; }
bool Book::operator==(const Book& other) const {
    return _title == other._title && _author == other._author &&
           _year == other._year && _price == other._price;
}

BookStore::BookStore() { ID = 1; }

void BookStore::addBook(const Book& book) {
    _books.push_back(Book(ID, book.GetTitle(), book.GetAuthor(), book.GetYear(),
                          book.GetPrice()));
    ID++;
}

bool BookStore::removeBook(const wstring& title) {
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

Book* BookStore::findBook(const wstring& title) {
    for (auto& book : _books)
        if (book.GetTitle() == title) return &book;
    return nullptr;
}

void BookStore::listBooks(SortType sortType) {
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

vector<Book> BookStore::findBookInRangePrice(double minPrice, double maxPrice) {
    vector<Book> result;
    for (const auto& book : _books) {
        if (book.GetPrice() >= minPrice && book.GetPrice() <= maxPrice) {
            result.push_back(book);
        }
    }
    return result;
}

size_t BookStore::ID = 1;