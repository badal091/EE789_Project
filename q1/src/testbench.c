#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#ifndef SW
#include "SockPipes.h"
#include "vhdlCStubs.h"
#else
#include "aa_c_model.h"
#endif

void Exit(int sig)
{
	fprintf(stderr, "## Break! ##\n");
	exit(0);
}

	
int main(int argc, char* argv[])
{
	int _err_ = 0;
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);

#ifdef SW
	start_daemons(NULL, 0);	
#endif
	unsigned int seed = 45;
	srand(seed);
	uint8_t idx1, idx2;
	for(idx1 = 0; idx1 < 10; idx1++)
	{
			int a = 100000;
			float z;
			float x = ((float)rand()/(float)(RAND_MAX))*a;;
#ifdef SW
		rpmethod(x,&z);
#else
		z = rpmethod(x);
#endif
			if (abs(z - 1.0/x) > 0.000001)
			{
				fprintf(stderr, "Error: 1 / %.8f = %.8f, expected %.8f.\n", x,z,1.0/x);
				_err_ = 1;
			}		
	}
	
	fprintf(stderr,"All done: %s\n", _err_ ? "Failure :-(" : "Success :-)");
	return(0);
}
