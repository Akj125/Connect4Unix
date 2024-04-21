#pragma once

#include <exception>

class colonnePleineException : public std::exception
{
public:
    const char* what() const throw()
    {
        return "La colonne est pleine";
    }
};

class colonneInvalideException : public std::exception
{
public:
    const char* what() const throw()
    {
        return "La colonne est invalide";
    }
};