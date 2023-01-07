#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include <math.h>
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
	int err = 0;
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);

#ifdef SW
	start_daemons(NULL, 0);	
#endif

	
	uint8_t i;
	uint8_t j;
	float temp=1;
	float x=1;
	float y=1;
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(i==j)
			x = (float)(1);
			else
			x = (float)(0);
			write_float32("input_data",x);
			
		}

	}
// fprintf(stderr, "Error: %f  expected = %f.\n",temp,x);
	for(j = 0; j < 16; j++)
		{
			x = (float)(j);
			write_float32("input_data",x);
			
		}
// fprintf(stderr, "Error: %f  expected = %f.\n",temp,x);
	for(i = 0; i < 16; i++)
	{
		
		temp = read_float32("output_data");
		
		fprintf(stderr, "Error: %f  expected = %f.\n",temp,y);
		
		
		// if (temp != 1 )
		// {
		// 	fprintf(stderr, "Error: %f  expected = %f.\n",temp,y);
		// 	err = 1;
		// }
	}


	fprintf(stderr,"All done: %s\n", err ? "Failure :-(" : "Success :-)");
	return(0);
}