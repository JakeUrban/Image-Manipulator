#include <PNMwriter.h>
#include <stdio.h>

PNMwriter::PNMwriter()
{name = "PNMwriter";}

PNMwriter::~PNMwriter()
{;}

void PNMwriter::Write(char *filename)
{
	FILE *fp = fopen(filename, "wb");
	fprintf(fp, "P6\n%d %d\n%d\n", img->GetWidth(), img->GetHeight(), 255);
	fwrite(img->GetData(), 3*img->GetWidth(), img->GetHeight(), fp);
	fclose(fp); 
}
