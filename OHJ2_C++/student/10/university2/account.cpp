#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <vector>

/*
 * Ohjelman kirjoittaja
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 * */

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

void Account::completed_courses(Course* code)
{
    completed_courses_.push_back(code);
    return;
}

void Account::ongoing_courses(Course* code)
{
    ongoing_courses_.push_back(code);
    return;
}

bool Account::get_graduated_status()
{
    return graduated_;
}

void Account::graduate_student()
{
    graduated_ = true;
    std::cout << GRADUATED << std::endl;
}

void Account::print_students_total_credits()
{
    std::cout << "Total credits: " << students_total_credits_ << std::endl;
    return;
}

void Account::add_credits_to_total_credits(int credits)
{
    students_total_credits_ += credits;
    return;
}

bool Account::complete_a_course(Course *code)
{
    // Tarkistaa onko tili ilmoittautunut kurssille.
    bool signed_up = false;
    for ( unsigned int i = 0; i < code->get_course_students().size(); ++i )
    {
        if ( code->get_course_students().at(i) == this )
        {
            signed_up = true;
            break;
        }
    }
    if ( !signed_up )
    {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    }

    // Tarkistaa onko tili jo suorittanut kurssin.
    bool completed = false;
    for ( unsigned int i = 0; i < this->get_completed_courses().size(); ++i )
    {
        if ( this->get_completed_courses().at(i) == code )
        {
            completed = true;
            break;
        }
    }
    if ( completed )
    {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    }

    // Kurssin lisääminen opiskelijan suoritetuille kursseille ja sen
    // poistaminen nykyisistä kursseista, sekä opiskelijan opintopisteisiin
    // lisätään kurssin opintopisteet.
    completed_courses(code);
    add_credits_to_total_credits(code->get_credits());
    remove_from_ongoing_courses(code);
    return true;
}

std::vector<Course*> Account::get_completed_courses() const
{
    return completed_courses_;
}

std::vector<Course*> Account::get_ongoing_courses() const
{
    return ongoing_courses_;
}

void Account::remove_from_ongoing_courses(Course* code)
{
    // Poistaa kurssin meneillään olevista kursseista.
    for (auto it = ongoing_courses_.begin(); it != ongoing_courses_.end(); ++it)
    {
        if (*it == code) {
            ongoing_courses_.erase(it);
            return;
        }
    }
}


