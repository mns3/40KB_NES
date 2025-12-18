#define SPEED 0x180


#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;

unsigned char pad2;
unsigned char pad2_new;

unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
unsigned char direction; //facing left or right?
unsigned char direction_idle;
unsigned char direction_DANCE;

unsigned char direction2; //facing left or right?
unsigned char direction_idle2;
unsigned char direction_DANCE2;
#define LEFT 0
#define RIGHT 1
#define IDLE 2
#define DANCE 3

int address;
unsigned char x; // room loader code
unsigned char y;
unsigned char index;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;

signed int hero_velocity_x; // signed, low byte is sub-pixel
signed int hero_velocity_y;
//unsigned int hero_x;
//unsigned int hero_y;
unsigned char L_R_switch;
unsigned int old_x;
unsigned int old_y;
unsigned char temp_x;
unsigned char temp_y;


#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240]; // not used in this example

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic;

struct BoxGuy {
	unsigned int x;
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
};

struct BoxGuy BoxGuy1 = {0x1000,0xd000};
struct BoxGuy BoxGuy2 = {0x2000,0xd000};


//struct box box1 = {0x2000,0xd000}
// the width and height should be 1 less than the dimensions (16x16)
// ...I shrunk it a bit 14x14 hitbox
// note, I'm using the top left as the 0,0 on x,y

#define HERO_WIDTH 7
#define HERO_HEIGHT 7



#define ACCEL 30
#define DECEL 100
#define GRAVITY 0x30
#define MAX_SPEED 0x190
#define JUMP_VEL -0x300
#define DASH_VEL -0x300
#define MAX_RIGHT 0x9000




const unsigned char palette_bg[]={
 0x0f,0x0c,0x1c,0x2a,
 0x0f,0x03,0x12,0x30,
 0x0f,0x17,0x27,0x05,
 0x0f,0x1c,0x2c,0x30 
}; 

const unsigned char palette_sp[]={
0x0f,0x24,0x10,0x30,
0x0f,0x21,0x10,0x30,
0x0f,0x17,0x27,0x05,
0x0f,0x05,0x27,0x20
}; 





// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes


const unsigned char metatiles[]={
	13, 14, 29, 30,  1,
	14, 15, 30, 31,  1,
	11, 14, 30, 11,  1,
	14, 11, 11, 30,  1,
	0, 1, 16, 17,  0,
	0, 1, 20, 21,  0,
	4, 1, 16, 21,  0,
	4, 1, 20, 17,  0,
	0, 1, 2, 3,  0,
	2, 3, 18, 19,  0,
	2, 5, 18, 19,  0,
	18, 19, 2, 5,  0,
	2, 3, 16, 17,  0,
	18, 3, 20, 21,  0,
	8, 8, 24, 24,  3,
	22, 23, 22, 23,  3,
	6, 6, 6, 6,  2,
	7, 7, 161, 161,  2,
	6, 6, 6, 26,  2,
	6, 6, 26, 6,  2,
	6, 26, 6, 6,  2,
	26, 6, 6, 6,  2,
	6, 26, 26, 6,  2,
	25, 6, 6, 26,  2,
	6, 26, 26, 26,  2,
	161, 6, 25, 25,  2,
	9, 25, 6, 25,  2,
	25, 25, 25, 6,  2,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	26, 26, 161, 161,  2,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0,
	161, 161, 161, 161,  0
};





#define COL_DOWN 0x80
#define COL_ALL 0x40

const unsigned char is_solid[]={
	0,
	0,
	0,
	0,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_ALL+COL_DOWN



};




#include "BG/Room1.c"
// data is exactly 240 bytes, 16 * 15
// doubles as the collision map data



// PROTOTYPES
void load_room(void);
void draw_sprites(void);
void movement(void);	
void movement2(void);	


char bg_collision_sub(void);

char bg_coll_L(void);
char bg_coll_R(void);
char bg_coll_U(void);
char bg_coll_D(void);
char bg_coll_D2(void);
char do_bg_coll_L(void);
char do_bg_coll_R(void);
char do_bg_coll_U(void);
char do_bg_coll_D(void);
char do_bg_coll_D2(void);
