#include <includes.h>

#include <game.h>
#include <neural_network.h>
#include <genetics.h>

#include <lib.h>
#include <fstream>

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

    genetics femg;
    femg.randomizeGenepool ( 10, 45, -0.5, 0.5 );
    femg.fitnessPolynomialAgents ( );
    femg.natrualSelection ( 200, "agent_polynomial" );
	string networkToTrain;

	getNetworkToTrain:;

    cout << "If you want to train a network, please enter the path to the network now: ";
    getline ( cin, networkToTrain );
    if ( networkToTrain.size ( ) ) {

		getDatasetFile:;

        cout << "Please enter the path to the database that you want to use: ";
		string databaseFilePath;
		getline ( cin, databaseFilePath );

		ifstream databaseFile;
		databaseFile.open ( databaseFilePath );
		database db;
		if ( databaseFile.is_open ( ) )
			databaseFile >> db;

		databaseFile.close ( );

		neural_network nw ( networkToTrain );

		cout << "What is the maximum accepted error? ";
		long double maxError;
		cin >> maxError;

		cout << "What learning rate should we use? ";
		long double phi;
		cin >> phi;

		cout << "How often do we print progress? ";
		long long reportTime;
		cin >> reportTime;

		cin.ignore ( );

        nw.filename = networkToTrain;
		nw.learnDatabase ( db, phi, maxError, reportTime );

		cout << "Backprop done. Where do you want to save the file? ";
		string outfile;
		getline ( cin, outfile );

		if ( outfile.size ( ) ) {

			ofstream outFileStream;
			outFileStream.open ( outfile );
			if ( outFileStream.is_open ( ) ) outFileStream << nw;
			else cout << "Could not write file.\n";

		} else {

			ofstream outFileStream;
			outFileStream.open ( networkToTrain );
			if ( outFileStream.is_open ( ) ) outFileStream << nw;
			else cout << "Could not write file.\n";

		}

		goto getNetworkToTrain;

    }
    int players = 2;
    cout << "How many players? ";
    cin >> players;
    game fem;
    fem.startGame ( players );
    return 0;
}
