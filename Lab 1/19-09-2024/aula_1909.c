#include <stdio.h>

int lenum(){
	int d0, d1, d2;
	d0 = getchar() - '0';
	d1 = getchar() - '0';
	d2 = getchar() - '0';

	int x = d0 * 100 + d1 * 10 + d2;
	return x;
}

void impnum(int num){
	int d0, d1, d2;
	d0 = num / 100 % 10;
	d1 = num / 10 % 10;
	d2 = num / 1 % 10;
	putchar(d0 + '0');
	putchar(d1 + '0');
	putchar(d2 + '0');
	putchar('\n');
}

int main(){
	int x, y;

	x = lenum();
	y = x * 2;
	impnum(y);

	putchar('\n');
}
