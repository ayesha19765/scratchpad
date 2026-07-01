#include <iostream>
using namespace std;
/*
    Problem:
    Find a path from the top-left corner to the bottom-right corner
    such that the minimum distance from any thief along the path is
    as large as possible.

    Intuition:
    The solution consists of two independent graph algorithms.

    1. Multi-source BFS
       - Compute the minimum distance of every cell from the nearest thief.
       - This transforms the grid into a "safeness map".

    2. Modified Dijkstra (Maximum Bottleneck Path)
       - Among all possible paths, maximize the minimum safeness value
         encountered along the path.
       - Instead of minimizing path cost, we maximize the bottleneck value.

    When to use?
    - Multi-source BFS:
      Whenever the shortest distance from multiple sources needs to be
      computed simultaneously.

    - Modified Dijkstra:
      Whenever the objective is to maximize the minimum value (or minimize
      the maximum value) along a path instead of minimizing the total cost.

    Topics:
    - Graphs
    - Multi-source BFS
    - Dijkstra
    - Priority Queue

    Overall Time Complexity: O(N² log N)
    Overall Space Complexity: O(N²)
*/

class Solution {
public:

    // Four possible movement directions:
    // Up, Down, Left, Right
    int rowDirection[4] = {-1, 1, 0, 0};
    int columnDirection[4] = {0, 0, -1, 1};

    // ------------------------------------------------------------
    // Step 2: Find the safest possible path using a modified
    // Dijkstra's algorithm.
    //
    // Instead of minimizing distance, maximize the minimum
    // safeness factor encountered along the path.
    // ------------------------------------------------------------
    int findMaximumSafeness(vector<vector<int>>& minimumDistance) {

        int gridSize = minimumDistance.size();

        // Max Heap
        // {currentSafeness, row, column}
        priority_queue<tuple<int, int, int>> maxHeap;

        // best[row][col] stores the maximum safeness value with
        // which we've reached this cell.
        vector<vector<int>> bestSafeness(
            gridSize,
            vector<int>(gridSize, -1)
        );

        maxHeap.push({minimumDistance[0][0], 0, 0});
        bestSafeness[0][0] = minimumDistance[0][0];

        while (!maxHeap.empty()) {

            auto [currentSafeness, currentRow, currentColumn] = maxHeap.top();
            maxHeap.pop();

            // Destination reached.
            // Since the heap always processes the safest path first,
            // this is the optimal answer.
            if (currentRow == gridSize - 1 &&
                currentColumn == gridSize - 1)
                return currentSafeness;

            // Ignore outdated states.
            if (currentSafeness < bestSafeness[currentRow][currentColumn])
                continue;

            for (int direction = 0; direction < 4; direction++) {

                int nextRow = currentRow + rowDirection[direction];
                int nextColumn = currentColumn + columnDirection[direction];

                if (nextRow >= 0 &&
                    nextRow < gridSize &&
                    nextColumn >= 0 &&
                    nextColumn < gridSize) {

                    // The safeness of the current path is limited by
                    // its least safe cell (bottleneck).
                    int newSafeness =
                        min(currentSafeness,
                            minimumDistance[nextRow][nextColumn]);

                    // Found a safer way to reach this cell.
                    if (newSafeness >
                        bestSafeness[nextRow][nextColumn]) {

                        bestSafeness[nextRow][nextColumn] = newSafeness;

                        maxHeap.push({
                            newSafeness,
                            nextRow,
                            nextColumn
                        });
                    }
                }
            }
        }

        return 0;
    }

    // ------------------------------------------------------------
    // Step 1: Multi-source BFS
    //
    // Computes the minimum distance from every cell to its
    // nearest thief.
    // ------------------------------------------------------------
    void computeMinimumDistanceFromThieves(
        vector<vector<int>>& minimumDistance,
        vector<vector<int>>& grid) {

        int gridSize = grid.size();

        queue<pair<int, int>> bfsQueue;

        // Every thief acts as a starting source.
        for (int row = 0; row < gridSize; row++) {
            for (int column = 0; column < gridSize; column++) {

                if (grid[row][column] == 1) {
                    bfsQueue.push({row, column});
                    minimumDistance[row][column] = 0;
                }
            }
        }

        while (!bfsQueue.empty()) {

            auto [currentRow, currentColumn] = bfsQueue.front();
            bfsQueue.pop();

            for (int direction = 0; direction < 4; direction++) {

                int nextRow = currentRow + rowDirection[direction];
                int nextColumn =
                    currentColumn + columnDirection[direction];

                if (nextRow >= 0 &&
                    nextRow < gridSize &&
                    nextColumn >= 0 &&
                    nextColumn < gridSize &&
                    minimumDistance[nextRow][nextColumn] == INT_MAX) {

                    minimumDistance[nextRow][nextColumn] =
                        minimumDistance[currentRow][currentColumn] + 1;

                    bfsQueue.push({nextRow, nextColumn});
                }
            }
        }
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {

        int gridSize = grid.size();

        // minimumDistance[row][col] stores the distance from
        // the nearest thief.
        vector<vector<int>> minimumDistance(
            gridSize,
            vector<int>(gridSize, INT_MAX)
        );

        // Step 1: Build the safeness map.
        computeMinimumDistanceFromThieves(minimumDistance, grid);

        // Step 2: Find the safest path.
        return findMaximumSafeness(minimumDistance);
    }
};

/*
---------------------------------------------------------------
Revision Notes

• Multi-source BFS computes the nearest-source distance for every cell.
• Treat every thief as a BFS source simultaneously.
• Dijkstra is modified to maximize the minimum safeness instead of
  minimizing the total distance.
• The path's safeness is determined by its weakest (minimum) cell.
• The priority queue always expands the currently safest path first.

Common Mistakes

1. Running BFS separately for every thief (O(N⁴)).
2. Using a min-heap instead of a max-heap.
3. Using max() instead of min() while extending the path.
4. Forgetting to ignore outdated states in the priority queue.
5. Thinking this is a shortest path problem—it is actually a
   maximum bottleneck path problem.

Overall Time Complexity : O(N² log N)
Overall Space Complexity: O(N²)
*/

int main()
{
    
    return 0;
}
