// PDI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atsc_interleaver.h"
#include "stdio.h"
#include "io.h"

#pragma warning	(disable: 4996)

using namespace std;

#define nbch 10800 //short frame
#define nldpc 16200 //short frame
#define qldpc 15 //short frame 10/15
#define rate 10 // 10/15
#define mod 64 //64-QAM

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f;

	atsc_interleaver I;
	
	//Parity
	unsigned char lamb_inter[nldpc];
	unsigned char U[nldpc];
	unsigned char lamb_deinter[nldpc];

	//Group
	unsigned char Y_inter[nldpc];
	unsigned char V[nldpc];
	unsigned char Y_deinter[nldpc];

	//Block Tipo A
	unsigned char BTA_inter[nldpc];
	unsigned char X[nldpc];
	unsigned char BTA_deinter[nldpc];

	//Block Tipo B
	unsigned char BTB_inter[nldpc];
	unsigned char Z[nldpc];
	unsigned char BTB_deinter[nldpc];

	for(int i = 0; i < nldpc; i++)
	{
		lamb_inter[i] = i;
		Y_inter[i] = i;
		BTA_inter[i] = i;
		BTB_inter[i] = i;
	}

	I.set(nbch, qldpc, rate, mod);

	int tab_short_r10_mod64[45] = {14, 22, 18, 11, 28, 26, 2, 38, 10, 0, 5, 12, 24, 17, 29, 16, 39, 13, 23, 8, 25, 43, 34, 33, 27, 15, 7, 1, 9, 35, 40, 32, 30, 20, 36, 31, 21, 41, 44, 3, 42, 6, 19, 37, 4}; //tabela B.2.3 p/ short frame, 10/15, 64-QAM


	//PARITY INTERLEAVER -----------------------------------------------------------------------------------------------------

	I.parity_interleaver(lamb_inter, U);

	I.parity_deinterleaver(U, lamb_deinter);

	f = fopen("teste_PI.txt", "w");

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

	//GROUP-WISE INTERLEAVER -----------------------------------------------------------------------------------------------------

	I.group_interleaver(Y_inter, V, tab_short_r10_mod64);

	I.group_deinterleaver(V, Y_deinter, tab_short_r10_mod64);

	f = fopen("teste_GI.txt", "w");

	fprintf(f, "Y_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", Y_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "V = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", V[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "Y_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", Y_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	//BLOCK INTERLEAVER TIPO A -----------------------------------------------------------------------------------------------------

	I.block_interleaver(BTA_inter, X, 0);

	I.block_deinterleaver(X, BTA_deinter, 0);

	f = fopen("teste_BI_Tipo_A.txt", "w");

	fprintf(f, "BTA_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTA_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "X = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", X[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "BTA_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTA_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	//BLOCK INTERLEAVER TIPO B -----------------------------------------------------------------------------------------------------

	I.block_interleaver(BTB_inter, Z, 1);

	I.block_deinterleaver(Z, BTB_deinter, 1);

	f = fopen("teste_BI_Tipo_B.txt", "w");

	fprintf(f, "BTB_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTB_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "Z = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", Z[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "BTB_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTB_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);


	printf("");

	return 0;
}

