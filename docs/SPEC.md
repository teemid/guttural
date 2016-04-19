EBNF:

digit  = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9';
letter = 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' |
         'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' |
         'u' | 'v' | 'x' | 'y' | 'z' |
         'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' |
         'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' |
         'U' | 'V' | 'X' | 'Y' | 'Z';
whitespace = ' ' | '\n' | '\r' | '\t'; ? more whitespace chars ?
symbol = '(' | ')' | '[' | ']' | '<' | '>' | '=' | '+' | '-' | '*' | '/' | ',' | '.';
character = letter | digit | symbol | whitespace;

identifier = (letter | '_') , { letter | digit | '_' };

string = ''', character*, ''' | '"' character*, '"';
integer = digit+;
double  = digit+, '.', digit+;
function = 'function', '(', argument*, ')' statement+, 'end';
statement = assignment | return | call;
