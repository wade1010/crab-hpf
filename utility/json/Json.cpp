//
// Created by cepher on 5/7/23.
//

#include <algorithm>
#include <sstream>
#include "Json.h"
#include "Parser.h"

using namespace crab::json;

static const Json null_json;

Json::Json() : m_type(Type::json_null), m_int(0), m_double(0.0), m_bool(false) {

}

Json::Json(Json::Type type) : m_type(type), m_int(0), m_double(0.0), m_bool(false) {

}

Json::Json(bool value) {
    m_type = Type::json_bool;
    m_bool = value;
}

Json::Json(int value) {
    m_type = Type::json_int;
    m_int = value;
}

Json::Json(double value) {
    m_type = Type::json_double;
    m_double = value;
}

Json::Json(const char *value) {
    m_type = Type::json_string;
    m_string = value;
}

Json::Json(const std::string &value) {
    m_type = Type::json_string;
    m_string = value;
}

Json::Json(const Json &other) {
    copy(other);
}

Json::~Json() {
    clear();
}

Json::Type Json::type() const {
    return Json::m_type;
}

bool Json::isNull() const {
    return type() == Type::json_null;
}

bool Json::isBool() const {
    return type() == Type::json_bool;
}

bool Json::isInt() const {
    return type() == Type::json_int;
}

bool Json::isDouble() const {
    return type() == Type::json_double;
}

bool Json::isString() const {
    return type() == Type::json_string;
}

bool Json::isArray() const {
    return type() == Type::json_array;
}

bool Json::isObject() const {
    return type() == Type::json_object;
}

bool Json::asBool() const {
    if (type() != Type::json_bool) {
        throw std::runtime_error("Not a bool");
    }
    return m_bool;
}

int Json::asInt() const {
    if (type() != Type::json_int) {
        throw std::runtime_error("Not an int");
    }
    return m_int;
}

double Json::asDouble() const {
    if (type() != Type::json_double) {
        throw std::runtime_error("Not a double");
    }
    return m_double;
}

std::string Json::asString() const {
    if (type() != Type::json_string) {
        throw std::runtime_error("Not a string");
    }
    return m_string;
}

void Json::copy(const Json &other) {
    clear();
    m_type = other.m_type;
    switch (m_type) {
        case Type::json_null:
            break;
        case Type::json_bool:
            m_bool = other.m_bool;
            break;
        case Type::json_int:
            m_int = other.m_int;
            break;
        case Type::json_double:
            m_double = other.m_double;
            break;
        case Type::json_string:
            m_string = other.m_string;
            break;
        case Type::json_array:
            m_array = other.m_array;
            break;
        case Type::json_object:
            m_object = other.m_object;
            break;
        default:
            break;
    }
}

size_t Json::size() {
    switch (type()) {
        case Type::json_array:
            return m_array.size();
        case Type::json_object:
            return m_object.size();
        default:
            break;
    }
    throw std::logic_error("size():type not supported");
}

bool Json::empty() {
    switch (type()) {
        case Type::json_array:
            return m_array.empty();
        case Type::json_object:
            return m_object.empty();
        default:
            break;
    }
    throw std::logic_error("empty():type not supported");
}

void Json::clear() {
    m_int = 0;
    m_double = 0.0;
    m_bool = false;
    m_string.clear();
    m_array.clear();
    m_object.clear();
}

bool Json::remove(size_t index) {
    if (type() != Type::json_array)
        return false;
    size_t size = m_array.size();
    if (index >= size)
        return false;
    m_array.erase(m_array.begin() + long(index));
    return true;
}

bool Json::remove(const char *key) {
    return remove(std::string(key));
}

bool Json::remove(const std::string &key) {
    if (type() != Type::json_object)
        return false;
    auto it = m_object.find(key);
    if (it == m_object.end())
        return false;
    m_object.erase(it);
    return true;
}

bool Json::has(size_t index) {
    if (type() != Type::json_array)
        return false;
    return index < m_array.size();
}

bool Json::has(const char *key) {
    return has(std::string(key));
}

bool Json::has(const std::string &key) {
    if (type() != Type::json_object)
        return false;
    return m_object.find(key) != m_object.end();
}

const Json &Json::get(size_t index) const {
    if (type() != Type::json_array)
        throw std::logic_error("type not supported");
    if (index < m_array.size())
        return m_array[index];
    return null_json;
}

const Json &Json::get(const char *key) const {
    return get(std::string(key));
}

const Json &Json::get(const std::string &key) const {
    if (type() != Type::json_object)
        throw std::logic_error("type not supported");
    auto it = m_object.find(key);
    if (it != m_object.end())
        return it->second;
    return null_json;
}

void Json::set(const Json &other) {
    copy(other);
}

void Json::set(bool value) {
    clear();
    m_type = Type::json_bool;
    m_bool = value;
}

void Json::set(int value) {
    clear();
    m_type = Type::json_int;
    m_int = value;
}

void Json::set(double value) {
    clear();
    m_type = Type::json_double;
    m_double = value;
}

void Json::set(const char *value) {
    set(std::string(value));
}

void Json::set(const std::string &value) {
    clear();
    m_type = Type::json_string;
    m_string = value;
}

Json &Json::append(const Json &other) {
    if (type() == Type::json_null) {
        m_type = Type::json_array;
    } else if (type() != Type::json_array) {
        throw std::logic_error("append:type not supported");
    }
    m_array.push_back(other);
    return *this;
}

Json &Json::operator=(const Json &other) {
    copy(other);
    return *this;
}

Json &Json::operator=(bool value) {
    Json other(value);
    copy(other);
    return *this;
}

Json &Json::operator=(int value) {
    Json other(value);
    copy(other);
    return *this;
}

Json &Json::operator=(double value) {
    Json other(value);
    copy(other);
    return *this;
}

Json &Json::operator=(const char *value) {
    Json other(value);
    copy(other);
    return *this;
}

Json &Json::operator=(const std::string &value) {
    Json other(value);
    copy(other);
    return *this;
}

bool Json::operator==(const Json &other) const {
    if (type() != other.m_type)
        return false;
    switch (type()) {
        case Type::json_null:
            return true;
        case Type::json_bool:
            return m_bool == other.m_bool;
        case Type::json_int:
            return m_int == other.m_int;
        case Type::json_double:
            return m_double == other.m_double;
        case Type::json_string:
            return m_string == other.m_string;
        case Type::json_array:
            if (m_array.size() != other.m_array.size())
                return false;
            for (size_t i = 0; i < m_array.size(); i++) {
                if (m_array[i] != other.m_array[i])
                    return false;
            }
            return true;
        case Type::json_object:
            if (m_object.size() != other.m_object.size())
                return false;
//            for(const auto &p:m_object){
//                auto other_p=other.m_object.find(p.first);
//                if (other_p == other.m_object.end()|| p.second != other_p->second)
//                    return false;
//            }
//上面根据 Clang-Tidy: Replace loop by 'std::all_of()' 的提示改为下面代码
            return std::all_of(m_object.cbegin(), m_object.cend(), [&other](const auto &p) {
                auto other_p = other.m_object.find(p.first);
                return other_p != other.m_object.end() && p.second == other_p->second;
            });
        default:
            return false;
    }
}

bool Json::operator==(bool value) const {
    return *this == Json(value);
}

bool Json::operator==(int value) const {
    return *this == Json(value);
}

bool Json::operator==(double value) const {
    return *this == Json(value);
}

bool Json::operator==(const char *value) const {
    return *this == Json(value);
}

bool Json::operator==(const std::string &value) const {
    return *this == Json(value);
}

bool Json::operator!=(const Json &other) const {
    return !(*this == other);
}

bool Json::operator!=(bool value) const {
    return *this != Json(value);
}

bool Json::operator!=(int value) const {
    return *this != Json(value);
}

bool Json::operator!=(double value) const {
    return *this != Json(value);
}

bool Json::operator!=(const char *value) const {
    return *this != Json(value);
}

bool Json::operator!=(const std::string &value) const {
    return *this != Json(value);
}

Json &Json::operator[](size_t index) {
    if (type() == Type::json_null) {
        m_type = Type::json_array;
    } else if (type() != Type::json_array) {
        throw std::logic_error("operator[]:type not supported");
    }
    size_t size = m_array.size();
    if (index < size)
        return m_array.at(index);
    if (index >= size) {
        for (size_t i = size; i <= index; i++) {
//            m_array.push_back(Json());
//            push_back() 成员函数将一个新元素副本添加到容器的末尾，而 emplace_back()成员函数则在容器的末尾直接构造一个新元素。
//            这意味着 emplace_back() 可以避免不必要的对象复制和移动，并且可以更好地支持容器中元素类型是不可复制或不可移动的情况。
            m_array.emplace_back();
        }
    }
    return m_array.at(index);
}

const Json &Json::operator[](size_t index) const {
    return get(index);
}

Json &Json::operator[](const char *key) {
    return (*this)[std::string(key)];
}

const Json &Json::operator[](const char *key) const {
    return get(key);
}

Json &Json::operator[](const std::string &key) {
    if (type() == Type::json_null) {
        m_type = Type::json_object;
    } else if (type() != Type::json_object) {
        throw std::logic_error("operator[]:type not supported");
    }
    return m_object[key];
}

const Json &Json::operator[](const std::string &key) const {
    return get(key);
}

Json::operator bool() {
    if (type() != Type::json_bool)
        throw std::logic_error("Json::operator bool():type not supported");
    return m_bool;
}

Json::operator int() {
    if (type() != Type::json_int)
        throw std::logic_error("Json::operator int():type not supported");
    return m_int;
}

Json::operator double() {
    if (type() != Type::json_double)
        throw std::logic_error("Json::operator double():type not supported");
    return m_double;
}

Json::operator std::string() {
    if (type() != Type::json_string)
        throw std::logic_error("Json::operator std::string():type not supported");
    return m_string;
}

Json::operator std::string() const {
    if (type() != Type::json_string)
        throw std::logic_error("Json::operator std::string() const:type not supported");
    return m_string;
}

void Json::parse(const std::string &str) {
    Parser parser;
    parser.load(str);
    *this = parser.parse();
}

std::string Json::toString() const {
    std::ostringstream oss;
    switch (type()) {
        case Type::json_null:
            oss << "null";
            break;
        case Type::json_string:
            oss << "\"" << m_string << "\"";
            break;
        case Type::json_bool:
            oss << (m_bool ? "true" : "false");
            break;
        case Type::json_int:
            oss << m_int;
            break;
        case Type::json_double:
            oss << m_double;
            break;
        case Type::json_array:
            oss << "[";
            for (auto it = m_array.begin(); it != m_array.end(); it++) {
                if (it != m_array.begin())
                    oss << ",";
                oss << it->toString();
            }
            oss << "]";
            break;
        case Type::json_object:
            oss << "{";
            for (auto it = m_object.begin(); it != m_object.end(); it++) {
                if (it != m_object.begin())
                    oss << ",";
                oss << "\"" << it->first << "\":" << it->second.toString();
            }
            oss << "}";
            break;
        default:
            break;
    }
    return oss.str();
}
