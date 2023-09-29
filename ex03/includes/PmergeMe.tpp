#pragma once
#include "PmergeMe.hpp"

/** Public **/

/* Constructors & Destructors */
// Default constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(void):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : default constructor called";
		std::cout << WHITE << std::endl;
	}
}

// Type constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const std::string &str):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with str parameter called";
		std::cout << WHITE << std::endl;
	}

	setUnsortedData(str);
}

// Type constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const int &argc, char **argv):
	_startTime(0),
	_endTime(0)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : constructor with argc and argv parameters called";
		std::cout << WHITE << std::endl;
	}

	setUnsortedData(argc, argv);
}

// Copy constructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::PmergeMe(const PmergeMe &other):
	_unsortedData(other._unsortedData),
	_sortedData(other._sortedData),
	_startTime(other._startTime),
	_endTime(other._endTime)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : copy constructor called";
		std::cout << WHITE << std::endl;
	}
}

// Assignment operator
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>	&PmergeMe<T, Container>::operator=(const PmergeMe &other)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : assignment operator called";
		std::cout << WHITE << std::endl;
	}

	if (this != &other)
	{
		_unsortedData = other._unsortedData;
		_sortedData = other._sortedData;
		_startTime = other._startTime;
		_endTime = other._endTime;
	}
	return (*this);
}

// Default destructor
template <typename T, template <typename, typename> class Container>
PmergeMe<T, Container>::~PmergeMe(void)
{
	if (DEBUG)
	{
		std::cout << CYAN;
		std::cout << "PmergeMe : default destructor called";
		std::cout << WHITE << std::endl;
	}
}

/* Member functions */

// ::Getters

// getUnsortedData()
template <typename T, template <typename, typename> class Container>
const Container<T, typename PmergeMe<T, Container>::Alloc>	&PmergeMe<T, Container>::getUnsortedData(void) const
{
	return (_unsortedData);
}

// getSortedData()
template <typename T, template <typename, typename> class Container>
const Container<T, typename PmergeMe<T, Container>::Alloc>	&PmergeMe<T, Container>::getSortedData(void) const
{
	return (_sortedData);
}

// getElapsedTime()
template <typename T, template <typename, typename> class Container>
double	PmergeMe<T, Container>::getElapsedTime(void) const
{
	// In milliseconds.
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// ::Setters

// setUnsortedData()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::setUnsortedData(const std::string &str)
{
	std::istringstream	iss;
	T					val;

	_unsortedData.clear();
	_sortedData.clear();

	iss.clear();
	iss.str(str);
	while (iss >> val)
		_unsortedData.push_back(val);

	if (!iss.eof())
	{
		_unsortedData.clear();
		throw std::runtime_error(
			std::string(RED)
			+ "Error: invalid data passed."
			+ WHITE
		);
	}
}

// setUnsortedData()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::setUnsortedData(const int &argc, char **argv)
{
	std::istringstream	iss;
	T					val;

	_unsortedData.clear();
	_sortedData.clear();

	for (size_t i = 1; i < static_cast<size_t>(argc); i++)
	{
		iss.clear();
		iss.str(argv[i]);

		while (iss >> val)
			_unsortedData.push_back(val);

		if (!iss.eof())
		{
			_unsortedData.clear();
			throw std::runtime_error(
				std::string(RED)
				+ "Error: invalid data passed."
				+ WHITE
			);
		}
	}
}

// :Other

// printUnsortedData()
template <typename T, template <typename, typename> class Container>
const std::string	PmergeMe<T, Container>::printUnsortedData(void) const
{
	std::stringstream	ss;
	ConstIterator		it;

	ss << "{";
	for (it = _unsortedData.begin(); it != _unsortedData.end(); it++)
	{
		ss << *it;
		if (it != --_unsortedData.end())
			ss << ", ";
	}
	ss << "}";
	return (ss.str());
}

// printSortedData()
template <typename T, template <typename, typename> class Container>
const std::string	PmergeMe<T, Container>::printSortedData(void) const
{
	std::stringstream	ss;
	ConstIterator		it;

	ss << "{";
	for (it = _sortedData.begin(); it != _sortedData.end(); it++)
	{
		ss << *it;
		if (it != --_sortedData.end())
			ss << ", ";
	}
	ss << "}";
	return (ss.str());
}

// fordJohnsonSort()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::fordJohnsonSort(void)
{
	startTimer();

	recursivePairsTraversal(_unsortedData);

	stopTimer();
}

/** Protected **/

/* Constructors & Destructors */
/* Member functions */

/** Private **/

/* Constructors & Destructors */
/* Member functions */

// startTimer()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::startTimer(void)
{
	_startTime = clock();
}

// stopTimer()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::stopTimer(void)
{
	_endTime = clock();
}














// generatePairs()
template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::recursivePairsTraversal(Container<T, Alloc> &container)
{

	if (container.size() <= 1)
	{
		_sortedData = container;
		return ;
	}

	t_pairedData			pairedData = createPairedData(container);
	Container<T, Alloc>		pendingElements = createPendingData(pairedData);

	recursivePairsTraversal(pendingElements);

	// ???
	insertSmallestNeighbour(pairedData);
	for (PairsIterator pairIt = pairedData.pairs.begin(); pairIt != pairedData.pairs.end(); pairIt++)
	{
		Iterator	insertionPos = higherboundBinarySearch(_sortedData, pairIt->second);
		_sortedData.insert(insertionPos, pairIt->second);
	}

	if (pairedData.hasStraggler)
	{
		Iterator	insertionPos = higherboundBinarySearch(_sortedData, pairedData.stragglerValue);
		_sortedData.insert(insertionPos, pairedData.stragglerValue);
	}
}

template <typename T, template <typename, typename> class Container>
void	PmergeMe<T, Container>::insertSmallestNeighbour(PmergeMe<T, Container>::t_pairedData &pairedData)
{
	T				smallestPairedElement;
	PairsIterator	smallestPairedElementIterator;

	for (PairsIterator it = pairedData.pairs.begin(); it != pairedData.pairs.end(); it++)
	{
		if (it == pairedData.pairs.begin() || it->second < smallestPairedElement)
		{
			smallestPairedElement = it->second;
			smallestPairedElementIterator = it;
		}
	}

	_sortedData.insert(_sortedData.begin(), smallestPairedElement);
	pairedData.pairs.erase(smallestPairedElementIterator);
}

template <typename T, template <typename, typename> class Container>
typename PmergeMe<T, Container>::t_pairedData
PmergeMe<T, Container>::createPairedData(Container<T, Alloc> &container)
{
	t_pairedData	pairedData;
	ConstIterator	end;

	// Isolate straggler.
	end = container.end();
	if (container.size() % 2 != 0)
	{
		pairedData.hasStraggler = true;
		pairedData.stragglerValue = container.back();
		end--;
	}
	else
	{
		pairedData.hasStraggler = false;
		pairedData.stragglerValue = T();
	}

	// Fill with pairs. First element is the biggest of both.
	for (ConstIterator it = container.begin(); it != end; it++)
	{
		const T	&first = *it++;
		const T &second = *it;
		if (first > second)
			pairedData.pairs.push_back(std::pair<T, T>(first, second));
		else
			pairedData.pairs.push_back(std::pair<T, T>(second, first));
	}

	return (pairedData);
}

template <typename T, template <typename, typename> class Container>
Container<T, typename PmergeMe<T, Container>::Alloc>
PmergeMe<T, Container>::createPendingData(t_pairedData &pairedData)
{
	Container<T, Alloc>	pendingData;

	for (ConstPairsIterator it = pairedData.pairs.begin(); it != pairedData.pairs.end(); it++)
		pendingData.push_back(it->first);

	return (pendingData);
}

// higherboundBinarySearch()
template <typename T, template <typename, typename> class Container>
typename Container<T, typename PmergeMe<T, Container>::Alloc>::iterator
PmergeMe<T, Container>::higherboundBinarySearch(Container<T, typename PmergeMe<T,
	Container>::Alloc> &container, const T &target)
{
	Iterator	left = container.begin();
	Iterator	right = container.end();

	while (std::distance(left, right) > 0)
	{
		Iterator	middle;

		middle = left;
		std::advance(middle, (std::distance(left, right) / 2));
		if (*middle < target)
		{
			left = middle;
			std::advance(left, 1);
		}
		else
			right = middle;
	}
	return (left);
}
