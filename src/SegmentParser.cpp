#include "SegmentParser.hpp"

#include <iostream>


Segment SegmentParser::next_segment()
{
    Segment vec;

    std::string line;

    std::getline(std::cin, line);
    vec.from_string(line);

    return vec;
}

bool SegmentParser::eof() const
{
    return std::cin.eof();
}
