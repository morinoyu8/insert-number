#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define SIZE 1000
#define FILENAME_SIZE 100
#define SPACE_MAX 10000

void argment_error() {
    fprintf(stderr, "arguments are missing.\n");
    exit(1);
}

char *new_filename(const char *name, int rem) {
    char *new = malloc(FILENAME_SIZE * sizeof(char));
    strcpy(new, name);
    int ext_idx = strlen(new);
    for (int i = 0; i < strlen(new); i++) {
        if (new[i] == '.') {
            ext_idx = i;
        }
    }
    new[ext_idx] = '\0';
    if (rem == 0)
        strcat(new, "-linenum.txt");
    else
        strcat(new, "-remnum.c");
    return new;
}

FILE *xfopen(char *filename, char *flag) {
    FILE *fp = fopen(filename, flag);
    if (fp == NULL) {
        fprintf(stderr, "%s cannot open.\n", filename);
        exit(1);
    }
    return fp;
}

char *remove_str(char *str, int len) {
    if (strlen(str) <= len)
        return "\n";
    return &str[len];
}

void remove_linenum(char **argv, int first, int len) {
    FILE *rf;
    FILE *wf;
    char *str = malloc(SIZE * sizeof(char));
    char *new_str;

    int rem_len = 4;
    for (int i = first; i < len; i++) {
        rf = xfopen(argv[i], "r");

        char *new_file = new_filename(argv[i], 1);
        wf = xfopen(new_file, "w");
        free(new_file);

        if (fgets(str, SIZE, rf) != NULL) {
            for (int j = 0; j < strlen(str); j++) {
                if (str[j] == '1') {
                    rem_len = j + 3;
                    break;
                }
            }
            new_str = remove_str(str, rem_len);
            fprintf(wf, "%s", new_str);
        }

        while (fgets(str, SIZE, rf) != NULL) {
            new_str = remove_str(str, rem_len);
            fprintf(wf, "%s", new_str);
        }
        fclose(rf);
        fclose(wf);
        printf("Removed line-numbers in %s\n", argv[i]);
    }
    free(str);
}

void insert_linenum(char **argv, int first, int len, int space) {
    FILE *rf;
    FILE *wf;
    char str[SIZE];
    char new_str[SIZE];
    char space_str[space + 1];
    for (int i = 0; i < space; i++)
        space_str[i] = ' ';
    space_str[space] = '\0';
    for (int i = first; i < len; i++) {
        rf = xfopen(argv[i], "r");

        char *new_file = new_filename(argv[i], 0);
        wf = xfopen(new_file, "w");
        free(new_file);

        int count = 1;
        int bound = 10;
        while (fgets(str, SIZE, rf) != NULL) {
            if (count == bound) {
                bound *= 10;
                if (strlen(space_str) > 0) {
                    space_str[strlen(space_str) - 1] = '\0';
                }
            }
            fprintf(wf, "%s%d  %s", space_str, count, str);
            count++;
        }
        fclose(rf);
        fclose(wf);
        printf("Inserted line-numbers in %s\n", argv[i]);
    }
}

int main(int argc, char **argv) {
    int rem = 0;
    int space = 1;
    int first = 1;

    struct option const long_opts[] = {
        {"remove", no_argument, NULL, 'r'},
        {"space", required_argument, NULL, 's'},
        {0, 0, 0, 0},
    };

    while (1) {
        int const opt = getopt_long(argc, argv, "rs:", long_opts, NULL);
        if (opt == -1) break;

        switch (opt) {
            case 'r':
                rem = 1;
                break;
            case 's':
                space = atoi(optarg);
                if (space < 0 || SPACE_MAX < space) {
                    fprintf(stderr, "'space' must be between 0 to %d\n", SPACE_MAX);
                    exit(1);
                }
                break;
            case '?':
                break;
            default:
                argment_error();
                break;
        }
    }
    if (optind >= argc) argment_error();
    first = optind;

    if (rem)
        remove_linenum(argv, first, argc);
    else
        insert_linenum(argv, first, argc, space);

    return 0;
}
