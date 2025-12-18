const unsigned char metasprite_0_data[]={

	  0,  0,0x00,0,
	128

};





// 1234 오른쪽 걷는 1p

const unsigned char metasprite_1_data[]={

	  0,  0,0x01,0,
	128

};

const unsigned char metasprite_2_data[]={

	  0,  0,0x02,0,
	128

};

const unsigned char metasprite_3_data[]={

	  0,  0,0x03,0,
	128

};

const unsigned char metasprite_4_data[]={

	  0,  0,0x04,0,
	128

};








// 5678 왼쪽 걷기 1p

const unsigned char metasprite_5_data[]={

	  0,  0,0x01,0|OAM_FLIP_H,
	128


};

const unsigned char metasprite_6_data[]={

	  0,  0,0x02,0|OAM_FLIP_H,
	128

};

const unsigned char metasprite_7_data[]={

	  0,  0,0x03,0|OAM_FLIP_H,
	128

};

const unsigned char metasprite_8_data[]={

	  0,  0,0x04,0|OAM_FLIP_H,
	128

};








// 9 10 11 12 춤추는거 1p

const unsigned char metasprite_9_data[]={

	  0,  0,0x00,0,
	128
};

const unsigned char metasprite_10_data[]={

	  0,  0,0x00,0|OAM_FLIP_H,
	128
};

const unsigned char metasprite_11_data[]={

	  0,  0,0x08,0,
	128

};

const unsigned char metasprite_12_data[]={


	  1,  0,0x08,0|OAM_FLIP_H,
	128

};








// 왼쪽 보는거 1p

const unsigned char metasprite_13_data[]={

	  0,  0,0x00,0|OAM_FLIP_H,
	128

};




// 박스

const unsigned char metasprite_14_data[]={

	  0,  0,0x0b,2,
	128

};
// 다리

const unsigned char metasprite_15_data[]={

	  0,  0,0x0c,2,
	128

};






// 오른쪽 보는거 2p
const unsigned char metasprite_0_data2[]={

	  0,  0,0x00,1,
	128

};


// 1234 오른쪽 걷는 2p

const unsigned char metasprite_1_data2[]={

	  0,  0,0x01,1,
	128

};

const unsigned char metasprite_2_data2[]={

	  0,  0,0x02,1,
	128

};

const unsigned char metasprite_3_data2[]={

	  0,  0,0x03,1,
	128

};

const unsigned char metasprite_4_data2[]={

	  0,  0,0x04,1,
	128

};








// 5678 왼쪽 걷기 2p

const unsigned char metasprite_5_data2[]={

	  0,  0,0x01,1|OAM_FLIP_H,
	128


};

const unsigned char metasprite_6_data2[]={

	  0,  0,0x02,1|OAM_FLIP_H,
	128

};

const unsigned char metasprite_7_data2[]={

	  0,  0,0x03,1|OAM_FLIP_H,
	128

};

const unsigned char metasprite_8_data2[]={

	  0,  0,0x04,1|OAM_FLIP_H,
	128

};








// 9 10 11 12 춤추는거 2p

const unsigned char metasprite_9_data2[]={

	  0,  0,0x00,1,
	128
};

const unsigned char metasprite_10_data2[]={

	  0,  0,0x00,1|OAM_FLIP_H,
	128
};

const unsigned char metasprite_11_data2[]={

	  0,  0,0x08,1,
	128

};

const unsigned char metasprite_12_data2[]={


	  1,  0,0x08,1|OAM_FLIP_H,
	128

};








// 왼쪽 보는거 2p

const unsigned char metasprite_13_data2[]={

	  0,  0,0x00,1|OAM_FLIP_H,
	128

};


// 불

const unsigned char fire[]={

	  0,  0,0x0c,3,
	128

};
const unsigned char fire1[]={

	  0,  0,0x0d,3,
	128

};
const unsigned char fire2[]={

	  0,  0,0x0e,3,
	128

};
const unsigned char fire3[]={

	  0,  0,0x0f,3,
	128

};

// redwin text

const unsigned char red_win_r[]={

	  0,  0,0x10,0,
	128

};
const unsigned char red_win_e[]={

	  0,  0,0x11,0,
	128

};
const unsigned char red_win_d[]={

	  0,  0,0x12,0,
	128

};
const unsigned char red_win_o[]={

	  0,  0,0x13,0,
	128

};
const unsigned char red_win_w[]={

	  0,  0,0x14,0,
	128

};
const unsigned char red_win_i[]={

	  0,  0,0x15,0,
	128

};
const unsigned char red_win_n[]={

	  0,  0,0x16,0,
	128

};

// bluewin text

const unsigned char blue_win_b[]={

	  0,  0,0x18,1,
	128

};
const unsigned char blue_win_l[]={

	  0,  0,0x19,1,
	128

};
const unsigned char blue_win_u[]={

	  0,  0,0x1a,1,
	128

};
const unsigned char blue_win_e[]={

	  0,  0,0x1b,1,
	128

};
const unsigned char blue_win_o[]={

	  0,  0,0x1c,1,
	128

};
const unsigned char blue_win_w[]={

	  0,  0,0x1d,1,
	128

};
const unsigned char blue_win_i[]={

	  0,  0,0x1e,1,
	128

};
const unsigned char blue_win_n[]={

	  0,  0,0x1f,1,
	128

};





// 리스트 모음

const unsigned char* const chr_idle_left[]={

	metasprite_13_data

};
const unsigned char* const chr_idle_right[]={

	metasprite_0_data

};

const unsigned char* const chr_left[]={


	metasprite_5_data,
	metasprite_6_data,
	metasprite_7_data,
	metasprite_8_data

};

const unsigned char* const chr_right[]={


	metasprite_1_data,
	metasprite_2_data,
	metasprite_3_data,
	metasprite_4_data

};

const unsigned char* const chr_dance[]={


	metasprite_9_data,
	metasprite_11_data,
	metasprite_12_data,
	metasprite_10_data,
	metasprite_12_data,
	metasprite_11_data,

};


const unsigned char* const box[]={


	metasprite_14_data

};


const unsigned char* const bridge[]={


	metasprite_15_data
};



// 2p 리스트 모음

const unsigned char* const chr_idle_left2[]={

	metasprite_13_data2

};
const unsigned char* const chr_idle_right2[]={

	metasprite_0_data2

};

const unsigned char* const chr_left2[]={


	metasprite_5_data2,
	metasprite_6_data2,
	metasprite_7_data2,
	metasprite_8_data2

};

const unsigned char* const chr_right2[]={


	metasprite_1_data2,
	metasprite_2_data2,
	metasprite_3_data2,
	metasprite_4_data2

};

const unsigned char* const chr_dance2[]={


	metasprite_9_data2,
	metasprite_11_data2,
	metasprite_12_data2,
	metasprite_10_data2,
	metasprite_12_data2,
	metasprite_11_data2,

};

const unsigned char* const fire_anime[]={

	fire,
	fire1,
	fire2,
	fire3,
	
};

const unsigned char* const red_win_anime[]={

	red_win_r,
	red_win_e,
	red_win_d,
	red_win_o,
	red_win_w,
	red_win_i,
	red_win_n,
	

	
};

const unsigned char* const blue_win_anime[]={

	blue_win_b,
	blue_win_l,
	blue_win_u,
	blue_win_e,
	blue_win_o,
	blue_win_w,
	blue_win_i,
	blue_win_n
	
};