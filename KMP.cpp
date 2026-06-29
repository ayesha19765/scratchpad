#include <iostream>
#include <vector>
using namespace std;

/*
    Problem:
    Find all occurrences of a pattern in a given text.

    Intuition:
    Instead of restarting the comparison after every mismatch,
    KMP uses the LPS (Longest Prefix Suffix) array to determine
    how much of the pattern has already been matched. This avoids
    unnecessary comparisons and makes the search linear.

    When to use?
    - Finding all occurrences of a substring in a string.
    - Repeated pattern matching.
    - Text editors, plagiarism detection, DNA sequence matching.

    Algorithm:
    Knuth-Morris-Pratt (KMP)

    Topics:
    - Strings
    - Pattern Matching
    - Prefix Function

    Overall Time Complexity: O(N + M)
    Overall Space Complexity: O(M)

    where,
    N = Length of text
    M = Length of pattern
*/

// ------------------------------------------------------------
// Step 1: Build the LPS (Longest Prefix Suffix) Array
// ------------------------------------------------------------
//
// LPS[i] stores the length of the longest proper prefix
// which is also a suffix for pattern[0...i].
//
// Example:
// Pattern = "ABABC"
// LPS     = [0, 0, 1, 2, 0]
//
vector<int> buildLPS(const string& pattern) {

    int patternLength = pattern.size();
    vector<int> longestPrefixSuffix(patternLength, 0);

    int previousPrefixLength = 0;
    int currentIndex = 1;

    while (currentIndex < patternLength) {

        if (pattern[currentIndex] == pattern[previousPrefixLength]) {

            // Current prefix can be extended.
            previousPrefixLength++;
            longestPrefixSuffix[currentIndex] = previousPrefixLength;
            currentIndex++;
        }
        else {

            if (previousPrefixLength != 0) {

                // Try the next longest valid prefix instead of
                // restarting from the beginning.
                previousPrefixLength = longestPrefixSuffix[previousPrefixLength - 1];
            }
            else {

                // No matching prefix exists.
                longestPrefixSuffix[currentIndex] = 0;
                currentIndex++;
            }
        }
    }

    return longestPrefixSuffix;
}

// ------------------------------------------------------------
// Step 2: Search for all occurrences of the pattern
// ------------------------------------------------------------
//
// Returns the starting indices where the pattern appears.
//
vector<int> findPatternOccurrences(const string& text, const string& pattern) {

    vector<int> matchIndices;

    vector<int> longestPrefixSuffix = buildLPS(pattern);

    int textLength = text.size();
    int patternLength = pattern.size();

    int textIndex = 0;
    int patternIndex = 0;

    while (textIndex < textLength) {

        // Characters match, continue expanding the match.
        if (text[textIndex] == pattern[patternIndex]) {
            textIndex++;
            patternIndex++;
        }

        // Entire pattern matched.
        if (patternIndex == patternLength) {

            matchIndices.push_back(textIndex - patternIndex);

            // Continue searching for overlapping matches.
            patternIndex = longestPrefixSuffix[patternIndex - 1];
        }

        // Mismatch occurred.
        else if (textIndex < textLength &&
                 text[textIndex] != pattern[patternIndex]) {

            if (patternIndex != 0) {

                // Skip unnecessary comparisons using the LPS array.
                patternIndex = longestPrefixSuffix[patternIndex - 1];
            }
            else {

                // No prefix matched, move to the next character.
                textIndex++;
            }
        }
    }

    return matchIndices;
}

int main() {

    string text, pattern;
    cin >> text >> pattern;

    vector<int> matchIndices = findPatternOccurrences(text, pattern);

    if (matchIndices.empty()) {
        cout << "Pattern not found\n";
    }
    else {

        cout << "Pattern found at indices: ";

        for (int index : matchIndices)
            cout << index << " ";

        cout << '\n';
    }

    return 0;
}

/*
---------------------------------------------------------------
Revision Notes

• Use KMP when efficient substring searching is required.
• LPS stores the longest proper prefix that is also a suffix.
• After a mismatch, never restart from the beginning—use the
  LPS array to continue from the best possible position.
• KMP finds all occurrences in linear time.

Common Mistakes

1. Incorrect LPS construction.
2. Forgetting to update patternIndex using the LPS array.
3. Resetting patternIndex to 0 after every match instead of
   longestPrefixSuffix[patternIndex - 1].
4. Confusing prefix with proper prefix.

Overall Time Complexity : O(N + M)
Overall Space Complexity: O(M)
*/
