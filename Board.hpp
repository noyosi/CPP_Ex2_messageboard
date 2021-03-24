
#include "Direction.hpp"
#include <string>

using namespace std;

namespace ariel {

    class Board {

    public:
    Board(){}
    void post(unsigned int row, unsigned int col, Direction d, const string &s);
    static std::string read(unsigned int row, unsigned int col, Direction d, unsigned int len);
    void show();
    };
    
}