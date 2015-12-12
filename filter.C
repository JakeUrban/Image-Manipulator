#include <filter.h>
#include <stdlib.h>
#include <iostream>
#include <logging.h>

using namespace std;

void Filter::Update()
{
	if(img != NULL)
	{
		char msg[1024];
		sprintf(msg,"%s: About to update input1",SourceName());
		Logger::LogEvent(msg);
		img->Update();
		sprintf(msg, "%s: Done updating input1",SourceName());
		Logger::LogEvent(msg);
	}
	if(img2 != NULL)
	{
		char msg[1024];
		sprintf(msg, "%s: About to update input2", SourceName());
		Logger::LogEvent(msg);
		img2->Update();
		sprintf(msg,"%s: Done update input2", SourceName());
		Logger::LogEvent(msg);
	}
	char msg[1024];
	sprintf(msg, "%s: About to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();	
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
	
}

const char*
Filter::SourceName()
{
	return FilterName();
}

const char*
Filter::SinkName()
{
	return FilterName();
}
