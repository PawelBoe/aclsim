#include "SegmentParser.hpp"

#include <iostream>


Segment SegmentParser::get_segment()
{
    Segment vec;

    vec.from_string(m_line);

    return vec;
}

bool SegmentParser::fetch_segment()
{
    m_line.clear();

    if (std::getline(std::cin, m_line))
        return true;

    return false;
}
