// ----------------------------------------------------
//
// Test class for the accompanying AliasSample.h file.
//
//-----------------------------------------------------


#include <vector>
#include <list>
#include <random>
#include <iostream>
#include <unordered_map>

#include "AliasSample.h"


using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::unordered_map;



void test() {

	vector<float> weights;

	weights.push_back(0.02);
	weights.push_back(0.1);
	weights.push_back(0.55);
	weights.push_back(0.65);
	weights.push_back(0.75);

	int len = weights.size();

	AliasSample alias;

	alias.init(weights);
	
	vector<float> sampleCounts(len, 0);

	// Draw samples
	int r;
	int numSamples = 100000;
	for (int i = 0; i < numSamples; i++) {
		r = alias.draw();
		sampleCounts[r]++;
	}

	// Normalise
	for (int i = 0; i < len; i++) sampleCounts[i] /= numSamples;
		
	// Print drawn probabilities
	for (auto v : sampleCounts) {
		cout << endl << v;
	}
}


int main() {

	test();

    return 0;
}



