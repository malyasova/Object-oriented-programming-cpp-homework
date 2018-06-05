#include <iostream>
#include <cmath>
using namespace std;
double distance(int a, int b){
  return(a-b);
};
double distance(double a, double b){
  return(a-b);
};
int main()
{
  cout << distance(1.0, 4.5) << " " << distance(4,3) << endl;
  return 0;
}
