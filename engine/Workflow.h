//
// Created by cepher on 5/11/23.
//

#ifndef CRAB_HPF_WORKFLOW_H
#define CRAB_HPF_WORKFLOW_H

#include <string>
#include <map>
#include "../utility/xml/Element.h"
#include "Work.h"

using namespace crab::xml;
namespace crab {
    namespace engine {

        class Workflow {
        public:
            Workflow();

            ~Workflow();

            bool load(const std::string &file);

            bool run(const std::string &work, const std::string &input, std::string &output);

        private:
            bool load_plugin(Work *work, Element &element);

        private:
            std::map<std::string, Work *> m_works;
        };

    } // engine
} // crab

#endif //CRAB_HPF_WORKFLOW_H
