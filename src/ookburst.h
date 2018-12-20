#ifndef DEF_OOKBURST
#define DEF_OOKBURST

#include "stdint.h"
#include "dma.h"
#include "gpio.h"

class ookburst:public bufferdma,public clkgpio,public pwmgpio,public pcmgpio
{
	protected:
	float timegranularity; //ns
	uint32_t Originfsel;
	bool syncwithpwm;
	dma_cb_t *lastcbp;
	public:
	ookburst(uint64_t TuneFrequency,uint32_t SymbolRate,int Channel,uint32_t FifoSize);
	~ookburst();
	void SetDmaAlgo();
	
	void SetSymbols(unsigned char *Symbols,uint32_t Size);
}; 

class ookbursttiming:public ookburst
{
	protected:
	unsigned char *ookrenderbuffer=nullptr;
	size_t m_MaxMessage=0;
	public:
	typedef struct SampleOOKTiming 
	{
	  unsigned char value;
	  size_t duration;
	} SampleOOKTiming;

	ookbursttiming(uint64_t TuneFrequency,size_t MaxMessageDuration);
	~ookbursttiming();
	void SendMessage(SampleOOKTiming *TabSymbols,size_t Size);
};

#endif