#include <iostream>

class B;

class A {
	public:
		void f(const B&) noexcept;
};

class B {
	public:
		B(const A& a) noexcept:
			a(a)
		{}
		
		void f() const noexcept {
			std::cout << "\n!\n";
		}
		
	private:
		A a;
};

void A::f(const B& b) noexcept {
	b.f();
}

int main() {
	A a;
	B b(a);
	a.f(b);
	
	return 0;
}