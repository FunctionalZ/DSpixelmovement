#include <nds.h>

int main() 
{
    int i = 0;
	int xPosition = 128;
	int yPosition = 80;

	videoSetMode(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//---------------------------------
	//lower screen printing console printing component number 1 to remove
	consoleDemoInit();

    irqInit();

    irqEnable(IRQ_VBLANK);
	//---------------------------------

	u16* gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	for(i = 0; i < 32 * 32 / 2; i++)
	{
		gfx[i] = 1 | (1 << 8);
	}

	SPRITE_PALETTE[1] = RGB15(31,0,0);

	while(1) {

		scanKeys();

		int held = keysHeld();

		if(held & KEY_START)
			break;
		if(held & KEY_LEFT)
			if(xPosition > 0)
			{
				xPosition = xPosition - 16;
			}
		if(held & KEY_RIGHT)
			if(xPosition < 240)
			{
				xPosition = xPosition + 16;
			}
		if(held & KEY_UP)
			if(yPosition > 0)
			{
				yPosition = yPosition - 16;
			}
		if(held & KEY_DOWN)
			if(yPosition < 176)
			{
				yPosition = yPosition + 16;
			}
		if(held & KEY_A)
		{
			xPosition = 0;
			yPosition = 0;
		}

    
		oamSet(&oamMain, //main graphics engine context
			0,           //oam index (0 to 127)  
			xPosition - 8, yPosition - 8,   //x and y pixle location of the sprite
			0,                    //priority, lower renders last (on top)
			0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfx,                  //pointer to the loaded graphics
			0,                  //sprite rotation/scale matrix index 
			true,               //double the size when rotating?
			false,			//hide the sprite?
			false, false, //vflip, hflip
			false	//apply mosaic
			);              
   
		//---------------------------------
		//positional debuging console printing component 2 for removal
		printf("x position: ");
		printf("%d", xPosition);
		printf("\ny position: ");
		printf("%d", yPosition);
		//---------------------------------

		swiWaitForVBlank();

		//---------------------------------
		//component 3 to remove for console printings
		consoleClear();
		//---------------------------------

		oamUpdate(&oamMain);
	}

	return 0;
}