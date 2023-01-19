#include <iostream>
#include <queue>
#include <forward_list>

enum class Status
{
    FREE,
    TAKEN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    START
};


struct Coord
{
    int row;
    int col;
};

const int   WIDTH   = 10;
const int   HEIGHT  = 6;

void printMap( const Status map[][ WIDTH ] )
{
    for ( int i = 0; i < WIDTH + 2; i++ )
        std::cout << "#";
    std::cout << "\n";

    for ( int i = 0; i < HEIGHT; i++ )
    {
        std::cout << "#";
        for ( int j = 0; j < WIDTH; j++ )
        {
            switch ( map[ i ][ j ] )
            {
                case Status::START:
                    std::cout << "O";
                    break;
                case Status::FREE:
                    std::cout << " ";
                    break;
                case Status::TAKEN:
                    std::cout << "#";
                    break;
                case Status::UP:
                    std::cout << "^";
                    break;
                case Status::DOWN:
                    std::cout << "v";
                    break;
                case Status::LEFT:
                    std::cout << "<";
                    break;
                case Status::RIGHT:
                    std::cout << ">";
                    break;
                default:
                    break;
            }
        }
        std::cout << "#\n";
    }

    for ( int i = 0; i < WIDTH + 2; i++ )
        std::cout << "#";
    std::cout << "\n";
}


int main()
{
    Status  map[ HEIGHT ][ WIDTH ]  = { Status::FREE, };

    // Map setup
    {
        map[ 0 ][ 1 ] = Status::TAKEN;
        map[ 1 ][ 1 ] = Status::TAKEN;
        map[ 2 ][ 1 ] = Status::TAKEN;
        map[ 3 ][ 1 ] = Status::TAKEN;
        map[ 4 ][ 1 ] = Status::TAKEN;

        map[ 4 ][ 3 ] = Status::TAKEN;
        map[ 5 ][ 3 ] = Status::TAKEN;

        map[ 1 ][ 4 ] = Status::TAKEN;
        map[ 2 ][ 5 ] = Status::TAKEN;

        map[ 5 ][ 5 ] = Status::TAKEN;
        map[ 4 ][ 6 ] = Status::TAKEN;

        map[ 1 ][ 8 ] = Status::TAKEN;
        map[ 2 ][ 8 ] = Status::TAKEN;
        map[ 3 ][ 8 ] = Status::TAKEN;
        map[ 4 ][ 8 ] = Status::TAKEN;
        map[ 5 ][ 8 ] = Status::TAKEN;

        // map[ 0 ][ 8 ] = Status::TAKEN;
        // map[ HEIGHT - 1 ][ WIDTH - 1 ] = Status::TAKEN;
    }


    // BFS to find the shortest path
    std::queue<Coord> wave;
    map[ 0 ][ 0 ] = Status::START;
    wave.push( { 0, 0 } );

    while ( !wave.empty() )
    {
        Coord curr = wave.front();

        // Break if we've found a path to bottom-right corner
        if ( curr.col == WIDTH - 1 && curr.row == HEIGHT - 1 )
            break;

        wave.pop();

        // Going down
        if ( curr.row < HEIGHT && map[ curr.row + 1 ][ curr.col ] == Status::FREE )
        {
            wave.push( { curr.row + 1, curr.col } );
            map[ curr.row + 1 ][ curr.col ] = Status::UP;
        }

        // Going right
        if ( curr.col < WIDTH && map[ curr.row ][ curr.col + 1 ] == Status::FREE )
        {
            wave.push( { curr.row, curr.col + 1 } );
            map[ curr.row ][ curr.col + 1 ] = Status::LEFT;
        }

        // Going up
        if ( curr.row > 0 && map[ curr.row - 1 ][ curr.col ] == Status::FREE )
        {
            wave.push( { curr.row - 1, curr.col } );
            map[ curr.row - 1 ][ curr.col ] = Status::DOWN;
        }

        // Going left
        if ( curr.col > 0 && map[ curr.row ][ curr.col - 1 ] == Status::FREE )
        {
            wave.push( { curr.row, curr.col - 1 } );
            map[ curr.row ][ curr.col - 1 ] = Status::RIGHT;
        }
    }

    printMap( map );

    // Starting from the bottom-right corner
    if ( map[ HEIGHT - 1 ][ WIDTH - 1 ] != Status::FREE && map[ HEIGHT - 1 ][ WIDTH - 1 ] != Status::TAKEN )
    {
        std::forward_list<Coord> path;
        Coord curr = { HEIGHT - 1, WIDTH - 1 };

        // While the top-left corner hasn't been reached
        while ( !(curr.col == 0 && curr.row == 0) )
        {
            // Add the current coord in the beginning
            // and move to the previous coord
            path.push_front( curr );
            switch ( map[ curr.row ][ curr.col ] )
            {
                case Status::UP:
                    curr.row -= 1;
                    break;
                case Status::DOWN:
                    curr.row += 1;
                    break;
                case Status::LEFT:
                    curr.col -= 1;
                    break;
                case Status::RIGHT:
                    curr.col += 1;
                    break;
                default:
                    break;
            }
        }

        // Add the starting coord
        path.push_front( { 0, 0 } );

        // Print the path
        std::cout << "Jerry's path: ";
        for ( const Coord& currCoord : path )
            std::cout << "(" << currCoord.row << ", " << currCoord.col << ") ";
    }
    else
    {
        std::cout << "The bottom-right corner couldn't be reached!";
    }

    return 0;
}
