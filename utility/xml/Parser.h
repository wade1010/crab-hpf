//
// Created by cepher on 5/7/23.
//

#ifndef CRAB_HPF_PARSER_H
#define CRAB_HPF_PARSER_H

#include <string>
#include <vector>
#include "Element.h"

namespace crab {
    namespace xml {

        //XML 解析类
        class Parser {
        public:
            Parser();

            virtual ~Parser();

            //加载 XML 文件
            void load_file(const std::string &filename);

            void skip_white_spaces();

            Element parse(bool is_child=false);

        private:
            bool parse_declaration();
            bool parse_comment();
            std::string parse_element_name();
            std::string parse_element_text();
            std::string parse_element_attr_key();
            std::string parse_element_attr_value();

            std::string m_str;
            size_t m_idx{};

        };

#endif //CRAB_HPF_PARSER_H
    }
}