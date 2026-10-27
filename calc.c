// Kamil Guluzada 251ADB067
// https://github.com/kamilsft/Programming_Languages_C_2026_Fall_Labs
// gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c -lm
// Referenced guides on geeksforgeeks.org for C string processing, file
// handling, and expression parsing

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Simple expression evaluator helper functions
typedef struct {
  const char* s;
} Parser;

double parse_expr(Parser* p);

double parse_factor(Parser* p) {
  while (*p->s == ' ') p->s++;
  if (*p->s == '(') {
    p->s++;
    double val = parse_expr(p);
    if (*p->s == ')') p->s++;
    return val;
  }
  char* end;
  double val = strtod(p->s, &end);
  p->s = end;
  return val;
}

double parse_term(Parser* p) {
  double val = parse_factor(p);
  while (1) {
    while (*p->s == ' ') p->s++;
    if (*p->s == '*') {
      p->s++;
      val *= parse_factor(p);
    } else if (*p->s == '/') {
      p->s++;
      double divisor = parse_factor(p);
      if (divisor != 0) val /= divisor;
    } else {
      break;
    }
  }
  return val;
}

double parse_expr(Parser* p) {
  double val = parse_term(p);
  while (1) {
    while (*p->s == ' ') p->s++;
    if (*p->s == '+') {
      p->s++;
      val += parse_term(p);
    } else if (*p->s == '-') {
      p->s++;
      val -= parse_term(p);
    } else {
      break;
    }
  }
  return val;
}

double evaluate(const char* expr) {
  Parser p = {expr};
  return parse_expr(&p);
}

int main(int argc, char* argv[]) {
  char* input_dir = NULL;
  char* output_dir = NULL;

  // read args
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
      input_dir = argv[++i];
    } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
      output_dir = argv[++i];
    }
  }

  // check if paths are given
  if (!input_dir || !output_dir) {
    fprintf(stderr, "Usage: %s -d <input_dir> -o <output_dir>\n", argv[0]);
    return 1;
  }

  // open input directory
  DIR* dir = opendir(input_dir);
  if (!dir) {
    perror("Error opening input directory");
    return 1;
  }

  struct dirent* entry;
  char in_path[512];
  char out_path[512];

  while ((entry = readdir(dir)) != NULL) {
    // skip . and ..
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // build full paths
    snprintf(in_path, sizeof(in_path), "%s/%s", input_dir, entry->d_name);
    snprintf(out_path, sizeof(out_path), "%s/%s", output_dir, entry->d_name);

    // open input file
    FILE* fin = fopen(in_path, "r");
    if (!fin) continue;

    char expr[256];
    if (fgets(expr, sizeof(expr), fin) != NULL) {
      expr[strcspn(expr, "\r\n")] = 0;  // strip newline
    } else {
      strcpy(expr, "0");
    }
    fclose(fin);

    // evaluate expression
    double result = evaluate(expr);

    // write result to output file
    FILE* fout = fopen(out_path, "w");
    if (fout) {
      fprintf(fout, "%.2f\n", result);
      fclose(fout);
    }
  }

  closedir(dir);
  return 0;
}