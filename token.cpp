#include "token.hpp"

Token::Token(TokenType type, std::size_t line) : m_type(type), m_line(line) {}

Token::Token(TokenType type, std::size_t line, const std::string &value)
    : m_type(type), m_line(line), m_value(value) {}


void Token::setType(TokenType type)  {
    m_type = type;
}
TokenType Token::type() const { return m_type; }

std::size_t Token::line() const { return m_line; }

std::string Token::value() const { return m_value; }

bool operator==(const Token &t1, const Token &t2) {
  return (t1.type() == t2.type()) && (t1.line() == t2.line()) &&
         (t1.value() == t2.value());
}

bool operator!=(const Token &t1, const Token &t2) { return !(t1 == t2); }

std::ostream &operator<<(std::ostream &oss, const Token &t) {
  //oss << "Token: type(" << t.type() << ") value (" << t.value()
  //    << ") source line (" << t.line() << ")";
    oss  << t.value() << " ";
    if (t.type() == EOL) {
        oss << "(EOL) ";
    }
    else if (t.type() == SEP) {
        oss << "(SEP) ";
    }
    else if (t.type() == EQUAL) {
        oss << "(EQUAL) ";
    }
    else if (t.type() == OPEN_PAREN) {
        oss << "(OPEN_PAREN) ";
    }
    else if (t.type() == CLOSE_PAREN) {
        oss << "(CLOSE_PAREN) ";
    }
    else if (t.type() == STRING_DELIM) {
        oss << "(STRING_DELIM) ";
    }
    else if (t.type() == STRING) {
        oss << "(STRING) ";
    }
    else if (t.type() == ERROR) {
        oss << "(ERROR) ";
    }
    else if (t.type() == COMMENT) {
        oss << "(COMMENT) ";
    }
  return oss;
}
