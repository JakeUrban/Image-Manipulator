#ifndef PNMWRITER_H
#define PNMWRITER_H
#include <sink.h>

class PNMwriter : public Sink
{
	public:
		PNMwriter(void);
		~PNMwriter(void);
		void Write(char*);
		const char* SinkName() {return name;}
	private:
		const char* name;
};

#endif
