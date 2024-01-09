#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"

class Book
{
public:
    Book();
    Book(const std::string& surname, const std::string& name);

    void print();
    void loan(Date &day);
    void renew();
    void give_back();

private:
    std::string surname_ = "";
    std::string name_ = "";

    Date loaned_;
    Date returned_;

    bool available_ = true;

};

#endif // BOOK_HH
