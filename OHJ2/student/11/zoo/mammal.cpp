#include "mammal.hh"

Mammal::Mammal() : Animal("Kip kop kip kop"), suckling_noise_("Mus mus")
{

}

void Mammal::suckle(std::ostream& output) const
{
    output << suckling_noise_ << std::endl;
}
