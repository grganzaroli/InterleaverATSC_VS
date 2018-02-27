// PDI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atsc_interleaver.h"
#include "stdio.h"
#include "io.h"

#pragma warning	(disable: 4996)

using namespace std;

//APENAS LDPC TIPO B

#define nbch 10800 //short frame
#define nldpc 16200 //short frame
#define qldpc 15 //short frame 10/15
#define rate 10 // 10/15

int _tmain(int argc, _TCHAR* argv[])
{
	atsc_interleaver I;

	unsigned char lamb_inter[nldpc];
	unsigned char U[nldpc];
	unsigned char lamb_deinter[nldpc];

	for(int i = 0; i < nldpc; i++)
	{
		lamb_inter[i] = i;
	}

	I.set(nbch, qldpc, rate);


	//PARITY INTERLEAVER -----------------------------------------------------------------------------------------------------

	I.parity_interleaver(lamb_inter, U);

	I.parity_deinterleaver(U, lamb_deinter);

	FILE *f = fopen("teste_PI.txt", "w");

	fprintf(f, "lamb_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", lamb_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "U = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", U[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "lamb_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", lamb_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	//GROUP-WISE INTERLEAVER INTERLEAVER -----------------------------------------------------------------------------------------------------



	printf("");

	return 0;
}

