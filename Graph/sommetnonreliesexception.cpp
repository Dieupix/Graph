#include "sommetsnonreliesexception.h"

SommetsNonReliesException::SommetsNonReliesException(char const* const message) throw() : runtime_error{message}
{}

char const* SommetsNonReliesException::what() const throw()
{
    return runtime_error::what();
}
