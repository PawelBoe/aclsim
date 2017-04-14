#ifndef SEGMENTPARSER_HPP
#define SEGMENTPARSER_HPP

#include "Segment.hpp"


class SegmentParser
{
public:
    Segment next_segment();

    bool eof() const;

private:
};


#endif /* end of include guard: SEGMENTPARSER_HPP */
