/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

const int NO_CREDITS_YET = 0;

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief add the course to completed_courses
     * @param course
     */
    void completed_courses(Course*);

    /**
     * @brief get_completed_courses
     * @return accounts completed courses
     */
    std::vector<Course*> get_completed_courses() const;

    /**
     * @brief add the course to ongoing_courses
     * @param course
     */
    void ongoing_courses(Course*);

    /**
     * @brief get_ongoing_courses
     * @return accounts ongoing courses
     */
    std::vector<Course*> get_ongoing_courses() const;

    /**
     * @brief complete_a_course
     * @param course
     * @return true or false. Returns true if the completation is successfull
     * and false if not. False occurs if the student have already completed the
     * course or student is not part of the course
     */
    bool complete_a_course(Course* code);

    /**
     * @brief get_graduated_status
     * @return true or false if the account is graduated or not
     */
    bool get_graduated_status();

    /**
     * @brief graduate_student and change graduated_ to value true
     */
    void graduate_student();

    /**
     * @brief print_students_total_credits
     */
    void print_students_total_credits();

    /**
     * @brief add_credits_to_total_credits
     * @param credits
     */
    void add_credits_to_total_credits(int credits);

    /**
     * @brief remove_from_ongoing_courses the course
     * @param course
     */
    void remove_from_ongoing_courses(Course* code);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    int students_total_credits_ = NO_CREDITS_YET;
    std::vector<Course*> completed_courses_; // Tilin suoritetut kurssit
    std::vector<Course*> ongoing_courses_; // Tilin meneillään olevat kurssit
    bool graduated_ = false;

};

#endif // ACCOUNT_HH
