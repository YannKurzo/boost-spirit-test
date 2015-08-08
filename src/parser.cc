
//  ==========================================================================
/// @file   parser.cc
/// @author Yann Kurzo
/// @date   August 8, 2015, 9:32 PM
/// @copyright Copyright 2015 Yann Kurzo. All rights reserved.
///         This project is released under the GNU Public License.
/// @brief  Simple recursive parser to check a string
//  ==========================================================================

#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    // Define grammar
    template <typename Iterator>
    struct MyParser : qi::grammar<Iterator, ascii::space_type>
    {
        // Parser
        MyParser() : MyParser::base_type(expression)
        {
            using qi::double_;

            // expression = term
            // expression = term + term ...
            // expression = term - term ...
            expression =
                term >> *(('+' >> term) |
                          ('-' >> term));

            // term = factor
            // term = factor * factor ...
            // term = factor / factor ...
            term =
                factor >> *(('*' >> factor) | 
                            ('/' >> factor));


            // factor = double
            // factor = (expression)
            // factor = -factor
            // factor = +factor
            factor =
                double_ |
                ('(' >> expression >> ')') |
                ('-' >> factor) |
                ('+' >> factor);
        }

        // Rules
        qi::rule<Iterator, ascii::space_type>
            expression, 
            term, 
            factor;
    };
}

using boost::spirit::ascii::space;
typedef std::string::const_iterator stringIterator_t;
typedef client::MyParser<stringIterator_t> myParserIterator_t;

// Main program
int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        // Set the grammar
        myParserIterator_t myParserIterator;

        // Get string to parse
        std::string str(argv[1]);
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();

        // Parsing
        bool r = phrase_parse(iter, end, myParserIterator, space);

        // Result
        if (r && iter == end)
        {
            std::cout << "Parsing succeeded\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
        }
    }

    return 0;
}
