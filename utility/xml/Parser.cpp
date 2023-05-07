//
// Created by cepher on 5/7/23.
//
#include <fstream>
#include <string>
#include "Parser.h"

using namespace crab::xml;

Parser::Parser() = default;

Parser::~Parser() = default;

void Parser::load_file(const std::string &filename) {
    std::fstream fin(filename);
    std::string line;
    while (std::getline(fin, line)) {
        m_str += line;
    }
    m_idx = 0;
}


void Parser::skip_white_spaces() {
    while (m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\t' || m_str[m_idx] == '\n')
        m_idx++;
}

Element Parser::parse(bool is_child) {

    if (!is_child) {
        skip_white_spaces();
        //解析xml声明
        if (m_idx == m_str.size() || m_str[m_idx] == '\0')
            throw std::logic_error("xml file is empty");
        size_t pos = m_str.find("<?xml", m_idx);
        if (pos == m_idx && !parse_declaration())
            throw std::logic_error("xml declaration is error");
        skip_white_spaces();
    }

    //解析xml注释
    if (m_str.find("<!--", m_idx) == m_idx) {
        if (!parse_comment())
            throw std::logic_error("xml comment is error");
        skip_white_spaces();
    }

    Element element;
    std::string name;
    if (m_str[m_idx] == '<' && isalpha(m_str[m_idx + 1]) || m_str[m_idx + 1] == '_') {
        m_idx++;
        //解析元素name
        name = parse_element_name();
        element.name(name);
        skip_white_spaces();

        while (m_str[m_idx] != '\0') {
            //空tag
            if (m_str[m_idx] == '/') {
                if (m_str[m_idx + 1] == '>') {
                    m_idx += 2;
                    return element;
                } else {
                    throw std::logic_error("xml empty element is error");
                }
            } else if (m_str[m_idx] == '<') {
                if (m_str[m_idx + 1] == '/') {
                    std::string end_tag = "</" + name + ">";
                    size_t pos = m_str.find(end_tag, m_idx);
                    if (pos == std::string::npos) {
                        throw std::logic_error("xml element " + name + " end tag not found");
                    }
                    if (pos == m_idx) {
                        m_idx += end_tag.size();
                        return element;
                    }
                } else if (m_str.find("<!--", m_idx) == m_idx) {
                    //解析xml comment
                    if (!parse_comment())
                        throw std::logic_error("xml comment is error");
                } else {
                    //解析child
                    Element child = parse();
                    element.append(child);
                }
            } else if (m_str[m_idx] == '>') {
                m_idx++;
                std::string text = parse_element_text();
                skip_white_spaces();
                if (!text.empty()) {
                    element.text(text);
                } else {
                    //解析child
                    Element child = parse();
                    element.append(child);
                }
            } else {
                //解析 元素 attr
                std::string key = parse_element_attr_key();
                skip_white_spaces();
                if (m_str[m_idx] !=  '=')
                    throw std::logic_error("xml element attr is error,key=" + key);
                m_idx++;
                element.attr(key, parse_element_attr_value());
            }
            skip_white_spaces();
        }
    }
    return element;
}

bool Parser::parse_declaration() {
    size_t pos = m_str.find("?>", m_idx);
    if (pos == std::string::npos)
        return false;
    m_idx = pos + 2;
    return true;
}

bool Parser::parse_comment() {
    size_t pos = m_str.find("-->", m_idx);
    if (pos == std::string::npos)
        return false;
    m_idx = pos + 3;
    return true;
}

std::string Parser::parse_element_name() {
    skip_white_spaces();
    std::string ret;
    if (std::isalpha(m_str[m_idx]) || m_str[m_idx] == '_') {
        ret += m_str[m_idx];
        m_idx++;
        while (m_str[m_idx] != '\0' &&
               (std::isalnum(m_str[m_idx]) || m_str[m_idx] == '_' || m_str[m_idx] == '-' || m_str[m_idx] == ':')) {
            ret += m_str[m_idx];
            m_idx++;
        }
    }
    return ret;
}

std::string Parser::parse_element_text() {
    skip_white_spaces();
    std::string ret;
    while (m_str[m_idx] != '<') {
        ret += m_str[m_idx];
        m_idx++;
    }
    return ret;
}

std::string Parser::parse_element_attr_key() {
    skip_white_spaces();
    std::string ret;
    if (std::isalpha(m_str[m_idx]) || m_str[m_idx] == '_') {
        ret += m_str[m_idx];
        m_idx++;
        while (m_str[m_idx] != '\0' &&
               (std::isalnum(m_str[m_idx]) || m_str[m_idx] == '_' || m_str[m_idx] == '-' || m_str[m_idx] == ':')) {
            ret += m_str[m_idx];
            m_idx++;
        }
    }
    return ret;
}

std::string Parser::parse_element_attr_value() {
    skip_white_spaces();
    if (m_str[m_idx] != '"')
        throw std::logic_error("xml element attr value is error");
    m_idx++;
    std::string ret;
    while (m_str[m_idx] != '"') {
        ret += m_str[m_idx];
        m_idx++;
    }
    m_idx++;
    return ret;
}
