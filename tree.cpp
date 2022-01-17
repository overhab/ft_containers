#include "main.hpp"
#include <map>

int main() {


	ft::RBTree<int, ft::pair<int, int> >		tree;

	tree.insert(ft::pair<int, int>(10, 434));
	tree.insert(ft::pair<int, int>(3, 21));
	tree.insert(ft::pair<int, int>(1, 84));

	tree.printTree();


/* 	std::map<int, std::string>	map;
	std::string str("Hello");

	map.insert(str); */


	return 0;
}