#include "main.hpp"


int main(void) {

/* 	std::cout << "======FT::STACK TESTS======" << std::endl;

	ft::stack<int> test;

	test.push(10);

	std::cout << test.top() << "\nempty() test = " << test.empty() << std::endl;
	test.pop();
	std::cout << "empty after pop() = " << test.empty() << std::endl;

	test.push(20);
	test.push(4442);
	std::cout << "4442 = " <<test.top() << std::endl;
	test.pop();
	std::cout << "20 = " <<test.top() << std::endl; */

	std::cout << "======STD::VECTOR TESTS======" << std::endl;

	std::vector<int> vector(12);
	
	std::vector<int>::iterator r_it;
	std::vector<int>::const_iterator r_const_it;

	r_const_it = r_it;
/* 	int i = 0;

	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
		*it = i++;
	}

	for (std::vector<int>::reverse_iterator it = vector.rbegin(); it != vector.rend(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
	std::cout << "SIZE = " << vector.size() << " CAPACITY = " << vector.capacity() << std::endl; */

	////////////////////////////////////////////////////////////

	std::cout << "======FT::VECTOR TESTS======" << std::endl;
	ft::vector<int> my_vec(12);

	ft::vector<int>::iterator it;
	ft::vector<int>::const_iterator const_it;

	const_it = it;
/* 	int i2 = 0;

	for (ft::vector<int>::iterator it = my_vec.begin(); it != my_vec.end(); ++it) {
		*it = i2++;
	}

	for (ft::vector<int>::reverse_iterator it = my_vec.rbegin(); it != my_vec.rend(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
	std::cout << "SIZE = " << my_vec.size() << " CAPACITY = " << my_vec.capacity() << std::endl; */

	return 0;
}
