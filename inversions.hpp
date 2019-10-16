/******************************************************
* Curtis Fortenberry
* 2019-10-15
* Chris Hartman CS411
* HW3: Ex B
* inversions.hpp last rev. 2019-15-10
******************************************************/
/******************************************************
* Desc: Count the number of inversions in a given 
* unsorted sequence using a Divide and Conquer strategy
******************************************************/
/******************************************************
* This assignment uses code from Dr. Glenn Chappell's
* stable merge sort code, with some edits for naming
* consistency.
******************************************************/
#ifndef INVERSIONS_HPP_INCLUDED
#define INVERSIONS_HPP_INCLUDED

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

template <typename FDIter>
std::size_t countInversions(FDIter first, FDIter middle, FDIter last) {
	using Value = typename std::remove_reference<decltype(*first)>::type;

    std::vector<Value> buffer(std::distance(first, last));
                                // Buffer for temporary copy of data
    FDIter in1 = first;         // Read location in 1st half
    FDIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than vector<Value>::iterator

    // Merge two sorted lists into a single list in buff.
	std::size_t inv = 0;
	
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) { // Must do comparison this way, to be stable.
            *out++ = *in2++;
			inv += (middle - in1);
		}
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    std::copy(in1, middle, out);
    std::copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    std::copy(buffer.begin(), buffer.end(), first);
	
	return inv;
}

template <typename FDIter>
std::size_t inversions_recurse(FDIter first, FDIter last) {
	// Compute size of sequence
    size_t size = std::distance(first, last);
    size_t inverts = 0;

    // RECURSIVE CASE
    if (size > 1) {
		FDIter middle = first;
		std::advance(middle, size/2);  // middle is iterator to middle of range

		// Recursively sort the two lists
		inverts = inversions_recurse(first, middle);
		inverts += inversions_recurse(middle, last);
		
		// And merge them
		inverts += countInversions(first, middle, last);
	}
	
	// BASE CASE REACHED
	return inverts;
}

template <typename RAIter>
std::size_t inversions(RAIter first, RAIter last) {
	return inversions_recurse(first, last);
}

#endif// INVERSIONS_HPP_INCLUDED