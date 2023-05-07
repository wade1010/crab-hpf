#include <iostream>

#include "utility/xml/Parser.h"

using namespace crab::xml;
int main(int argc, char const *argv[])
{
    Parser p;
    p.load_file("../../crab-hpf/utility/xml/test.xml");
    const Element &element = p.parse();
    return 0;
}
