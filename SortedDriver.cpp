// SortedDriver.cpp
// Jesse Cornejo
// COSC 2030
// 10/27/2017
// Help from Damire Pulatov

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{

	// Find length of number vector
	int length = number.size();


	// Set up variables to store the distances and max distance
	double distance;
	double max = 0;
	int max_index = 0;

	for (int i = 0; i < length; i++)
	{
		// If first/last element, find right/left distances only
		if (i == 0)
		{
			distance = abs(number[i] - number[i + 1]);
		}
		else if (i == length - 1)
		{
			distance = abs(number[i] - number[i - 1]);
		}

		// Calculate left and right distances and find the nearest neighbor
		else
		{
			double left = abs(number[i] - number[i - 1]);
			double right = abs(number[i] - number[i + 1]);
			if (left > right)
			{
				distance = right;
			}
			else
			{
				distance = left;
			}
		}

		// Compare distances and find max distance index
		if (distance > max)
		{
			max = distance;
			max_index = i;
		}

	}


	return number[max_index];

}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	// STUB  STUB  STUB
	// Inititalize number of matched words to zero
	int matched = 0;

	// Iterate through two lists with iterators
	// If found a match, break and increment number of matched
	int index_offset = 0;

	// Set up iterators
	list<string>::iterator it_a = A.begin();
	list<string>::iterator it_b = B.begin();


	// Search through strings
	while (it_a != A.end() && it_b != B.end())
	{
		// If words are equal, count as match
		if (*it_a == *it_b)
		{
			it_a++;
			matched++;
		}
		// If the word in first list is greater, move to next word in second list (there is a match)
		else if(*it_a > *it_b)
		{
			it_b++;
		}
		// If the word in first list is less, move to next word in first list (there is no match)
		else if (*it_a < *it_b)
		{
			it_a++;
		}
	}


	// Number of unmatched = size - matched
	int unmatched = A.size() - matched;

	return unmatched;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
