#include "player.hh"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player():
    name_("")
{
}
Player::Player(const std::string& name):
    name_(name)
{
}

void Player::add_points(int pts) {
    points_ += pts;

    if (points_ > 50) {
        points_ = 25;
        cout << name_ << " gets penalty points!" << endl;
        return;
        }

    return;
}

bool Player::has_won() {

    if (points_ == 50) {
        return true;
    }

    return false;
}

string Player::get_name() const {
    return name_;
}

int Player::get_points() const {
    return points_;
}
