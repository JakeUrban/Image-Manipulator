#include <PNMreader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

PNMreader::PNMreader(char *filename)
{
	fn = (char*)malloc(sizeof(filename));
	strcpy(fn,filename);
	name = "PNMreader";
}

void PNMreader::Execute()
{
	int maxVal;
	int height, width;

	FILE *fp = fopen(fn, "rb");
	fscanf(fp, "P6\n%d %d\n%d\n", &width, &height, &maxVal);
	fprintf(stderr, "%d, %d, %d", width, height, maxVal);

	sourceImg.ResetSize(height,width);

	fread((void*)sourceImg.GetData(), 3*sourceImg.GetWidth(), sourceImg.GetHeight(), fp);
	

	fclose(fp);
}

PNMreader::~PNMreader()
{
	free(fn);
}
