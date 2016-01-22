#ifndef FILTER_H
#define FILTER_H

#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
	public:
	virtual void Update(void);
	virtual const char* FilterName(void) = 0;
	const char* SourceName(void);
	const char* SinkName(void);
};

#endif
