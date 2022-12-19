#pragma once
struct Character {
	int C_Hp;

	int C_x;
	int C_y;

	char char_Hp;
};

struct Bullet {
	bool B_create = false;
	bool B_tpye = false;

	int B_x;
	int B_y;
};

struct Enemy {
	bool isValid = false;
	short E_Hp = 0;

	short E_x = 0;
	short E_y = 0;
	short type = 0;
};
