#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>

int Height, Width;

class point{
  public:
    point(int x, int y) : x(x), y(y) {}
    point() {}
    int x, y;
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
};

int toA(int x){
  return x * 2 + 1;
}

int toA(double x){
  return x * 2.0 + 1.0;
}

bool exists(int x, int y){
  return (x < Height && x >= 0 && y < Width && y >= 0);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
      std::cout << "Enter the height: ";
      std::cin >> Height;
      std::cout << "Enter the width: ";
      std::cin >> Width;
  }else{
    Height = std::stoi(argv[1]);
    Width = std::stoi(argv[2]);
  }

  srand(time(NULL));

  std::vector<std::vector<char>> maze(toA(Height), std::vector<char>(toA(Width), '#'));
  std::vector<point> visitedStack;

  int x = rand() % Height;
  int y = rand() % Width;

  while(true){
    point pos(x,y);
    if(std::find(visitedStack.begin(), visitedStack.end(), pos) == visitedStack.end()) visitedStack.push_back(pos);
    maze[toA(x)][toA(y)] = ' ';

    std::vector<int> directions = {0, 1, 2, 3};
    int n = directions.size();
    for (int i = 0; i < n - 1; i++) {
        int j = i + (rand() % (n - i));
        int temp = directions[i];
        directions[i] = directions[j];
        directions[j] = temp;
    }

    bool pathFound = false;
    for(int i = 0; i < directions.size(); i++){
      switch (directions[i]){
        /*UP   */ case 0: if(exists(x-1, y)) {if(maze[toA(x-1)][toA(y)] == '#') {maze[toA(x-0.5)][toA(y)] = ' '; x = x - 1; y = y; pathFound = true; break;}} else {break;} 
        /*DOWN */ case 1: if(exists(x+1, y)) {if(maze[toA(x+1)][toA(y)] == '#') {maze[toA(x+0.5)][toA(y)] = ' '; x = x + 1; y = y; pathFound = true; break;}} else {break;} 
        /*LEFT */ case 2: if(exists(x, y-1)) {if(maze[toA(x)][toA(y-1)] == '#') {maze[toA(x)][toA(y-0.5)] = ' '; x = x; y = y - 1; pathFound = true; break;}} else {break;}
        /*RIGHT*/ case 3: if(exists(x, y+1)) {if(maze[toA(x)][toA(y+1)] == '#') {maze[toA(x)][toA(y+0.5)] = ' '; x = x; y = y + 1; pathFound = true; break;}} else {break;}
      }
      if(pathFound) break;
    }
    if(!pathFound){
      visitedStack.pop_back();
      if(visitedStack.empty()){
        break;
      }
      x = visitedStack.back().x;
      y = visitedStack.back().y;
    }
  }

  std::ofstream outputFile("outputMaze.txt");
  for (const auto& row : maze) {
      for (char ch : row) outputFile << ch;
      outputFile << '\n';
  }
  outputFile.close();

  std::cout << "Done :)";

  return 0;
}