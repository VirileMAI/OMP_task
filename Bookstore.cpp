#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class SortType { TITLE, AUTHOR, YEAR };

class Book {
  private:
    string title;
    string author;
    int year;
    double price;

  public:
    Book(const string& title, const string& author, int year, double price)
        : title(title), author(author), year(year), price(price){};

    //геттеры
    const string& GetTitle() const { return title; }
    const string& GetAuthor() const { return author; }
    int GetYear() { return year; }
    double GetPrice() { return price; }

    //сеттеры
    void SetTitle(const string& newTitle) { title = newTitle; }
    void SetAuthor(const string& newAuthor) { author = newAuthor; }
    void SetYear(int newYear) { year = newYear; }
    void SetPrice(double newPrice) { price = newPrice; }

    void Print() {
        cout << "Название: " << title << ", Автор: " << author
             << ", Год: " << year << ", Цена: " << price << " руб." << endl;
    }
};

class BookStore {
  private:
    vector<Book> books;

  public:
    void addBook(const Book& book) { books.push_back(book); }
};

int main() {
    Book book1("Война и мир", "Л.Н. Толстой", 1862, 2000);

    book1.Print();

    return 0;
}