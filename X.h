/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=sprites -for_bitmap=1 -bpp=4 -transparent=000000 X X.png X1.png X2.png X3.png X4.png X5.png X6.png X7.png X8.png X9.png X10.png X11.png X12.png X13.png X14.png X15.png X16.png X17.png X18.png X19.png X20.png blast.png blast1.png blast2.png blast3.png minion.png minion1.png minion2.png turret.png bullet.png drlight.png charges.png 
 * Time-stamp: Sunday 11/08/2015, 03:14:26
 * 
 * Image Information
 * -----------------
 * X.png 32@32
 * X1.png 32@32
 * X2.png 32@32
 * X3.png 32@32
 * X4.png 32@32
 * X5.png 32@32
 * X6.png 32@32
 * X7.png 32@32
 * X8.png 32@32
 * X9.png 32@32
 * X10.png 32@32
 * X11.png 32@32
 * X12.png 32@32
 * X13.png 32@32
 * X14.png 32@32
 * X15.png 32@32
 * X16.png 32@32
 * X17.png 32@32
 * X18.png 32@32
 * X19.png 32@32
 * X20.png 32@32
 * blast.png 32@32
 * blast1.png 32@32
 * blast2.png 32@32
 * blast3.png 32@32
 * minion.png 32@32
 * minion1.png 32@32
 * minion2.png 32@32
 * turret.png 32@32
 * bullet.png 32@32
 * drlight.png 32@32
 * charges.png 32@32
 * Transparent color: (0, 0, 0)
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef X_H
#define X_H

#define X_TRANSPARENT 0x00

#define X_PALETTE_TYPE (0 << 13)
#define X_DIMENSION_TYPE (1 << 6)

extern const unsigned short X_palette[256];
#define X_PALETTE_SIZE 256

extern const unsigned short X[8192];
#define X_SIZE 8192

#define CHARGES_PALETTE (0 << 12)
#define CHARGES_SPRITE_SHAPE (0 << 14)
#define CHARGES_SPRITE_SIZE (2 << 14)
#define CHARGES_ID 512

#define X1_PALETTE (0 << 12)
#define X1_SPRITE_SHAPE (0 << 14)
#define X1_SPRITE_SIZE (2 << 14)
#define X1_ID 528

#define X2_PALETTE (0 << 12)
#define X2_SPRITE_SHAPE (0 << 14)
#define X2_SPRITE_SIZE (2 << 14)
#define X2_ID 544

#define X3_PALETTE (0 << 12)
#define X3_SPRITE_SHAPE (0 << 14)
#define X3_SPRITE_SIZE (2 << 14)
#define X3_ID 560

#define X4_PALETTE (0 << 12)
#define X4_SPRITE_SHAPE (0 << 14)
#define X4_SPRITE_SIZE (2 << 14)
#define X4_ID 576

#define X5_PALETTE (0 << 12)
#define X5_SPRITE_SHAPE (0 << 14)
#define X5_SPRITE_SIZE (2 << 14)
#define X5_ID 592

#define X6_PALETTE (0 << 12)
#define X6_SPRITE_SHAPE (0 << 14)
#define X6_SPRITE_SIZE (2 << 14)
#define X6_ID 608

#define X7_PALETTE (0 << 12)
#define X7_SPRITE_SHAPE (0 << 14)
#define X7_SPRITE_SIZE (2 << 14)
#define X7_ID 624

#define X8_PALETTE (0 << 12)
#define X8_SPRITE_SHAPE (0 << 14)
#define X8_SPRITE_SIZE (2 << 14)
#define X8_ID 640

#define X9_PALETTE (0 << 12)
#define X9_SPRITE_SHAPE (0 << 14)
#define X9_SPRITE_SIZE (2 << 14)
#define X9_ID 656

#define X10_PALETTE (0 << 12)
#define X10_SPRITE_SHAPE (0 << 14)
#define X10_SPRITE_SIZE (2 << 14)
#define X10_ID 672

#define X11_PALETTE (0 << 12)
#define X11_SPRITE_SHAPE (0 << 14)
#define X11_SPRITE_SIZE (2 << 14)
#define X11_ID 688

#define X12_PALETTE (0 << 12)
#define X12_SPRITE_SHAPE (0 << 14)
#define X12_SPRITE_SIZE (2 << 14)
#define X12_ID 704

#define X13_PALETTE (0 << 12)
#define X13_SPRITE_SHAPE (0 << 14)
#define X13_SPRITE_SIZE (2 << 14)
#define X13_ID 720

#define X14_PALETTE (0 << 12)
#define X14_SPRITE_SHAPE (0 << 14)
#define X14_SPRITE_SIZE (2 << 14)
#define X14_ID 736

#define X15_PALETTE (0 << 12)
#define X15_SPRITE_SHAPE (0 << 14)
#define X15_SPRITE_SIZE (2 << 14)
#define X15_ID 752

#define X_PALETTE (0 << 12)
#define X_SPRITE_SHAPE (0 << 14)
#define X_SPRITE_SIZE (2 << 14)
#define X_ID 768

#define X17_PALETTE (0 << 12)
#define X17_SPRITE_SHAPE (0 << 14)
#define X17_SPRITE_SIZE (2 << 14)
#define X17_ID 784

#define X18_PALETTE (0 << 12)
#define X18_SPRITE_SHAPE (0 << 14)
#define X18_SPRITE_SIZE (2 << 14)
#define X18_ID 800

#define X19_PALETTE (0 << 12)
#define X19_SPRITE_SHAPE (0 << 14)
#define X19_SPRITE_SIZE (2 << 14)
#define X19_ID 816

#define BLAST1_PALETTE (0 << 12)
#define BLAST1_SPRITE_SHAPE (0 << 14)
#define BLAST1_SPRITE_SIZE (2 << 14)
#define BLAST1_ID 832

#define BLAST2_PALETTE (0 << 12)
#define BLAST2_SPRITE_SHAPE (0 << 14)
#define BLAST2_SPRITE_SIZE (2 << 14)
#define BLAST2_ID 848

#define BLAST3_PALETTE (0 << 12)
#define BLAST3_SPRITE_SHAPE (0 << 14)
#define BLAST3_SPRITE_SIZE (2 << 14)
#define BLAST3_ID 864

#define MINION_PALETTE (0 << 12)
#define MINION_SPRITE_SHAPE (0 << 14)
#define MINION_SPRITE_SIZE (2 << 14)
#define MINION_ID 880

#define MINION1_PALETTE (0 << 12)
#define MINION1_SPRITE_SHAPE (0 << 14)
#define MINION1_SPRITE_SIZE (2 << 14)
#define MINION1_ID 896

#define MINION2_PALETTE (0 << 12)
#define MINION2_SPRITE_SHAPE (0 << 14)
#define MINION2_SPRITE_SIZE (2 << 14)
#define MINION2_ID 912

#define TURRET_PALETTE (0 << 12)
#define TURRET_SPRITE_SHAPE (0 << 14)
#define TURRET_SPRITE_SIZE (2 << 14)
#define TURRET_ID 928

#define BULLET_PALETTE (1 << 12)
#define BULLET_SPRITE_SHAPE (0 << 14)
#define BULLET_SPRITE_SIZE (2 << 14)
#define BULLET_ID 944

#define DRLIGHT_PALETTE (1 << 12)
#define DRLIGHT_SPRITE_SHAPE (0 << 14)
#define DRLIGHT_SPRITE_SIZE (2 << 14)
#define DRLIGHT_ID 960

#define X16_PALETTE (0 << 12)
#define X16_SPRITE_SHAPE (0 << 14)
#define X16_SPRITE_SIZE (2 << 14)
#define X16_ID 976

#define X20_PALETTE (0 << 12)
#define X20_SPRITE_SHAPE (0 << 14)
#define X20_SPRITE_SIZE (2 << 14)
#define X20_ID 992

#define BLAST_PALETTE (0 << 12)
#define BLAST_SPRITE_SHAPE (0 << 14)
#define BLAST_SPRITE_SIZE (2 << 14)
#define BLAST_ID 1008

#endif

