#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <deque>
#include <utility>

class PmergeMe {

	private:

		std::list<int> _list;
		std::deque<int> _deque;
		std::list<int> smallElements;

	public:

		PmergeMe( std::string av );
		~PmergeMe();

		//list
		void log( std::string msg );
		bool buildList( std::string av );
		void printList(const std::list<int>& _list);
		bool isDigit(const std::string& numStr);
		void checkListStraggler( std::list<int>& _list, int& straggler );
		void fordJohnsonSortList( std::list<int>& _list);
		void mergeList( std::list<int>& _list, std::list<int>& left, std::list<int>& right, int straggler );
		std::list<int> build_large_list(std::list<int> &pairs, std::list<int>& inputList);
		void recursiveSort(std::list<int>& inputList);



		//deque
		void buildDeque( std::string av );
		void printDeque(const std::deque<int>& _deque);
		void checkDequeStraggler( std::deque<int>& _deque, int& straggler );
		void fordJohnsonSortDeque( std::deque<int>& _deque, int straggler );
		void mergeDeque( std::deque<int>& _deque, std::deque<int>& left, std::deque<int>& right, int straggler );

};

#endif
