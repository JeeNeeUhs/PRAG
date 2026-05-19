#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

extern int	optind;

void print_help(char *prog);
void usage(char *prog);
void info(char *prog);
void str_to_upper(char *str);
void print_acronym(char *c, char *mid, char *middle, char **argv, int argc, int optind);

int main(int argc, char *argv[]) {
	// FLAGS
	int		i = 0;
	int		l = 0;
	int		s = 0;
	int		p = 0;
	int		r = 0;
	int		n = 0;

	char	opt;

	if (argc == 1) {
		usage(argv[0]);
		return 1;
	}

	while ((opt = getopt(argc, argv, "hilsprn")) != -1) {
		switch (opt) {
			case 'h':
				print_help(argv[0]);
				return 0;
			case 'i':
				i = 1;
				break;
			case 'l':
				l = 1;
				break;
			case 's':
				s = 1;
				break;
			case 'p':
				p = 1;
				break;
			case 'r':
				r = 1;
				break;
			case 'n':
				n = 1;
				break;
			case '?':
				info(argv[0]);
				return 1;
		}
	}

	if (i + s + p + r > 1) {
		fprintf(stderr, "Error: -i, -s, -p, -r cannot be used together.\n");
		info(argv[0]);
		return 1;
	}

	if (!s) {
		if (l) {
			if (argv[optind][0] == '\0') {
				fprintf(stderr, "Error: <char> cannot be empty when -l is used.\n");
				info(argv[0]);
				return 1;
			}
		} else {
			if (argv[optind][1] != '\0') {
				fprintf(stderr, "Error: <char> must be a single character when -l is not used.\n");
				info(argv[0]);
				return 1;
			}
		}
	} else {
		for (int i = optind; i < argc; i++) {
			if (isupper((unsigned char)argv[i][0])) {
				printf("%c", argv[i][0]);
			}
		}
		printf(", ");
		for (int i = optind; i < argc; i++) {
			printf("%s", argv[i]);
			if (i < argc - 1) printf(" ");
		}
		printf("\n");
		return 0;
	}

	if (l) {
		char *c = argv[optind];
		str_to_upper(c);

		if (i) {
			print_acronym(c, "IN", " is not ", argv, argc, optind);
		} else if (p) {
			print_acronym(c, "", "'s ", argv, argc, optind);
		} else if (r) {
			print_acronym(c, "I", " is ", argv, argc, optind);
		} else if (n){
			print_acronym(c, "", " ", argv, argc, optind);
		} else {
			print_acronym(c, "N", "'s not ", argv, argc, optind);
		}
	} else {
		char c = toupper(argv[optind][0]);

		if (i) {
			print_acronym(&c, "IN", " is not ", argv, argc, optind);
		} else if (p) {
			print_acronym(&c, "", "'s ", argv, argc, optind);
		} else if (r) {
			print_acronym(&c, "I", " is ", argv, argc, optind);
		} else if (n){
			print_acronym(&c, "", " ", argv, argc, optind);
		} else {
			print_acronym(&c, "N", "'s not ", argv, argc, optind);
		}
	}





	// if (argc - optind < 2) {
	// 	fprintf(stderr, "Usage: %s [OPTIONS] <char> <project-to-replace>\n", argv[0]);
	// 	return 1;
	// }

	// if (argv[optind][1] != '\0') {
	// 	fprintf(stderr, "Usage: %s [OPTIONS] <char> <project-to-replace>\n", argv[0]);
	// 	return 1;
	// }

	// char c = toupper(argv[optind][0]);
	// char *project = argv[optind + 1];

	// if (isnot) {
	// 	printf("%cIN%c\n", c, toupper(project[0]));
	// 	printf("%cIN%c is not %s!\n", c, toupper(project[0]), project);
	// } else {
	// 	printf("%cN%c\n", c, toupper(project[0]));
	// 	printf("%cN%c's not %s!\n", c, toupper(project[0]), project);
	// }
}
