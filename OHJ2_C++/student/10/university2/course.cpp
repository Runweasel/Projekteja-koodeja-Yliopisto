#include "course.hh"
#include <iostream>

/*
 * Ohjelman kirjoittaja
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 * */

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::sign_up(Account *new_student_member)
{
    // Tarkistaa onko tili jo suorittanut kurssin
    bool completed = false;
    for ( unsigned int i = 0;
          i < new_student_member->get_completed_courses().size(); ++i ) {
        if ( new_student_member->get_completed_courses().at(i) == this )
        {
            completed = true;
            break;
            }
        }
        if ( completed )
        {
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }

    // Tarkistaa onko tili jo kurssilla   
    for ( unsigned int i = 0; i < course_students_.size(); ++i )
    {
        if ( course_students_.at(i) == new_student_member )
        {
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }
    }  

    // Lisätään henkilö kurssille, sekä kurssi henkilölle.
    course_students_.push_back(new_student_member);
    new_student_member->ongoing_courses(this);

    std::cout << SIGNED_UP << std::endl;
}

std::vector<Account*> Course::get_course_students() const
{
    return course_students_;
}

std::string Course::get_course_name() const
{
    return name_;
}


