#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <string>


class Segment
{
public:
    void from_string(const std::string &line);

    const std::string& data() const;

private:
    std::string m_data;
};

#endif /* end of include guard: SEGMENT_HPP */
