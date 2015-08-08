
//  ==========================================================================
/// @file   main.cc
/// @author Yann Kurzo
/// @date   August 8, 2015, 9:32 PM
/// @copyright Copyright 2015 Yann Kurzo. All rights reserved.
///         This project is released under the GNU Public License.
/// @brief  Simple recursive parser to check a string
//  ==========================================================================

#define BOOST_VARIANT_MINIMIZE_SIZE

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

#include <iostream>
#include <string>

using namespace boost::spirit;
using namespace boost::spirit::ascii;

// Token definition
enum tokenIDs_e
{
    IDANY = lex::min_token_id + 10
};

// Define lexer
template <typename Lexer>
struct MyLexer : lex::lexer<Lexer>
{
    MyLexer()
    {
        // Define patterns to use for token definition
        this->self.add_pattern("WORD", "[^ \t\n]+");

        // Define tokens and associate them with the lexer
        word = "{WORD}";

        // Add tokens to the lexer
        this->self.add
            (word)          // no token id is needed here
            ('\n')          // characters are usable as tokens as well
            (".", IDANY)    // string literals will not be escaped by the library
        ;
    }

    // Define the tokens
    lex::token_def<std::string> word;
};

// Define parser
template <typename Iterator>
struct MyParser : qi::grammar<Iterator>
{
    // Construct parser
    template <typename TokenDef>
    MyParser(TokenDef const& tok)
        : MyParser::base_type(start), c(0), w(0), l(0)
    {
        using boost::phoenix::ref;
        using boost::phoenix::size;

        start =  *(   tok.word          [++ref(w), ref(c) += size(_1)]
                  |   lit('\n')         [++ref(c), ++ref(l)] 
                  |   qi::token(IDANY)  [++ref(c)]
                  );
    }

    // Variables
    std::size_t c, w, l;

    // Rules
    qi::rule<Iterator> start;
};

// Main program
int main(int argc, char* argv[])
{
    // Define the token type to be used
    typedef lex::lexertl::token<char const*, boost::mpl::vector<std::string> > token_t;

    // Define the lexer type to use implementing the state machine
    typedef lex::lexertl::lexer<token_t> lexer_t;

    // Define the iterator type exposed by the lexer type
    typedef MyLexer<lexer_t>::iterator_type iterator_t;

    // Create lexer and parser
    MyLexer<lexer_t> myLexer;
    MyParser<iterator_t> myParser(myLexer);

    // Test string
    std::string str("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla maximus eget turpis sed fringilla. Quisque dapibus posuere sollicitudin. Fusce vehicula felis ac malesuada consectetur. Suspendisse potenti. Mauris eu tincidunt magna. Donec congue facilisis leo nec molestie. Mauris sed augue accumsan risus posuere dignissim. Nunc a velit vulputate, imperdiet erat malesuada, laoreet ex. Nulla sed tortor mauris. Ut et varius lectus. Sed velit nulla, eleifend in mauris ac, tempus consequat orci.");
    char const* first = str.c_str();
    char const* last = &first[str.size()];

    // Lex and parse
    bool r = lex::tokenize_and_parse(first, last, myLexer, myParser);

    // Result
    if (r) {
        std::cout << "lines: " << myParser.l << ", words: " << myParser.w 
                  << ", characters: " << myParser.c << "\n";
    }
    else {
        std::string rest(first, last);
        std::cerr << "Parsing failed\n" << "stopped at: \"" 
                  << rest << "\"\n";
    }

    return 0;
}
