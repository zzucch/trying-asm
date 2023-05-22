#include <stdio.h>

void GreatestNumbers(int *array, int *answer, int n, int answer_size) {
  __asm__ __volatile__(
      ".att_syntax prefix\n"
      "decl %[n]\n\t"
  "outer_loop:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %[ptr], %%esi\n\t"
      "movl %[n], %%ecx\n"
  "inner_loop:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 4(%%esi), %%ebx\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jge forward\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "movl %%eax, 4(%%esi)\n\t"
      "movl $1, %%edx\n"
  "forward:\n\t"
      "addl $4, %%esi\n\t"
      "dec %%ecx\n\t"
      "jnz inner_loop\n\t"
      "testl %%edx, %%edx\n\t"
      "jnz outer_loop\n\t"
      "movl %[ptr], %%esi\n\t"
      "movl %[ans], %%eax\n\t"
      "movl %[m], %%ecx\n\t"
  "greater_numbers_loop:\n\t"
      "mov (%%esi), %%ebx\n\t"
      "mov %%ebx, (%%eax)\n\t"
      "addl $4, %%esi\n\t"
      "addl $4, %%eax\n\t"
      "loop greater_numbers_loop\n\t"
      :
      : [ptr] "m"(array), [n] "m"(n), [ans] "m"(answer), [m] "m"(answer_size)
      : "%eax", "%ebx", "%ecx", "%edx", "%esi");
}

int main() {
  FILE *input_file = fopen("input.txt", "r");
  if (input_file == NULL) {
    printf("Error: cannot open input file.\n");
    return 1;
  }
  FILE *output_file = fopen("output.txt", "w");
  if (output_file == NULL) {
    printf("Error: cannot open output file.\n");
    return 1;
  }

  const int kSize = 1000;
  int array[kSize];
  int n = 0;
  while (fscanf(input_file, "%d", &array[n]) == 1 && n < kSize) {
    n++;
  }
  int answer_size = 10;
  int greatest_numbers[answer_size];

  if (n < answer_size) {
    printf("Error: too little numbers");
    return 1;
  }
  GreatestNumbers(array, greatest_numbers, n, answer_size);

  for (int i = 0; i < answer_size; ++i) {
    fprintf(output_file, "%d ", greatest_numbers[i]);
  }
  fclose(input_file);
  fclose(output_file);
  return 0;
}
