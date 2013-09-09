//MONTEK SINGH
#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	int r, c;
	for(r=0; r<height; r++)
	{
		for(c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

void drawRect4(int row, int col, int height, int width, unsigned char index)
{
	volatile unsigned short color = index | (index<<8);
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)/2];
		DMA[3].cnt = (width/2) | DMA_SOURCE_FIXED | DMA_ON; 
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void setPixel4(int row, int col, u8 index)
{
	int pixel = OFFSET(row, col, 240);
	int shrt = pixel/2;
	if(col & 1)
	{
		// column is odd
		videoBuffer[shrt] = (videoBuffer[shrt] & 0x00FF) | (index<<8);
	}
	else
	{
		// column is even
		videoBuffer[shrt] = (videoBuffer[shrt] & 0xFF00) | (index);
	}
}

void FlipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG)
	{
		// We were displaying Buffer 1
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		// We were displaying Buffer 0
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

void fillScreen3(volatile unsigned short color)
{

	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_SOURCE_FIXED | DMA_ON;
}

void fillScreen4(unsigned char index)
{
	volatile unsigned short color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_ON;
}




