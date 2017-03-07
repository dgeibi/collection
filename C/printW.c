#include <stdio.h>

void Putc(char c, int count) {
	for(int i = 0; i<count; i++) {
		putchar(c);
	}
}

void PrintW(int count) {
	if(count < 2) return;
	for(int i = 0; i<count;i++){
		int gap=2*count-2-2*i;
		Putc(' ',i);
		putchar('w');
		Putc(' ',gap);
		putchar('w');
		Putc(' ',2*i);
		putchar('w');
		Putc(' ',gap);
		putchar('w');
		putchar('\n');
	}
}

int main()
{
	PrintW(2);
	PrintW(4);
	PrintW(7);
}
