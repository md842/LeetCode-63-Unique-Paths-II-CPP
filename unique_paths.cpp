/*
 * Leetcode 46: Permutations https://leetcode.com/problems/permutations/.

 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 
 * Constraints:
 *  1 <= nums.length <= 6
 *  -10 <= nums[i] <= 10
 *  All the integers of nums are unique.
 */

#include <iostream>
#include <vector>
#include <iomanip> // This is used by test(), not the main algorithm
#include <string> // This is used by test(), not the main algorithm

using std::vector;
using std::cout; // This is used by test(), not the main algorithm
using std::endl; // This is used by test(), not the main algorithm

int pathfinder(int** obstacleArr, int row, int col, int goalRow,
               int goalCol, int** cache){
  int out = 0;

  if (cache[row][col] != -1) // Check if in cache
    return cache[row][col]; // Return result from cache
  
  if(row == goalRow){ // At goal row
    if(col == goalCol) // Check if also at goal column
      return 1; // Goal reached, return 1
    else{
      if (obstacleArr[row][col + 1]) // Check if obstacle to the right
        return 0; // Stuck at an obstacle, this path is a dead end, return 0
      else{
        int result = pathfinder(obstacleArr, row, col + 1, // Move right
                                goalRow, goalCol, cache);
        cache[row][col + 1] = result; // Cache the result
        out += result;
      }
    }
  }
  else if(col == goalCol) // At goal column but not at goal row
    if (obstacleArr[row + 1][col]) // Check if obstacle below
      return 0; // Stuck at an obstacle, this path is a dead end, return 0
    else{
      int result = pathfinder(obstacleArr, row + 1, col, // Move down
                              goalRow, goalCol, cache);
      cache[row + 1][col] = result; // Cache the result
      out += result;
    }
  else{
    if (obstacleArr[row + 1][col]){ // If there is an obstacle below
      if (obstacleArr[row][col + 1]) // Check if there is also one to the right
        return 0; // Obstacles in both directions, dead end, return 0
    }
    else{
      int result = pathfinder(obstacleArr, row + 1, col, // Move down
                              goalRow, goalCol, cache);
      cache[row + 1][col] = result; // Cache the result
      out += result;
    }
    if (!obstacleArr[row][col + 1]){ // If no obstacle to the right
      int result = pathfinder(obstacleArr, row, col + 1, // Move right
                              goalRow, goalCol, cache);
      cache[row][col + 1] = result; // Cache the result
      out += result;
    }
  }
  
  return out;
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
  if (obstacleGrid[0][0]) // Can't start on an obstacle
    return 0;
  int goalRow = obstacleGrid.size() - 1;
  int goalCol = obstacleGrid[0].size() - 1;

  // Create cache and convert obstacleGrid to array for faster accesses
  int **cache = new int* [goalRow + 1]; // Allocate cache
  int **obstacleArr = new int* [goalRow + 1]; // Allocate obstacleArr
  for (int i = 0; i <= goalRow; i++){
    cache[i] = new int[goalCol + 1]; // Allocate rows of cache
    obstacleArr[i] = new int[goalCol + 1]; // Allocate rows of obstacleArr
    std::fill(cache[i], cache[i] + goalCol + 1, -1); // Initialize cache
    for (int j = 0; j <= goalCol; j++)
      obstacleArr[i][j] = obstacleGrid[i][j]; // Fill rows of obstacleArr
  }

  int output = pathfinder(obstacleArr,
                          0, // Starting X position
                          0, // Starting Y position
                          goalRow, // Goal X position
                          goalCol, // Goal Y position
                          cache);

  // Free dynamically allocated cache and obstacleArr
  for( int i = 0 ; i <= goalRow; i++){
      delete[] cache[i];
      delete[] obstacleArr[i];
  }
  delete[] cache;
  delete[] obstacleArr;

  return output;
}

void test(vector<vector<int>>& obstacleGrid, int exp){
  std::string testCase = "obstacleGrid: [";
  for (int i = 0; i < obstacleGrid.size(); i++){
    testCase += "[";
    for (int j = 0; j < obstacleGrid[i].size(); j++){
      testCase += std::to_string(obstacleGrid[i][j]);
      if (j < obstacleGrid[i].size() - 1)
        testCase += ", ";
    }
    testCase += "]";
    if (i < obstacleGrid.size() - 1)
        testCase += ", ";
  }

  std::string details = "Expected " + std::to_string(exp) + ", got ";

  int output = uniquePathsWithObstacles(obstacleGrid);
  details += std::to_string(output);

  std::string status = "";
  if (exp == output)
    status = "OK";
  else
    status = "Error";

  cout << std::setw(50) << testCase << std::setw(11) << status << std::setw(24) << details << endl;
}

int main(){
  // Test cases
  cout << endl << std::setw(50) << "Test case" << std::setw(11) << "Status";
  cout << std::setw(24) << "Details" << endl;
  cout << std::string(85, '-') << endl;

  vector<vector<int>> obstacleGrid;
  
  obstacleGrid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  test(obstacleGrid, 2);

  obstacleGrid = {{0, 1}, {0, 0}};
  test(obstacleGrid, 1);

  obstacleGrid = {{0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0},{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1},{0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0},{0,0,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,1},{0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0},{1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,1},{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0},{1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{0,1,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},{0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0},{0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0},{0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}};
  test(obstacleGrid, 718991952);

  return 0;
}

