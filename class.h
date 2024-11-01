#ifndef CLASS
#define CLASS

#include <string>
#include <vector>
using namespace std;

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
         double price);


    size_t GetID() const;
    const wstring& GetTitle() const;
    const wstring& GetAuthor() const;
    int GetYear() const;
    double GetPrice() const;

    void Print() const;

    bool operator<(const Book& other) const;
    bool operator>(const Book& other) const;
    bool operator==(const Book& other) const;
};

class BookStore {
  private:
    vector<Book> _books;
    static size_t ID;

  public:
    BookStore();

    void addBook(const Book& book);

    bool removeBook(const wstring& title);

    Book* findBook(const wstring& title);

    void listBooks(SortType sortType);

    vector<Book> findBookInRangePrice(double minPrice, double maxPrice);
};

#endif