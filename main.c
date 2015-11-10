#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>



//global
int moving = 0;
int walkCounter = 0;
int walkDelay = 0;
int jumpCounter = 0;
int jumpDelay = 0;
int jumpForward = 0;
int dashCounter = 0;
int dashDelay = 0;
int stopMove = 0;
int charge = 0;
int blastType = 0;
int swtch = 0;
int blastDelay = 0;
int chargesDelay = 0;
int falling = 0;
int block = 0;
int minionSpawn = 0;
int minionCounter = 0;
int minionDelay = 0;
int turretSpawn = 0;
int turretFired = 0;
int bulletDelay = 50;
int hurtCounter = 0;
int hurtDelay = 0;
int hurtTime = 4;
int hurting = 0;
int explosionDelay = 0;
int started = 0;
int telCount = 0;
int gameState = 0;

int main()
{
	//create obj
	//X
	megaman megamanX;
	megamanX.r = 62;
	megamanX.c = 30;
	megamanX.mapX = megamanX.c;
	megamanX.mapY = megamanX.r;
	megamanX.inAir = 0;
	megamanX.lives = 20;
	//blast
	Blast blast;;
	blast.r = 0;
	blast.c = megamanX.c;
	blast.fired = 0;
	blast.speed = 8;
	//drlight
	Drlight drlight;
	drlight.r = 0;
	drlight.c = 0;
	//minion
	Minion minion;
	minion.r = 0;
	minion.c = 0;
	minion.lives = 5;
	//turret
	Turret turret;
	turret.r = 0;
	turret.c = 0;
	turret.lives = 10;
	//bullet
	Bullet bullet;
	bullet.r = 0;
	bullet.c = 0;

	//worldMap ground set up
	WorldMap worldmap[1688];
	for(int x=0; x<535; x++){
		worldmap[x].y = 94;
	}
	for(int x=545; x<905; x++) {
		worldmap[x].y = 74;
	}
	for(int x=921; x<1688; x++) {
		worldmap[x].y = 84;
	}

// 	1. Set up REG_DISPCNT
// Enable objects (sprites) (by setting bit 10) and set the sprite dimension type (given to you by nin10kit)
// 2. Copy the palette given to into the sprite palette (SPRITEPAL)
// 3 Copy the sprite tile graphics to character block 5
// 4. For each of the 128 sprites set its attribute 0 to hide them (ATTR0_HIDE)
// 5. When you want to use a sprite pick a OamEntry.
// a. Modify its attribute 0 with its x and or this with the palette type (from nin10kit) and shape (nin10kit)
// b. Modify its attribute 1 with its y and size (nin10kit)
// c. Modify its attribute 2 with the sprite id (nin10kit)
	REG_DISPCTL = MODE4 | BG2_ENABLE | OBJ_ENABLE | X_DIMENSION_TYPE;

	DMA[3].src = X_palette;
	DMA[3].dst = SPRITEPAL;
	DMA[3].cnt = DMA_ON | X_PALETTE_SIZE;

	DMA[3].src = X;
	DMA[3].dst = SPRITEDATA;
	DMA[3].cnt = DMA_ON | X_SIZE;
	//copy
	OamEntry shadow[128];
	//make all sprites transparent
	for(int i=0; i<128; i++) {
		shadow[i].attr0 = ATTR0_HIDE;
	}

	//helper
	//((SPRITEMEM[0].attr0 &~ 0x00FF)|(20))
	//((SPRITEMEM[1].attr0 &~ 0x01FF)|(0))
	int state=0;
	int hold=0;
	while(1) {
		if(gameState==0) {
			DMA[3].src = title_palette;
			DMA[3].dst = PALETTE;
			DMA[3].cnt = DMA_ON | TITLE_PALETTE_SIZE;
			stage_stop();
			megaman_play();
		}
		while(gameState==0) {
			drawImage4(0,0,240,160,title);
			if(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_START)) {
				gameState=1;
				megaman_stop();
				break;
			}
			waitForVblank();
			flipPage();
		}

		if(gameState==1) {
			//setup stage palette
			DMA[3].src = stage_palette;
			DMA[3].dst = PALETTE;
			DMA[3].cnt = DMA_ON | STAGE_PALETTE_SIZE;

			//music
			stage_play();
		}
		while(gameState==1) {

			if(KEY_DOWN_NOW(BUTTON_SELECT)) {
				for(int i=0; i<128; i++) {
					shadow[i].attr0 = ATTR0_HIDE;
				}
				hurting=0;
				minionSpawn=0;
				turretSpawn=0;
				turretFired=0;
				megamanX.r = 62;
				megamanX.c = 30;
				megamanX.mapX = megamanX.c;
				megamanX.mapY = megamanX.r;
				megamanX.inAir = 0;
				megamanX.lives = 20;
				started=0;
				telCount=0;
				gameState=0;
			}
			//conversation
			if(started==0) {
				drawStage(30,STAGE_WIDTH,STAGE_HEIGHT,stage);
				switch (state) {
				case 0:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer[50];
					sprintf(buffer, "X:");
					drawString4(105,5,buffer,0);
					sprintf(buffer, "What happened here?");
					drawString4(120,5,buffer,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=1;
						hold=1;
					}
					break;
				case 1:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer2[50];
					sprintf(buffer2, "X:");
					drawString4(105,5,buffer2,0);
					sprintf(buffer2, "The highway is destroyed!");
					drawString4(120,5,buffer2,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=2;
						hold=1;
					}
					break;
				case 2:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer3[50];
					sprintf(buffer3, "X:");
					drawString4(105,5,buffer3,0);
					sprintf(buffer3, "I need to turn in my CS2110 homework!");
					drawString4(120,5,buffer3,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=3;
						hold=1;
					}
					break;
				case 3:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer4[50];
					sprintf(buffer4, "Press Right to walk, Up to jump,");
					drawString4(105,5,buffer4,0);
					char buffer5[50];
					sprintf(buffer5, "B to dash, A to fire.");
					drawString4(120,5,buffer5,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						started=1;
						state=0;
						hold=1;
					}
					break;
				}
				if(!KEY_DOWN_NOW(BUTTON_A)) {
					hold=0;
				}
			}
			//teleports
			if(started==1) {
				drawStage(30,STAGE_WIDTH,STAGE_HEIGHT,stage);
				if(telCount<80) {
					drawRect4(telCount,megamanX.c-1+14,30,6,149);
					drawRect4(telCount+1,megamanX.c+14,26,2,0);
					telCount+=8;
				}
				else if(telCount>=80 && telCount<=120) {
					shadow[2].attr0 = megamanX.r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
					shadow[2].attr1 = megamanX.c | X_SPRITE_SIZE;
					shadow[2].attr2 = CHARGES_ID;
					telCount+=8;
				}
				else {
					shadow[2].attr0 = ATTR0_HIDE;
					//draw megaman
					shadow[0].attr0 = megamanX.r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
					shadow[0].attr1 = megamanX.c | X_SPRITE_SIZE;
					shadow[0].attr2 = X_ID;
					started=2;
					telCount=0;
				}
			}
			//in Game
			if(started==2) {
				//update background
				moveScreen(megamanX.mapX);
				//status check
				if(!borderCheck(megamanX.r, megamanX.c)) {
					megamanX.lives-=1;
					hurting=1;
				}
				if(!checkHealth(&megamanX)) {
					//need delay here
					// for(int i=0; i<160;i++) {
					// 	hurt(&megamanX, shadow);
					// }
					for(int i=0; i<128; i++) {
						shadow[i].attr0 = ATTR0_HIDE;
					}
					refreshBlast(&megamanX, &blast, shadow, 1);
					hurting=0;
					minionSpawn=0;
					turretSpawn=0;
					turretFired=0;
					started=0;
					gameState=3;
				}

				//buttons
				if(KEY_DOWN_NOW(BUTTON_A) && hurting==0) {
					if(charge<102)
						charge++;
					if(charge>20) {
						drawCharges(&megamanX, shadow);
					}
				}
				if(!KEY_DOWN_NOW(BUTTON_A) && charge<=20 && charge>0 && hurting==0) {
					blast.fired = 1;
					blast.r = megamanX.r;
					charge = 0;
					blastType = 0;
				}
				else if(!KEY_DOWN_NOW(BUTTON_A) && charge<=100 && charge>20 && hurting==0) {
					blast.fired = 1;
					blast.r = megamanX.r;
					charge = 0;
					blastType = 1;
					shadow[2].attr0 = ATTR0_HIDE;
					chargesDelay = 0;
				}
				else if(!KEY_DOWN_NOW(BUTTON_A) && charge<=102 && charge>100 && hurting==0) {
					blast.fired = 1;
					blast.r = megamanX.r;
					charge = 0;
					blastType = 2;
					shadow[2].attr0 = ATTR0_HIDE;
					chargesDelay = 0;
				}
				if((KEY_DOWN_NOW(BUTTON_B) || (KEY_DOWN_NOW(BUTTON_B) && KEY_DOWN_NOW(BUTTON_RIGHT)))
				 && stopMove==0 && hurting==0) {
					dash(&megamanX, shadow);
					moving = 2;
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT) && !KEY_DOWN_NOW(BUTTON_UP) && 
					!KEY_DOWN_NOW(BUTTON_LEFT) && !KEY_DOWN_NOW(BUTTON_B) &&
					megamanX.inAir==0 && hurting==0) {
					stopMove = 0;
					dashCounter = 0;
					megamanX.mapX++;
					walk(&megamanX, shadow);
					moving = 1;
				}
				if(KEY_DOWN_NOW(BUTTON_LEFT) && !KEY_DOWN_NOW(BUTTON_UP) && 
					!KEY_DOWN_NOW(BUTTON_RIGHT) && !KEY_DOWN_NOW(BUTTON_B) && 
					megamanX.inAir==0 && hurting==0) {
					stopMove = 0;
					dashCounter = 0;
					if(megamanX.mapX-25>0)
						megamanX.mapX--;
					walk(&megamanX, shadow);
					moving = -1;
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT) && KEY_DOWN_NOW(BUTTON_UP) 
					&& megamanX.inAir==0 && hurting==0) {
					megamanX.inAir = 1;
					jumpForward = 1;
					moving = 1;
				}
				if(KEY_DOWN_NOW(BUTTON_UP) && megamanX.inAir==0 && hurting==0) {
					megamanX.inAir = 1;
					moving = 0;
				}
				//default position
				if(!KEY_DOWN_NOW(BUTTON_START) && !KEY_DOWN_NOW(BUTTON_SELECT) &&
					!KEY_DOWN_NOW(BUTTON_B) && 
					!KEY_DOWN_NOW(BUTTON_R) && !KEY_DOWN_NOW(BUTTON_L) &&
					!KEY_DOWN_NOW(BUTTON_LEFT) && !KEY_DOWN_NOW(BUTTON_RIGHT) &&
					!KEY_DOWN_NOW(BUTTON_DOWN) && !KEY_DOWN_NOW(BUTTON_UP) && 
					megamanX.inAir==0 && hurting==0) {
					stopMove = 0;
					jumpCounter = 0;
					dashCounter = 0;
					shadow[0].attr2 = X_ID;
					moving = 0;
				}
				//draw blast
				drawBlast(&blast, &megamanX, shadow);
				//gap check when walking
				if(((megamanX.mapX>=535 && megamanX.mapX<=545) 
					|| (megamanX.mapX>=905 && megamanX.mapX<=921))) {
					if(megamanX.inAir==0) {
						megamanX.inAir=1;
						falling=1;
						jumpCounter=4;
					}
				}
				if(megamanX.inAir==1) {
					jump(&megamanX, shadow);
				}
				if(falling==1) {
					groundCheck(&megamanX, worldmap);
				}
				geoCheck(&megamanX);

				drawLives(&megamanX);
				//restore
				if(hurtTime<=0) {
					restore(shadow);
				}

				blastCollision(&megamanX, &blast, &minion, &turret,shadow);
				if(explosionDelay==0) {
					shadow[2].attr0 = ATTR0_HIDE;
					explosionDelay=12;
				}
				else {
					explosionDelay--;
				}

				//player collision
				if(hurting==0) {
					playerCollision(&megamanX, &minion, &turret, &bullet, shadow);
				}
				//check hurt is second priority
				if(hurting==1) {
					hurt(&megamanX, shadow);
				}

				// for testing
				// char string[50];
				// char string2[50];
				// sprintf(string, "world x: %d, y: %d", megamanX.mapX, worldmap[megamanX.mapX].y-32);
				// sprintf(string2, "I am x: %d, y: %d", megamanX.mapX, megamanX.r);
				// drawString4(10,0,string,5);
				// drawString4(20,0,string2,5);

				//Enemy
				if(((megamanX.mapX>=50 && megamanX.mapX<=250) || (megamanX.mapX>=922 && megamanX.mapX<=1122) 
					|| (megamanX.mapX>=1200 && megamanX.mapX<=1300)) && minionSpawn==0) {	//more condition here to spawn in area
					minionSpawn = 1;
					minion.lives=5;
					minion.c = megamanX.mapX%240+240;
					if(megamanX.mapX>=50 && megamanX.mapX<=250) {
						minion.r = 67;	//it's short
					}
					else {
						minion.r = 57;
					}
				}
				if(minionSpawn==1) {
					drawMinion(&minion, shadow);
					if(!borderCheck(minion.r,minion.c)) {
						minionSpawn=0;
						shadow[3].attr0 = ATTR0_HIDE;
					}
					if(moving!=0 && hurting==0) {
						minion.c-=moving;
					}
				}
				//turret
				if(((megamanX.mapX>=300 && megamanX.mapX<=650) 
					|| (megamanX.mapX>=950 && megamanX.mapX<=1050)) && turretSpawn==0) {
					turretSpawn = 1;
					turret.lives = 10;
					turret.c = megamanX.mapX%240+240;
					if(megamanX.mapX>=300 && megamanX.mapX<=650) {
						turret.r = 36;	//it's short
					}
					else {
						turret.r = 46;
					}
				}
				
				if(turretSpawn==1) {
					drawTurret(&turret, shadow);
					if(!borderCheck(turret.r,turret.c)) {
						turretSpawn=0;
						shadow[4].attr0 = ATTR0_HIDE;
					}
					else if(turretFired==0) {
						bullet.c = turret.c-10;
						if(megamanX.mapX>=300 && megamanX.mapX<=650) {
							bullet.r = 45;	//it's short
						}
						else {
							bullet.r = 55;
						}
					}
					if(moving!=0 && hurting==0) {
						bullet.c-=moving;
					}
					
				}
				//fire
				if(turretFired==1) {
					bulletAnimate(&bullet, shadow);
				}
				if(!borderCheck(bullet.r,bullet.c)) {
					turretFired=0;
					shadow[5].attr0 = ATTR0_HIDE;
				}
				else if(turretSpawn==1){
					if(bulletDelay<=0) {
						turretFired=1;	
						bulletDelay=100;
					}
					else {
						bulletDelay--;
					}
				}
				if(moving!=0 && hurting==0) {
					turret.c-=moving;
				}


				//spawn drlight when reach end
				if(megamanX.mapX>=STAGE_WIDTH-270) {	//more condition here to spawn in area
					started=3;
				}
			}

			if(started==3) {
				for(int i=0; i<128; i++) {
					shadow[i].attr0 = ATTR0_HIDE;
				}
				drawStage(STAGE_WIDTH-270,STAGE_WIDTH,STAGE_HEIGHT,stage);
				shadow[0].attr0 = 52 | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[0].attr1 = 30 | X_SPRITE_SIZE;
				shadow[0].attr2 = X_ID;
				drlight.c = megamanX.c+160;
				drlight.r = megamanX.r;	
				shadow[6].attr0 = drlight.r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[6].attr1 = drlight.c | X_SPRITE_SIZE;
				shadow[6].attr2 = DRLIGHT_ID;
				switch (state) {
				case 0:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer[50];
					sprintf(buffer, "X:");
					drawString4(105,5,buffer,0);
					sprintf(buffer, "Professor!");
					drawString4(120,5,buffer,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=1;
						hold=1;
					}
					break;
				case 1:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer2[50];
					sprintf(buffer2, "Professor Light:");
					drawString4(105,5,buffer2,0);
					sprintf(buffer2, "Finally, you have come.");
					drawString4(120,5,buffer2,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=2;
						hold=1;
					}
					break;
				case 2:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer3[50];
					sprintf(buffer3, "X:");
					drawString4(105,5,buffer3,0);
					sprintf(buffer3, "Here's my assignment");
					drawString4(120,5,buffer3,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						state=3;
						hold=1;
					}
					break;
				case 3:
					drawHollowRect4(100,0,59,239,0);
					drawRect4(102,2,56,236,140);
					char buffer4[50];
					sprintf(buffer4, "Professor Light:");
					drawString4(105,5,buffer4,0);
					char buffer5[50];
					sprintf(buffer5, "Goodjob X.");
					drawString4(120,5,buffer5,0);
					if(KEY_DOWN_NOW(BUTTON_A) && hold==0) {
						started=4;
						state=0;
						hold=1;
						break;
					}
					break;
				}
				if(!KEY_DOWN_NOW(BUTTON_A)) {
					hold=0;
				}
			}

			if(started==4) {
				drawStage(STAGE_WIDTH-270,STAGE_WIDTH,STAGE_HEIGHT,stage);
				if(telCount<40) {
					//hide megaman
					shadow[0].attr0 = ATTR0_HIDE;
					shadow[2].attr0 = megamanX.r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
					shadow[2].attr1 = megamanX.c | X_SPRITE_SIZE;
					shadow[2].attr2 = CHARGES_ID;
					telCount+=8;
				}
				else if(telCount>=40 && telCount<=120) {
					shadow[2].attr0 = ATTR0_HIDE;
					drawRect4(121-telCount,megamanX.c-1+14,30,6,149);
					drawRect4(121-telCount+1,megamanX.c+14,26,2,0);
					telCount+=8;
				}
				else {
					for(int i=0; i<128; i++) {
						shadow[i].attr0 = ATTR0_HIDE;
					}
					megamanX.r = 62;
					megamanX.c = 30;
					megamanX.mapX = megamanX.c;
					megamanX.mapY = megamanX.r;
					megamanX.inAir = 0;
					megamanX.lives = 20;
					started=0;
					telCount=0;
					gameState=2;
				}
			}

			waitForVblank();
			flipPage();
			//update spritememory
			DMA[3].src = shadow; 
	        DMA[3].dst = SPRITEMEM; 
	        DMA[3].cnt = 128 * 4 | DMA_ON;
		}

		if(gameState==2) {
			stage_stop();
			DMA[3].src = win_palette;
			DMA[3].dst = PALETTE;
			DMA[3].cnt = DMA_ON | WIN_PALETTE_SIZE;
		}
		while(gameState==2) {
			drawImage4(0,0,240,160,win);
			if(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_START) || KEY_DOWN_NOW(BUTTON_SELECT)) {
				gameState=0;
				break;
			}
			waitForVblank();
			flipPage();
		}

		if(gameState==3) {
			stage_stop();
			DMA[3].src = lost_palette;
			DMA[3].dst = PALETTE;
			DMA[3].cnt = DMA_ON | LOST_PALETTE_SIZE;
		}
		while(gameState==3) {
			drawImage4(0,0,240,160,lost);
			if(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_START)) {
				hurting=0;
				megamanX.r = 62;
				megamanX.c = 30;
				megamanX.mapX = megamanX.c;
				megamanX.mapY = megamanX.r;
				megamanX.inAir = 0;
				megamanX.lives = 20;
				started=0;
				telCount=0;
				gameState=1;
				break;
			}
			if(KEY_DOWN_NOW(BUTTON_SELECT)) {
				megamanX.r = 62;
				megamanX.c = 30;
				megamanX.mapX = megamanX.c;
				megamanX.mapY = megamanX.r;
				megamanX.inAir = 0;
				megamanX.lives = 20;
				started=0;
				telCount=0;
				gameState=0;
				break;
			}
			waitForVblank();
			flipPage();
		}
	}
}

void drawCharges(megaman* X, OamEntry* shadow) {
	if(charge<100) {
		if(chargesDelay>8) {
			shadow[2].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[2].attr1 = X->c | X_SPRITE_SIZE;
			shadow[2].attr2 = CHARGES_ID;
		} else {
			shadow[2].attr0 = ATTR0_HIDE;
		}
		chargesDelay--;
		if(chargesDelay<=0) {
			chargesDelay=16;
		}
	}
	else {
		if(chargesDelay>1) {
			shadow[2].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[2].attr1 = X->c | X_SPRITE_SIZE;
			shadow[2].attr2 = CHARGES_ID;
		} else {
			shadow[2].attr0 = ATTR0_HIDE;
		}
		chargesDelay--;
		if(chargesDelay<=0) {
			chargesDelay=2;
		}
	}
}

void drawBlast(Blast* blast, megaman* X, OamEntry* shadow) {
	switch(blastType) {
		case 0:
			if(blast->fired==1 && borderCheck(blast->r, blast->c)) {
				blast->c += blast->speed;
				shadow[1].attr0 = blast->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[1].attr1 = blast->c | X_SPRITE_SIZE;
				shadow[1].attr2 = BLAST_ID;
			}
			if(!borderCheck(blast->r, blast->c)){
				refreshBlast(X, blast, shadow, 1);
			}
			break;
		case 1:
			if(blast->fired==1 && borderCheck(blast->r, blast->c)) {
				blast->c += blast->speed;
				shadow[1].attr0 = blast->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[1].attr1 = blast->c | X_SPRITE_SIZE;
				shadow[1].attr2 = BLAST1_ID;
			}
			if(!borderCheck(blast->r, blast->c)){
				refreshBlast(X, blast, shadow, 1);
			}
			break;
		case 2:
			if(blastDelay<=0) {
				if(swtch==0) {
					swtch=1;
				} else {
					swtch=0;
				}
				blastDelay=10;
			}
			else {
				blastDelay--;
			}
			drawBigBlast(blast, X, shadow);
			break;	
	}
}

void drawBigBlast(Blast* blast, megaman* X, OamEntry* shadow) {
	switch(swtch) {
		case 0:
			if(blast->fired==1 && borderCheck(blast->r, blast->c)) {
				blast->c += blast->speed;
				shadow[1].attr0 = blast->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[1].attr1 = blast->c | X_SPRITE_SIZE;
				shadow[1].attr2 = BLAST2_ID;
			}
			if(!borderCheck(blast->r, blast->c)){
				refreshBlast(X, blast, shadow, 1);
			}
			break;
		case 1:
			if(blast->fired==1 && borderCheck(blast->r, blast->c)) {
				blast->c += blast->speed;
				shadow[1].attr0 = blast->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[1].attr1 = blast->c | X_SPRITE_SIZE;
				shadow[1].attr2 = BLAST3_ID;
			}
			if(!borderCheck(blast->r, blast->c)){
				refreshBlast(X, blast, shadow, 1);
			}
			break;
	}
}

int moveScreen(int c) {
	if(c+240>=STAGE_WIDTH || c-20<0) {
		//dont draw
		return 0;
	}
	drawStage(c,STAGE_WIDTH,STAGE_HEIGHT,stage);
	return 1;				
}

void walk(megaman *X, OamEntry *shadow) {
	//walking animation
    if(walkCounter>7) {
		walkCounter=0;
	}
	if(walkDelay==0) {
		walkAnimate(walkCounter, X, shadow);
		walkCounter++;
		walkDelay=3;	
	} else {
		walkDelay--;
	}
}

//helper for walk
void walkAnimate(int count, megaman *X, OamEntry *shadow) {
	switch(count) 
	{
		case 0:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X1_ID;
			break;
		case 1:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X2_ID;
			break;
		case 2:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X3_ID;
			break;
		case 3:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X4_ID;
			break;
		case 4:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X5_ID;
			break;
		case 5:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X6_ID;
			break;
		case 6:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X7_ID;
			break;
		case 7:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X8_ID;
			break;
	}
}

void walkBack(megaman *X, OamEntry *shadow) {
	//walking animation
    if(walkCounter>7) {
		walkCounter=0;
	}
	if(walkDelay==0) {
		walkBackAnimate(walkCounter, X, shadow);
		walkCounter++;
		walkDelay=3;	
	} else {
		walkDelay--;
	}
}

//helper doesnt work
void walkBackAnimate(int count, megaman *X, OamEntry *shadow) {
	switch(count) 
	{
		case 0:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X1_ID;
			break;
		case 1:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X2_ID;
			break;
		case 2:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X3_ID;
			break;
		case 3:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X4_ID;
			break;
		case 4:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X5_ID;
			break;
		case 5:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X6_ID;
			break;
		case 6:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X7_ID;
			break;
		case 7:
			shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE | ATTR1_HFLIP;
			shadow[0].attr2 = X8_ID;
			break;
	}
}

void jump(megaman *X, OamEntry *shadow) {
	//jumping animation
	if(jumpCounter>4) {
		jumpCounter=4;
	}
	if(jumpDelay==0) {
		if(jumpForward==1) {
			X->mapX+=4;
		}
		jumpAnimate(jumpCounter, X, shadow);
		jumpCounter++;
		jumpDelay=3;	
	} else {
		jumpDelay--;
	}
}

//helper for jump
void jumpAnimate(int count, megaman *X, OamEntry *shadow) {
	switch(count) 
	{
		case 0:
			X->r-=20;
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X9_ID;
			break;
		case 1:
			X->r-=10;
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X10_ID;
			break;
		case 2:
			X->r-=2;
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X11_ID;
			break;
		case 3:
			X->r+=2;
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X12_ID;
			falling = 1;
			break;
		case 4:
			X->r+=10;
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X13_ID;
			falling = 1;
			break;
	}
}


int dash(megaman *X, OamEntry *shadow) {
	if(dashCounter>14) {
		return 0;
	}
	else if(dashDelay==0) {
		X->mapX+=6;
		dashAnimate(dashCounter, X, shadow);
		dashCounter++;
		dashDelay=2;	
	} else {
		dashDelay--;
	}
	return 1;
}

void dashAnimate(int count, megaman *X, OamEntry *shadow) {
	switch(count) 
	{
		case 0:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X14_ID;
			break;
		case 1:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 2:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 3:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;		
			break;
		case 4:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 5:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 6:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 7:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 8:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;		
			break;
		case 9:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;
		case 10:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X15_ID;		
		case 11:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X16_ID;
			break;
		case 12:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X17_ID;
			break;
		case 13:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X18_ID;
			break;
		case 14:
			shadow[0].attr0 = (X->r) | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[0].attr1 = X->c | X_SPRITE_SIZE;
			shadow[0].attr2 = X_ID;
			stopMove = 1;
			break;	
	}
}

//need to fix according to world mapGround
void groundCheck(megaman *X, WorldMap *worldmap) {
	int x = X->mapX;
	int y = X->r;
	if(worldmap[x].y==(y+32)) {
		X->inAir = 0;
		jumpCounter=-1;
		jumpForward = 0;
		falling = 0;
	}
}

void geoCheck(megaman *X) {
	int x = X->mapX;
	int y = X->r;
	if((x<=535 && y>62) || ((x+32>=545 && x<=905) && y>42) || (x+32>=921 && y>52)) {
		block = 1;
	}
	block = 0;
}

int borderCheck(int r, int c) {
	if(r>=0 && r+32<=160 && c>=0 && c-30<=240) {
		return 1;
	}
	return 0;
}

void refreshBlast(megaman* X, Blast* blast, OamEntry* shadow, int index) {
	blast->r = 0;
	blast->c = X->c;
	shadow[index].attr0 = ATTR0_HIDE;
	blast->fired = 0;
	blastType = 0;
}

void drawMinion(Minion* minion, OamEntry* shadow) {
	if(minionDelay==0) {
		minion->c--;

		if(minionCounter>2) {
			minionCounter=0;
		}
		else {
			minionCounter++;
		}
		minionAnimate(minionCounter, minion, shadow);
		minionDelay=5;
	}
	else {
		minionDelay--;
	}
}

void minionAnimate(int counter, Minion* minion, OamEntry* shadow) {
	switch(counter) {
		case 0:
			shadow[3].attr0 = minion->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[3].attr1 = minion->c | X_SPRITE_SIZE;
			shadow[3].attr2 = MINION_ID;
			break;
		case 1:
			shadow[3].attr0 = minion->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[3].attr1 = minion->c | X_SPRITE_SIZE;
			shadow[3].attr2 = MINION1_ID;
			break;
		case 2:
			shadow[3].attr0 = minion->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[3].attr1 = minion->c | X_SPRITE_SIZE;
			shadow[3].attr2 = MINION2_ID;
			break;
	}
}

void drawTurret(Turret* turret, OamEntry* shadow) {
	shadow[4].attr0 = turret->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
	shadow[4].attr1 = turret->c | X_SPRITE_SIZE;
	shadow[4].attr2 = TURRET_ID;
}

void bulletAnimate(Bullet *bullet, OamEntry* shadow) {
	bullet->c-=2;
	shadow[5].attr0 = bullet->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
	shadow[5].attr1 = bullet->c | X_SPRITE_SIZE;
	shadow[5].attr2 = BULLET_ID;
}

void drawLives(megaman* X) {
	drawHollowRect4(20,1,53,15,5);
	drawRect4(21,2,52,14,202);
	drawRect4(23,4,41,10,5);
	for(int i=0; i<(X->lives); i++) {
		drawRect4(2*i+24+(20-X->lives)*2,6,1,6,254);
	}
	char string[5];
	sprintf(string,"x");
	drawString4(64,6,string,149);
}

void hurt(megaman* X, OamEntry* shadow) {
	if(hurtDelay==0) {
		if(hurtCounter==1) {
			hurtCounter=0;
		} 
		else {
			hurtTime--;
			hurtCounter=1;
		}
		switch(hurtCounter) {
			case 0:
				shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[0].attr1 = X->c | X_SPRITE_SIZE;
				shadow[0].attr2 = X19_ID;
				break;
			case 1: 
				shadow[0].attr0 = X->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
				shadow[0].attr1 = X->c | X_SPRITE_SIZE;
				shadow[0].attr2 = X20_ID;
				break;
		}
		hurtDelay=6;
	}
	else {
		hurtDelay--;
	}
}

void restore(OamEntry* shadow) {
	hurtTime=4;
	shadow[0].attr2 = X_ID;
	hurting=0;
}
	
void blastCollision(megaman* X, Blast* blast, Minion* minion, Turret* turret, OamEntry* shadow) {
	int bx = blast->c;
	int by = blast->r;
	int mx = minion->c;
	int my = minion->r;
	int tx = turret->c;
	int ty = turret->r;
	if(bx<mx+20 && bx>mx && by<my+20 && by+20>my && minionSpawn==1) {
		if(blastType==0) {
			minion->lives--;
		}
		if(blastType>0) {
			minion->lives = 0;
		}
		if(blastType<2) {
			refreshBlast(X, blast, shadow, 1);
		}
		if(minion->lives<=0) {
			//explosion
			shadow[2].attr0 = minion->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[2].attr1 = minion->c | X_SPRITE_SIZE;
			shadow[2].attr2 = CHARGES_ID;
			enemyDead(3,shadow);	
			minionSpawn=0;
		}
	}
	if(bx<tx+32 && bx>tx && by<ty+20 && by+20>ty && turretSpawn==1) {
		if(blastType==0) {
			turret->lives--;
		}
		if(blastType==1) {
			turret->lives-=3;
		}
		if(blastType==2) {
			turret->lives = 0;
		}
		if(blastType<2) {
			refreshBlast(X, blast, shadow, 1);
		}
		if(turret->lives<=0) {
			//explosion
			shadow[2].attr0 = turret->r | X_PALETTE_TYPE | X_SPRITE_SHAPE;
			shadow[2].attr1 = turret->c | X_SPRITE_SIZE;
			shadow[2].attr2 = CHARGES_ID;
			enemyDead(4,shadow);
			turretSpawn=0;
		}
	}
}

void enemyDead(int index, OamEntry* shadow) {
	shadow[index].attr0 = ATTR0_HIDE;
}	

void playerCollision(megaman* X, Minion* minion, Turret* turret, Bullet* bullet, OamEntry* shadow) {
	int x = X->c;
	int y = X->r;
	int mx = minion->c;
	int my = minion->r;
	int tx = turret->c;
	int ty = turret->r;
	int ux = bullet->c;
	int uy = bullet->r;
	if(x<mx+10 && x+10>mx && y<my+10 && y+10>my && minionSpawn==1) {
		X->lives-=1;
		X->mapX-=30;
		minion->c+=30;
		moving=-1;
		hurting=1;
	}
	if(x<tx+15 && x+15>tx && y<ty+15 && y+15>ty && turretSpawn==1) {
		X->lives-=2;
		X->mapX-=30;
		turret->c+=30;
		moving=-1;
		hurting=1;
	}
	if(x<ux+5 && x+5>ux && y<uy+5 && y+5>uy && turretFired==1) {
		X->lives-=4;
		hurting=1;
		turretFired=0;
		shadow[5].attr0 = ATTR0_HIDE;
	}
}

int checkHealth(megaman* X) {
	int health = X->lives;
	if(health<=0) {
		return 0;
	}
	return 1;
}
