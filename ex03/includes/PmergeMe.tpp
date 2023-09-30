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

	// Step 1
	t_pairedData	pairedData = generateOrderedPairs(_unsortedData);

	// Step2
	Container	pendingElements = recursivePairSort(pairedData);

	stopTimer();
}

/*
	Step 1:
		- Split the collection in n/2 pairs of 2 elements.
		-  Order these pair's elements pairwise (highest value as first,
			smallest value as second, it's an arbitrary choice).
		- If the number of elements is odd, put the last element on the side.
			It isn't paired with any element and it will be considered at the
			end of the list. That element is called the straggler.
*/
template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::t_pairedData
PmergeMe<T, C>::generateOrderedPairs(const Container &container)
{
	t_pairedData	pairedData;
	ConstIterator	it = container.begin();
	ConstIterator	end = container.end();

	// Isolate straggler if odd number of values.
	if (container.size() % 2 != 0)
	{
		pairedData.hasStraggler = true;
		pairedData.straggler = container.back();
		end--;
	}
	else
	{
		pairedData.hasStraggler = false;
		pairedData.straggler = T();
	}

	// Fill the pairedData container, sorting the pairs internally.
	while (it != end)
	{
		const T	&first = *it;
		std::advance(it, 1);
		const T	&second = *it;
		std::advance(it, 1);

		if (first > second)
			pairedData.pairs.push_back(std::pair<T, T>(first, second));
		else
			pairedData.pairs.push_back(std::pair<T, T>(second, first));
	}
	return (pairedData);
}

/*
	Step 2:
		- Recursivly sort the pairs of elements by their highest value.
		- The straggler is isolated and considered as if at the end of the
			pairs collection.
		- The highest values of the sorted pairs form the 'main chain' and
			the smallest the 'pending elements'. In our situation we know
			that mainChain[i] <= pendingElements[i].
*/
template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::merge(PairIterator begin, PairIterator middle, PairIterator end)
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

template <typename T, template <typename, typename> class C>
void	PmergeMe<T, C>::mergeSort(PairIterator begin, PairIterator end)
{
	if (std::distance(begin, end) <= 1)
		return ;

	PairIterator	middle;

	middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);

	mergeSort(begin, middle);
	mergeSort(middle, end);

	merge(begin, middle, end);
}

template <typename T, template <typename, typename> class C>
typename PmergeMe<T, C>::Container
PmergeMe<T, C>::recursivePairSort(t_pairedData &pairedData)
{
	// Recursivly sort the pairs, excluding the straggler.
	mergeSort(pairedData.pairs.begin(), pairedData.pairs.end());

	Container	pendingElements;

	// Build the mainChain (_sortedData) and pendingElementsChain from the highest
	// values of the pairs. Those are sorted so _sortedData will be sorted as well.
	for (ConstPairIterator it = pairedData.pairs.begin(); it != pairedData.pairs.end(); it++)
	{
		_sortedData.push_back(it->first);
		pendingElements.push_back(it->second);
	}

	// Insert straggler at the end of pendingElements.
	if (pairedData.hasStraggler)
		pendingElements.push_back(pairedData.straggler);

	return (pendingElements);
}
