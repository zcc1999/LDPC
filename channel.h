#ifndef CHANNEL_H
#define CHANNEL_H
#include <random>
#include <vector>
using std::vector;

class CHANNEL
{
public:
	CHANNEL(void);
	~CHANNEL();
	void addAWGN(vector <float>tran_signal);
	vector <float>reSignal;
	double sigma = 1;
};

#endif

