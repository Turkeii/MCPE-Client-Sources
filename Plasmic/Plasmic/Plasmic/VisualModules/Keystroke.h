#pragma once
#include "../Module.h"
#define KEY_WIDTH 18.5f
#define KEY_PADDING 2.5f


class Keystroke : public VisualModule {

public:
	bool hideCPS = false;
	bool hideMouseButton = false;
	bool hideSpace = false;
	bool drawBorder = false;
	float scale = 1.f;

	uint16_t keyForward = 'W';
	uint16_t keyLeft = 'A';
	uint16_t keyBack = 'S';
	uint16_t keyRight = 'D';
	uint16_t keyJump = VK_SPACE;


	ClickguiColor textColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor downtextColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor DowntextColor = ClickguiColor(1.f, 1.f, 1.f, 1.f, true);
	ClickguiColor downBackgroundColor = ClickguiColor(0.686274f, 0.686274f, 0.686274f, 0.6f, true);
	ClickguiColor upBackgroundColor = ClickguiColor(0.176470f, 0.176470f, 0.176470f, 0.3f, true);

	Keystroke() : VisualModule("Keystrokes", Vec2(10.f, 200.f), Vec2(60.f,80.f), mltext("Shows the keys on the screen.", "Affiche les touches de mouvement et attack sur l'ecran.")) {
		addBoolSetting(mltext("Hide CPS", "Cacher les CPS"), "styletwo", hideCPS, &hideCPS);
		addBoolSetting(mltext("Hide Mouse Buttons", "Cacher les Mouse Buttons"), "hideMouseButton", hideMouseButton, &hideMouseButton);
		addBoolSetting(mltext("Hide Spacebar", "Cacher la barre espace"), "hideSpace", hideSpace, &hideSpace);
		addBoolSetting(mltext("Key Border", "Bordure autour des touches"), "drawBorder", drawBorder, &drawBorder);

		addKeybindSetting(mltext("Forward key", "Touche pour avancer"), "keyForward", keyForward, &keyForward);
		addKeybindSetting(mltext("Left key", "Touche pour aller a gauche"), "keyLeft", keyLeft, &keyLeft);
		addKeybindSetting(mltext("Backward key", "Touche pour aller a reculons"), "keyBackward", keyBack, &keyBack);
		addKeybindSetting(mltext("Right key", "Touche pour aller a droite"), "keyRight", keyRight, &keyRight);

		addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
		addColorSetting(mltext("Up Text Color", "Couleur du Texte Relacher"), "textColor", textColor, &textColor);
		addColorSetting(mltext("Down Text Color", "Couleur du Texte Enfonce"), "downtextColor", downtextColor, &downtextColor);
		addColorSetting(mltext("Up Background Color", "Couleur du fond Relacher"), "upColor", upBackgroundColor, &upBackgroundColor);
		addColorSetting(mltext("Down Background Color", "Couleur du fond Enfonce"), "downColor", downBackgroundColor, &downBackgroundColor);
	}

	enum class KeyType {
		FORWARD,
		LEFT,
		BACKWARD,
		RIGHT,
		JUMP,
		ATTACK,
		INTERACT
	};


	void onRender();
	virtual void onKey(uint16_t key, bool isDown, bool& cancel) override;
	virtual void onMouse(MouseButton button, bool isDown, bool& cancel) override;

};

