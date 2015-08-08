
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
enum tokenids 
{
    IDANY = lex::min_token_id + 10
};

template <typename Lexer>
struct word_count_tokens : lex::lexer<Lexer>
{
    word_count_tokens()
    {
        // define patterns (lexer macros) to be used during token definition 
        // below
        this->self.add_pattern
            ("WORD", "[^ \t\n]+")
        ;

        // define tokens and associate them with the lexer
        word = "{WORD}";    // reference the pattern 'WORD' as defined above

        // this lexer will recognize 3 token types: words, newlines, and 
        // everything else
        this->self.add
            (word)          // no token id is needed here
            ('\n')          // characters are usable as tokens as well
            (".", IDANY)    // string literals will not be escaped by the library
        ;
    }

    // the token 'word' exposes the matched string as its parser attribute
    lex::token_def<std::string> word;
};

// Grammar definition
template <typename Iterator>
struct word_count_grammar : qi::grammar<Iterator>
{
    template <typename TokenDef>
    word_count_grammar(TokenDef const& tok)
      : word_count_grammar::base_type(start)
      , c(0), w(0), l(0)
    {
        using boost::phoenix::ref;
        using boost::phoenix::size;

        start =  *(   tok.word          [++ref(w), ref(c) += size(_1)]
                  |   lit('\n')         [++ref(c), ++ref(l)] 
                  |   qi::token(IDANY)  [++ref(c)]
                  )
              ;
    }

    std::size_t c, w, l;
    qi::rule<Iterator> start;
};

// Main program
int main(int argc, char* argv[])
{
/*<  Define the token type to be used: `std::string` is available as the 
     type of the token attribute 
>*/  typedef lex::lexertl::token<
        char const*, boost::mpl::vector<std::string>
    > token_type;

/*<  Define the lexer type to use implementing the state machine
>*/  typedef lex::lexertl::lexer<token_type> lexer_type;

/*<  Define the iterator type exposed by the lexer type
>*/  typedef word_count_tokens<lexer_type>::iterator_type iterator_type;

    // now we use the types defined above to create the lexer and grammar
    // object instances needed to invoke the parsing process
    word_count_tokens<lexer_type> word_count;          // Our lexer
    word_count_grammar<iterator_type> g (word_count);  // Our parser 

    // Test string
    std::string str("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla maximus eget turpis sed fringilla. Quisque dapibus posuere sollicitudin. Fusce vehicula felis ac malesuada consectetur. Suspendisse potenti. Mauris eu tincidunt magna. Donec congue facilisis leo nec molestie. Mauris sed augue accumsan risus posuere dignissim. Nunc a velit vulputate, imperdiet erat malesuada, laoreet ex. Nulla sed tortor mauris. Ut et varius lectus. Sed velit nulla, eleifend in mauris ac, tempus consequat orci.");
    char const* first = str.c_str();
    char const* last = &first[str.size()];

/*<  Parsing is done based on the token stream, not the character 
     stream read from the input. The function `tokenize_and_parse()` wraps
     the passed iterator range `[first, last)` by the lexical analyzer and 
     uses its exposed iterators to parse the token stream.
>*/  bool r = lex::tokenize_and_parse(first, last, word_count, g);

    if (r) {
        std::cout << "lines: " << g.l << ", words: " << g.w 
                  << ", characters: " << g.c << "\n";
    }
    else {
        std::string rest(first, last);
        std::cerr << "Parsing failed\n" << "stopped at: \"" 
                  << rest << "\"\n";
    }
    return 0;
}
