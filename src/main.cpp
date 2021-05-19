#include "heading.h"

// prototype of bison-generated parser function
int yyparse();

int yylex();
extern FILE* yyin;

inline void usage(char* p) {
    std::cerr << "Usage: " << p << " [/path/to/file.ta3]" << std::endl;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        yyin = stdin;
    } else if (argc == 2) {
        const auto s = std::string(argv[1]);
        if (s == "-h" || s == "--help") {
            usage(argv[0]);
            return 0;
        } else {
            yyin = fopen(argv[1], "r");
            if (yyin == NULL) {
                std::cerr << "Invalid file path: " << argv[1] << std::endl;
                return 1;
            }
        }
    } else {
        usage(argv[0]);
        return 1;
    }

#ifdef DEBUG_LEX
    std::cout << "enabled only-lexical-analysis mode" << std::endl;
    do { } while (yylex());
    return 0; // not reachable
#elif YYDEBUG==1
    std::cout << "enabled parser tracing" << std::endl;

    extern int yydebug;
    yydebug = 1;
#endif

    return yyparse();
}
