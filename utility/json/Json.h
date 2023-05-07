//
// Created by cepher on 5/7/23.
//

#ifndef CRAB_HPF_JSON_H
#define CRAB_HPF_JSON_H

#include <vector>
#include <map>

namespace crab {
    namespace json {

        class Json {
        public:
            enum class Type {
                json_null = 0,
                json_bool,
                json_int,
                json_double,
                json_string,
                json_array,
                json_object
            };

            Json();

            explicit Json(Type type);

            explicit Json(bool value);

            explicit Json(int value);

            explicit Json(double value);

            explicit Json(const char *value);

            explicit Json(const std::string &value);

            Json(const Json &other);

            virtual ~Json();

            Type type() const;

            bool isNull() const;

            bool isBool() const;

            bool isInt() const;

            bool isDouble() const;

            bool isString() const;

            bool isArray() const;

            bool isObject() const;

            bool asBool() const;

            int asInt() const;

            double asDouble() const;

            std::string asString() const;

            void copy(const Json &other);

            size_t size();

            bool empty();

            void clear();

            bool remove(size_t index);

            bool remove(const char *key);

            bool remove(const std::string &key);

            bool has(size_t index);

            bool has(const char *key);

            bool has(const std::string &key);

            const Json &get(size_t index) const;

            const Json &get(const char *key) const;

            const Json &get(const std::string &key) const;

            void set(const Json &other);

            void set(bool value);

            void set(int value);

            void set(double value);

            void set(const char *value);

            void set(const std::string &value);

            Json &append(const Json &other);

            Json &operator=(const Json &other);

            Json &operator=(bool value);

            Json &operator=(int value);

            Json &operator=(double value);

            Json &operator=(const char *value);

            Json &operator=(const std::string &value);

            bool operator==(const Json &other) const;

            bool operator==(bool value) const;

            bool operator==(int value) const;

            bool operator==(double value) const;

            bool operator==(const char *value) const;

            bool operator==(const std::string &value) const;

            bool operator!=(const Json &other) const;

            bool operator!=(bool value) const;

            bool operator!=(int value) const;

            bool operator!=(double value) const;

            bool operator!=(const char *value) const;

            bool operator!=(const std::string &value) const;

            //Access an array element
            Json &operator[](size_t index);//越界就添加
            const Json &operator[](size_t index) const;

            Json &operator[](const char *key);//key
            const Json &operator[](const char *key) const;

            Json &operator[](const std::string &key);

            const Json &operator[](const std::string &key) const;

            explicit operator bool();

            explicit operator int();

            explicit operator double();

            explicit operator std::string();//返回一个非常量对象的副本，可以用于修改对象
            explicit operator std::string() const;//返回一个常量对象的副本，不能修改对象

            void parse(const std::string &str);

            std::string toString() const;

        private:
            Type m_type;
            int m_int;
            double m_double;
            bool m_bool;
            std::string m_string;
            std::vector<Json> m_array;
            std::map<std::string, Json> m_object;

        };
    }
}
#endif //CRAB_HPF_JSON_H
