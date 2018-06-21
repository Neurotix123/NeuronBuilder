#include "Neurologic.h"
#include <iostream>

int main()
{
	// build a single neuron
	using namespace::Neuro;
	RNG_simple rng;

	std::shared_ptr< Neuron<> > neuron_linear(new Neuron<>());
	std::shared_ptr< Neuron<McCulloughPitts> > neuron_MP(new Neuron<McCulloughPitts>());
	std::shared_ptr< Neuron<Logistic> > neuron_logistic(new Neuron<Logistic>());

	neuron_MP->initialise(rng.uni_01());
	auto f = neuron_MP->output();
	std::cout << f << std::endl;

	char c;
	std::cin >> c;
}