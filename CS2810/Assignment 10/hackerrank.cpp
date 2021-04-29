/***********************************************
 *  
 *  FILE            :       Minesweeper.cpp -- submission to hackerrank contest CS2810-A10
 *
 *  VERSION         :       1.0
 *  AUTHOR          :       Vedant Ashish Saboo, CS19B074
 *  
 *  CREATED         :       26/4/2021 2034HRS
 *  LAST MODIFIED   :       27/4/2021 1157HRS by vedant
 *
 *  BUGS            :       NONE
 *
 *************************************************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

/**
 * class Minesweeper -- contains information about the game
 **/
class Minesweeper {
    vector<vector<int>> grid;           //playing grid of integers
    int N;                              //order of the grid (N*N)
    int M;                              //number of mines
    static const int MINE = -1;         //symbolises mines
    static const int UNREVEALED = -2;   //symobolises unrevealed cells
    static const int BLANK = 0;         //symobolises blank cells (no neighbours have mines)
    const string won = "Won";    //string to print when won
    const string lost = "Lost";  //string to print when lost
    int numRevealed;                    //current number of revealed cells
    public:
    Minesweeper() {
        resetGame();                    //reset the game at start
    }
    void resetGame() {
        N = -1;                         
        M = -1;
        numRevealed = 0;
        if(!grid.empty())
            grid.clear();
    }
    void getGameData() {
        cin >> N >> M;                  //get grid order and number of mines from stdin
        grid = vector<vector<int>> (N); 
        for(int i = 0; i < N; i++)
            grid[i] = vector<int> (N, UNREVEALED);
        
        getMineData();
    }
    void getMineData() {
        if(N == -1 || M == -1) {
            return;
        }
        int loc;
        for(int i = 0; i < M; i++) {
            cin >> loc;                 //get locations of mines from stdin
            
            //translate loc into grid indices
            int x = loc / N;
            int y = loc % N;
            
            //set up a mine
            grid[x][y] = MINE;
        }
    }
    void startGamePlay() {
        int x, y;
        int res;
        while(cin.eof()==0) {
            cin >> x >> y;              //get move coordinates from stdin
            res = playMove(x, y);       //play the move
            if (res == 0) {
                continue;
            } else if (res == 1) {
                cout << won << endl;
                return;
            } else if (res == -1) {
                cout << lost << endl;
                return;
            }
        }
        return;
    }
    int playMove(int x, int y) {
        //reveal the grid, check
        int content = grid[x][y];
        if(content == MINE) {           //lost
            return -1;
        }
        
        if(content != UNREVEALED) {     //futile move, nothing more revealed
            cout << numRevealed << endl;
            return 0;
        }
        
        numRevealed += reveal(x, y);    //reveal a non mine, (x,y)
        if(checkForWin()) {             //check for win
            return 1;
        }
        else {
            cout << numRevealed << endl;
            return 0;
        }
        
    }
    int reveal(int x, int y) {
        //count neighbouring mines
        int count = 0;
        int ret = 1;                    //number of cells revealed in this iteration
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                if(x+i >= N || y+j >= N || x+i < 0 || y+j < 0 || (i==0 && j==0))
                        continue;
                if(grid[x+i][y+j] == MINE)
                    count++;
            }
        }
        //update count of the cell
        grid[x][y] = count;
        if(count == BLANK) {            //if blank, reveal all neighbours if unrevealed
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    if(x+i >= N || y+j >= N || x+i < 0 || y+j < 0 || (i==0 && j==0))
                        continue;
                    if(grid[x+i][y+j] == UNREVEALED) {
                        ret += reveal(x+i, y+j);
                    }
                }
            }
        }
        return ret;
    }
    bool checkForWin() {
        if(numRevealed + M == N*N) {    //if number of revealed plus mines equaled total, won
            return true;
        } else {
            return false;               //game is still on
        }
    }
    
};
/**
 *  end of class
 **/


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    Minesweeper game;
    game.getGameData();
    game.startGamePlay();
    return 0;
}

/**
 * end of FILE
 **/
