#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"
#include "source.h"
#include <iostream>
using namespace std;

Image::Image()
{
	height = 0;
	width = 0;
	data = NULL;
}

Image::Image(int h, int w, unsigned char *d)
{
	height = h;
	width = w;
	data = (unsigned char*)malloc(3*width*height);
	memcpy(data, d, width*height*3);
}

Image::Image(Image &i)
{
	height = i.height;
	width = i.width;
	data = (unsigned char*)malloc(3*width*height);
       	memcpy(data, i.data, width*height*3);	
}

int
Image::GetHeight() const
{
	return height;
}

int
Image::GetWidth() const
{
	return width;
}

const unsigned char*
Image::GetData() const
{
	return data;
}

unsigned char*
Image::SetData() const
{
	return data;
}

void
Image::ResetSize(int h, int w)
{
	height = h;
	width = w;
	if(data != NULL)
	{
		free(data);
	}
		data = (unsigned char*)malloc(3*height*width);
}

void
Image::SetSource(Source *src)
{
	source = src;
}

void Image::Update() const
{
	if(source != NULL)
	{
		source->Update();
	}	
}
