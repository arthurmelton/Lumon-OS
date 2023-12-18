#ifndef INPUT
#define INPUT

struct mice {
	int x;
	int y;
	int left;
	int right;
	int middle;
};

void input_init();

struct mice get_mice();

#endif
