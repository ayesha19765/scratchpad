#include <iostream>
#include <vector>
using namespace std;

/*
    Problem:
    Given a list of patterns and a word, return the number of patterns
    that appear as a substring in the given word.

    Intuition:
    Instead of checking every possible starting position for each pattern,
    use the KMP (Knuth-Morris-Pratt) algorithm to efficiently determine
    whether a pattern exists in the word.

    When to use?
    - Efficient substring searching.
    - Checking if a pattern exists in a larger string.
    - Multiple pattern searches (one pattern at a time).

    Algorithm:
    Knuth-Morris-Pratt (KMP)

    Topics:
    - Strings
    - Pattern Matching
    - KMP

    Overall Time Complexity: O(P × (N + M))
    Overall Space Complexity: O(M)

    where,
    P = Number of patterns
    N = Length of the word
    M = Average length of a pattern
*/

class Solution {
public:

    // ------------------------------------------------------------
    // Step 1: Build the LPS (Longest Prefix Suffix) Array
    // ------------------------------------------------------------
    //
    // LPS[i] stores the length of the longest proper prefix
    // which is also a suffix for pattern[0...i].
    //
    vector<int> buildLPS(string pattern) {

        int patternLength = pattern.size();
        vector<int> longestPrefixSuffix(patternLength, 0);

        int previousPrefixLength = 0;
        int currentIndex = 1;

        while (currentIndex < patternLength) {

            if (pattern[currentIndex] == pattern[previousPrefixLength]) {

                // Extend the current matching prefix.
                longestPrefixSuffix[currentIndex++] = ++previousPrefixLength;
            }
            else {

                if (previousPrefixLength != 0) {

                    // Try the next longest valid prefix.
                    previousPrefixLength =
                        longestPrefixSuffix[previousPrefixLength - 1];
                }
                else {

                    // No valid prefix exists for this position.
                    currentIndex++;
                }
            }
        }

        return longestPrefixSuffix;
    }

    // ------------------------------------------------------------
    // Step 2: Check if the pattern exists in the text
    // ------------------------------------------------------------
    //
    // Returns true as soon as the first occurrence is found.
    //
    bool isSubstring(string text, string pattern) {

        int textLength = text.size();
        int patternLength = pattern.size();

        vector<int> longestPrefixSuffix = buildLPS(pattern);

        int textIndex = 0;
        int patternIndex = 0;

        while (textIndex < textLength) {

            // Characters match, continue expanding the match.
            if (text[textIndex] == pattern[patternIndex]) {
                textIndex++;
                patternIndex++;
            }

            // Entire pattern has been matched.
            if (patternIndex == patternLength)
                return true;

            // Mismatch after matching some characters.
            if (textIndex < textLength &&
                text[textIndex] != pattern[patternIndex]) {

                if (patternIndex != 0) {

                    // Use the LPS array to skip unnecessary comparisons.
                    patternIndex =
                        longestPrefixSuffix[patternIndex - 1];
                }
                else {

                    // No prefix matched, move to the next character.
                    textIndex++;
                }
            }
        }

        return false;
    }

    int numOfStrings(vector<string>& patterns, string word) {

        int matchingPatternCount = 0;

        // Count how many patterns are present in the given word.
        for (const string& pattern : patterns) {
            matchingPatternCount += isSubstring(word, pattern);
        }

        return matchingPatternCount;
    }
};

/*
---------------------------------------------------------------
Revision Notes

• Use KMP whenever efficient substring searching is required.
• LPS stores the longest proper prefix that is also a suffix.
• After a mismatch, use the LPS array instead of restarting
  the comparison from the beginning.
• This solution checks each pattern independently.

Common Mistakes

1. Incorrect construction of the LPS array.
2. Forgetting to update patternIndex using the LPS array.
3. Accessing pattern[patternIndex] after patternIndex reaches
   patternLength.
4. Restarting the search after every mismatch.

Overall Time Complexity : O(P × (N + M))
Overall Space Complexity: O(M)
*/
