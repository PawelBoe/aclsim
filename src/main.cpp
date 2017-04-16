#include "ArgumentParser.hpp"

#include "RuleParser.hpp"
#include "SegmentParser.hpp"
#include "Matcher.hpp"

#include "Rule.hpp"
#include "Segment.hpp"

#include <iostream>


int main(int argc, char *argv[])
{
    try
    {
        ArgumentParser argumentParser(argc, argv);
        Option option = argumentParser.get_option();

        if (option == Option::HELP)
        {
            argumentParser.print_help();
            return 0;
        }

        RuleParser ruleParser;
        ruleParser.from_file(argumentParser.get_aclFile());

        SegmentParser segmentParser;

        while (segmentParser.fetch_segment())
        {
            Matcher matcher;
            Segment segment = segmentParser.get_segment();

            for (auto &aclRule : ruleParser.get_rules()) {
                matcher.match(aclRule, segment);
            }

            matcher.print_matches(segment, option);
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cerr
            << "Invalid Argument: " << e.what() << std::endl
            << "Terminating program .." << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cerr
            << "Runtime Error: " << e.what() << std::endl
            << "Terminating program .." << std::endl;
    }

    return 0;
}
