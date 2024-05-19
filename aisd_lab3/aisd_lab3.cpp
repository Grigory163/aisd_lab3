// aisd_lab3.cpp: определяет точку входа для приложения.
//

#include "aisd_lab3.h"

using namespace std;

int main()
{
	Graph<int, int> a;
	a.add_vertex(1);
	std::cout << a.has_vertex(1);
	auto b = a.vertices();
	std::cout << b.capacity();
}
