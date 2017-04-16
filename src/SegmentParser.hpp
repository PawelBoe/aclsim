#ifndef SEGMENTPARSER_HPP
#define SEGMENTPARSER_HPP

#include "Segment.hpp"


class SegmentParser
{
public:
    Segment get_segment();

    bool fetch_segment();

private:
    std::string m_line;
};


#endif /* end of include guard: SEGMENTPARSER_HPP */
