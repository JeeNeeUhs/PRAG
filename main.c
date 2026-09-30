#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

extern int	optind;

void print_help(char *prog);
void usage(char *prog);
void info(char *prog);
void str_to_upper(char *str);
void print_acronym(char *c, char *mid, char *middle, char **argv, int argc, int start);

int main(int argc, char *argv[]) {
	// FLAGS
	int		i = 0;
	int		l = 0;
	int		s = 0;
	int		p = 0;
	int		r = 0;
	int		n = 0;
	int		a = 0;

	int		opt;

	if (argc == 1) {
		usage(argv[0]);
		return 1;
	}

	while ((opt = getopt(argc, argv, "hvilsprna")) != -1) {
		switch (opt) {
			case 'h':
				print_help(argv[0]);
				return 0;
			case 'v':
				printf("PRAGv1.0.1\n");
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
			case 'a':
				a = 1;
				break;
			case '?':
				info(argv[0]);
				return 1;
		}
	}

	// mode flags are mutually exclusive, report the first two that were given
	int		modes[] = {i, s, p, r, n};
	char	*mode_names = "isprn";
	char	first = '\0';

	for (int k = 0; k < 5; k++) {
		if (!modes[k])
			continue;
		if (first) {
			fprintf(stderr, "Error: -%c and -%c cannot be used together.\n", first, mode_names[k]);
			info(argv[0]);
			return 1;
		}
		first = mode_names[k];
	}

	if (a && l) {
		fprintf(stderr, "Error: -a and -l cannot be used together.\n");
		info(argv[0]);
		return 1;
	}

	if (a && s) {
		fprintf(stderr, "Error: -a and -s cannot be used together.\n");
		info(argv[0]);
		return 1;
	}

	if (l && s) {
		fprintf(stderr, "Error: -l and -s cannot be used together.\n");
		info(argv[0]);
		return 1;
	}

	// -a and -s take no <char>, so the project words start right away
	if (!a && !s) {
		if (optind >= argc || argv[optind][0] == '\0') {
			fprintf(stderr, "Error: <char> cannot be empty.\n");
			info(argv[0]);
			return 1;
		}
		if (!l && argv[optind][1] != '\0') {
			fprintf(stderr, "Error: <char> must be a single character when -l is not used.\n");
			info(argv[0]);
			return 1;
		}
	}

	int		start = (a || s) ? optind : optind + 1;

	if (start >= argc) {
		fprintf(stderr, "Error: <project-to-replace> cannot be empty.\n");
		info(argv[0]);
		return 1;
	}

	for (int k = start; k < argc; k++) {
		if (argv[k][0] == '\0') {
			fprintf(stderr, "Error: <project-to-replace> cannot contain empty words.\n");
			info(argv[0]);
			return 1;
		}
	}

	if (s) {
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

	char	*mid = "N";
	char	*middle = "'s not ";

	if (i) {
		mid = "IN";
		middle = " is not ";
	} else if (p) {
		mid = "";
		middle = "'s ";
	} else if (r) {
		mid = "I";
		middle = " is ";
	} else if (n) {
		mid = "";
		middle = " ";
	}

	if (a) {
		for (char c = 'A'; c <= 'Z'; c++) {
			char pre[2] = {c, '\0'};
			print_acronym(pre, mid, middle, argv, argc, start);
		}
	} else if (l) {
		char *c = argv[optind];
		str_to_upper(c);
		print_acronym(c, mid, middle, argv, argc, start);
	} else {
		char pre[2] = {toupper(argv[optind][0]), '\0'};
		print_acronym(pre, mid, middle, argv, argc, start);
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
