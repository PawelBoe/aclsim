#include "SegmentParser.hpp"

#include <iostream>
#include <stdexcept>


Segment SegmentParser::get_segment()
{
    Segment vec;


    try
    {
        vec.from_string(m_line);
    }
    catch (std::runtime_error &e)
    {
        throw std::runtime_error("Vector [" + m_line + "] " + e.what());
    }

    return vec;
}

bool SegmentParser::fetch_segment()
{
    m_line.clear();

    if (std::getline(std::cin, m_line))
        return true;

    return false;
}
