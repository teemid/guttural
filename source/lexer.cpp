#include "guttural/lexer.hpp"
#include "guttural/common.hpp"


namespace Guttural
{
    struct Keyword
    {
        Kind kind;
        char * keyword;
        int length;
    }

    static keywords[] = {
        #define GUTTURAL_KEYWORD(token_kind, string, length) { Kind::token_kind, #string, length },
        #include "guttural/definitions/tokens.def"
    };

    #define SetToken(token, token_kind, token_start) \
        (token).kind = (token_kind); \
        (token).length = 1; \
        (token).start = (token_start);

    #define IsLowerCase(c) ('a' <= (c) && (c) <= 'z')
    #define IsUpperCase(c) ('A' <= (c) && (c) <= 'Z')
    #define IsValidIdentifierStart(c) (IsLowerCase(c) || IsUpperCase(c) || (c) == '_')
    #define IsValidIdentifierContinuation(c) (IsLowerCase(c) || IsUpperCase(c) || (c) == '_')

    Lexer::Lexer (void) { }

    Lexer::Lexer (SourceReader * reader) : reader(reader), line(0), column(0) { };

    Lexer::~Lexer (void) { }

    Kind Lexer::Next (void)
    {
        current = (lookahead.kind == Kind::EndOfFile) ? Lex() : lookahead;
        lookahead.kind = Kind::EndOfFile;

        return current.kind;
    }

    Kind Lexer::Peek (void)
    {
        lookahead = Lex();

        return lookahead.kind;
    }

    Token Lexer::Lex (void)
    {
        Token token;
        char * c = reader->Next();

        switch (*c)
        {
            case '\r':
            {
                column++;
            }
            case '\n':
            {
                line++;
                column++;

                SetToken(token, Kind::NewLine, c);

                return token;
            }
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': 
            case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
            case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
            case 'V': case 'W': case 'X': case 'Y': case 'Z':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
            case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
            case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
            case 'v': case 'w': case 'x': case 'y': case 'z':
            case '_':
            {
                SetToken(token, Kind::Identifier, c);
                while (IsValidIdentifierContinuation(*c))
                {
                    c = reader->Next();
                }

                token.length = c - token.start;

                return token;
            }
            case '.':
            {
                SetToken(token, Kind::Period, c);

                return token;
            }
            case '(':
            {
                SetToken(token, Kind::OpenParen, c);

                return token;
            }
            case ')':
            {
                SetToken(token, Kind::CloseParen, c);

                return token;
            }
            case '[':
            {
                SetToken(token, Kind::OpenBracket, c);

                return token;
            }
            case ']':
            {
                SetToken(token, Kind::CloseBracket, c);

                return token;
            }
            case '{':
            {
                SetToken(token, Kind::OpenBrace, c);

                return token;
            }
            case '}':
            {
                SetToken(token, Kind::CloseBrace, c);

                return token;
            }
            default:
            {
                Assert(false, "Lexer got illegal token: %s.\n", c);
            }
        }
    }
}
