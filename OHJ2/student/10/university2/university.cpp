#include "university.hh"
#include <iostream>

/*
 * Ohjelman kirjoittaja
 * Nimi: Lassi Lappalainen
 * Opiskelijanumero: 150390123
 * Käyttäjätunnus: kvlala
 * E-Mail: lassi.lappalainen@tuni.fi
 * */

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto& course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);

    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto& course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( !is_code_or_account_valid( code, ACCOUNT_NONE ) ) {
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int accountber = running_number_++;
    Account* n_account = new Account(full_name, accountber, num,
                                     email_suffix_);
    accounts_.insert({accountber, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);

    if ( !is_code_or_account_valid( CODE_NONE, account ) ) {
        return;
    }

    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if ( !is_code_or_account_valid( code, account) ) {
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if ( !is_code_or_account_valid( code, account ) ) {
        return;
    }

    if ( accounts_.at(account)->get_graduated_status() ) {
        std::cout << ALREADY_GRADUATED << std::endl;
        return;
    }

    courses_.at(code)->sign_up(accounts_.at(account));
}

void University::complete(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if ( !is_code_or_account_valid( code, account ) ) {
        return;
    }

    if ( accounts_.at(account)->complete_a_course(courses_.at(code)) == false ){
        return;
    }

    std::cout << COMPLETED << std::endl;
}

void University::print_signups(Params params)
{
    std::string code = params.at(0);
    auto iter = courses_.find(code);

    if ( !is_code_or_account_valid( code, ACCOUNT_NONE ) ) {
        return;
    }

    std::vector<Account*> course_students = iter->second->get_course_students();

    if (!course_students.empty()) {
        for (auto student : course_students) {
            student->print();
        }
    }
}

void University::print_completed(Params params)
{
    int account = std::stoi(params.at(0));
    auto iter = accounts_.find(account);

    if ( !is_code_or_account_valid( CODE_NONE, account ) ) {
        return;
    }

    std::vector<Course*> completed_courses =
            iter->second->get_completed_courses();

    if (!completed_courses.empty()) {
        for (auto course : completed_courses) {
            course->print_info(true);
        }
    }

    iter->second->print_students_total_credits();
}

void University::print_study_state(Params params)
{
    int account = std::stoi(params.at(0));
    auto iter = accounts_.find(account);

    if ( !is_code_or_account_valid( CODE_NONE, account ) ) {
        return;
    }

    std::cout << "Current:" << std::endl;
    std::vector<Course*> ongoing_courses = iter->second->get_ongoing_courses();

    if (!ongoing_courses.empty()) {
        for (auto course : ongoing_courses) {
            course->print_info(true);
        }
    }

    std::cout << "Completed:" << std::endl;
    University::print_completed(params);
}

void University::graduate(Params params)
{
    int account = std::stoi(params.at(0));
    auto iter = accounts_.find(account);

    if ( !is_code_or_account_valid( CODE_NONE, account) ) {
        return;
    }

    std::vector<Course*> ongoing_courses = iter->second->get_ongoing_courses();

    for ( auto course : ongoing_courses ) {
        iter->second->complete_a_course(course);
    }

    iter->second->graduate_student();
}

bool University::is_code_or_account_valid(std::string code, int account)
{
    // Tutkitaan löytyykö kurssia tiedoista.
    if ( code != CODE_NONE ){

        if ( courses_.find(code) == courses_.end() )
        {
            std::cout << CANT_FIND << code << std::endl;
            return false;
        }
    }

    // Tutkitaan löytyykö käyttäjää tiedoista.
    if ( account != ACCOUNT_NONE ){

        if ( accounts_.find(account) == accounts_.end() )
        {
            std::cout << CANT_FIND << account << std::endl;
            return false;
        }
    }
    return true;
}
