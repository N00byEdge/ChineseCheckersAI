#include <includes.h>

#include <game.h>

#ifdef DEBUGGING

int main ( ) {






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
    int players = 2;
    cout << "How many players? ";
    cin >> players;
    game fem;
    fem.startGame ( players );
    return 0;
}
