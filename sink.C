#include <sink.h>
#include <stdlib.h>
#include <stdio.h>
#include <logging.h>
void
Sink::TwoImgCheck()
{	
	if(img == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img was passed!");
		DataFlowException e(SinkName(), msg);
		throw e;	
	}
	if(img2 == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img2 was passed!");
		DataFlowException e(SinkName(), msg);
		throw e;
	}
}

void
Sink::OneImgCheck()
{
	if(img == NULL)
	{
		char msg[1024];
		sprintf(msg, "No img was passed!");
		DataFlowException e(SinkName(), msg);
		throw e;	
	}
}

Sink::Sink()
{
	img = NULL;
	img2 = NULL;
}
