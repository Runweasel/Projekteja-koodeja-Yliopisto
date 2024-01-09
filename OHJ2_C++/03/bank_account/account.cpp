#include "account.hh"
#include <iostream>

using namespace std;

Account::Account (const string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::save_money(long long int summa)
{
    if ( summa < 0) {
        return;
    }
    raha += summa;
}

void Account::set_credit_limit(long long int krediitti)
{
    if ( has_credit_ == true ) {
        krediitti_ = krediitti;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }

}

void Account::take_money(long long int ota)
{

    if ( has_credit_ == true ) {
            if ( ota > krediitti_+raha ) {
                cout << "Cannot take money: credit limit overflow" << endl;
                return;
            }
            else {
                raha -= ota;
                cout << ota << " euros taken: new balance of " << iban_ << " is " << raha << " euros" << endl;
                return;
            }
        }

    if ( ota > raha ) {
        cout << "Cannot take money: balance underflow" << endl;
        return;
    }

    else {
        raha -= ota;
        cout << ota << " euros taken: new balance of " << iban_ << " is " << raha << " euros" << endl;
        return;
    }

}

void Account::transfer_to(Account &a, long long int siirto)
{

    if ( has_credit_ == true ) {
            if ( siirto > krediitti_+raha ) {
                cout << "Cannot take money: credit limit overflow" << endl;
                cout << "Transfer from " << iban_ << " failed" << endl;
                return;
            }
            else {
                raha -= siirto;
                a.raha += siirto;
                cout << siirto << " euros taken: new balance of " << iban_ << " is " << raha << " euros" << endl;
                return;
            }
        }

    if ( siirto > raha ) {
        cout << "Cannot take money: balance underflow" << endl;
        cout << "Transfer from " << iban_ << " failed" << endl;
        return;
    }

    else {
        raha -= siirto;
        a.raha += siirto;
        cout << siirto << " euros taken: new balance of " << iban_ << " is " << raha << " euros" << endl;
        return;
    }



}
void Account::print() const
{
    cout << owner_ << " : " << iban_ << " : " << raha << " euros" << endl;
}
