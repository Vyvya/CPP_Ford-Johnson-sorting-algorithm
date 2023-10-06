#include "PmergeMe.hpp"
#include "Color.hpp"
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

PmergeMe::PmergeMe( std::string av ) {

	// timeval start, end;

	// //list
	// gettimeofday(&start, NULL);
	// // unsync the I/O of C and C++.
    // std::ios_base::sync_with_stdio(false);
	if( buildList(av) == false ) {

		return;
	}
	// gettimeofday(&end, NULL);

	// double elapsedTime;

	// elapsedTime = (end.tv_sec - start.tv_sec) * 1e6;
    // elapsedTime = (elapsedTime + (end.tv_usec - start.tv_usec)) * 1e-6;

	// std::cout << GR << "Time to process a range of " << _list.size() << " elements with std::deque: "
	// 		<< std::fixed << std::setprecision(6) << elapsedTime << " us" << std::endl;
	// std::cout << RES << std::endl;

	// //deque
	// timeval startD, endD;
	// gettimeofday(&startD, NULL);
    // std::ios_base::sync_with_stdio(false);
	// buildDeque(av);
	// gettimeofday(&endD, NULL);

	// double elapsedTimeD;

	// elapsedTimeD = (endD.tv_sec - startD.tv_sec) * 1e6;
    // elapsedTimeD = (elapsedTimeD + (endD.tv_usec - startD.tv_usec)) * 1e-6;
	// std::cout << GR << "Time to process a range of " << _deque.size() << " elements with std::deque: "
	// 		<< std::fixed << std::setprecision(6) << elapsedTimeD << " us" << std::endl;
	// std::cout << RES << std::endl;

}

PmergeMe::~PmergeMe() {

	// std::cout << "PmergeMe destructor called" << std::endl;
}

//list

bool PmergeMe::isDigit(const std::string& numStr) {

    std::string::const_iterator it = numStr.begin();
    while (it != numStr.end() && std::isdigit(*it) && *it != '0' )
		++it;
    return !numStr.empty() && it == numStr.end();
}

bool PmergeMe::buildList(std::string av) {

	std::istringstream iss(av);
	std::string num_str;
	int num;

	while (iss >> num_str) {

		if (!isDigit(num_str)) {
			log("Usage: a positive integer sequence as argument");
			return false;
		}

		num = std::stoi(num_str);
		_list.push_back( num );

	}

	if( _list.size() < 1 ) {

		log( "List is empty");
		return false;
	}

	if( _list.size() == 1 ) {

		if( num == 0 ) {

			log( "Usage: a positive integer sequence as argument");
			return false;
			
		} else {

			std::cout << BL << "Before:\t";
			printList( _list );
			std::cout << OR << "After:\t";
			printList( _list );
			return false;
		}
	}

	std::cout << BL << "Ford Johnson Sort List" << std::endl;
	std::cout << BL << "Before:\t";
	printList( _list );

	// int straggler = 0;
	// checkListStraggler( _list, straggler );
	fordJohnsonSortList( _list);

	std::cout << OR << "After:\t";
	printList( _list );
	return true;
}

void PmergeMe::printList( const std::list<int>& _list ) {

	for( std::list<int>::const_iterator it = _list.begin(); it != _list.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

// void PmergeMe::checkListStraggler( std::list<int>& _list, int& straggler ) {

// 	bool isStraggler = (_list.size() % 2 == 1);

// 	if( isStraggler ) {

// 		std::list<int>::iterator its = _list.end();
// 		--its;
// 		straggler = *its;
// 		_list.pop_back();
// 	}
// }

// void PmergeMe::fordJohnsonSortList( std::list<int>& _list) {

// 	if( _list.size() <= 1 ) {
// 		return;
// 	}

// 	std::list<std::pair<int, int> > pairs;

//     std::list<int>::iterator it = _list.begin();

//      while (it != _list.end()) {
//         if (std::next(it) != _list.end()) {
//             // Create pairs of elements and add them to 'pairs'
//             pairs.push_back(std::make_pair(*it, *std::next(it)));
//             it = std::next(it, 2); // Move to the next pair
//         } else {
//             // If there's an odd number of elements, leave one unpaired
//             pairs.push_back(std::make_pair(*it, -1)); // Use -1 to indicate unpaired
//             break;
//         }
//     }
	

// 	// Print the pairs
//     for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++ ) {
//         if (it->second == -1) {
//             std::cout << "(" << it->first << ", UNPAIRED)" << std::endl;
//         } else {
//             std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
//         }
//     }
// 	// mergeList( _list, left, right, straggler );
// }

void PmergeMe::fordJohnsonSortList( std::list<int>& _list) {

	if( _list.size() <= 1 ) {
		return;
	}

	std::list<int> pairs;

    std::list<int>::iterator it = _list.begin();

     while (it != _list.end()) {
        if (std::next(it) != _list.end()) {
            // Create pairs of elements and add them to 'pairs'
            pairs.push_back(*it);
            pairs.push_back(*std::next(it));
			if (*it > *std::next(it))
				std::swap(*it, *next(it));

            it = std::next(it, 2); // Move to the next pair
        } else {
            // If there's an odd number of elements, leave one unpaired
            pairs.push_back(*it); // Use -1 to indicate unpaired
            break;
        }
    }
	

	// Print the pairs
    for (std::list<int>::iterator it = pairs.begin(); it != pairs.end(); it++ ) {
     {
            std::cout << *it << " ";
			std::cout <<std::endl;
        }
    }
	// mergeList( _list, left, right, straggler );
	recursiveSort(pairs);
 
}

std::list<int> PmergeMe:: build_large_list(std::list<int> &pairs, std::list<int> &sortedList)
{
	std::list<int> remainingElements;
	// std::list<int> smallElements;

    std::list<int>::iterator it = pairs.begin();

	while (it != pairs.end()) {
        if (std::next(it) != pairs.end()) {
            // Create pairs of elements and add them to 'pairs'
			if (*it > *std::next(it))
			{
				sortedList.push_back(*it);
				this->smallElements.push_back(*std::next(it));
			}
			else {
			{
				sortedList.push_back(*std::next(it));
				this->smallElements.push_back(*it);
			}
			}
			it = std::next(it, 2); // Move to the next pair
		}
		else
		{
			remainingElements.push_back(*it);
			break ;
		}
    }
	for (std::list<int>::iterator it = sortedList.begin(); it != sortedList.end(); it++ ) 
     {
            std::cout << "Large: " << *it << " ";
			std::cout <<std::endl;
    }
	for (std::list<int>::iterator it = this->smallElements.begin(); it != this->smallElements.end(); it++ ) 
     {
            std::cout << "small: " << *it << " ";
			std::cout <<std::endl;
	 }
	return (sortedList);
}

void PmergeMe:: recursiveSort(std::list<int>& inputList) {
    if (inputList.size() <= 1) {
        return; // Base case: nothing to sort
    }

    std::list<int> sortedList;

    // Select larger elements and populate sortedPairs, leaving smaller elements in inputList
    std::list<int> remainingElements = build_large_list(inputList, sortedList);

    // Now, sortedPairs contains larger elements, and inputList contains remaining elements
    // Perform further processing or recursive sorting on sortedPairs if needed

    // Recursive call to sort remainingElements
    recursiveSort(remainingElements);
	for (std::list<int>::iterator it =  remainingElements.begin(); it != remainingElements.end(); it++ ) 
     {
            std::cout << "remaining elements: " << *it << " ";
			std::cout <<std::endl;
	 }
	mergeList(inputList, sortedList, this->smallElements, 0);

    // Merge sortedPairs and remainingElements if necessary
    // (This depends on the specific algorithm you're implementing)

    // Example: Merge sortedPairs into inputList
    // inputList.splice(inputList.begin(), sortedList);
}


void PmergeMe::mergeList( std::list<int>& _list, std::list<int>& left, std::list<int>& right, int straggler ) {

	(void)straggler;
	(void)_list;

    std::list<int>::iterator large;
    std::list<int>::iterator small;

	// for (std::list<int>::iterator it = right.begin(); it != right.end(); it++ ) 
    //  {
    //         std::cout << "before: " << *it << " ";
	// 		std::cout <<std::endl;
	//  }
	for (large = left.begin(); large != left.end(); ++large)
	{
		small = std::lower_bound(right.begin(), right.end(), *large, std::greater<int>());
		right.assign(small, large);
	}
	for (std::list<int>::iterator it = right.begin(); it != right.end(); it++ ) 
     {
            std::cout << "final: " << *it << " ";
			std::cout <<std::endl;
	 }

    // for (itPair = _pairList.begin(); itPair != _pairList.end(); ++itPair)
    // {
    //     itPos = lower_bound(_mainList.begin(), _mainList.end(), itPair->first); //cherche le bon emplacement
    //     _mainList.insert(itPos, itPair->first); // inserer au bon endroit
    // }
}


template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}

template <class T1, class T2> struct pair;

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}


    // while ( leftIt != left.end() && rightIt != right.end() ) {

    //     if ( *leftIt <= *rightIt) {
    //         _list.push_back( *leftIt );
    //         leftIt++;
    //     } else {
    //          _list.push_back( *rightIt );
    //         rightIt++;
    //     }
    // }

    // while( leftIt != left.end() ) {

	// 	_list.push_back(( *leftIt ));
	// 	++leftIt;
	// }

	//  while( rightIt != right.end() ) {

	// 	_list.push_back(( *rightIt ));
	// 	++rightIt;
	// }


// 	if( straggler ) {

// 		std::list<int>::iterator itEnd = _list.end();
// 		--itEnd;

// 		for( std::list<int>::iterator it = _list.begin(); it != _list.end(); it++ ) {

// 			if( straggler < *it ) {

// 				_list.insert( it, straggler );
// 				break;
// 			}

// 			if( straggler > *itEnd ) {

// 				_list.push_back( straggler );
// 				break;
// 			}
// 		}
// 	}
// }

// //deque

// void PmergeMe::buildDeque(std::string av) {

// 	std::istringstream iss(av);
// 	std::string num_str;
// 	int num;

// 	while (iss >> num_str) {

// 		if (!isDigit(num_str)) {
// 			log("Usage: a positive integer sequence as argument");
// 			return;
// 		}

// 		num = std::stoi(num_str);
// 		_deque.push_back( num );

// 	}

// 	std::cout << BL << "Ford Johnson Sort Deque" << std::endl;
// 	std::cout << BL << "Before:\t";
// 	printDeque( _deque );

// 	int straggler = 0;

// 	checkDequeStraggler( _deque, straggler );
// 	fordJohnsonSortDeque( _deque, straggler );

// 	std::cout << OR << "After:\t";
// 	printDeque( _deque );
// }

// void PmergeMe::printDeque( const std::deque<int>& _deque ) {

// 	for(  std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 		std::cout << " " << *it;
// 	}
// 	std::cout << std::endl;
// }

// void PmergeMe::checkDequeStraggler( std::deque<int>& _deque, int& straggler ) {

// 	if( _deque.size() <= 1 ) {
// 		return;
// 	}

// 	bool isStraggler = (_deque.size() % 2 == 1);

// 	if( isStraggler ) {

// 		std::deque<int>::iterator its = _deque.end();
// 		--its;
// 		straggler = *its;
// 		_deque.pop_back();
// 	}
// }

// void PmergeMe::fordJohnsonSortDeque( std::deque<int>& _deque, int straggler ) {

// 	if( _deque.size() <= 1 ) {
// 		return;
// 	}

// 	std::deque<int> left;
// 	std::deque<int> right;
// 	int middle = _deque.size() / 2;
// 	int i = 0;

// 	for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 		if( i < middle ) {

// 			left.push_back( *it );
// 		} else {

// 			right.push_back( *it );
// 		}
// 		++i;
// 	}

// 	fordJohnsonSortDeque( left, 0);
// 	fordJohnsonSortDeque( right, 0 );

// 	_deque.clear();
// 	mergeDeque( _deque, left, right, straggler );
// }

// void PmergeMe::mergeDeque( std::deque<int>& _deque, std::deque<int>& leftIt, std::deque<int>& rightIt, int straggler ) {

//     while ( !leftIt.empty() && !rightIt.empty() ) {

//         if ( leftIt.front() <= rightIt.front() ) {
//             _deque.push_back( leftIt.front() );
//             leftIt.pop_front();
//         } else {
//              _deque.push_back( rightIt.front() );
//             rightIt.pop_front();
//         }
//     }

// 	// Add any remaining elements from both containers
//     _deque.insert( _deque.end(), leftIt.begin(), leftIt.end() );
//     _deque.insert( _deque.end(), rightIt.begin(), rightIt.end() );

// 	// Insert the straggler element back into the sorted deque
// 	if( straggler ) {

// 		std::deque<int>::iterator itEnd = _deque.end();
// 		--itEnd;

// 		for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 			if( straggler < *it ) {

// 				_deque.insert( it, straggler );
// 				break;
// 			}

// 			if( straggler > *itEnd ) {

// 				_deque.push_back( straggler );
// 				break;
// 			}
// 		}
// 	}
// }

void PmergeMe::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}
