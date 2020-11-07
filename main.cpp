#include <iostream>
#include "GeneralQueue.hpp"

int main() {
	Queue<double> a(7.9128);
	std::cout << a << '\n';

	Queue <double> b(a);
	b.enqueue(12.617);
	b.enqueue(4.385);

	b.print();

	b.dequeue();
	b.print();

	std::cout << (a == b) << '\t' << (a != b) << '\n';

	std::cout << b.front() << ' ' << b.back() << ' ' <<  b.size() << '\n';

	Queue<double> c = b;

	c.enqueue(5.0423);
	std::cout << c << '\n';

	return 0;
}

