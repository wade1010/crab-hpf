//
// Created by cepher on 5/7/23.
//

#include <fstream>
#include <iostream>
#include <utility>
#include "IniFile.h"

using namespace crab::ini;

Value::Value() = default;

Value::~Value() = default;

Value::Value(bool value) {
    *this = value;
}

Value::Value(int value) {
    *this = value;
}

Value::Value(double value) {
    *this = value;
}

Value::Value(std::string value) : m_value(std::move(value)) {

}

Value::Value(const char *value) : m_value(std::string(value)) {

}

Value &Value::operator=(bool value) {
    m_value = value ? "true" : "false";
    return *this;
}

Value &Value::operator=(int value) {
    m_value = std::to_string(value);
    return *this;
}

Value &Value::operator=(double value) {
    m_value = std::to_string(value);
    return *this;
}

Value &Value::operator=(const std::string &value) {
    m_value = value;
    return *this;
}

Value &Value::operator=(const char *value) {
    m_value = value;
    return *this;
}

Value::operator bool() const {
    return m_value == "true";
}

Value::operator int() const {
    return std::stoi(m_value);
}

Value::operator double() const {
    return std::atof(m_value.c_str());
}

Value::operator std::string() {
    return m_value;
}

Value::operator std::string() const {
    return m_value;
}


IniFile::IniFile() = default;

IniFile::IniFile(const std::string &filename) {
    load_file(filename);
}

IniFile::~IniFile() = default;


bool IniFile::load_file(const std::string &filename) {
    m_filename = filename;
    m_ini_file.clear();
    std::string name;
    std::string line;
    std::ifstream fin(filename.c_str());
    if (fin.fail()) {
        std::cout << "loading file failed:" << m_filename << "is not found" << std::endl;
        return false;
    }
    while (std::getline(fin, line)) {
        line = trim(line);
        //section
        if (line[0] == '[') {
            size_t pos = line.find_first_of(']');
            if (pos != std::string::npos)
                name = trim(line.substr(1, pos - 1));
        } else if (line[0] == '#') {//注释
            continue;
        } else {
            size_t pos = line.find_first_of('=');
            if (pos != std::string::npos && pos > 0) {
                std::string key = trim(line.substr(0, pos));
                std::string value = trim(line.substr(pos + 1, line.size() - pos - 1));
                if (name.empty()) {
                    name = "default";
                }
                m_ini_file[name][key] = value;
            }
        }
    }
    return true;
}

void IniFile::save(const std::string &filename) {
    std::ofstream fout(filename.c_str());
    for (const auto &section: m_ini_file) {
        fout << "[" << section.first << "]" << std::endl;
        for (const auto &item: section.second) {
            fout << item.first << "=" << std::string(item.second) << std::endl;
        }
        fout << std::endl;
    }
}

void IniFile::show() {
    Thread    for (const auto &section: m_ini_file) {
        std::cout << "[" << section.first << "]" << std::endl;
        for (const auto &item: section.second) {
            std::cout << item.first << "=" << std::string(item.second) << std::endl;
        }
        std::cout << std::endl;
    }
}

void IniFile::clear() {
    m_ini_file.clear();
}

Value &IniFile::get(const std::string &section, const std::string &key) {
    return m_ini_file[section][key];
}

void IniFile::set(const std::string &section, const std::string &key, bool value) {
    m_ini_file[section][key] = value;
}

void IniFile::set(const std::string &section, const std::string &key, int value) {
    m_ini_file[section][key] = value;
}

void IniFile::set(const std::string &section, const std::string &key, const char *value) {
    m_ini_file[section][key] = value;
}

void IniFile::set(const std::string &section, const std::string &key, const std::string &value) {
    m_ini_file[section][key] = value;
}

bool IniFile::has(const std::string &section) {
    return m_ini_file.find(section) != m_ini_file.end();
}

bool IniFile::has(const std::string &section, const std::string &key) {
    auto it = m_ini_file.find(section);
    return it != m_ini_file.end() && it->second.find(key) != it->second.end();
}

void IniFile::remove(const std::string &section) {
    m_ini_file.erase(section);
}

void IniFile::remove(const std::string &section, const std::string &key) {
    auto it = m_ini_file.find(section);
    if (it != m_ini_file.end()) {
        auto iter = it->second.find(key);
        if (iter != it->second.end()) {
            it->second.erase(iter);
        }
    }
}

IniFile::Section &IniFile::operator[](const std::string &key) {
    return m_ini_file[key];
}

std::string IniFile::trim(std::string s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}





