For parser use: Just compile together with Bison (parser.tab.h is included) like this:

bash
Copy
Edit
bison -d parser.y
flex ../lexer/lexer.l
gcc parser.tab.c lex.yy.c -o parser
This lets you use the same lexer both for token inspection and as part of the full parser pipeline.

cd ../parser
bison -d parser.y # Generate parser.tab.c and parser.tab.h
flex ../lexer/lexer.l # Regenerate lex.yy.c based on lexer.l
gcc parser.tab.c lex.yy.c -o parser -lfl # Compile the parser and link with Flex
