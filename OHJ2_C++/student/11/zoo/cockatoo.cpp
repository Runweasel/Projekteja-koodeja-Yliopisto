#include "cockatoo.hh"

Cockatoo::Cockatoo() : Bird(), song_("Kee-ow kee-ow!")
{

}

void Cockatoo::sing(std::ostream& output) const
{
    output << song_ << std::endl;
}
