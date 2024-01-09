#include "book.hh"
#include "date.hh"
#include <iostream>

using namespace std;

Book::Book():
    surname_(""), name_(""), available_(true) {

}

Book::Book(const string& surname, const string& name ):
    surname_(surname), name_(name), available_(true) {

}

void Book::print() {
    cout << surname_ << " : " << name_ << endl;
    if ( available_ == false) {
        cout << "- loaned: ";
        loaned_.print();
        cout << "- to be returned: ";
        returned_.print();
    }
    if ( available_ == true) {
        cout << "- available" << endl;
    }
    return;
}
void Book::loan(Date& date) {
    if ( available_ == true) {
        available_ = false;
        loaned_ = date;
        returned_ = date;
        returned_.advance(28);
        return;
    }
    if ( available_ == false) {
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }
}
void Book::renew() {
    if ( available_ == false) {
        returned_.advance(28);
    }
    if ( available_ == true) {
        cout << "Not loaned: cannot be renewed" << endl;
    }

    return;
}
void Book::give_back() {
    available_ = true;
    return;
}
