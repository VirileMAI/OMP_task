#ifndef CLASS
#define CLASS

#include <string>
#include <vector>
using namespace std;

// Перечисление для сортировки книг по параметрам: названию, автору или году
// издания
enum class SortType { TITLE, AUTHOR, YEAR };

//Класс, представляющий книгу
class Book {
  private:
    size_t _id;
    wstring _title;
    wstring _author;
    short _year;
    double _price;

  public:
    //Конструктор
    Book(size_t id, const wstring& title, const wstring& author, short year,
         double price);

    //Геттеры
    size_t GetID() const;
    const wstring& GetTitle() const;
    const wstring& GetAuthor() const;
    int GetYear() const;
    double GetPrice() const;

    //Вывод информации о книге
    void Print() const;

    //Операторы для сортировки и сравнения книг
    bool operator<(const Book& other) const;
    bool operator>(const Book& other) const;
    bool operator==(const Book& other) const;
};

//Класс, представляющий магазин(хранилище) книг
class BookStore {
  private:
    vector<Book> _books;
    static size_t ID;

  public:
    //Конструктор
    BookStore();

    //Добавление книги в магазин
    void addBook(const Book& book);

    //Удаление книги из магазина по названию
    bool removeBook(const wstring& title);

    //Поиск книги по названию
    Book* findBook(const wstring& title);

    //Вывод списка отсортированных по параметру книг
    void listBooks(SortType sortType);

    //Поиск книг в ценовом диапазоне
    vector<Book> findBookInRangePrice(double minPrice, double maxPrice);
};

#endif