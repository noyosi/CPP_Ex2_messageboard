/**
 * AUTHORS: Noy Osi
 * 
 * Date: 2021-03
 */

#include "doctest.h"
#include "Board.hpp"
using namespace ariel;

#include <string>
using namespace std;


TEST_CASE("post & read - horizontal") {
    Board board;
    board.post(10, 1, Direction::Horizontal, "checking");

    CHECK(board.read(10, 1, Direction::Horizontal, 8) == "checking");
    CHECK(board.read(10, 1, Direction::Horizontal, 5) == "check");
    CHECK(board.read(10, 6, Direction::Horizontal, 3) == "ing");
    CHECK(board.read(10, 8, Direction::Horizontal, 1) == "g");
    CHECK(board.read(10, 8, Direction::Horizontal, 2) == "g_");
    CHECK(board.read(12, 12, Direction::Horizontal, 2) == "__");
    CHECK(board.read(15, 18, Direction::Horizontal, 2) == "__");
    CHECK(board.read(15, 15, Direction::Horizontal, 1) == "_");
}

TEST_CASE("post & read - vertical") {
    Board board;
    board.post(10, 1, Direction::Vertical, "checking");

    CHECK(board.read(10, 1, Direction::Vertical, 8) == "checking");
    CHECK(board.read(10, 1, Direction::Vertical, 5) == "check");
    CHECK(board.read(15, 1, Direction::Vertical, 3) == "ing");
    CHECK(board.read(17, 1, Direction::Vertical, 1) == "g");
    CHECK(board.read(17, 1, Direction::Vertical, 2) == "g_");
    CHECK(board.read(12, 12, Direction::Vertical, 2) == "__");
    CHECK(board.read(15, 18, Direction::Vertical, 2) == "__");
}

TEST_CASE("post & read - vertical & horizontal") {
    Board board;
    board.post(5, 5, Direction::Horizontal, "checking");
    board.post(4, 8, Direction::Vertical, "check");

    CHECK(board.read(5, 8, Direction::Vertical, 1) == "h");
    CHECK(board.read(5, 5, Direction::Horizontal, 8) == "chehking");
    CHECK(board.read(4, 8, Direction::Vertical, 5) == "check");
    CHECK(board.read(7, 8, Direction::Vertical, 3) == "ck_");
    CHECK(board.read(8, 8, Direction::Vertical, 2) == "k_");
    CHECK(board.read(5, 12, Direction::Horizontal, 1) == "g");
    CHECK(board.read(5, 12, Direction::Horizontal, 2) == "g_");
}

TEST_CASE("other tests"){
    Board board;
    
    //special strings
    board.post(4, 4, Direction::Horizontal, "h*y");
    board.post(5, 5, Direction::Horizontal, "*");
    board.post(6, 6, Direction::Horizontal, "?");
    board.post(7, 7, Direction::Horizontal, "-");
    board.post(8, 8, Direction::Horizontal, " ");

    CHECK(board.read(4, 4, Direction::Horizontal, 2) == "h*");
    CHECK(board.read(4, 5, Direction::Vertical, 2) == "**");
    CHECK(board.read(5, 5, Direction::Horizontal, 1) == "*");
    CHECK(board.read(5, 4, Direction::Horizontal, 3) == "_*_");
    CHECK(board.read(6, 6, Direction::Horizontal, 1) == "?");
    CHECK(board.read(7, 7, Direction::Horizontal, 1) == "-");
    CHECK(board.read(8, 8, Direction::Horizontal, 1) == " ");

    //big letters
    board.post(9, 9, Direction::Horizontal, "Noy");
    CHECK(board.read(9, 9, Direction::Horizontal, 3) != "noy");
}

TEST_CASE("mixed"){
    Board board;
    board.post(8, 1, Direction::Horizontal, "noy");
    board.post(6, 2, Direction::Vertical, "osi");
    board.post(7, 2, Direction::Horizontal, "cpp");
    board.post(6, 1, Direction::Vertical, "test");
    board.post(6, 3, Direction::Horizontal, "success");

    CHECK(board.read(6, 1, Direction::Horizontal, 9) == "tosuccess");
    CHECK(board.read(7, 1, Direction::Horizontal, 4) == "ecpp");
    CHECK(board.read(8, 1, Direction::Horizontal, 3) == "siy");
    CHECK(board.read(9, 1, Direction::Horizontal, 1) == "t");
    CHECK(board.read(6, 1, Direction::Vertical, 4) == "test");
    CHECK(board.read(6, 2, Direction::Vertical, 3) == "oci");
    CHECK(board.read(6, 3, Direction::Vertical, 4) == "spy");
    CHECK(board.read(9, 1, Direction::Vertical, 1) == "t");

    CHECK(board.read(9, 1, Direction::Horizontal, 2) == "t_");
    CHECK(board.read(9, 1, Direction::Vertical, 4) == "t___");
    CHECK(board.read(10, 10, Direction::Horizontal, 2) == "__");
    CHECK(board.read(9, 1, Direction::Vertical, 2) == "t_");
    CHECK(board.read(10, 10, Direction::Vertical, 2) == "__");
}

TEST_CASE("string with spaces") {
    Board board;
    board.post(5, 5, Direction::Horizontal, "checking spaces");
    board.post(6, 5, Direction::Vertical, "pp test");

    CHECK(board.read(5, 5, Direction::Horizontal, 15) == "checking spaces"); 
    CHECK(board.read(5, 5, Direction::Vertical, 8) == "cpp test");
    CHECK(board.read(5, 14, Direction::Horizontal, 6) == "spaces");  
    CHECK(board.read(9, 5, Direction::Vertical, 4) == "test");
}

TEST_CASE("tests"){
    Board board;

    //override
    board.post(1, 1, Direction::Horizontal, "noy");
    board.post(1, 1, Direction::Horizontal, "os");

    CHECK(board.read(1, 1, Direction::Horizontal, 3) == "osy");

    board.post(1, 3, Direction::Horizontal, "i");
    CHECK(board.read(1, 1, Direction::Horizontal, 3) == "osi");

    //ovrride with a longer string
    board.post(1, 1, Direction::Horizontal, "noya");
    CHECK(board.read(1, 1, Direction::Horizontal, 4) == "noya");

    board.post(5, 5, Direction::Horizontal, "noy");
    board.post(5, 5, Direction::Vertical, "roy");
    CHECK(board.read(5, 5, Direction::Vertical, 3) == "roy");
    CHECK(board.read(5, 5, Direction::Horizontal, 3) == "roy");
}