#include <filters.h>
#include <stdio.h>
#include <iostream>
#include <logging.h>
#include <stdlib.h>
using namespace std;
Shrinker::Shrinker()
{
	name = "Shinker";
}

Shrinker::~Shrinker()
{;}

void Shrinker::Execute()
{
	OneImgCheck();
	sourceImg.ResetSize((img->GetHeight())/2,(img->GetWidth())/2);
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();

	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < sWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*iWidth+j)*6;
			buffer[sIndex] = buffer1[iIndex];
			buffer[sIndex + 1] = buffer1[iIndex + 1];
			buffer[sIndex + 2] = buffer1[iIndex + 2];
		}
	}
	
}

LRConcat::LRConcat()
{
	name = "LRConcat";
}

LRConcat::~LRConcat()
{;}

void LRConcat::Execute()
{
	TwoImgCheck();
	if(img->GetHeight() != img2->GetHeight())
	{
		char msg[1024];
		sprintf(msg, "heights must match: %d, %d", img->GetHeight(), img2->GetHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	sourceImg.ResetSize(img->GetHeight(), img->GetWidth()+img2->GetWidth());
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	int i2Width = img2->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();
	const unsigned char* buffer2 = img2->GetData();

	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < iWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*iWidth+j)*3;
			buffer[sIndex] = buffer1[iIndex];
			buffer[sIndex+1] = buffer1[iIndex+1];
			buffer[sIndex+2] = buffer1[iIndex+2];
		}
	}
	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = iWidth; j < sWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*i2Width+(j-iWidth))*3;			
			buffer[sIndex] = buffer2[iIndex];
			buffer[sIndex+1] = buffer2[iIndex+1];
			buffer[sIndex+2] = buffer2[iIndex+2];
		}
	}
}

TBConcat::TBConcat()
{
	name = "TBConcat";
}

TBConcat::~TBConcat()
{;}

void TBConcat::Execute()
{
	TwoImgCheck();	
	if(img->GetWidth() != img2->GetWidth())
	{
		char msg[1024];
		sprintf(msg, "widths must match: %d, %d", img->GetWidth(), img2->GetWidth());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	sourceImg.ResetSize(img->GetHeight()+img2->GetHeight(), img->GetWidth());
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	int iHeight = img->GetHeight();
	int i2Width = img2->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();
	const unsigned char* buffer2 = img2->GetData();

	for(int i = 0; i < img->GetHeight(); i++)
	{
		for(int j = 0; j < sWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*iWidth+j)*3;
			buffer[sIndex] = buffer1[iIndex];
			buffer[sIndex+1] = buffer1[iIndex+1];
			buffer[sIndex+2] = buffer1[iIndex+2];
		}
	}
	for(int i = iHeight; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < sWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = ((i-iHeight)*i2Width+j)*3;
			buffer[sIndex] = buffer2[iIndex];
			buffer[sIndex+1] = buffer2[iIndex+1];
			buffer[sIndex+2] = buffer2[iIndex+2];
		}
	}
}

Blender::Blender()
{
	name = "Blender";
}

Blender::~Blender()
{;}

void Blender::Execute()
{
	TwoImgCheck();
	if(factor > 1)
	{
		char msg[1024];
		sprintf(msg,"Invalid factor for Blender: %f", factor);
		DataFlowException e(SinkName(),msg);
		throw e;
	}
	sourceImg.ResetSize(img->GetHeight(),img2->GetWidth());
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	int i2Width = img2->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();
	const unsigned char* buffer2 = img2->GetData();

        for(int i = 0; i < sourceImg.GetHeight(); i++)
        {
                for(int j = 0; j < sWidth; j++)
                {
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*iWidth+j)*3;
			int i2Index = (i*i2Width+j)*3;
                        buffer[sIndex] = factor*(buffer1[iIndex]) + (1-factor)*(buffer2[i2Index]);
                        buffer[sIndex+1] = factor*(buffer1[iIndex+1]) + (1-factor)*(buffer2[i2Index+1]);
                        buffer[sIndex+2] = factor*(buffer1[iIndex+2]) + (1-factor)*(buffer2[i2Index+2]);
                }
        }	
}

void
Crop::Execute(void)
{
    OneImgCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= img->GetWidth() || Istop >= img->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= img->GetHeight() || Jstop >= img->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = img->GetWidth();
    sourceImg.ResetSize(height, width);
    unsigned char *buffer = sourceImg.SetData();
    const unsigned char *buffer1 = img->GetData();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
}

Transpose::Transpose()
{
	name = "Transpose";
}

Transpose::~Transpose()
{;}

void
Transpose::Execute()
{
	OneImgCheck();
	sourceImg.ResetSize(img->GetWidth(),img->GetHeight());
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();
	
	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < sourceImg.GetWidth(); j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (j*iWidth+i)*3;
			buffer[sIndex] = buffer1[iIndex];
			buffer[sIndex+1] = buffer1[iIndex+1];
			buffer[sIndex+2] = buffer1[iIndex+2];
		}
	}
}

Invert::Invert()
{
	name = "Invert";
}

Invert::~Invert()
{;}

void
Invert::Execute()
{
	OneImgCheck();
	sourceImg.ResetSize(img->GetHeight(),img->GetWidth());
	
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();

	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < sWidth; j++)
		{
			int sIndex = (i*sWidth+j)*3;
			int iIndex = (i*iWidth+j)*3;
			buffer[sIndex] = 255 - buffer1[iIndex];
			buffer[sIndex+1] = 255 - buffer1[iIndex+1];
			buffer[sIndex+2] = 255 - buffer1[iIndex+2];
		}
	}
	
}

Checkerboard::Checkerboard()
{
	name = "Checkerboard";
}

Checkerboard::~Checkerboard()
{;}

void
Checkerboard::Execute()
{
	TwoImgCheck();
	sourceImg.ResetSize(img->GetHeight(),img->GetWidth());
	int sWidth = sourceImg.GetWidth();
	int iWidth = img->GetWidth();
	int i2Width = img2->GetWidth();
	unsigned char* buffer = sourceImg.SetData();
	const unsigned char* buffer1 = img->GetData();
	const unsigned char* buffer2 = img2->GetData();
	
	for(int i = 0; i < sourceImg.GetHeight(); i++)
	{
		for(int j = 0; j < sourceImg.GetWidth(); j++)
		{
			int sIndex = (i*sWidth+j)*3;
			if( (i/10 + j/10) % 2 == 0)
			{
				int iIndex = (i*iWidth+j)*3;
				buffer[sIndex] = buffer1[iIndex];
				buffer[sIndex+1] = buffer1[iIndex+1];
				buffer[sIndex+2] = buffer1[iIndex+2];
			}
			else
			{
				int i2Index = (i*i2Width+j)*3;
				buffer[sIndex] = buffer2[i2Index];
				buffer[sIndex+1] = buffer2[i2Index+1];
				buffer[sIndex+2] = buffer2[i2Index+2];
			}
		}
	}
}

Color::Color(int w,int h, unsigned char red, unsigned char green, unsigned char blue)
{
	r = red;
	g = green;
	b = blue;
	name = "Color";
	sourceImg.ResetSize(h,w);
	unsigned char* buffer = sourceImg.SetData();

	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			int index = (i*w+j)*3;
			buffer[index] = r;
			buffer[index+1] = g;
			buffer[index+2] = b;
		}
	}
}

void
Color::Execute(){;}

CheckSum::CheckSum()
{
	name = "CheckSum";
}

void
CheckSum::OutputCheckSum(const char* filename)
{	
	OneImgCheck();
	int iWidth = img->GetWidth();
	const unsigned char* buffer1 = img->SetData();

	for(int i = 0; i < img->GetHeight(); i++)
	{
		for(int j = 0; j < img->GetWidth(); j++)
		{
			int index = (i*iWidth+j)*3;
			r += buffer1[index];
			g += buffer1[index+1];
			b += buffer1[index+2];
		}	
	}
	r = r % 256;
	g = g % 256;
	b = b % 256;
	
	file = fopen(filename, "w");
	fprintf(file,"CHECKSUM: %u, %u, %u \n", r, g, b);
	fclose(file);
	
}
