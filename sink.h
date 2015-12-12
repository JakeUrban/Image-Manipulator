#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <stdlib.h>
class Sink
{
	protected:
		const Image *img;
		const Image *img2;
	public:
		Sink(void);
		void SetInput(Image *i) {img = i;}
		void SetInput2(Image *i2) {img2 = i2;}
		void TwoImgCheck(void);
		void OneImgCheck(void);
		virtual const char* SinkName(void) = 0;
};

#endif
