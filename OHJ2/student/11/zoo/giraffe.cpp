#include "giraffe.hh"
#include "animal.hh"
#include "mammal.hh"

Giraffe::Giraffe()
{

}

void Giraffe::make_noise(std::ostream& output) const
{
    output << "Ori ori ori!" << std::endl;
}
