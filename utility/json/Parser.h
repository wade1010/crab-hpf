//
// Created by cepher on 5/7/23.
//

#ifndef CRAB_HPF_JSON_PARSER_H
#define CRAB_HPF_JSON_PARSER_H

#include "Json.h"

namespace crab {
    namespace json {

        class Parser {
        public:
            Parser();

            virtual ~Parser();

            void load(const std::string &str);

            Json parse();

        private:
            void skip_white_spaces();
            char get_next_char();

            Json parse_null();
            Json parse_bool();
            Json parse_number();
            Json parse_string();

            static bool in_range(long x,long lower,long upper){
                return x >= lower && x <= upper;
            }
        private:
            std::string m_str;
            size_t m_idx;
        };
    }
}
#endif //CRAB_HPF_JSON_PARSER_H
