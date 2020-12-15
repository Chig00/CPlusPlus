#include <iostream>

void pointer_swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void reference_swap(int &x, int &y) {
	x = x + y;
	y = x - y;
	x -= y;
}

void display_values(int x, int y) {
	std::cout << "x = " << x << std::endl
	          << "y = " << y << std::endl
			                 << std::endl;
}

int main() {
	int x = 123;
	int y = 321;
	display_values(x, y);
	pointer_swap(&x, &y);
	display_values(x, y);
	reference_swap(x, y);
	display_values(x, y);
	
	return 0;
}