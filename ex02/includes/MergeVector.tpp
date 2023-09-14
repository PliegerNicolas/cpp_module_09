/* Constructors & Destructors */

// Public

template <typename T>
MergeVector<T>::MergeVector(const std::string &values):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeVector : constructor with values parameter called";
	std::cout << WHITE << std::endl;

	std::istringstream	iss(values);
	T					value;

	while (iss >> value)
		_data.push_back(value);

	fordJohnsonSort();
}

template <typename T>
MergeVector<T>::MergeVector(const MergeVector &other):
	APmergeMe<T>(other),
	_data(other._data),
	_sorted(other._sorted),
	_pairs(other._pairs)
{
	std::cout << CYAN;
	std::cout << "MergeVector : copy constructor called";
	std::cout << WHITE << std::endl;
}

template <typename T>
MergeVector<T>	&MergeVector<T>::operator=(const MergeVector &other)
{
	std::cout << CYAN;
	std::cout << "MergeVector : assignment operator called";
	std::cout << WHITE << std::endl;

	if (this != &other)
	{
		APmergeMe<T>::operator=(other);
		_data = other._data;
		_sorted = other._sorted;
		_pairs = other._pairs;
	}
	return (*this);
}

template <typename T>
MergeVector<T>::~MergeVector(void)
{
	std::cout << CYAN;
	std::cout << "MergeVector : default destructor called";
	std::cout << WHITE << std::endl;
}

// Protected

// Private

template <typename T>
MergeVector<T>::MergeVector(void):
	APmergeMe<T>()
{
	std::cout << CYAN;
	std::cout << "MergeVector : default constructor called";
	std::cout << WHITE << std::endl;
}

/* Member functions */

// Public

template <typename T>
void	MergeVector<T>::fordJohnsonSort(void)
{
	_pairs.clear();
	_sorted.clear();
	_pendingElements.clear();

	_sorted.reserve((_data.size() / 2) + 1);
	if (_data.size() % 2 != 0)
		_pendingElements.reserve(_data.size() / 2);
	else
		_pendingElements.reserve((_data.size() / 2) - 1);

	// .reserve() maybe for later

	/* Start timer */
	APmergeMe<T>::startTimer();

	/* Step 1 & 2:	[n comparisons] Split data into pairs and sort the elements of		*/
	/*			these pairs with each other.											*/
	toSortedPairs();

	/* Step 3 & 4:	[n / 2 comparisons] Recursivly sort the pairs and build '_sorted'	*/
	/*				also known as 'S' in Wikipedia and _pendingElements, the unsorted	*/
	/*				values left. 'S' contains n/2 elements. It also inserts at the		*/
	/*				start of S the element that was paired with the first and smallest	*/
	/*				element of 'S'.														*/
	mergeSort(0, _pairs.size() - 1);
	generateSortedAndPending();

	// End timer
	APmergeMe<T>::stopTimer();

	std::cout << "Vector = " << APmergeMe<T>::getElapsedTime() << " seconds" << std::endl;
}

// Protected

// Step 1

template <typename T>
void	MergeVector<T>::toSortedPairs(void)
{
	size_t	size;

	_pairs.clear();

	size = _data.size();
	if (size % 2 != 0)
	{
		APmergeMe<T>::_straggler.has = true;
		APmergeMe<T>::_straggler.value = _data.back();
		size--;
	}

	_pairs.reserve(size / 2);

	for (size_t i = 0; i < size; i += 2)
	{
		T	first = _data[i];
		T	second = _data[i + 1];
		if (first < second)
			_pairs.push_back(std::pair<T, T>(first, second));
		else
			_pairs.push_back(std::pair<T, T>(second, first));
	}
}

// Step 2

template <typename T>
void	MergeVector<T>::mergeSort(size_t begin, size_t end)
{

	if (begin>= end)
		return ;

	size_t	middle = begin + (end - begin) / 2;

	mergeSort(begin, middle);
	mergeSort(middle + 1, end);

	merge(begin, middle, end);
}

template <typename T>
void	MergeVector<T>::merge(size_t begin, size_t middle, size_t end)
{
	std::vector<std::pair<T, T> >	leftArr(_pairs.begin() + begin, _pairs.begin() + middle + 1);
	std::vector<std::pair<T, T> >	rightArr(_pairs.begin() + middle + 1, _pairs.begin() + end + 1);

	size_t	leftIdx = 0;
	size_t	rightIdx = 0;
	size_t	mergedIdx = begin;

	while (leftIdx < leftArr.size() && rightIdx < rightArr.size())
	{
		if (leftArr[leftIdx].first <= rightArr[rightIdx].first)
			_pairs[mergedIdx++] = leftArr[leftIdx++];
		else
			_pairs[mergedIdx++] = rightArr[rightIdx++];
	}

	while (leftIdx < leftArr.size())
		_pairs[mergedIdx++] = leftArr[leftIdx++];

	while (rightIdx < rightArr.size())
		_pairs[mergedIdx++] = rightArr[rightIdx++];

}

template <typename T>
void	MergeVector<T>::generateSortedAndPending(void)
{
	if (_pairs.empty())
		return ;

	if (_pairs.size() > 0)
	{
		_sorted.push_back(_pairs[0].second);
		_sorted.push_back(_pairs[0].first);
	}

	for (size_t i = 1; i < _pairs.size(); i++)
	{
		_sorted.push_back(_pairs[i].first);
		_pendingElements.push_back(_pairs[i].second);
	}

	if (APmergeMe<T>::_straggler.has)
	{
		_pendingElements.push_back(APmergeMe<T>::_straggler.value);
		APmergeMe<T>::_straggler.has = false;
		APmergeMe<T>::_straggler.value = 0;
	}

	_pairs.clear();
}

// ----------

template <typename T>
size_t	MergeVector<T>::lowerboundBinarySearch(const std::vector<T> &arr, const T &target)
{
	size_t	left = 0;
	size_t	right = arr.size();
	size_t	middle;
	size_t	result = arr.size();

	while (left < right)
	{
		middle = left + (right - left) / 2;

		if (arr[middle] == target)
			return (middle);
		else if (arr[middle] < target)
			left = middle + 1;
		else
		{
			result = middle;
			right = middle;
		}
	}
	return (result);
}

// Private
