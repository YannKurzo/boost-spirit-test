
//  ==========================================================================
/// @file   main.cc
/// @author Yann Kurzo
/// @date   August 8, 2015, 9:32 PM
/// @copyright Copyright 2015 Yann Kurzo. All rights reserved.
///         This project is released under the GNU Public License.
/// @brief  Simple recursive parser to check a string
//  ==========================================================================

#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <string>

namespace lex = boost::spirit::lex;

// Token id definitions
enum tokenIDs_e
{
    ID_WORD = 1000,
    ID_EOL,
    ID_CHAR
};

// Lexer
template <typename Lexer>
struct MyLexer : lex::lexer<Lexer>
{
    MyLexer()
    {
        // Define tokens (the regular expression to match and the corresponding
        // token id) and add them to the lexer 
        this->self.add
            ("[^ \t\n]+", ID_WORD) // words (anything except ' ', '\t' or '\n')
            ("\n", ID_EOL)         // newline characters
            (".", ID_CHAR)         // anything else is a plain character
        ;
    }
};

// Define this structure to use it as a functor analyzing the matched tokens
struct counter
{
    typedef bool result_type;

    // This function gets called for each of the matched tokens
    template <typename Token>
    bool operator()(Token const& t, std::size_t& c, std::size_t& w, std::size_t& l) const
    {
        // Check the token ID
        switch (t.id())
        {
            // Word
            case ID_WORD:
        // since we're using a default token type in this example, every 
        // token instance contains a `iterator_range<BaseIterator>` as its token
        // attribute pointing to the matched character sequence in the input 
                ++w; c += t.value().size(); 
                break;
            // New line
            case ID_EOL:
                ++l; ++c; 
                break;
            // Normal character
            case ID_CHAR:
                ++c; 
                break;
            default:
                break;
        }

        // Continue to the next token
        return true;
    }
};

// Main program
int main(int argc, char* argv[])
{
    // Variable to count
    std::size_t c = 0, w = 0, l = 0;

    // Test string
    std::string str("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla maximus eget turpis sed fringilla. Quisque dapibus posuere sollicitudin. Fusce vehicula felis ac malesuada consectetur. Suspendisse potenti. Mauris eu tincidunt magna. Donec congue facilisis leo nec molestie. Mauris sed augue accumsan risus posuere dignissim. Nunc a velit vulputate, imperdiet erat malesuada, laoreet ex. Nulla sed tortor mauris. Ut et varius lectus. Sed velit nulla, eleifend in mauris ac, tempus consequat orci.");

    // Create the token definition from the lexer
    MyLexer<lex::lexertl::lexer<> > myLexer;

    // Get the string
    char const* first = str.c_str();
    char const* last = &first[str.size()];

    // Tokenize
    bool r = lex::tokenize(first, last, myLexer, 
        boost::bind(counter(), _1, boost::ref(c), boost::ref(w), boost::ref(l)));

    // Print results
    if (r) {
        std::cout << "lines: " << l << ", words: " << w 
                  << ", characters: " << c << "\n";
    }
    else {
        std::string rest(first, last);
        std::cout << "Lexical analysis failed\n" << "stopped at: \"" 
                  << rest << "\"\n";
    }

    return 0;
}
