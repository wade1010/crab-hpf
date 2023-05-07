//
// Created by cepher on 5/7/23.
//

#ifndef CRAB_HPF_ELEMENT_H
#define CRAB_HPF_ELEMENT_H


#include <string>
#include <vector>
#include <map>

namespace crab {
    namespace xml {


        class Element {
        public:
            Element();

            virtual ~Element();

            explicit Element(const std::string &name);

            Element(const std::string &name, const std::string &text);

            //获取元素name
            const std::string &name() const;  //const std::string的话，返回的是副本

            //设置元素name
            void name(const std::string &name);

            //获取元素text
            const std::string &text() const;

            //设置元素text
            void text(const std::string &text);

            //获取元素attr
            const std::string &attr(const std::string &key);

            //设置元素attr
            void attr(const std::string &key, const std::string &value);

            //根据index获取child element
            const Element &operator[](size_t index) const;

            //根据name获取child element
            const Element &operator[](const std::string &name) const;

            //添加child
            void append(const Element &element);

            void clear();

            std::string toString()const;

        private:
            std::string m_name;
            std::string m_text;
            std::vector<Element> m_children;
            std::map<std::string,std::string> m_attrs;

        };
    }
}
#endif //CRAB_HPF_ELEMENT_H
