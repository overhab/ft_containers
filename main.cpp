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


	std::vector<int> for_fill(4, 42);

	std::cout << "======STD::VECTOR TESTS======" << std::endl;

	std::vector<int> vector(12, 12);

	vector.insert(vector.begin() + 3, for_fill.begin(), for_fill.end());
	std::cout << "new capacity = " << vector	.capacity() << std::endl;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
/* 	int i2 = 0;

	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		*it = i2++;
	}
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << vector.size() << std::endl;

	vector.erase(vector.begin() + 3);
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << vector.size() << std::endl; */



	//vector.at(12);
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
	ft::vector<int> my_vec(12, 12);

	my_vec.insert(my_vec.begin() + 3, for_fill.begin(), for_fill.end());
	std::cout << "new capacity = " << my_vec.capacity() << std::endl;
	for (ft::vector<int>::iterator it = my_vec.begin(); it != my_vec.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;

/* 	int i = 0;

	for (ft::vector<int>::iterator it = my_vec.begin(); it != my_vec.end(); it++) {
		*it = i++;
	}
	for (ft::vector<int>::iterator it = my_vec.begin(); it != my_vec.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << my_vec.size() << std::endl;

	my_vec.erase(my_vec.begin() + 3);
	for (ft::vector<int>::iterator it = my_vec.begin(); it != my_vec.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << my_vec.size() << std::endl; */



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
