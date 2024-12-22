#pragma once

enum FontType {
	ARIAL,
	SUPERMARIO256,
	NUM_FONTS
};

enum BackgroundType {
	LOGINSTATE_BACKGROUND,
	NUM_BACKGROUND_TYPE
};

enum Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

enum Environment {
	OVERWORLD,
	UNDERGROUND,
	ATHLETIC,
	CASTLE,
	UNDERWATER
};

Direction getOpposite(const Direction& direction);