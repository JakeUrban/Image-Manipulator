#ifndef SOURCE_H
#define SOURCE_H

#include "image.h"

class Source
{
	protected:
		Image sourceImg;	
		virtual void Execute(void) = 0;
	public:
		Source();
		Image* GetOutput(void) {return &sourceImg;}
		virtual void Update(void);
		virtual const char* SourceName(void) = 0;
};

#endif
