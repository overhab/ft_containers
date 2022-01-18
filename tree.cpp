#include "main.hpp"
#include <map>

int main() {


	ft::RBTree<int, ft::pair<int, int> >		tree;

	tree.insert(ft::pair<int, int>(10, 434));
	tree.insert(ft::pair<int, int>(3, 21));
	tree.insert(ft::pair<int, int>(35, 61));
	tree.insert(ft::pair<int, int>(1, 84));
	tree.insert(ft::pair<int, int>(12, 81));
	tree.insert(ft::pair<int, int>(7, 55));

	tree.printTree();

	std::cout << "-----------ITERATOR-------------" << std::endl;
	ft::RBTree<int, ft::pair<int, int> >::const_reverse_iterator	itt = tree.rbegin();
	//itt->second = 2222222;
	for (; itt != tree.rend(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;

	std::cout << "find(35): " << tree.find(35)->second << "\ncount(3): " << tree.count(3) << std::endl;
	
	ft::RBTree<int, ft::pair<int, int> >::iterator	kek = tree.end();
	--kek;
	std::cout << "--end(): " << kek->first << ' ' << kek->second << std::endl;

	ft::RBTree<int, ft::pair<int, int> >::const_iterator	low_b = tree.lower_bound(12);

	std::cout << "lower bound(12): " << low_b->second << std::endl;

	ft::RBTree<int, ft::pair<int, int> >::const_iterator	up_b = tree.upper_bound(12);

	std::cout << "upper bound(12): " << up_b->second << std::endl;

	//tree.iterator_test();
	
	std::cout << "-----------MAP-------------" << std::endl;

	std::map<int, int>	mmap;

	mmap.insert(std::pair<int, int>(1, 10));
	mmap.insert(std::pair<int, int>(2, 20));
	mmap.insert(std::pair<int, int>(3, 30));
	mmap.insert(std::pair<int, int>(4, 40));
	mmap.insert(std::pair<int, int>(5, 50));
	mmap.insert(std::pair<int, int>(5, 5120));

	std::map<int, int>::iterator it = mmap.begin();
	for (; it != mmap.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	std::map<int, int>::iterator lb = mmap.lower_bound(3);

	std::cout << "lower bound(3): " << lb->second << std::endl;

	std::map<int, int>::iterator ub = mmap.upper_bound(3);

	std::cout << "upper bound(3): " << ub->second << std::endl;

	return 0;
}