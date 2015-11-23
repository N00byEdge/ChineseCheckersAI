#ifndef NEURON
#define NEURON

#include <includes.h>

class neuron {

	public:

		neuron ( vector < neuron * > lastLayer, istream & is );
		neuron ( );

		long double value ( );

		/* Raw input functions, only used for first layer */

		void addRawInput (
			long double input
		);

		void addRawInputWithWeight (
			long double input,
			long double weight
		);

		vector <
			pair <
				long double,
				long double
			>
		>   getRawInputs ( ) const;

		void setRawInputs (
			vector <
				pair <
					long double,
					long double
				>
			>
		vpinputweight );

		/* Neuron input functions */

		void addNeuron (
			neuron *
		);

		void addNeuronWithWeight (
			neuron * neuron,
			long double weight
		);

		vector <
			pair <
				neuron *,
				long double
			>
		>	getInputNeurons ( ) const;

		void setInputNeurons (
			vector <
				pair <
					neuron *,
					long double
				>
			>
		);

		void setBias ( long double bias );

		long double getBias ( ) const;

	protected:

	private:

		vector < pair < neuron *, long double > > neuronInputs;

		vector < pair < long double, long double > > rawInputs;

		long double bias;

};

ostream & operator<< ( ostream &, const neuron & );

#endif // NEURON
