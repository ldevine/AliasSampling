#ifndef ALIAS_SAMPLE_HPP
#define ALIAS_SAMPLE_HPP

// Author: Lance De Vine
// Based on Python implementation: 
// https://hips.seas.harvard.edu/blog/2013/03/03/the-alias-method-efficient-sampling-with-many-discrete-outcomes/


#include <vector>
#include <list>
#include <random>


class AliasSample {

	int len;

	std::vector<int> J;
	std::vector<float> q;
	std::vector<float> probs;

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist;

public:

	AliasSample() {
		std::uniform_real_distribution<float>::param_type d(0.0, 1.0);
		dist.param(d);
	}

	// Initialize the distribution
	void init(std::vector<float> &weights) {
		probs = weights;

		len = probs.size();
		float sum = 0.0f;
		for (auto v : probs) sum += v;
		for (int i = 0; i < len; i++) probs[i] /= sum;

		setup();
	}

	int draw() {

		int idx, result;

		// Draw from the uniform mixture
		idx = (int)(floor(dist(gen) * q.size()));
		// Draw from the binary mixture 
		if (dist(gen) < q[idx]) result = idx;
		else result = J[idx];

		return result;
	}

private:

	void setup() {

		int small, large;

		J.resize(len, 0);
		q.resize(len, 0);

		std::list<int> smaller;
		std::list<int> larger;

		// Sort the data into the outcomes with probabilities
		// that are larger and smaller than 1 / len.
		for (int i = 0; i < len; i++) {
			q[i] = (float)len * probs[i];
			if (q[i] < 1.0f) smaller.push_back(i);
			else larger.push_back(i);
		}

		// Create binary mixtures
		while (smaller.size() > 0 && larger.size() > 0) {
			small = smaller.back(); smaller.pop_back();
			large = larger.back(); larger.pop_back();
			J[small] = large;
			q[large] = q[large] + q[small] - 1.0;
			if (q[large] < 1.0) smaller.push_back(large);
			else larger.push_back(large);
		}
	}

};


#endif


