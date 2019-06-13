#include <iostream>
#include<cstring>
#include<vector>

using namespace std;

struct cell_colours {
    char up = ' ';
    char down = ' ';
    char left = ' ';
    char right = ' ';
    char front = ' ';
    char back = ' ';
};
//char colours
/*
 r - red
 g - green
 b - blue
 y - yellow
 w - white
 o - orange
 */
// 0: Down part
/*
 0 - down,back,left
 1 - down,back
 2 - down,back,right
 3 - down,left
 4 - down
 5 - down,right
 6 - down,front,left
 7 - down,front
 8 - down,front,right
 */
// 1: Middle part
/*
 0 9 - back,left
 1 10 - back
 2 11 - back,right
 3 12 - left
 4 13 - null
 5 14 - right
 6 15 - front,left
 7 16 - front
 8 17 - front,right
 */
// 2: Up part
/*
 0 18 - up,back,left
 1 19 - up,back
 2 20 - up,back,right
 3 21 - up,left
 4 22 - up
 5 23 - up,right
 6 24 - up,front,left
 7 25 - up,front
 8 26 - up,front,right
 */

bool cell_have_colour(cell_colours cell, char colour) {
    if (colour == ' ') {return true;}
    else if (cell.up == colour) {return true;}
    else if (cell.down == colour) {return true;}
    else if (cell.left == colour) {return true;}
    else if (cell.right == colour) {return true;}
    else if (cell.front == colour) {return true;}
    else {return (cell.back == colour);}
}

void R (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "R ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[0][8].front;
    cube[2][8].right = cube[0][8].right;
    cube[2][8].front = cube[0][8].down;
    tmp2 = cube[2][2];
    cube[2][2].up = tmp1.front;
    cube[2][2].right = tmp1.right;
    cube[2][2].back = tmp1.up;
    tmp1 = cube[0][2];
    cube[0][2].back = tmp2.up;
    cube[0][2].down = tmp2.back;
    cube[0][2].right = tmp2.right;

    cube[0][8].front = tmp1.down;
    cube[0][8].right = tmp1.right;
    cube[0][8].down = tmp1.back;

    tmp1 = cube[2][5];
    cube[2][5].up = cube[1][8].front;
    cube[2][5].right = cube[1][8].right;
    tmp2 = cube[1][2];
    cube[1][2].right = tmp1.right;
    cube[1][2].back = tmp1.up;
    tmp1 = cube[0][5];
    cube[0][5].down = tmp2.back;
    cube[0][5].right = tmp2.right;

    cube[1][8].front = tmp1.down;
    cube[1][8].right = tmp1.right;
}
void Rc (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "R' ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[2][2].back;
    cube[2][8].right = cube[2][2].right;
    cube[2][8].front = cube[2][2].up;
    tmp2 = cube[0][8];
    cube[0][8].down = tmp1.front;
    cube[0][8].right = tmp1.right;
    cube[0][8].front = tmp1.up;
    tmp1 = cube[0][2];
    cube[0][2].back = tmp2.down;
    cube[0][2].down = tmp2.front;
    cube[0][2].right = tmp2.right;

    cube[2][2].back = tmp1.down;
    cube[2][2].right = tmp1.right;
    cube[2][2].up = tmp1.back;

    tmp1 = cube[2][5];
    cube[2][5].up = cube[1][2].back;
    cube[2][5].right = cube[1][2].right;
    tmp2 = cube[1][8];
    cube[1][8].right = tmp1.right;
    cube[1][8].front = tmp1.up;
    tmp1 = cube[0][5];
    cube[0][5].down = tmp2.front;
    cube[0][5].right = tmp2.right;

    cube[1][2].back = tmp1.down;
    cube[1][2].right = tmp1.right;
}

void L (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "L ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][6];
    cube[2][6].up = cube[2][0].back;
    cube[2][6].left = cube[2][0].left;
    cube[2][6].front = cube[2][0].up;
    tmp2 = cube[0][6];
    cube[0][6].front = tmp1.up;
    cube[0][6].left = tmp1.left;
    cube[0][6].down = tmp1.front;
    tmp1 = cube[0][0];
    cube[0][0].back = tmp2.down;
    cube[0][0].down = tmp2.front;
    cube[0][0].left = tmp2.left;

    cube[2][0].back = tmp1.down;
    cube[2][0].left = tmp1.left;
    cube[2][0].up = tmp1.back;

    tmp1 = cube[1][6];
    cube[1][6].front = cube[2][3].up;
    cube[1][6].left = cube[2][3].left;
    tmp2 = cube[0][3];
    cube[0][3].left = tmp1.left;
    cube[0][3].down = tmp1.front;
    tmp1 = cube[0][9];
    cube[0][9].back = tmp2.down;
    cube[0][9].left = tmp2.left;

    cube[2][3].up = tmp1.back;
    cube[2][3].left = tmp1.left;
}
void Lc (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "L' ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][6];
    cube[2][6].up = cube[0][6].front;
    cube[2][6].left = cube[0][6].left;
    cube[2][6].front = cube[0][6].down;
    tmp2 = cube[2][0];
    cube[2][0].back = tmp1.up;
    cube[2][0].left = tmp1.left;
    cube[2][0].up = tmp1.front;
    tmp1 = cube[0][0];
    cube[0][0].back = tmp2.up;
    cube[0][0].down = tmp2.back;
    cube[0][0].left = tmp2.left;

    cube[0][6].front = tmp1.down;
    cube[0][6].left = tmp1.left;
    cube[0][6].down = tmp1.back;

    tmp1 = cube[1][6];
    cube[1][6].front = cube[0][3].down;
    cube[1][6].left = cube[0][3].left;
    tmp2 = cube[2][3];
    cube[2][3].left = tmp1.left;
    cube[2][3].up = tmp1.front;
    tmp1 = cube[0][9];
    cube[0][9].back = tmp2.up;
    cube[0][9].left = tmp2.left;

    cube[0][3].down = tmp1.back;
    cube[0][3].left = tmp1.left;
}

void U (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "U ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[2][2].up;
    cube[2][8].right = cube[2][2].back;
    cube[2][8].front = cube[2][2].right;
    tmp2 = cube[2][6];
    cube[2][6].up = tmp1.up;
    cube[2][6].left = tmp1.front;
    cube[2][6].front = tmp1.right;
    tmp1 = cube[2][0];
    cube[2][0].back = tmp2.left;
    cube[2][0].up = tmp2.up;
    cube[2][0].left = tmp2.front;

    cube[2][2].back = tmp1.left;
    cube[2][2].right = tmp1.back;
    cube[2][2].up = tmp1.up;

    tmp1 = cube[2][5];
    cube[2][5].up = cube[2][1].up;
    cube[2][5].right = cube[2][1].back;
    tmp2 = cube[2][7];
    cube[2][7].up = tmp1.up;
    cube[2][7].front = tmp1.right;
    tmp1 = cube[2][3];
    cube[2][3].up = tmp2.up;
    cube[2][3].left = tmp2.front;

    cube[2][1].back = tmp1.left;
    cube[2][1].up = tmp1.up;
}
void Uc (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "U' ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[2][6].up;
    cube[2][8].right = cube[2][6].front;
    cube[2][8].front = cube[2][6].left;
    tmp2 = cube[2][2];
    cube[2][2].up = tmp1.up;
    cube[2][2].right = tmp1.front;
    cube[2][2].back = tmp1.right;
    tmp1 = cube[2][0];
    cube[2][0].back = tmp2.right;
    cube[2][0].up = tmp2.up;
    cube[2][0].left = tmp2.back;

    cube[2][6].front = tmp1.left;
    cube[2][6].left = tmp1.back;
    cube[2][6].up = tmp1.up;

    tmp1 = cube[2][5];
    cube[2][5].up = cube[2][7].up;
    cube[2][5].right = cube[2][7].front;
    tmp2 = cube[2][1];
    cube[2][1].up = tmp1.up;
    cube[2][1].back = tmp1.right;
    tmp1 = cube[2][3];
    cube[2][3].up = tmp2.up;
    cube[2][3].left = tmp2.back;

    cube[2][7].front = tmp1.left;
    cube[2][7].up = tmp1.up;
}

void D (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "D ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[0][8];
    cube[0][8].down = cube[0][6].down;
    cube[0][8].right = cube[0][6].front;
    cube[0][8].front = cube[0][6].left;
    tmp2 = cube[0][2];
    cube[0][2].down = tmp1.down;
    cube[0][2].right = tmp1.front;
    cube[0][2].back = tmp1.right;
    tmp1 = cube[0][0];
    cube[0][0].back = tmp2.right;
    cube[0][0].down = tmp2.down;
    cube[0][0].left = tmp2.back;

    cube[0][6].front = tmp1.left;
    cube[0][6].left = tmp1.back;
    cube[0][6].down = tmp1.down;

    tmp1 = cube[0][5];
    cube[0][5].down = cube[0][7].down;
    cube[0][5].right = cube[0][7].front;
    tmp2 = cube[0][1];
    cube[0][1].down = tmp1.down;
    cube[0][1].back = tmp1.right;
    tmp1 = cube[0][3];
    cube[0][3].down = tmp2.down;
    cube[0][3].left = tmp2.back;

    cube[0][7].front = tmp1.left;
    cube[0][7].down = tmp1.down;
}
void Dc (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "D' ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[0][8];
    cube[0][8].down = cube[0][2].down ;
    cube[0][8].right = cube[0][2].back;
    cube[0][8].front = cube[0][2].right;
    tmp2 = cube[0][6];
    cube[0][6].down = tmp1.down;
    cube[0][6].left = tmp1.front;
    cube[0][6].front = tmp1.right;
    tmp1 = cube[0][0];
    cube[0][0].back = tmp2.left;
    cube[0][0].down = tmp2.down;
    cube[0][0].left = tmp2.front;

    cube[0][2].back = tmp1.left;
    cube[0][2].right = tmp1.back;
    cube[0][2].down = tmp1.down;

    tmp1 = cube[0][5];
    cube[0][5].down = cube[0][1].down;
    cube[0][5].right = cube[0][1].back;
    tmp2 = cube[0][7];
    cube[0][7].down = tmp1.down;
    cube[0][7].front = tmp1.right;
    tmp1 = cube[0][3];
    cube[0][3].down = tmp2.down;
    cube[0][3].left = tmp2.front;

    cube[0][1].back = tmp1.left;
    cube[0][1].down = tmp1.down;
}

void F (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "F ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[2][6].left;
    cube[2][8].right = cube[2][6].up;
    cube[2][8].front = cube[2][6].front;
    tmp2 = cube[0][8];
    cube[0][8].down = tmp1.right;
    cube[0][8].right = tmp1.up;
    cube[0][8].front = tmp1.front;
    tmp1 = cube[0][6];
    cube[0][6].front = tmp2.front;
    cube[0][6].down = tmp2.right;
    cube[0][6].left = tmp2.down;

    cube[2][6].front = tmp1.front;
    cube[2][6].left = tmp1.down;
    cube[2][6].up = tmp1.left;

    tmp1 = cube[2][7];
    cube[2][7].up = cube[1][6].left;
    cube[2][7].front = cube[1][6].front;
    tmp2 = cube[1][8];
    cube[1][8].right = tmp1.up;
    cube[1][8].front = tmp1.front;
    tmp1 = cube[0][7];
    cube[0][7].down = tmp2.right;
    cube[0][7].front = tmp2.front;

    cube[1][6].front = tmp1.front;
    cube[1][6].left = tmp1.down;
}
void Fc (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "F' ";}
    cell_colours tmp1, tmp2;
    tmp1 = cube[2][8];
    cube[2][8].up = cube[0][8].right;
    cube[2][8].right = cube[0][8].down;
    cube[2][8].front = cube[0][8].front;
    tmp2 = cube[2][6];
    cube[2][6].up = tmp1.right;
    cube[2][6].left = tmp1.up;
    cube[2][6].front = tmp1.front;
    tmp1 = cube[0][6];
    cube[0][6].front = tmp2.front;
    cube[0][6].down = tmp2.left;
    cube[0][6].left = tmp2.up;

    cube[0][8].front = tmp1.front;
    cube[0][8].right = tmp1.down;
    cube[0][8].down = tmp1.left;

    tmp1 = cube[2][7];
    cube[2][7].up = cube[1][8].right;
    cube[2][7].front = cube[1][8].front;
    tmp2 = cube[1][6];
    cube[1][6].left = tmp1.up;
    cube[1][6].front = tmp1.front;
    tmp1 = cube[0][7];
    cube[0][7].down = tmp2.left;
    cube[0][7].front = tmp2.front;

    cube[1][8].front = tmp1.front;
    cube[1][8].right = tmp1.down;
}

void M_right (vector<vector<cell_colours>>& cube) {
    cell_colours tmp1, tmp2;
    tmp1 = cube[1][8];
    cube[1][8].right = cube[1][2].back;
    cube[1][8].front = cube[1][2].right;
    tmp2 = cube[1][6];
    cube[1][6].left = tmp1.front;
    cube[1][6].front = tmp1.right;
    tmp1 = cube[1][0];
    cube[1][0].back = tmp2.left;
    cube[1][0].left = tmp2.front;

    cube[1][2].back = tmp1.left;
    cube[1][2].right = tmp1.back;

    tmp1 = cube[1][5];
    cube[1][5].right = cube[1][1].back;
    tmp2 = cube[1][7];
    cube[1][7].front = tmp1.right;
    tmp1 = cube[1][3];
    cube[1][3].left = tmp2.front;

    cube[1][1].back = tmp1.left;
}
void M_left (vector<vector<cell_colours>>& cube) {
    cell_colours tmp1, tmp2;
    tmp1 = cube[1][8];
    cube[1][8].right = cube[1][6].front;
    cube[1][8].front = cube[1][6].left;
    tmp2 = cube[1][2];
    cube[1][2].right = tmp1.front;
    cube[1][2].back = tmp1.right;
    tmp1 = cube[1][0];
    cube[1][0].back = tmp2.right;
    cube[1][0].left = tmp2.back;

    cube[1][6].front = tmp1.left;
    cube[1][6].left = tmp1.back;

    tmp1 = cube[1][5];
    cube[1][5].right = cube[1][7].front;
    tmp2 = cube[1][1];
    cube[1][1].back = tmp1.right;
    tmp1 = cube[1][3];
    cube[1][3].left = tmp2.back;

    cube[1][7].front = tmp1.left;
}

void rotate_right (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "\r\n rotate cube to see left face \r\n";}
    U(cube, moves, false);
    Dc(cube, moves, false);
    M_right(cube);
}

void rotate_left (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "\r\n rotate cube to see right face \r\n";}
    Uc(cube, moves, false);
    D(cube, moves, false);
    M_left(cube);
}

void rotate_twice (vector<vector<cell_colours>>& cube, string* moves, bool print = true) {
    if (print) {(*moves) += "\r\n rotate cube to see back face \r\n";}
    Uc(cube, moves, false);
    Uc(cube, moves, false);
    D(cube, moves, false);
    D(cube, moves, false);
    M_right(cube);
    M_right(cube);
}

pair<int, int> find_colors_pos (vector<vector<cell_colours>>& cube, char colour_one = ' ', char colour_two = ' ', char colour_three = ' ') {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (colour_two == ' ') {
                if (cell_have_colour(cube[i][j], colour_one)) {
                    if ((i == 0 || i == 2)&&j == 4) {return {i,j};}
                    else if ((i == 1)&&(j == 1||j == 3||j == 5||j == 7)) {return {i,j};}
                }
            } else if (colour_three == ' ') {
                if (cell_have_colour(cube[i][j], colour_one) && cell_have_colour(cube[i][j], colour_two)) {
                    if ((i == 0 || i == 2) && (j%2 == 1)) {return {i,j};}
                    else if ((i == 1) && (j != 4) && (j%2 == 0)) {return {i,j};}

                }
            } else if (cell_have_colour(cube[i][j], colour_one) && cell_have_colour(cube[i][j], colour_two) &&
                cell_have_colour(cube[i][j], colour_three)) {
                return {i,j};
            }
        }
    }
}

vector<char> colours_in_assembled (vector<vector<cell_colours>>& cube, pair<int,int> pos) {
    vector<char> result;
    if (pos.first == 0) {result.push_back(cube[0][4].down);}
    if (pos.first == 2) {result.push_back(cube[2][4].up);}
    if (pos.second == 0||pos.second == 3||pos.second == 6) {result.push_back(cube[1][3].left);}
    if (pos.second == 6||pos.second == 7||pos.second == 8) {result.push_back(cube[1][7].front);}
    if (pos.second == 2||pos.second == 5||pos.second == 8) {result.push_back(cube[1][5].right);}
    if (pos.second == 0||pos.second == 1||pos.second == 2) {result.push_back(cube[1][1].back);}
    return result;
}

void F2l_firstrow(vector<vector<cell_colours>>& cube, string* moves) {
    pair<int,int> to_pos, from_pos;
    to_pos = {0,8};
    for (int i = 0; i < 4; i++) {
        vector<char> colours = colours_in_assembled(cube,to_pos);
        from_pos = find_colors_pos(cube,colours[0], colours[1],colours[2]);
        if (from_pos == to_pos) {
            if (cube[from_pos.first][from_pos.second].down == cube[0][4].down) {
                rotate_left(cube,moves);
                break;
            }
        }
        if (to_pos.second != from_pos.second) {
            if (from_pos.first == 2) {
                if (from_pos.second == 6) {
                    Uc(cube, moves);
                } else if (from_pos.second == 2) {
                    U(cube, moves);
                } else if (from_pos.second == 0) {
                    U(cube, moves);
                    U(cube, moves);
                }
            } else {
                if (from_pos.second == 6) {
                    rotate_left(cube,moves);
                    R(cube, moves); U(cube, moves); Rc(cube, moves); Uc(cube, moves);
                    Uc(cube, moves);
                    rotate_right(cube,moves);
                } else if (from_pos.second == 2) {
                    rotate_right(cube,moves);
                    R(cube, moves); U(cube, moves); Rc(cube, moves); Uc(cube, moves);
                    U(cube, moves);
                    rotate_left(cube,moves);
                } else if (from_pos.second == 0) {
                    rotate_twice(cube,moves);
                    R(cube, moves); U(cube, moves); Rc(cube, moves); Uc(cube, moves);
                    U(cube, moves); U(cube, moves);
                    rotate_twice(cube,moves);
                }
            }
        }
        if (from_pos.second == 8 && from_pos.first == 0) {
            if (cube[from_pos.first][from_pos.second].down == cube[0][4].down) {
                rotate_left(cube,moves);
                break;
            } else {
                R(cube, moves); U(cube, moves); Rc(cube, moves); Uc(cube, moves);
            }
        }
        from_pos = find_colors_pos(cube,colours[0], colours[1],colours[2]);
            if (cube[from_pos.first][from_pos.second].up == cube[0][4].down) {
                for (int j = 0; j < 3; j++) {
                    R(cube, moves); U(cube, moves); Rc(cube, moves); Uc(cube, moves);
                }
            } else if (cube[from_pos.first][from_pos.second].right == cube[0][4].down) {
                Uc(cube, moves); Fc(cube, moves); U(cube, moves); F(cube, moves);
            } else if (cube[from_pos.first][from_pos.second].front == cube[0][4].down) {
                U(cube, moves); R(cube, moves); Uc(cube, moves); Rc(cube, moves);
            }
        rotate_left(cube, moves);
    }
}

void F2L_secondrow(vector<vector<cell_colours>>& cube, string* moves) {
    pair<int,int> to_pos, from_pos;
    to_pos = {1,8};
    for (int i = 0; i < 4; i++) {
        vector<char> colours = colours_in_assembled(cube,to_pos);
        from_pos = find_colors_pos(cube,colours[0], colours[1]);
        if (from_pos.first == 1) {
            if (from_pos.second == 0) {
                rotate_twice(cube, moves);
                U(cube,moves); R(cube,moves); Uc(cube,moves); Rc(cube,moves);
                Uc(cube,moves); Fc(cube,moves); U(cube,moves); F(cube,moves);
                rotate_twice(cube, moves);
            } else if (from_pos.second == 2) {
                rotate_right(cube, moves);
                U(cube,moves); R(cube,moves); Uc(cube,moves); Rc(cube,moves);
                Uc(cube,moves); Fc(cube,moves); U(cube,moves); F(cube,moves);
                Uc(cube,moves);
                rotate_left(cube, moves);
            } else if (from_pos.second == 6) {
                rotate_left(cube, moves);
                U(cube,moves); R(cube,moves); Uc(cube,moves); Rc(cube,moves);
                Uc(cube,moves); Fc(cube,moves); U(cube,moves); F(cube,moves);
                U(cube,moves);
                rotate_right(cube, moves);
            } else if (from_pos.second == 8) {
                if (cube[1][8].front == cube[1][7].front) {
                    rotate_left(cube,moves);
                    break;
                } else {
                    U(cube, moves); R(cube, moves); Uc(cube, moves); Rc(cube, moves);
                    Uc(cube, moves); Fc(cube, moves); U(cube, moves); F(cube, moves);
                    U(cube,moves); U(cube,moves);
                }
            }
        } else {
            if (from_pos.second == 1) {
                U(cube,moves); U(cube,moves);
            } else if (from_pos.second == 3) {
                Uc(cube,moves);
            } else if (from_pos.second == 5) {
                U(cube,moves);
            }
        }
        from_pos = find_colors_pos(cube,colours[0], colours[1]);
        if (cube[from_pos.first][from_pos.second].front == cube[1][7].front) {
            U(cube,moves);
            R(cube,moves);
            Uc(cube,moves);
            Rc(cube,moves);
            Uc(cube,moves);
            Fc(cube,moves);
            U(cube,moves);
            F(cube,moves);
        } else {
            rotate_right(cube,moves);
            Uc(cube,moves);
            Uc(cube,moves); Lc(cube,moves); U(cube,moves); L(cube,moves);
            U(cube,moves); F(cube,moves); Uc(cube,moves); Fc(cube,moves);
            rotate_left(cube,moves);
        }
        rotate_left(cube, moves);
    }
}

bool cube_is_ready(vector<vector<cell_colours>>& cube) {
    if (cube[2][0].up == cube[2][4].up && cube[2][1].up == cube[2][4].up
    && cube[2][2].up == cube[2][4].up && cube[2][3].up == cube[2][4].up
    && cube[2][5].up == cube[2][4].up && cube[2][6].up == cube[2][4].up
    && cube[2][7].up == cube[2][4].up && cube[2][8].up == cube[2][4].up) {
        if (cube[0][0].down == cube[0][4].down && cube[0][1].down == cube[0][4].down
        && cube[0][2].down == cube[0][4].down && cube[0][3].down == cube[0][4].down
        && cube[0][5].down == cube[0][4].down && cube[0][6].down == cube[0][4].down
        && cube[0][7].down == cube[0][4].down && cube[0][8].down == cube[0][4].down){
            if (cube[2][2].right == cube[1][5].right && cube[2][5].right == cube[1][5].right
            && cube[2][8].right == cube[1][5].right && cube[0][2].right == cube[1][5].right
            && cube[0][5].right == cube[1][5].right && cube[0][8].right == cube[1][5].right
            && cube[1][2].right == cube[1][5].right && cube[1][8].right == cube[1][5].right){
                if (cube[0][0].left == cube[1][3].left && cube[1][0].left == cube[1][3].left
                && cube[2][0].left == cube[1][3].left && cube[0][3].left == cube[1][3].left
                && cube[1][3].left == cube[2][3].left && cube[1][3].left == cube[0][6].left
                && cube[1][3].left == cube[1][6].left && cube[1][3].left == cube[2][6].left) {
                    if (cube[0][0].back  == cube[1][1].back && cube[1][0].back  == cube[1][1].back
                    &&  cube[2][0].back  == cube[1][1].back &&  cube[0][1].back  == cube[1][1].back
                    &&  cube[1][1].back == cube[2][1].back  && cube[0][3].back  == cube[1][1].back
                    &&  cube[1][3].back  == cube[1][1].back &&  cube[2][3].back  == cube[1][1].back){
                        if (cube[0][6].front == cube[1][7].front && cube[1][6].front == cube[1][7].front
                        && cube[2][6].front == cube[1][7].front && cube[0][7].front == cube[1][7].front
                        && cube[1][7].front == cube[2][7].front && cube[0][8].front == cube[1][7].front
                        && cube[1][8].front == cube[1][7].front && cube[2][8].front == cube[1][7].front){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool up_cross(vector<vector<cell_colours>>& cube) {
    return (cube[2][1].up  == cube[2][4].up && cube[2][3].up == cube[2][4].up && cube[2][5].up == cube[2][4].up
            &&cube[2][7].up == cube[2][4].up);
}

void OLL(vector<vector<cell_colours>>& cube, string* moves) {
    if (up_cross(cube)) {return;}
    if ((cube[2][1].up != cube[2][4].up && cube[2][3].up != cube[2][4].up && cube[2][5].up != cube[2][4].up)
        ||(cube[2][1].up != cube[2][4].up && cube[2][3].up != cube[2][4].up && cube[2][7].up != cube[2][4].up)
        ||(cube[2][1].up != cube[2][4].up && cube[2][7].up != cube[2][4].up && cube[2][5].up != cube[2][4].up)
        ||(cube[2][7].up != cube[2][4].up && cube[2][3].up != cube[2][4].up && cube[2][5].up != cube[2][4].up) ) {
        F(cube,moves); R(cube,moves); U(cube,moves); Rc(cube, moves); Uc(cube,moves); Fc(cube,moves);
    }
    bool corner = false;

    if (cube[2][1].up == cube[2][4].up && cube[2][4].up == cube[2][5].up
        && cube[2][3].up != cube[2][4].up && cube[2][7].up != cube[2][4].up) {
        Uc(cube,moves);
        corner = true;
    } else if (cube[2][7].up == cube[2][4].up && cube[2][4].up == cube[2][5].up
            && cube[2][3].up != cube[2][4].up && cube[2][1].up != cube[2][4].up) {
        U(cube,moves); U(cube,moves);
        corner = true;
    } else if (cube[2][7].up == cube[2][4].up && cube[2][4].up == cube[2][3].up
             && cube[2][1].up != cube[2][4].up && cube[2][5].up != cube[2][4].up) {
        U(cube,moves);
        corner = true;
    } else if (cube[2][1].up == cube[2][4].up && cube[2][4].up == cube[2][3].up
               && cube[2][7].up != cube[2][4].up && cube[2][5].up != cube[2][4].up) {
        corner = true;
    }
    if (corner) {
        F(cube,moves); R(cube,moves); U(cube,moves); Rc(cube, moves); Uc(cube,moves); Fc(cube,moves);
    }
    if (cube[2][1].up == cube[2][4].up && cube[2][4].up == cube[2][7].up
        && cube[2][3].up != cube[2][4].up && cube[2][5].up != cube[2][4].up) {
        U(cube,moves);
    }
    while (!up_cross(cube)) {
        F(cube, moves); R(cube, moves); U(cube, moves);
        Rc(cube, moves); Uc(cube, moves); Fc(cube, moves);
    }
}

void PLL_part1(vector<vector<cell_colours>>& cube, string* moves) {
    bool found_right_pos = false;
    while (!found_right_pos) {
        for (int i = 0; i < 4; i++) {
            if ((cube[2][1].back == cube[1][1].back && cube[2][3].left != cube[1][3].left
                && cube[2][5].right != cube[1][5].right && cube[2][7].front != cube[1][7].front)
                ||(cube[2][1].back != cube[1][1].back && cube[2][3].left == cube[1][3].left
                && cube[2][5].right != cube[1][5].right && cube[2][7].front != cube[1][7].front)
                ||(cube[2][1].back != cube[1][1].back && cube[2][3].left != cube[1][3].left
                && cube[2][5].right == cube[1][5].right && cube[2][7].front != cube[1][7].front)
                ||(cube[2][1].back != cube[1][1].back && cube[2][3].left != cube[1][3].left
                && cube[2][5].right != cube[1][5].right && cube[2][7].front == cube[1][7].front)) {
                if (cube[2][1].back != cube[1][1].back && cube[2][3].left == cube[1][3].left
                && cube[2][5].right != cube[1][5].right && cube[2][7].front != cube[1][7].front) {
                    rotate_right(cube,moves);
                }
                if (cube[2][1].back != cube[1][1].back && cube[2][3].left != cube[1][3].left
                    && cube[2][5].right == cube[1][5].right && cube[2][7].front != cube[1][7].front) {
                    rotate_left(cube,moves);
                }
                if (cube[2][1].back != cube[1][1].back && cube[2][3].left != cube[1][3].left
                    && cube[2][5].right != cube[1][5].right && cube[2][7].front == cube[1][7].front) {
                    rotate_twice(cube,moves);
                }
                found_right_pos = true;
                break;
            }
            U(cube, moves);
        }
        if (!found_right_pos) {
            if ((cube[2][1].back == cube[1][1].back && cube[2][7].front == cube[1][7].front)
             ||(cube[2][3].left == cube[1][3].left && cube[2][5].right == cube[1][5].right)) {
                R(cube,moves); Uc(cube,moves); R(cube,moves); U(cube,moves);
                R(cube,moves); U(cube,moves); R(cube,moves); Uc(cube,moves);
                Rc(cube,moves); Uc(cube,moves); R(cube,moves); R(cube,moves);
            } else {
                U(cube,moves);
                R(cube,moves); Uc(cube,moves); R(cube,moves); U(cube,moves);
                R(cube,moves); U(cube,moves); R(cube,moves); Uc(cube,moves);
                Rc(cube,moves); Uc(cube,moves); R(cube,moves); R(cube,moves);
            }
        }
    }

    if (cube[2][7].front == cube[1][3].left) {
        Lc(cube,moves); U(cube,moves); Lc(cube,moves); Uc(cube,moves);
        Lc(cube,moves); Uc(cube,moves); Lc(cube,moves); U(cube,moves);
        L(cube,moves); U(cube,moves); L(cube,moves); L(cube,moves);
    }
    if (cube[2][7].front == cube[1][5].right) {
        R(cube,moves); Uc(cube,moves); R(cube,moves); U(cube,moves);
        R(cube,moves); U(cube,moves); R(cube,moves); Uc(cube,moves);
        Rc(cube,moves); Uc(cube,moves); R(cube,moves); R(cube,moves);
    }
}

void PLL_part2(vector<vector<cell_colours>>& cube, string* moves) {
    vector<char> colours;
    bool all_wrong = true;
    while (all_wrong) {
        for (int i = 0; i < 4; i++) {
            colours = colours_in_assembled(cube, {2, 0});
            pair<int, int> where_cell = find_colors_pos(cube, colours[0], colours[1], colours[2]);
            if (where_cell.first == 2 && where_cell.second == 0) {
                all_wrong = false;
                break;
            }
            rotate_left(cube, moves, false);
        }
        if (all_wrong) {
            Rc(cube,moves); Fc(cube,moves); Lc(cube,moves); F(cube,moves);
            R(cube,moves); Fc(cube,moves); L(cube,moves); F(cube,moves);
        }
    }
    colours = colours_in_assembled(cube,{2,2});
    if (find_colors_pos(cube, colours[0], colours[1], colours[2]).second == 6) {
        Rc(cube,moves); Fc(cube,moves); Lc(cube,moves); F(cube,moves);
        R(cube,moves); Fc(cube,moves); L(cube,moves); F(cube,moves);
    } else {
        Fc(cube,moves); Lc(cube,moves); F(cube,moves); Rc(cube,moves);
        Fc(cube,moves); L(cube,moves); F(cube,moves); R(cube,moves);
    }

        colours = colours_in_assembled(cube,{2,8});
        if (find_colors_pos(cube, colours[0], colours[1],colours[2]).second == 8) {
            while (cube[2][8].up == cube[2][4].up && !cube_is_ready(cube)) {rotate_left(cube,moves);}
            int cube_ready = 0;
            while (cube[2][8].up != cube[2][4].up) {
                if (cube_ready == 4) {break;}
                while (cube[2][8].up != cube[2][4].up) {
                    Rc(cube, moves); Dc(cube, moves); R(cube, moves); D(cube, moves);
                    Rc(cube, moves); Dc(cube, moves); R(cube, moves); D(cube, moves);
                }
                while (!cube_is_ready(cube) && cube[2][8].up == cube[2][4].up) {
                    U(cube,moves);
                    cube_ready++;
                    if (cube_ready == 4) {break;}
                }
            }
        }
}

int main() {
    vector<vector<cell_colours>> cube;
    string moves;
    cube.resize(3);
    cube[0].resize(9);
    cube[1].resize(9);
    cube[2].resize(9);

        cout << "Enter your cube positions" << endl;
        cout << "Down face:" << endl;
        for (int i = 0; i < 9; i++) {
            cout << i << ' ' << endl;
            char colour;
            cin >> colour;
            cube[0][i].down = colour;
        }
        cout << "Up face:" << endl;
        for (int i = 0; i < 9; i++) {
            cout << i << ' ' << endl;
            char colour;
            cin >> colour;
            cube[2][i].up = colour;
        }
        cout << "Left face:" << endl;
        for (int i = 0; i < 3; i++) {
            int k = 0;
            cout << i << ' ' << k << ' ' << endl;
            char colour;
            cin >> colour;
            cube[i][k].left = colour;
            k = 3;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].left = colour;
            k = 6;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].left = colour;
        }
        cout << "Back face:" << endl;
        for (int i = 0; i < 3; i++) {
            int k = 0;
            cout << i << ' ' << k << ' ' << endl;
            char colour;
            cin >> colour;
            cube[i][k].back = colour;
            k = 1;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].back = colour;
            k = 2;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].back = colour;
        }
        cout << "Right face:" << endl;
        for (int i = 0; i < 3; i++) {
            int k = 2;
            cout << i << ' ' << k << ' ' << endl;
            char colour;
            cin >> colour;
            cube[i][k].right = colour;
            k = 5;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].right = colour;
            k = 8;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].right = colour;
        }
        cout << "Front face:" << endl;
        for (int i = 0; i < 3; i++) {
            int k = 6;
            cout << i << ' ' << k << ' ' << endl;
            char colour;
            cin >> colour;
            cube[i][k].front = colour;
            k = 7;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].front = colour;
            k = 8;
            cout << i << ' ' << k << ' ' << endl;
            cin >> colour;
            cube[i][k].front = colour;
        }

    if (!cube_is_ready(cube)) {F2l_firstrow(cube,&moves);}
    cout<<"For first row: "<<moves;
    moves="";
    if (!cube_is_ready(cube)) {F2L_secondrow(cube,&moves);}
    cout<<"For second row: "<<moves;
    moves="";
    if (!cube_is_ready(cube)) {OLL(cube,&moves);}
    cout<<"For OLL: "<<moves;
    moves="";
    if (!cube_is_ready(cube)) {PLL_part1(cube,&moves);}
    cout<<"For PLL cross: "<<moves;
    moves="";
    if (!cube_is_ready(cube)) {PLL_part2(cube,&moves);}
    cout<<"For PLL corners: "<<moves;
    moves="";

    return 0;
}