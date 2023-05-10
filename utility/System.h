//
// Created by cepher on 5/10/23.
//

#ifndef CRAB_HPF_SYSTEM_H
#define CRAB_HPF_SYSTEM_H

#include <string>

namespace crab {

    class System {
    public:
        System();
        ~System();

        void init();

        std::string get_root_path();
    private:
        void core_dump();
    private:
        std::string m_root_path;
    };

} // crab

#endif //CRAB_HPF_SYSTEM_H
