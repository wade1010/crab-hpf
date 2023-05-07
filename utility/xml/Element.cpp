//
// Created by cepher on 5/7/23.
//
#include <sstream>
#include "Element.h"

using namespace crab::xml;

static const Element null_element;

Element::Element() = default;

Element::~Element() = default;

Element::Element(const std::string &name) {

}

Element::Element(const std::string &name, const std::string &text) {

}

const std::string &Element::name() const {
    return m_name;
}

void Element::name(const std::string &name) {
    m_name = name;
}

const std::string &Element::text() const {
    return m_text;
}

void Element::text(const std::string &text) {
    m_text = text;
}

const std::string &Element::attr(const std::string &key) {
    return m_attrs[key];
}

void Element::attr(const std::string &key, const std::string &value) {
    if (!value.empty()) {
        m_attrs[key] = value;
        return;
    }
    auto it = m_attrs.find(key);
    if (it != m_attrs.end()) {
        m_attrs.erase(it);
    }
}

const Element &Element::operator[](size_t index) const {
    size_t size = m_children.size();
    if (index < size)
        return m_children.at(index);
    return null_element;
}

const Element &Element::operator[](const std::string &name) const {
    for (auto &ele: m_children) {
        if (ele.name() == name)
            return ele;
    }
    return null_element;
}

void Element::append(const Element &element) {
    m_children.push_back(element);
}

void Element::clear() {
    m_name.clear();
    m_text.clear();
    m_attrs.clear();
    m_children.clear();
}

std::string Element::toString() const {
    if (m_name.empty())
        return "";
    std::ostringstream oss;
    oss << "<" << m_name;
    for (auto &attr: m_attrs)
        oss << " " << attr.first << "=\"" << attr.second << "\"";
    oss << ">";
    if (!m_children.empty())
        for (auto &child: m_children)
            oss << child.toString();
    else
        oss << m_text;
    oss << "</" << m_name << ">";
    return oss.str();
}
