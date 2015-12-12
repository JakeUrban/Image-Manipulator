#include <PNMreaderCPP.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;

PNMreader::PNMreader(char *filename)
{
	fn = (char*)malloc(sizeof(filename));
	strcpy(fn,filename);
	name = "PNMreader";
}

void PNMreader::Execute()
{
	string format;
	int maxVal;
	int height, width;

	ifstream input;
	input.open(fn, ios::in | ios::binary);

	input >> format >> width >> height >> maxVal;
	sourceImg.ResetSize(height, width);

	input.read((char*)sourceImg.GetData()-1, 3*width*height);

	input.close();
}

PNMreader::~PNMreader()
{
	free(fn);
}
