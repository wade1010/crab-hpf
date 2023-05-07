//
// Created by cepher on 5/7/23.
//
#include <string>
#include "Parser.h"

using namespace crab::json;

Parser::Parser():m_idx(0){

}
Parser::~Parser() = default;

void Parser::load(const std::string &str) {
    m_str = str;
    m_idx = 0;
}

void Parser::skip_white_spaces() {
    while (m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\n' || m_str[m_idx] == '\t')
        ++m_idx;
}

char Parser::get_next_char() {
    skip_white_spaces();
    if (m_idx==m_str.size())
        throw std::runtime_error("Unexpected end of input");
    return m_str[m_idx++];
}

Json Parser::parse_null() {
    //比较从当前索引 m_idx 开始的四个字符是否为 null
    if(m_str.compare(m_idx,4,"null") == 0){
        m_idx+=4;
        return Json();
    }
    throw std::runtime_error("parse null error");
}

Json Parser::parse_bool() {
    if(m_str.compare(m_idx,4,"true") == 0){
        m_idx+=4;
        return Json(true);
    }else if(m_str.compare(m_idx,5,"false") == 0){
        return Json(false);
    }
    throw std::runtime_error("parse bool error");
}

Json Parser::parse_number() {
    size_t pos = m_idx;
    if(m_str[m_idx] == '-')
        m_idx++;
    if (m_str[m_idx] == '0'){
        m_idx++;
        if (in_range(m_str[m_idx], '0', '9'))
            throw std::logic_error("Numbers can not begin with 0");
    }else if (in_range(m_str[m_idx], '1', '9')){
        m_idx++;
        while (in_range(m_str[m_idx], '0', '9'))
            m_idx++;
    }else{
        throw std::logic_error("Invalid character");
    }
    if(m_str[m_idx] != '.')
        return Json(std::atoi(m_str.c_str()+pos));

    if (m_str[m_idx]=='.'){
        m_idx++;
        while (!in_range(m_str[m_idx], '0', '9'))
            throw std::logic_error("at least one digit required in fractional part");
        while (in_range(m_str[m_idx], '0', '9'))
            m_idx++;
    }
    return Json(std::atof(m_str.c_str()+pos));
}

Json Parser::parse_string() {
    std::string ret;
    while (true){
        if (m_idx==m_str.size())
            throw std::runtime_error("Unexpected end of input");
        char ch = m_str[m_idx++];
        if (ch == '"')
            return Json(ret);
        // The usual case: non-escaped characters
        if (ch != '\\')
        {
            ret += ch;
            continue;
        }
        // Handle escapes
        throw std::logic_error("not support escaped characters in string");
    }
}

Json Parser::parse() {
    char ch = get_next_char();

    if (ch == 'n')
    {
        m_idx--;
        return parse_null();
    }

    if (ch == 't' || ch == 'f')
    {
        m_idx--;
        return parse_bool();
    }

    if (ch == '-' || (ch >= '0' && ch <= '9'))
    {
        m_idx--;
        return parse_number();
    }

    if (ch == '"')
    {
        return parse_string();
    }

    if (ch == '[')
    {
        Json arr(Json::Type::json_array);
        ch = get_next_char();
        if (ch == ']')
        {
            return arr;
        }
        while (true)
        {
            m_idx--;
            arr.append(parse());
            ch = get_next_char();
            if (ch == ']')
            {
                break;
            }
            if (ch != ',')
            {
                throw std::logic_error("expected ',' in array");
            }
            ch = get_next_char();
        }
        return arr;
    }


    if (ch == '{')
    {
        Json obj(Json::Type::json_object);
        ch = get_next_char();
        if (ch == '}')
        {
            return obj;
        }

        while (true)
        {
            if (ch != '"')
            {
                throw std::logic_error("expected '\"' in object");
            }
            Json j = parse_string();

            ch = get_next_char();
            if (ch != ':')
            {
                throw std::logic_error("expected ':' in object");
            }

            obj[j.asString()] = parse();

            ch = get_next_char();
            if (ch == '}')
            {
                break;
            }
            if (ch != ',')
            {
                throw std::logic_error("expected ',' in object");
            }
            ch = get_next_char();
        }
        return obj;
    }

    throw std::logic_error("unexpected character in parse json");
}

