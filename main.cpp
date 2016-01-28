#include <includes.h>

#include <game.h>
#include <neural_network.h>

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

	string networkToTrain;

	getNetworkToTrain:;

    cout << "If you want to train a network, please enter the path to the network now: ";
    getline ( cin, networkToTrain );
    if ( networkToTrain.size ( ) ) {

		getDatasetFile:;

        cout << "Please enter the path to the dataset that you want to use: ";
		string datasetFilePath;
		getline ( cin, datasetFilePath );

		ifstream datasetFile;
		datasetFile.open ( datasetFilePath );

		if ( !datasetFile.is_open ( ) ) {

			cout << "Could not load network.\n";
			goto getNetworkToTrain;

		}
		neural_network nw ( networkToTrain );

		if ( datasetFile.is_open ( ) ) {

			auto datasets = lib::getDatasets ( datasetFile );

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

			nw.learn ( datasets, maxError, phi, reportTime );

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

		} else {

			cout << "Could not open dataset file.\n";
			goto getDatasetFile;

		}

		datasetFile.close ( );

    }
    int players = 2;
    cout << "How many players? ";
    cin >> players;
    game fem;
    fem.startGame ( players );
    return 0;
}
