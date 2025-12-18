/*	example code for cc65, for NES
 *  draw a BG with metatile system
 *	, also sprite collisions with BG
 *	using neslib
 *	Doug Fraker 2018
 */	
 

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" // holds our metasprite data
#include "metatiles.h"

unsigned char can_jump = 1;
unsigned char can_jump2 = 1;
unsigned char frame_count=0000;
unsigned char frame_count2=0000;
unsigned char die1=0;
unsigned char die2=0;
unsigned char RED_WIN = 0;
unsigned char BLUE_WIN = 0;

const unsigned char REDTXT[]="RED WIN!!"; // 출력 문자
const unsigned char BLUETXT[]="BLUE WIN!!"; // 출력 문자

unsigned char ri = 0;
unsigned char bi = 0;

	
void main (void) {
	
	ppu_off(); // screen off
	
	// load the palettes
	pal_bg(palette_bg);
	pal_spr(palette_sp);

	// use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

	set_vram_buffer(); // do at least once, sets a pointer to a buffer

	load_room();
	
	set_scroll_y(0xff); // shift the bg down 1 pixel
	
	ppu_on_all(); // turn on screen

	
	while (1){
		// infinite loop
		ppu_wait_nmi(); // wait till beginning of the frame
		
		pad1 = pad_poll(0); // read the first controller
        pad2 = pad_poll(1); // read the second controller

		pad1_new = get_pad_new(0);
		pad2_new = get_pad_new(1);


		movement();
        movement2(); // 2P 움직임 처리

		draw_sprites();
        ++frame_count;
		if(frame_count == 24)
		{
			frame_count = 0;
		}
        ++frame_count2;
		if(frame_count2 == 36)
		{
			frame_count2 = 0;
		}
	}
}




void load_room(void){
	set_data_pointer(Room1);
	set_mt_pointer(metatiles);
	for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	set_vram_update(NULL); // just turn ppu updates OFF for this example
	
	//copy the room to the collision map
	memcpy (c_map, Room1, 240);
	
	//BoxGuy1.x and BoxGuy1.y already defined in metatiles.h
}




void draw_sprites(void){
	// clear all sprites from sprite buffer
	oam_clear();
	
	temp_x = BoxGuy1.x >> 8;
	temp_y = BoxGuy1.y >> 8;
	if(temp_x == 0) temp_x = 1;
	if(temp_y == 0) temp_y = 1;
	
	// draw 1 metasprite
    if (direction_DANCE == DANCE){
        oam_meta_spr(temp_x, temp_y, chr_dance[frame_count2/6]);

    }else{
    if(direction_idle == IDLE){
        
        if(direction == LEFT){
        oam_meta_spr(temp_x, temp_y, chr_idle_left[0]);
        }else if(direction == RIGHT){
        oam_meta_spr(temp_x, temp_y, chr_idle_right[0]);
        }

    }else if(direction == LEFT) {
        oam_meta_spr(temp_x, temp_y, chr_left[frame_count/6]);
	}
	else{
		oam_meta_spr(temp_x, temp_y, chr_right[frame_count/6]);
	}
    }

	// 2P 캐릭터 그리기
	temp_x = BoxGuy2.x >> 8;
	temp_y = BoxGuy2.y >> 8;
	if(temp_x == 0) temp_x = 1;
	if(temp_y == 0) temp_y = 1;
	
	if (direction_DANCE2 == DANCE){
		oam_meta_spr(temp_x, temp_y, chr_dance2[frame_count2/6]);
	} else {
		if(direction_idle2 == IDLE){
			if(direction2 == LEFT){
				oam_meta_spr(temp_x, temp_y, chr_idle_left2[0]);
			} else if(direction2 == RIGHT){
				oam_meta_spr(temp_x, temp_y, chr_idle_right2[0]);
			}
		} else if(direction2 == LEFT) {
			oam_meta_spr(temp_x, temp_y, chr_left2[frame_count/6]);
		} else {
			oam_meta_spr(temp_x, temp_y, chr_right2[frame_count/6]);
		}
	}

    oam_meta_spr(232, 40, fire_anime[frame_count/6]);
	if(RED_WIN){
    oam_meta_spr(60, 120, red_win_anime[0]);
	oam_meta_spr(80, 120, red_win_anime[1]);
	oam_meta_spr(100, 120, red_win_anime[2]);
	oam_meta_spr(120, 120, red_win_anime[3]);
	oam_meta_spr(140, 120, red_win_anime[4]);
	oam_meta_spr(160, 120, red_win_anime[5]);
	oam_meta_spr(180, 120, red_win_anime[6]);
	}
	
	if(BLUE_WIN){
    oam_meta_spr(60, 120, blue_win_anime[0]);
    oam_meta_spr(80, 120, blue_win_anime[1]);
    oam_meta_spr(100, 120, blue_win_anime[2]);
    oam_meta_spr(120, 120, blue_win_anime[3]);
    oam_meta_spr(140, 120, blue_win_anime[4]);
    oam_meta_spr(160, 120, blue_win_anime[5]);
    oam_meta_spr(180, 120, blue_win_anime[6]);
    oam_meta_spr(200, 120, blue_win_anime[7]);


	}

}
	

	
	
void movement(void){

	old_x = BoxGuy1.x;
	
	if(pad1 & PAD_LEFT){
		direction = LEFT;
        direction_idle = LEFT;
        direction_DANCE = LEFT;
		
        if(BoxGuy1.vel_x >= DECEL){
            BoxGuy1.vel_x -= DECEL;
        }
        else if(BoxGuy1.vel_x > 0){
            BoxGuy1.vel_x = 0;
        }
		else {
			BoxGuy1.vel_x -= ACCEL;
			if(BoxGuy1.vel_x < -MAX_SPEED) BoxGuy1.vel_x = -MAX_SPEED;
		}
	}
	else if (pad1 & PAD_RIGHT){
		
		direction = RIGHT;
        direction_idle = RIGHT;
        direction_DANCE = RIGHT;


		if(BoxGuy1.vel_x <= DECEL){
            BoxGuy1.vel_x += DECEL;
        }
        else if(BoxGuy1.vel_x < 0){
            BoxGuy1.vel_x = 0;
        }
		else {
			BoxGuy1.vel_x += ACCEL;
			if(BoxGuy1.vel_x >= MAX_SPEED) BoxGuy1.vel_x = MAX_SPEED;
		}
	}
	else { // nothing pressed
        direction_idle = IDLE;
		if(BoxGuy1.vel_x >= ACCEL) BoxGuy1.vel_x -= ACCEL;
		else if(BoxGuy1.vel_x < -ACCEL) BoxGuy1.vel_x += ACCEL;
		else BoxGuy1.vel_x = 0;
	}
	
	BoxGuy1.x += BoxGuy1.vel_x;
	
	if(BoxGuy1.x > 0xf000) { // too far, don't wrap around
        
        if(old_x >= 0x8000){
            BoxGuy1.x = 0xf000; // max right
        }
        else{
            BoxGuy1.x = 0x0000; // max left
        }
        
		BoxGuy1.vel_x = 0;
	} 
	
	Generic.x = high_byte(BoxGuy1.x); // this is much faster than passing a pointer to BoxGuy1
	Generic.y = high_byte(BoxGuy1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	
    if(BoxGuy1.vel_x < 0){
        if(bg_coll_L() ){ // check collision left
            high_byte(BoxGuy1.x) = high_byte(BoxGuy1.x) - eject_L;
            BoxGuy1.vel_x = 0;
            if(BoxGuy1.x > 0xf000) {
                // no wrap around
                BoxGuy1.x = 0xf000;
            }
        }
    }
    else if(BoxGuy1.vel_x > 0){
        if(bg_coll_R() ){ // check collision right
            high_byte(BoxGuy1.x) = high_byte(BoxGuy1.x) - eject_R;
            BoxGuy1.vel_x = 0;
            if(BoxGuy1.x > 0xf000) {
                // no wrap around
                BoxGuy1.x = 0x0000;
            }
        }
    }
    // skip collision if vel = 0

	
// handle y

// gravity

	// BoxGuy1.vel_y is signed
	if(BoxGuy1.vel_y < 0x300){
		BoxGuy1.vel_y += GRAVITY;
	}
	else{
		BoxGuy1.vel_y = 0x300; // consistent
	}
	BoxGuy1.y += BoxGuy1.vel_y;
	
	Generic.x = high_byte(BoxGuy1.x);
	Generic.y = high_byte(BoxGuy1.y);
	
    if(BoxGuy1.vel_y > 0){
        if(bg_coll_D() ){ // check collision below
            high_byte(BoxGuy1.y) = high_byte(BoxGuy1.y) - eject_D;
            BoxGuy1.y &= 0xff00;
            if(BoxGuy1.vel_y > 0) {
                BoxGuy1.vel_y = 0;
            }
        }
    }
    else if(BoxGuy1.vel_y < 0){
        if(bg_coll_U() ){ // check collision above
            high_byte(BoxGuy1.y) = high_byte(BoxGuy1.y) - eject_U;
            BoxGuy1.vel_y = 0;
        }
    }
    
	// check collision down a little lower than hero
	Generic.y = high_byte(BoxGuy1.y); // the rest should be the same

	if(pad1_new & PAD_DOWN) {
        direction_DANCE = DANCE;
	}

	if(pad1_new & PAD_A) {
        if(bg_coll_D2() ) {
			BoxGuy1.vel_y = JUMP_VEL; // JUMP
		}
		
	}

	if (bg_coll_D2()) {
		can_jump = 1; // 땅에 닿으면 점프 가능 상태로 변경
	}

	if (can_jump){
		if(pad1_new & PAD_B) {
			if(!bg_coll_D() ) {
				// B 키가 눌렸을 때 캐릭터를 앞으로 점프시킵니다.
				if (direction == LEFT) {
					// 왼쪽을 보고 있을 때
					BoxGuy1.vel_x = DASH_VEL; // 왼쪽으로 이동
				} else {
					// 오른쪽을 보고 있을 때
					BoxGuy1.vel_x = -DASH_VEL; // 오른쪽으로 이동
				}
				BoxGuy1.vel_y = DASH_VEL/2; // JUMP
				can_jump = 0;
			}
		}
    }
}	


char bg_coll_L(void){
    // check 2 points on the left side
    temp5 = Generic.x + scroll_x;
    temp_x = (char)temp5; // low byte
    
    eject_L = temp_x | 0xf0;
    temp_y = Generic.y + 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp_y = Generic.y + Generic.height;
    temp_y -= 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_R(void){
    // check 2 points on the right side
    temp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)temp5; // low byte
    
    eject_R = (temp_x + 1) & 0x0f;
    temp_y = Generic.y + 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp_y = Generic.y + Generic.height;
    temp_y -= 2;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_U(void){
    // check 2 points on the top side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y;
    eject_U = temp_y | 0xf0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_D(void){
    // check 2 points on the bottom side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y + Generic.height;
    
    if((temp_y & 0x0f) > 3) return 0; // bug fix
    // so we don't snap to those platforms
    // don't fall too fast, or might miss it.
    
    eject_D = (temp_y + 1) & 0x0f;
    
    if(bg_collision_sub() ) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub() ) return 1;
    
    return 0;
}

char bg_coll_D2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y + Generic.height;
    temp_y += 2;
    if(bg_collision_sub() ) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub() ) return 1;
    
    return 0;
}





char bg_collision_sub(void){
	if(temp_y >= 0xf0) return 0;
	
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
	
	collision = c_map[coordinates];
	
	if(collision == 0 || collision == 1 || collision == 2 || collision == 3) {
        return 0;
    }
	if(collision == 14 || collision == 15) {
		// 캐릭터의 위치를 {0x1000, 0xd000}으로 리셋
		BoxGuy1.x = 0x1000;
		BoxGuy1.y = 0xd000;
	}
	if(collision == 18) {
		// 캐릭터의 위치를 {0x1000, 0xd000}으로 리셋
		RED_WIN =1;
	}


	return is_solid[collision];;
}

char bg_collision_sub2(void){
	if(temp_y >= 0xf0) return 0;
	
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
	
	collision = c_map[coordinates];
	
	if(collision == 0 || collision == 1 || collision == 2 || collision == 3) {
        return 0;
    }
	if(collision == 14 || collision == 15) {
		// 캐릭터의 위치를 {0x1000, 0xd000}으로 리셋
		BoxGuy2.x = 0x1000;
		BoxGuy2.y = 0xd000;
	}
	if(collision == 18) {
		// 캐릭터의 위치를 {0x1000, 0xd000}으로 리셋
		BLUE_WIN = 1;
	}


	return is_solid[collision];;
}




void movement2(void){

	old_x = BoxGuy2.x;

	if(pad2 & PAD_LEFT){
        direction2 = LEFT;
        direction_idle2 = LEFT;
        direction_DANCE2 = LEFT;
		
		// 왼쪽으로 이동
		if(BoxGuy2.vel_x >= DECEL){
			BoxGuy2.vel_x -= DECEL;
		}
        else if(BoxGuy2.vel_x > 0){
			BoxGuy2.vel_x = 0;
		}
        else {
			BoxGuy2.vel_x -= ACCEL;
			if(BoxGuy2.vel_x < -MAX_SPEED) BoxGuy2.vel_x = -MAX_SPEED;
		}
	}
    else if (pad2 & PAD_RIGHT){
		// 오른쪽으로 이동
        direction2 = RIGHT;
        direction_idle2 = RIGHT;
        direction_DANCE2 = RIGHT;


		if(BoxGuy2.vel_x <= DECEL){
			BoxGuy2.vel_x += DECEL;
		}
        else if(BoxGuy2.vel_x < 0){
			BoxGuy2.vel_x = 0;
		}
        else {
			BoxGuy2.vel_x += ACCEL;
			if(BoxGuy2.vel_x >= MAX_SPEED) BoxGuy2.vel_x = MAX_SPEED;
		}
	} else {// 아무것도 누르지 않음
        direction_idle2 = IDLE;
		if(BoxGuy2.vel_x >= ACCEL) BoxGuy2.vel_x -= ACCEL;
		else if(BoxGuy2.vel_x < -ACCEL) BoxGuy2.vel_x += ACCEL;
		else BoxGuy2.vel_x = 0;
	}
	
	BoxGuy2.x += BoxGuy2.vel_x;

	// 경계 처리
	if(BoxGuy2.x > 0xf000) { 

		if(old_x >= 0x8000){
			BoxGuy2.x = 0xf000;
		}
        else {
			BoxGuy2.x = 0x0000;
		}

		BoxGuy2.vel_x = 0;
	}

	Generic.x = high_byte(BoxGuy2.x);
	Generic.y = high_byte(BoxGuy2.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	
	if(BoxGuy2.vel_x < 0){
		if(do_bg_coll_L() ){
			high_byte(BoxGuy2.x) = high_byte(BoxGuy2.x) - eject_L;
			BoxGuy2.vel_x = 0;
			if(BoxGuy2.x > 0xf000) {

				BoxGuy2.x = 0xf000;
			}
		}
	}
    else if(BoxGuy2.vel_x > 0){
		if(do_bg_coll_R() ){
			high_byte(BoxGuy2.x) = high_byte(BoxGuy2.x) - eject_R;
			BoxGuy2.vel_x = 0;
			if(BoxGuy2.x > 0xf000) {

				BoxGuy2.x = 0x0000;
			}
		}
	}

	// 중력 처리
	if(BoxGuy2.vel_y < 0x300){
		BoxGuy2.vel_y += GRAVITY;
	}
    else {
		BoxGuy2.vel_y = 0x300;
	}
	BoxGuy2.y += BoxGuy2.vel_y;

	Generic.x = high_byte(BoxGuy2.x);
	Generic.y = high_byte(BoxGuy2.y);

	if(BoxGuy2.vel_y > 0){
		if(do_bg_coll_D() ){
			high_byte(BoxGuy2.y) = high_byte(BoxGuy2.y) - eject_D;
			BoxGuy2.y &= 0xff00;
			if(BoxGuy2.vel_y > 0) {
				BoxGuy2.vel_y = 0;
			}
		}
	} else if(BoxGuy2.vel_y < 0){
		if(do_bg_coll_U() ){
			high_byte(BoxGuy2.y) = high_byte(BoxGuy2.y) - eject_U;
			BoxGuy2.vel_y = 0;
		}
	}
    Generic.y = high_byte(BoxGuy2.y); // the rest should be the same

    if(pad2_new & PAD_DOWN) {
        direction_DANCE2 = DANCE;
	}

	if(pad2_new & PAD_A) {
		if(do_bg_coll_D2() ) {
			BoxGuy2.vel_y = JUMP_VEL;
		}
	}

    
	if (do_bg_coll_D2()) {
		can_jump2 = 1; // 땅에 닿으면 점프 가능 상태로 변경
	}

	if (can_jump2){
		if(pad2_new & PAD_B) {
			if(!do_bg_coll_D() ) {
				// B 키가 눌렸을 때 캐릭터를 앞으로 점프시킵니다.
				if (direction2 == LEFT) {
					// 왼쪽을 보고 있을 때
					BoxGuy2.vel_x = DASH_VEL; // 왼쪽으로 이동
				} else {
					// 오른쪽을 보고 있을 때
					BoxGuy2.vel_x = -DASH_VEL; // 오른쪽으로 이동
				}
				BoxGuy2.vel_y = DASH_VEL/2; // JUMP
				can_jump2 = 0;
			}
		}
    }
}








char do_bg_coll_L(void){
    // check 2 points on the left side
    temp5 = Generic.x + scroll_x;
    temp_x = (char)temp5; // low byte
    
    eject_L = temp_x | 0xf0;
    temp_y = Generic.y + 2;
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    temp_y = Generic.y + Generic.height;
    temp_y -= 2;
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    return 0;
}

char do_bg_coll_R(void){
    // check 2 points on the right side
    temp5 = Generic.x + scroll_x + Generic.width;
    temp_x = (char)temp5; // low byte
    
    eject_R = (temp_x + 1) & 0x0f;
    temp_y = Generic.y + 2;
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    temp_y = Generic.y + Generic.height;
    temp_y -= 2;
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    return 0;
}

char do_bg_coll_U(void){
    // check 2 points on the top side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y;
    eject_U = temp_y | 0xf0;
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub2() & COL_ALL) return 1;
    
    return 0;
}

char do_bg_coll_D(void){
    // check 2 points on the bottom side
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y + Generic.height;
    
    if((temp_y & 0x0f) > 3) return 0; // bug fix
    // so we don't snap to those platforms
    // don't fall too fast, or might miss it.
    
    eject_D = (temp_y + 1) & 0x0f;
    
    if(bg_collision_sub2() ) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub2() ) return 1;
    
    return 0;
}

char do_bg_coll_D2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    temp5 = Generic.x + scroll_x;
    temp5 += 2;
    temp_x = (char)temp5; // low byte
    
    temp_y = Generic.y + Generic.height;
    temp_y += 2;
    if(bg_collision_sub2() ) return 1;
    
    temp5 = Generic.x + scroll_x + Generic.width;
    temp5 -= 2;
    temp_x = (char)temp5; // low byte
    
    if(bg_collision_sub2() ) return 1;
    
    return 0;
}



