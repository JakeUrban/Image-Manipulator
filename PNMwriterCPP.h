#ifndef PNMWRITER_H
#define PNMWRITER_H
#include <sink.h>
#include <string>

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
