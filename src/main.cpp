#include "heading.h"

// prototype of bison-generated parser function
int yyparse();

extern "C" int yylex();
extern FILE* yyin;
extern ProgramNode* prgnodeptr;

CompileContext compile_context;
bool disableDebug = false;

inline void usage(char* p) {
    std::cerr << "Usage: " << p << " [--only-symbol-table] [/path/to/file.ta3]" << std::endl;
}

inline void printProgram(const Program& p) {
	for (const auto& line : p) {
		std::cout << line << std::endl;
	}
}

int main(int argc, char **argv) {
	bool onlyPrintSymTable = false;

	if (argc == 1) {
		yyin = stdin;
	} else if (argc == 3 || argc == 2) {
		while (argc > 1) {
			const auto s = std::string(argv[argc-1]);
			argc--;

			if (s == "-h" || s == "--help") {
				usage(argv[0]);
				return 0;
			} else if (s == "--only-symbol-table") {
				onlyPrintSymTable = true;
				disableDebug = true;
			} else {
				yyin = fopen(s.c_str(), "r");
				if (yyin == NULL) {
					std::cerr << "Invalid file path: " << s << std::endl;
					return 1;
				}
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

	DEBUG("finished parsing, will compile");
	DEBUG(prgnodeptr->toString());

	prgnodeptr->compile(compile_context);
	compile_context.symbolTable.checkUnusedDataSymbols(compile_context.warningRegistry);

	if (yyparse_return != 0 || !compile_context.errorRegistry.empty()) {
		if (!onlyPrintSymTable) { compile_context.errorRegistry.displayErrors(); }
		return yyparse_return == 0? 1:yyparse_return;
	}

	if (!onlyPrintSymTable) { compile_context.warningRegistry.displayWarnings(); }

	cerr << compile_context.symbolTable;
	if (onlyPrintSymTable) { return 0; }

	DEBUG("finished compiling, will print assembly");
	printProgram(compile_context.toProgram());

	DEBUG("finished printing assembly");

	return 0;
}
