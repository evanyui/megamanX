#include "screens/title.h"
#include "screens/win.h"
#include "screens/lost.h"
#include "text.h"
#include "X.h"
#include "stage.h"
#include "megaman.h"
#include "stagemusic.h"

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern unsigned short *videoBuffer;


#define REG_DISPCTL *(u16 *)0x4000000
#define MODE4 4
#define BG2_ENABLE (1<<10)

#define BUFFER0 (u16 *)0x6000000
#define BUFFER1 (u16 *)0x600A000
#define BUFFER1FLAG (1<<4)
#define PALETTE ((u16 *)0x5000000)

#define SCANLINECOUNTER *(volatile u16 *)0x4000006

#define COLOR(r, g, b)  ((r) | (g)<<5  | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define WHITE COLOR(31, 31, 31)
#define BLACK 0

#define OFFSET(row, col, rowlen) ((row)*(rowlen)+(col))

// Buttons
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	volatile u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000

// Sprites .........................................................
typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
} OamEntry;

//Sprite definitions
#define SPRITEMEM  ((OamEntry*)0x7000000)
#define SPRITEDATA ((u16 *)(0x6014000))
#define SPRITEPAL  ((u16 *)0x5000200)
#define OBJ_ENABLE 0x1000
#define MODE1D (1<<6)

// ATTR0

// 0-7 Row position of the top of the sprite.

// 8-9 Object Mode
#define ATTR0_REG (0<<8)
#define ATTR0_AFF (1<<8)
#define ATTR0_HIDE (2<<8)
#define ATTR0_AFF_DBL (3<<8)

// 10-11 Graphics Mode for special effects
#define ATTR0_BLEND (1<<10) // Forbidden to use both of these
#define ATTR0_WIN (2<<10)

// 12 Mosaic Effect
#define ATTR0_MOSAIC (1<<12)

// 13 Color Mode
#define ATTR0_4BPP 0          // 16 colors
#define ATTR0_8BPP (1<<13)    // 256 colors

// 14-15 Shape
#define ATTR0_SQUARE 0
#define ATTR0_WIDE (1<<14)
#define ATTR0_TALL (2<<14)

// ATTR1

// 0-8 Column position of left hand side of sprite

// 9-13 Valid if Affine Flag (Attribute 0 Bit 8)
// Defines which OAM_AFF_ENTY this sprite uses.

// 12-13
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1<<12)
#define ATTR1_VFLIP (1<<13)
// Used only if the Affine Flag (Attribute 0 Bit 8) is clear

// 14-15 Size...Together with the shape bits Attribute 0 Bits 14-15
// these determine the sprite's real size, see table:

//                                          col x row
/*-------------------------------------------------------------
 *
 *       Size                   00      01      10      11
 *   Shape
 *              00              8x8     16x16   32x32   64x64
 *         Wide 01              16x8    32x8    32x16   64x32
 *         Tall 10              8x16    8x32    16x32   32x64
 *------------------------------------------------------------*/
#define ATTR1_SIZE8 0
#define ATTR1_SIZE16 (1<<14)
#define ATTR1_SIZE32 (2<<14)
#define ATTR1_SIZE64 (3<<14)

// ATTR2

//0-9 Base tile-index of sprite. Note that in bitmap modes this must
// be 512 or higher.

// 10-11 Priority. Higher priorities are drawn first (and therefore
// can be covered by later sprites and backgrounds). Sprites cover
// backgrounds of the same priority, and for sprites of the same
// priority, the higher OBJ_ATTRs are drawn first.
#define ATTR2_PRI0 0
#define ATTR2_PRI1 (1<<10)
#define ATTR2_PRI2 (2<<10)
#define ATTR2_PRI3 (3<<10)

// 12-15 Palette-bank to use when in 16-color mode. Has no effect if
//the color mode flag Attribute 0 Bit 12 is set.
#define ATTR2_PALETTE_BANK(pbn) ((pbn)<<12)

extern unsigned short *videoBuffer;

// Prototypes
void drawImage4(int r, int c, int width, int height, const u16* image);
void waitForVblank();
void setPixel4(int row, int col, u8 index);
void flipPage();
void fillScreen4(u8 index);
void drawRect4(int row, int col, int height, int width, u8);
void drawHollowRect4(int row, int col, int height, int width, u8);
void drawFullScreen(const unsigned short bitmap[]);
void drawStage(int c, int width, int height, const u16* image);

typedef struct
{
	int row;
	int col;
	int rdel;
	int cdel;
	int size;
	u16 color;		
} MOVOBJ;

//typedef
typedef struct {
	int r;
	int c;
	int mapX;
	int mapY;
	int inAir;
	int lives;
} megaman;

typedef struct {
	int r;
	int c;
	int fired;
	int speed;
} Blast;

typedef struct {
	int r;
	int c;
} Drlight;

typedef struct {
	int r;
	int c;
	int lives;
} Minion;

typedef struct {
	int r;
	int c;
	int lives;
} Turret;

typedef struct {
	int r;
	int c;
} Bullet;

typedef struct {
	int y;
}  WorldMap;

//prototypes
void walk(megaman*, OamEntry*);
void walkAnimate(int, megaman*, OamEntry*);
void walkBack(megaman*, OamEntry*);
void walkBackAnimate(int, megaman*, OamEntry*);
void jump(megaman*, OamEntry*);
void jumpAnimate(int, megaman*, OamEntry*);
int dash(megaman*, OamEntry*);
void dashAnimate(int, megaman*, OamEntry*);
int borderCheck(int, int);
void refreshBlast(megaman*, Blast*, OamEntry*, int);
void drawBlast(Blast*, megaman*, OamEntry*);
void drawBigBlast(Blast*, megaman*, OamEntry*);
int moveScreen(int);
void groundCheck(megaman*, WorldMap*);
void drawCharges(megaman*, OamEntry*);
void geoCheck(megaman*);
void drawMinion(Minion*, OamEntry*);
void minionAnimate(int, Minion*, OamEntry* );
void drawTurret(Turret*, OamEntry*);
void bulletAnimate(Bullet*, OamEntry*);
void drawLives(megaman*);
void hurt(megaman*, OamEntry*);
void restore(OamEntry*);
void blastCollision(megaman*, Blast*, Minion*, Turret*, OamEntry*);
void enemyDead(int index, OamEntry* shadow);
void playerCollision(megaman*, Minion*, Turret*, Bullet*, OamEntry*);
int checkHealth(megaman*);
