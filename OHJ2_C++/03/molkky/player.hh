#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

class Player
{
public:
    Player();
    Player(const std::string& name);

    void add_points(int pts);
    int get_points() const;

    std::string get_name() const;

    bool has_won();

    std::string in_turn() const;

private:

    int points_ = 0;
    std::string name_ = "";


};

#endif // PLAYER_HH
