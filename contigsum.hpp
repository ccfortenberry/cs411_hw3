/******************************************************
* Curtis Fortenberry
* 2019-10-15
* Chris Hartman CS411
* HW3: Ex A
* contigsum.hpp last rev. 2019-15-10
******************************************************/
/******************************************************
* Desc: Use a Divide and Conquer strategy to find the
* greatest contiguous sum of a given sequence. The
* algorithm must be O(n*lg(n))+O(1), and implemented
* in such a way that it finds the following info:
*    A. The GCS of the sequence
*    B. The GCS including the first value
*    C. The GCS including the last value
*    D. The total sum of the sequence
******************************************************/
#ifndef CONTIGSUM_HPP_INCLUDED
#define CONTIGSUM_HPP_INCLUDED

#include <algorithm>
#include <iterator>

// Maxima
// Simple struct to hold the info required for the alg.
struct Maxima {
	int a, b, c, d = 0; // See above description for what
						// the letters correspond to.
	Maxima()=default; // default'd Default Ctor
	Maxima(int val)   // Ctor by value
		:a(val), b(val), c(val), d(val)
	{}
	
	// Let the compiler handle the copy, move, and dtor
};

Maxima findMax(const Maxima & leftSum, const Maxima & rightSum) {
	Maxima maxsum;
	
	maxsum.d = leftSum.d + rightSum.d; // The total of the sequence
	maxsum.c = std::max({rightSum.c, rightSum.d+leftSum.c, maxsum.d}); // GCS including final value of the sequence
	maxsum.b = std::max({leftSum.b, leftSum.d+rightSum.b, maxsum.d}); // GCS including the first value of the seq.
	maxsum.a = std::max({maxsum.b, maxsum.c, maxsum.d, leftSum.a, rightSum.a, leftSum.c+rightSum.b}); // The GCS we want
	
	return maxsum;
}

template <typename RAIter>
Maxima contigSum_recurse(RAIter first, RAIter last) {
	std::size_t size = std::distance(first, last);
	
	// CASE: RECURSE
	if (size > 1) {
		RAIter middle = first;
		std::advance(middle, size/2);
		
		Maxima leftSum = contigSum_recurse(first, middle);
		Maxima rightSum = contigSum_recurse(middle, last);
		return findMax(leftSum, rightSum);
	} // CASE: BASE
	else if (size == 1)
		return Maxima(*first);
}

template <typename RAIter>
int contigSum(RAIter first, RAIter last) {
	Maxima maxsum = contigSum_recurse(first, last);
	if (maxsum.a < 0) maxsum.a = 0;
	return maxsum.a;
}

#endif// CONTIGSUM_HPP_INCLUDED