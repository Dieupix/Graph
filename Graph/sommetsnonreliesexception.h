#ifndef SOMMETSNONRELIESEXCEPTION_H
#define SOMMETSNONRELIESEXCEPTION_H

#include <iostream>
#include <string>

using std::string;
using std::runtime_error;

class SommetsNonReliesException : public runtime_error
{
public:
    SommetsNonReliesException(char const* const message) throw();

    virtual char const* what() const throw();
};

#endif // SOMMETSNONRELIESEXCEPTION_H
