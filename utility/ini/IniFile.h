//
// Created by cepher on 5/7/23.
//



#ifndef CRAB_HPF_INIFILE_H
#define CRAB_HPF_INIFILE_H

#include <string>
#include <map>

namespace crab {
    namespace ini {
        class Value {
        public:
            Value();

            virtual ~Value();

            explicit Value(bool value);

            explicit Value(int value);

            explicit Value(double value);

            explicit Value(std::string value);

            explicit Value(const char *value);

            Value &operator=(bool value);

            Value &operator=(int value);

            Value &operator=(double value);

            Value &operator=(const std::string &value);

            Value &operator=(const char *value);

            operator bool() const;

            operator int() const;

            operator double() const;

            operator std::string();

            operator std::string() const;

        private:
            std::string m_value;
        };

        class IniFile {
        public:
            IniFile();

            explicit IniFile(const std::string &filename);

            virtual ~IniFile();

            bool load_file(const std::string &filename);

            void save(const std::string &filename);

            void show();

            void clear();

            Value &get(const std::string &section, const std::string &key);

            void set(const std::string &section, const std::string &key, bool value);

            void set(const std::string &section, const std::string &key, int value);

            void set(const std::string &section, const std::string &key, const char *value);

            void set(const std::string &section, const std::string &key, const std::string &value);

            bool has(const std::string &section);

            bool has(const std::string &section, const std::string &key);

            void remove(const std::string &section);

            void remove(const std::string &section, const std::string &key);

            typedef std::map<std::string, Value> Section;

            Section &operator[](const std::string &key);

        private:
            static std::string trim(std::string s);

        private:
            std::string m_filename;
            std::map<std::string, Section> m_ini_file;
        };
    }
}
#endif //CRAB_HPF_INIFILE_H
