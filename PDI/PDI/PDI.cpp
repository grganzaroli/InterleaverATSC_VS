// PDI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atsc_interleaver.h"
#include "stdio.h"
#include "io.h"

#pragma warning	(disable: 4996)

using namespace std;

#define nldpc 16200 //short frame
#define rate 10 // 10/15
#define mod 64 //64-QAM

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f;

	atsc_interleaver I;
	
	//Parity
	unsigned char lamb_inter[nldpc];
	unsigned char U_inter[nldpc];
	float U_deinter[nldpc];
	float lamb_deinter[nldpc];

	//Group
	unsigned char Y_inter[nldpc];
	unsigned char V_inter[nldpc];
	float V_deinter[nldpc];
	float Y_deinter[nldpc];

	//Block Tipo A
	unsigned char BTA_inter[nldpc];
	unsigned char X_inter[nldpc];
	float X_deinter[nldpc];
	float BTA_deinter[nldpc];

	//Block Tipo B
	unsigned char BTB_inter[nldpc];
	unsigned char Z_inter[nldpc];
	float Z_deinter[nldpc];
	float BTB_deinter[nldpc];

	for(int i = 0; i < nldpc; i++)
	{
		lamb_inter[i] = i;
		Y_inter[i] = i;
		BTA_inter[i] = i;
		BTB_inter[i] = i;
	}

	I.set(nldpc, rate, mod);

	int tab_short_r10_mod64[45] = {14, 22, 18, 11, 28, 26, 2, 38, 10, 0, 5, 12, 24, 17, 29, 16, 39, 13, 23, 8, 25, 43, 34, 33, 27, 15, 7, 1, 9, 35, 40, 32, 30, 20, 36, 31, 21, 41, 44, 3, 42, 6, 19, 37, 4}; //tabela B.2.3 p/ short frame, 10/15, 64-QAM


	//PARITY INTERLEAVER -----------------------------------------------------------------------------------------------------

	I.parity_inter(lamb_inter, U_inter);

	for(int i = 0; i < nldpc; i++)
	{
		U_deinter[i] = U_inter[i];
	}

	I.parity_deinter(U_deinter, lamb_deinter);

	f = fopen("teste_PI.txt", "w");

	fprintf(f, "lamb_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", lamb_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "U_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", U_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "lamb_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%.0lf ", lamb_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	printf("");

	//GROUP-WISE INTERLEAVER -----------------------------------------------------------------------------------------------------

	I.group_inter(Y_inter, V_inter);

	for(int i = 0; i < nldpc; i++)
	{
		V_deinter[i] = V_inter[i];
	}

	I.group_deinter(V_deinter, Y_deinter);

	f = fopen("teste_GI.txt", "w");

	fprintf(f, "Y_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", Y_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "V_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", V_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "Y_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%.0lf ", Y_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	printf("");

	//BLOCK INTERLEAVER TIPO A -----------------------------------------------------------------------------------------------------

	I.block_inter(BTA_inter, X_inter);

	for(int i = 0; i < nldpc; i++)
	{
		X_deinter[i] = X_inter[i];
	}

	I.block_deinter(X_deinter, BTA_deinter);

	f = fopen("teste_BI_Tipo_A.txt", "w");

	fprintf(f, "BTA_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTA_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "X_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", X_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "BTA_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%.0lf ", BTA_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);

	printf("");

	//BLOCK INTERLEAVER TIPO B -----------------------------------------------------------------------------------------------------

	I.block_inter(BTB_inter, Z_inter);

	for(int i = 0; i < nldpc; i++)
	{
		Z_deinter[i] = Z_inter[i];
	}

	I.block_deinter(Z_deinter, BTB_deinter);

	f = fopen("teste_BI_Tipo_B.txt", "w");

	fprintf(f, "BTB_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", BTB_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "Z_inter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%i ", Z_inter[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "BTB_deinter = ");
	for(int i = 0; i < nldpc; i++)
	{
		fprintf(f, "%.0lf ", BTB_deinter[i]);
	}
	fprintf(f, "\n");
	fclose(f);


	printf("");

	return 0;
}

