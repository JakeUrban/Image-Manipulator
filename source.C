#include <source.h>
#include <iostream>
#include <stdlib.h>
#include <logging.h>
using namespace std;
void Source::Update()
{
	char msg[128];
	sprintf(msg, "%s: about to execute",SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing",SourceName());
	Logger::LogEvent(msg);
}

Source::Source()
{
	sourceImg.SetSource(this);
}
