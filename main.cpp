#include <includes.h>

#include <game.h>

#ifdef DEBUGGING

void testStuff(){
    int players = 2;
    cout << "How many players? ";
    cin >> players;
    game fem;
    fem.startGame ( players );

    pair < int, int > temp;
    temp.first = 0;
    temp.second = 3;

    cout << "\tGame board: "
        << fem.getBoard ( )
        << endl;

    cout << "\tSample tile: "
        << fem.getBoard ( ) -> getTile ( temp )
        << endl;

    fem.getBoard ( ) -> printWithCoords ( );

    pair < int, int > coords = fem.getBoard ( ) -> getTile ( temp ) -> getCoordinates ( );

    cout << "\t["
        << coords.first
        << ", "
        << coords.second
        << "]"
        << endl;

    cout << "\tIs ["
        << temp.first
        << ", "
        << temp.second
        << "] a valid tile? "
        << fem.getBoard ( ) -> isValidTile ( fem.getBoard ( ) -> getTile ( temp ) )
        << endl;

    cout << "\tUp to the right relative to ["
        << temp.first
        << ", "
        << temp.second
        << "]: "
        << fem.getBoard ( ) -> getTileUpRight ( fem.getBoard ( ) -> getTile ( temp ) ) -> getContents ( )
        << endl;

    cout << "\tCoordinates up to the right relative to ["
        << temp.first
        << ", "
        << temp.second
        << "]: ["
        << fem.getBoard ( ) -> getTileUpRight ( fem.getBoard ( ) -> getTile ( temp ) ) -> getCoordinates ( ) .first
        << ", "
        << fem.getBoard ( ) -> getTileUpRight ( fem.getBoard ( ) -> getTile ( temp ) ) -> getCoordinates ( ) .second
        << "]\n";

    cout << "\tCan ["
        << temp.first
        << ", "
        << temp.second
        << "] walk in the upwards right direction? "
        << fem.getBoard ( ) -> canWalkUpRight ( fem.getBoard ( ) -> getTile ( temp ) )
        << endl;

    cout << "\tCan ["
        << temp.first
        << ", "
        << temp.second
        << "] jump in the upwards right direction? "
        << fem.getBoard ( ) -> canJumpUpRight ( fem.getBoard ( ) -> getTile ( temp ) )
        << endl;

    temp.first = 1;
    temp.second = 2;

    cout << "\tCan ["
        << temp.first
        << ", "
        << temp.second
        << "] jump in the upwards right direction? "
        << fem.getBoard ( ) -> canJumpUpRight ( fem.getBoard ( ) -> getTile ( temp ) )
        << endl;

    vector < bool > boolv;

    for ( int i = 0; i < 6; ++ i ) {
        boolv.push_back ( fem.getBoard ( )
                            -> canJump (
                                fem.getBoard ( ) -> getTile ( temp ),
                                i + 1 ));
    }

    cout << "\t["
        << temp.first
        << ", "
        << temp.second
        << "] can jump in the following directions: ";

    for ( int i = 0; i < boolv.size ( ); ++ i ) {
        if ( boolv [ i ] ) cout << i + 1 << " ";
    }

    cout << endl;
}

#endif

int main(){
    #ifdef INTERFACE
    sf::RenderWindow win(sf::VideoMode(200, 200), "Fem");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color(125, 103, 4, 255));
    while (win.isOpen()){
        sf::Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                win.close();
        }
        win.clear();
        win.draw(shape);
        win.display();
    }
    #endif
    #ifdef DEBUGGING
    testStuff();
    #else
    game g ( 2 );
    #endif
    return 0;
}
