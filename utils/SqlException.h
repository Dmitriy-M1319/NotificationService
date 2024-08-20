#pragma once

#include <exception>
#include <string>

namespace notifications
{
namespace exceptions 
{

class SqlException: public std::exception
{
public:
    SqlException(const std::string&);
    const char *what() const noexcept override;
private:
    std::string m_info;
};

}; //exceptions
}; //notifications
