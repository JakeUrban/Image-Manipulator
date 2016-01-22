#ifndef PNMREADER_H
#define PNMREADER_H
#include <source.h>

class PNMreader : public Source
{
	public:
		PNMreader(char *);
		~PNMreader(void);
		void Execute(void);
		const char* SourceName() {return name;}
	protected:
		char *fn;
	private:
		const char* name;
};

#endif
