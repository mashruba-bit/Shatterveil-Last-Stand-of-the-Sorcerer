#ifndef BUTTON_H
#define BUTTON_H

// Struct for a button
struct Button {
	int x, y;       // position
	int width, height;  // size
	const char* label;  // text to display
};

// Declare buttons as extern
extern Button btnStart;
extern Button btnCredits;
extern Button btnOptions;
extern Button btnExit;

#endif // BUTTON_H
