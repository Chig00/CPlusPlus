#include <iostream>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;

class Decayer {
  public:
    Decayer(int size) {
      this->size = size;
    }

    int check_size() {
      return size;
    }

    void new_day(int day, double chance) {
      for (int i=0; i<size; i++) {
        if (chance >= (double) rand() / RAND_MAX) {
          decay(day);
        }
      }
    }

  private:
    int size;

    void decay(int day) {
      size--;
      cout << "Decayer decayed on day " << day << " to size " << this->size << "!" << endl;
    }
};

int main() {
  srand(time(NULL));
  int size;
  double chance;
  int day = 0;

  cout << "What is the size of the decayer? ";
  cin >> size;
  cout << "What is the chance of decay on each day per part? ";
  cin >> chance;

  Decayer decayer (size);

  while (decayer.check_size()) {
    day++;
    decayer.new_day(day, chance);
  }

  cout << "Decayer has now decayed from " << size << " to 0 in " << day << " days." << endl;

  return 0;
}
