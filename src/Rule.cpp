#include "Rule.hpp"


void Rule::from_string(const std::string &line)
{
    m_data = line;
}

bool Rule::apply(Segment segment) const
{
    // TODO

    return true;
}

Action Rule::get_action() const
{
    // TODO

    return Action::PERMIT;
}

const std::string& Rule::data() const
{
    return m_data;
}
