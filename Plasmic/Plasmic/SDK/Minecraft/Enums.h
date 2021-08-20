#pragma once

//this is to be able to do
//Difficultys::D


enum class Difficulty {
	Peaceful = 0,
	Easy = 1,
	Normal = 2,
	Hard = 3
};



enum class Dimensions {
	Overworld = 0,
	Nether = 1,
	End = 2
};


enum class Gamemodes {
	Survival = 0,
	Creative = 1,
	Adventure = 2,
	Default = 5
};


enum class MouseButton {
	MOUSE_MOVE = 0,
	LEFT = 1,
	RIGHT = 2,
	MIDDLE = 3,
	SCROLL = 4
};

enum class PlayerAction {
	JUMP = 8,
	START_SPRINT = 9,
	STOP_SPRINT = 10,
	START_SNEAK = 11,
	STOP_SNEAK = 12
};

















enum class SettingType {

	BOOL = 0,
	INT = 1,
	FLOAT = 2,
	KEYBIND = 3,
	VEC2 = 4,
	COLOR = 6
};