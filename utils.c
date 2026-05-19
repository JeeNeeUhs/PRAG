#include <stdio.h>
#include <ctype.h>

void print_acronym(char *c, char *mid, char *middle, char **argv, int argc, int optind) {
	printf("%s%s", c, mid);
	for (int i = optind + 1; i < argc; i++) {
		printf("%c", toupper(argv[i][0]));
	}
	printf("\n");
	printf("%s%s", c, mid);
	for (int i = optind + 1; i < argc; i++) {
		printf("%c", toupper(argv[i][0]));
	}
	printf("%s", middle);
	for (int i = optind + 1; i < argc; i++) {
		printf("%s", argv[i]);
		if (i < argc - 1) printf(" ");
	}
	printf("\n");
}

void str_to_upper(char *str) {
	while (*str) {
		*str = toupper(*str);
		str++;
	}
}

void info(char *prog) {
	fprintf(stderr, "Try '%s -h' for more information.\n", prog);
}

void usage(char *prog) {
	fprintf(stderr, "Usage: %s [OPTIONS] <char> <project-to-replace>\n", prog);
}

void print_help(char *prog) {
	printf("Usage: %s [OPTIONS] <char> <project-to-replace>\n", prog);
	printf("\n");
	printf("Generate GNU WINE style recursive acronyms for open-source projects.\n");
	printf("\n");
	printf("Options:\n");
	printf("  -h\t Show this help message\n");
	printf("  -i\t Use \"is not\" instead of \"'s not\"(You can't use with -spr)\n");
	printf("  -l\t Use a full string prefix (all chars included in acronym)\n");
	printf("  -s\t Shorten each argument to its uppercase letters in the acronym (e.g. YAML)(You can't use with -iprn)\n");
	printf("  -p\t Use \"'s\" instead of \"'s not\" (passive is not seen in the acronym)(You can't use with -isrn)\n");
	printf("  -r\t Use \"is\" instead of \"'s not\" (e.g. PRAG)(You can't use with -ispn)\n");
	printf("  -n\t just acronym not print anything in between (e.g. RPM)(You can't use with -ispr)\n");
	printf("\n");
	printf("Arguments:\n");
	printf("  <char(s)> \t\t The character to use in the acronym (e.g. G for GNU, W for WINE)\n");
	printf("  <project-to-replace> \t The project name to replace in the acronym (e.g. unix, emulator)\n");
	printf("\n");
	printf("Example:\n");
	printf("  %s G unix \t\t\t\t -> GNU, GNU's not unix\n", prog);
	printf("  %s -h \t\t\t\t\t -> Show this help message\n", prog);
	printf("  %s -i W emulator \t\t\t\t -> WINE, WINE is not emulator\n", prog);
	printf("  %s -l GNU unix \t\t\t\t -> GNUNU, GNUNU's not unix\n", prog);
	printf("  %s -s YAML Ain't Markup Language \t -> YAML, YAML Ain't Markup Language\n", prog);
	printf("  %s -p P Recursive Acronym Generator \t -> PIRAG, PIRAG is Recursive Acronym Generator\n", prog);
	printf("  %s -r P Recursive Acronym Generator \t -> PRAG, PRAG's Recursive Acronym Generator\n", prog);
	printf("  %s -n R Project Manager \t\t\t -> RPM, RPM Project Manager\n", prog);
}
