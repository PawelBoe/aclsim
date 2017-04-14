#include "Segment.hpp"


void Segment::from_string(const std::string &line)
{
    m_data = line;
}

const std::string& Segment::data() const
{
    return m_data;
}
