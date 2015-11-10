#include "mylib.h"

unsigned short *videoBuffer = (u16 *)0x6000000;

//setting pixel in mode 4
void setPixel4(int row, int col, u8 color)
{
	//videoBuffer[OFFSET(r, c, 240)] = color;
	// u16 *dst= &videoBuffer[(c*240+r)/2];  // Division by 2 due to u8/u16 pointer mismatch!
 //    if(r&1)
 //        *dst= (*dst& 0xFF) | (color<<8);    // odd pixel
 //    else
 //        *dst= (*dst&~0xFF) |  color;
	int pixel = row*240+col;
	int whichShort = pixel/2;
	if(col&1)
	{
		// Odd column must insert index into left side
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (color<<8);
	}
	else
	{
		// Even column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | color;
	}
}

//draw rectangle in mode 4
void drawRect4(int row, int col, int height, int width, u8 index)
{
	volatile int color = index << 8 | index;
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer +OFFSET(row+r, col, 240)/2;
		DMA[3].cnt = (width/2) | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void drawHollowRect4(int row, int col, int height, int width, u8 index) 
{
	int c, r;
	for(c=0; c<width; c++)
	{
		setPixel4(row, col+c, index);
		setPixel4(row+height, col+c, index);
	}
	for(r=0; r<height; r++)
	{
		setPixel4(row+r, col, index);
		setPixel4(row+r, col+width, index);
	}
}

//draw image in mode 4
void drawImage4(int r, int c, int width, int height, const u16* image)
{
	// for(int i = 0; i < width; ++i) {
	// 	for(int j = 0; j < height; ++j) {
	// 		videoBuffer[(r+i) + 240*(j+c)] = image[i + width*j];
	// 	}
	// }
	for(int row=0; row<height; row++) {
		DMA[3].src = image+(row*width)/2;
		DMA[3].dst = videoBuffer+(r*240+c)/2+(row*240)/2;
		DMA[3].cnt = DMA_ON | width/2;
	}
}

void drawStage(int c, int width, int height, const u16* image)
{
	for(int row=0; row<height; row++) {
		DMA[3].src = image+(c)/2+(row*width)/2;
		DMA[3].dst = videoBuffer + (row*240)/2;
		DMA[3].cnt = DMA_ON | 240;
	}
}


//fill the image in mode 4
void drawFullScreen(const unsigned short bitmap[])
{	
	DMA[3].src = bitmap;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = DMA_ON | 240*160;	
}

//fill screen with color in mode 4
void fillScreen4(u8 index)
{	
	volatile u16 color = (index<<8) | index;
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | 240*160;	
}

//vsync
void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

//something i dont understand
void flipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG)
	{
		// We were display BUFFER1
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}