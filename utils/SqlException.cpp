#include "SqlException.h"

using namespace notifications::exceptions;

SqlException::SqlException(const std::string& message): m_info(message){}


const char *SqlException::what() const noexcept
{
    return m_info.c_str();
}
