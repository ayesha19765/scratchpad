#include <iostream>
#include <vector>
using namespace std;
/*
    Problem:
    Count the number of substrings containing at least one occurrence
    of each character: 'a', 'b', and 'c'.

    Intuition:
    Instead of counting valid substrings directly, count the substrings
    that are invalid (contain fewer than 3 distinct characters) and
    subtract them from the total number of substrings.

    Total Substrings = N * (N + 1) / 2

    Answer = Total Substrings - Invalid Substrings

    When to use?
    - When counting the complement (invalid cases) is simpler than
      counting the required cases directly.
    - Useful in counting and combinatorial problems.

    Topics:
    - Strings
    - Brute Force
    - Counting
    - Complement Counting

    Overall Time Complexity: O(N²)
    Overall Space Complexity: O(1)
*/

class Solution {
public:

    // ------------------------------------------------------------
    // Counts substrings containing fewer than 3 distinct characters.
    // ------------------------------------------------------------
    int countInvalidSubstrings(string& text) {

        int textLength = text.size();
        int invalidSubstringCount = 0;

        // Consider every possible starting index.
        for (int startIndex = 0; startIndex < textLength; startIndex++) {

            int characterFrequency[3] = {0};
            int distinctCharacterCount = 0;

            // Extend the current substring.
            for (int endIndex = startIndex;
                 endIndex < textLength;
                 endIndex++) {

                // Count a newly encountered character.
                if (++characterFrequency[text[endIndex] - 'a'] == 1)
                    distinctCharacterCount++;

                // Still an invalid substring.
                if (distinctCharacterCount < 3)
                    invalidSubstringCount++;
                else
                    // Once all three characters are present,
                    // every longer substring from this start
                    // will also be valid.
                    break;
            }
        }

        return invalidSubstringCount;
    }

    int numberOfSubstrings(string text) {

        long long textLength = text.size();

        // Total number of possible substrings.
        long long totalSubstrings =
            textLength * (textLength + 1) / 2;

        return totalSubstrings - countInvalidSubstrings(text);
    }
};

/*
---------------------------------------------------------------
Revision Notes

• Count invalid substrings instead of valid ones.
• Invalid = substring containing fewer than 3 distinct characters.
• As soon as all three characters appear, stop extending the
  current substring because every longer substring will also be valid.
• Final Answer = Total Substrings − Invalid Substrings.

Common Mistakes

1. Forgetting to break once all three characters are present.
2. Using int for totalSubstrings when N can be large.
3. Forgetting that the string contains only 'a', 'b', and 'c'.

Overall Time Complexity : O(N²)
Overall Space Complexity: O(1)
*/
