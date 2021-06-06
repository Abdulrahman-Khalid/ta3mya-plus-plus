#include "heading.h"

// prototype of bison-generated parser function
int yyparse();

extern "C" int yylex();
extern FILE* yyin;
extern ProgramNode* prgnodeptr;

CompileContext compile_context;

inline void usage(char* p) {
    std::cerr << "Usage: " << p << " [/path/to/file.ta3]" << std::endl;
}

inline void printProgram(const Program& p) {
	for (const auto& line : p) {
		std::cout << line << std::endl;
	}
	if (p.size() > 0) {
		std::cout<<endl;
	}
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
    DEBUG("entered only-lexical debug mode");
    do { } while (yylex());
    return 0; // not reachable
#elif YYDEBUG==1
    DEBUG("enabled parser debugging");
    extern int yydebug;
    yydebug = 1;
#endif

	DEBUG("started parsing");

	int yyparse_return = yyparse();
	if (yyparse_return != 0 || !compile_context.errors.empty()) {
		for(const auto& error: compile_context.errors) {
			cout << error << endl;
		}
		return yyparse_return;
	}

	DEBUG("finished parsing, will compile");
	DEBUG(prgnodeptr->toString());

	prgnodeptr->compile(compile_context);

	DEBUG("finished compile, will print assembly");

	printProgram(compile_context.toProgram());

	DEBUG("finished printing assembly");

	return 0;
}
