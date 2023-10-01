#pragma once

/** Public **/

/* Constructors & Destructors */
// Default constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(void):
	_startTime(0),
	_endTime(0)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : default constructor called";
	std::cout << WHITE << std::endl;
}

// Type constructor
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const std::string &str):
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
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const int &argc, char **argv):
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
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::PmergeMe(const PmergeMe &other):
	_unsortedData(other._unsortedData),
	_sortedData(other._sortedData),
	_startTime(other._startTime),
	_endTime(other._endTime)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : copy constructor called";
	std::cout << WHITE << std::endl;
}

// Assignment operator
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>	&PmergeMe<T, C>::operator=(const PmergeMe &other)
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
template <typename T, template <typename, typename> class C>
PmergeMe<T, C>::~PmergeMe(void)
{
	if (!DEBUG)
		return ;
	std::cout << CYAN;
	std::cout << "PmergeMe : default destructor called";
	std::cout << WHITE << std::endl;
}

/* Member functions */

// ::Getters

// getUnsortedData()
template <typename T, template <typename, typename> class C>
const typename PmergeMe<T, C>::Container&
PmergeMe<T, C>::getUnsortedData(void) const
{
	return (_unsortedData);
}

// getSortedData()
template <typename T, template <typename, typename> class C>
const typename PmergeMe<T, C>::Container&
PmergeMe<T, C>::getSortedData(void) const
{
	return (_sortedData);
}

// getElapsedTime()
template <typename T, template <typename, typename> class C>
double	PmergeMe<T, C>::getElapsedTime(void) const
{
	// In milliseconds.
	return (static_cast<double>(_endTime - _startTime) * 1000 / CLOCKS_PER_SEC);
}

// ::Setters

// setUnsortedData()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::setUnsortedData(const std::string &str)
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
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::setUnsortedData(const int &argc, char **argv)
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
template <typename T, template <typename, typename> class C>
const std::string	PmergeMe<T, C>::printUnsortedData(void) const
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
template <typename T, template <typename, typename> class C>
const std::string	PmergeMe<T, C>::printSortedData(void) const
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

/** Protected **/

/* Constructors & Destructors */
/* Member functions */

/** Private **/

/* Constructors & Destructors */
/* Member functions */

// startTimer()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::startTimer(void)
{
	_startTime = clock();
}

// stopTimer()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::stopTimer(void)
{
	_endTime = clock();
}

/* ************************************************************************** */
/* *               Ford-Johnson Merge Insertion sort Algorythm              * */
/* ************************************************************************** */

// fordJohnsonSort()
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::fordJohnsonSort(void)
{
	if (_sortedData.size() > 0)
		_sortedData.clear();

	startTimer();
	/* ******************** */

	// Step 1:
	t_pairedData	pairedData = generatePairs(_unsortedData);

	// Step 2:
	sortPairs(pairedData.pairs);

	//Step 3:
	if (pairedData.pairs.size())
		mergeSort(pairedData.pairs.begin(), pairedData.pairs.end());

	// Step 4:
	_sortedData = insertPendingElements(pairedData);

	/* ******************** */
	stopTimer();
}

/*
	Step 1:
		- Groups the unsorted list into pairs. If the list is odd, the last
			element is left unpaired. It will be called the straggler.
*/

template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::t_pairedData
PmergeMe<T, C>::generatePairs(const Container &container)
{
	t_pairedData	pairedData;
	ConstIterator	it = container.begin();
	ConstIterator	endIt = container.end();

	if (container.size() % 2 != 0)
	{
		pairedData.hasStraggler = true;
		pairedData.straggler = container.back();
		endIt--;
	}
	else
	{
		pairedData.hasStraggler = false;
		pairedData.straggler = T();
	}

	while (it != endIt)
	{
		const T	&first = *it++;
		const T	&second = *it++;

		pairedData.pairs.push_back(std::pair<T, T>(first, second));
	}

	return (pairedData);
}

/*
	Step 2:
		- Sort each pair into [a, b] pairs where the highest value of the pair is put first.
		- This uses [n / 2] comparaisons.
*/

template <typename T, template <typename, typename> class C>
void
PmergeMe<T, C>::sortPairs(PairContainer &pairs)
{
	for (PairIterator pairIt = pairs.begin(); pairIt != pairs.end(); pairIt++)
		if (pairIt->first < pairIt->second)
			std::swap(pairIt->first, pairIt->second);
}

/*
	Step 3:
		- Sort the pairs recursively based on the a (smallest value) of each pair.
			The pairs would become {[a1, b1], [a2, b2], ...}.
		- If there is a straggler, it will be considered as last element.
*/
template <typename T, template <typename, typename> class C>
void
PmergeMe<T, C>::mergeSort(PairIterator begin, PairIterator end)
{
	if (std::distance(begin, end) <= 1)
		return ;

	PairIterator	middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);

	mergeSort(begin, middle);
	mergeSort(middle, end);

	merge(begin, middle, end);
}

template <typename T, template <typename, typename> class C>
void
PmergeMe<T, C>::merge(PairIterator begin, PairIterator middle, PairIterator end)
{
	PairContainer	left(begin, middle);
	PairContainer	right(middle, end);

	PairIterator	leftIt = left.begin();
	PairIterator	rightIt = right.begin();
	PairIterator	currentIt = begin;

	while (leftIt != left.end() && rightIt != right.end())
	{
		if (*leftIt <= *rightIt)
			*currentIt++ = *leftIt++;
		else
			*currentIt++ = *rightIt++;
	}

	while (leftIt != left.end())
		*currentIt++ = *leftIt++;

	while (rightIt != right.end())
		*currentIt++ = *rightIt++;
}

/*
	Step 4:
		- The a elements of the pairs form the mainChain. The b elements form
			the pendingElements.
		- The mainChain is composed of [n / 2] elements and already sorted.
		- The pendingElements could be inserted via BinarySearch. But different
			b have different worst-case cost of comparaisons during BinarySearch
			insertion. We can minimize that cost by following the order based on
			the Jacobsthal sequence who match (2^x - 1) values. BinarySearch uses
			the same number of comparisons for 2^x  than 2^(x + 1) - 1 elements.
*/

template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::Container
PmergeMe<T, C>::insertPendingElements(const t_pairedData &pairedData)
{
	Container		mainChain;
	GroupContainer	pendingChain;

	splitPairs(pairedData.pairs, mainChain, pendingChain);

	ConstGroupIterator	groupIt = pendingChain.begin();
	size_t				groupOffset = 0;

	// First insert doesn't need any comparator. We know b1 <= a1.
	mainChain.insert(mainChain.begin(), *groupIt->begin());
	groupIt++;
	groupOffset++;

	while (groupIt != pendingChain.end())
	{
		groupOffset += groupIt->size();

		for (ConstIterator it = groupIt->begin(); it != groupIt->end(); it++)
		{
			const T		&target = *it;

			Iterator	searchStart = mainChain.begin();
			Iterator	searchEnd = mainChain.begin();
			std::advance(searchEnd, groupOffset);

			Iterator	insertionPos = binarySearch(searchStart, searchEnd, target);
			mainChain.insert(insertionPos, target);
		}

		groupIt++;
	}

	if (pairedData.hasStraggler)
	{
		const T		&target = pairedData.straggler;
		Iterator	searchStart = mainChain.begin();
		Iterator	searchEnd = mainChain.end();

		Iterator	insertionPos = binarySearch(searchStart, searchEnd, target);
		mainChain.insert(insertionPos, target);
	}

	return (mainChain);
}

template <typename T, template <typename, typename> class C>
void
PmergeMe<T, C>::splitPairs(const PairContainer &pairs,
	Container &mainChain, GroupContainer &pendingChain)
{
	JacobsthalContainer	jacobsthalSequence = generateJacobsthalSequence(pairs.size());
	ConstPairIterator	pairIt = pairs.begin();
	ConstPairIterator	nextPairIt = pairs.begin();
	ConstJacobIterator	jacobIt = jacobsthalSequence.begin();

	while (jacobIt != jacobsthalSequence.end() && pairIt != pairs.end())
	{
		Container			group;

		nextPairIt = pairs.begin();
		std::advance(nextPairIt, *jacobIt);

		while (pairIt != pairs.end() && pairIt != nextPairIt)
		{
			mainChain.push_back(pairIt->first);
			group.push_back(pairIt->second);

			pairIt++;
		}

		std::reverse(group.begin(), group.end());
		pendingChain.push_back(group);

		jacobIt++;
	}
}

template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::Iterator
PmergeMe<T, C>::binarySearch(Iterator left, Iterator right, const T &target)
{
	// Lowerbound binary search

	while (std::distance(left, right) > 0)
	{
		Iterator	middle = left;
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

template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::JacobsthalContainer
PmergeMe<T, C>::generateJacobsthalSequence(const size_t size)
{
	JacobsthalContainer				jacobsthalSequence;

	if (size <= 2)
		return (jacobsthalSequence);

	size_t	a = 0;
	size_t	b = 1;
	size_t	next;

	while (a < size)
	{
		next = (a * 2) + b;
		jacobsthalSequence.push_back(next);
		a = b;
		b = next;
	}
	return (jacobsthalSequence);
}
