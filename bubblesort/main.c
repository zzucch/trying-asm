#include <stdio.h>

void BubbleSort(int *array, int n) {
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
      "jle forward\n\t"
      "movl %%ebx, (%%esi)\n\t"
      "movl %%eax, 4(%%esi)\n\t"
      "movl $1, %%edx\n"
  "forward:\n\t"
      "addl $4, %%esi\n\t"
      "dec %%ecx\n\t"
      "jnz inner_loop\n\t"
      "testl %%edx, %%edx\n\t"
      "jnz outer_loop\n\t"
      :
      : [ptr] "m"(array), [n] "m"(n)
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
    ++n;
  }

  BubbleSort(array, n);

  for (int i = 0; i < n; ++i) {
    fprintf(output_file, "%d ", array[i]);
  }

  fclose(input_file);
  fclose(output_file);
  return 0;
}
