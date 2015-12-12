#include <PNMwriterCPP.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

PNMwriter::PNMwriter()
{
	name = "PNMwriter";
}

PNMwriter::~PNMwriter()
{;}

void PNMwriter::Write(char *filename)
{

	ofstream output;
	output.open(filename, ios::out | ios::binary);

	output << "P6" << endl << img->GetWidth() << " " << img->GetHeight() << endl << 255 << endl;

	output.write((char*)img->GetData(),3*img->GetWidth()*img->GetHeight());

	output.close();
}
