#pragma once
#include "../Module.h"

class SetColorCommand : public Command {
public:

	SetColorCommand() : Command("setcolor", ".setcolor <ID> <HexColorCode> change a color to a hex color code.") {

	}

    virtual void execute(const char* args) override {
        size_t argc = strlen(args);
        if (argc < 4) {
            game::sendClientChat("§§cSyntax Error\nGet the ID of the color in the color changer!\n§§b%s", helpMessage);
            return;
        }


        int colorId = std::atoi(args);
        if (ClickguiColor::colors.size() < colorId) {
            game::sendClientChat("§§cInvalid color ID!\nGet the ID of the color in the color changer!\n§§b%s", helpMessage);
            return;
        }

        for (uint16_t game = 0;; game++)
            if (args[game] == ' ') {
                game++;
                args += game;
                break;
            }
            else if (args[game] == '\0') {
                game::sendClientChat("§§cSyntax Error\nGet the ID of the color in the color changer!\n§§b%s", helpMessage);
                return;
            }
        if (args[0] == '#')
            args++;
        if (args[0] == '0' && args[1] == 'x')
            args += 2;

        //be sure we have a 6 digits hex code
        if (strlen(args) < 6) {
            game::sendClientChat("§§cInvalid color code!\nyou need a 6 digits hex color code!\n§§b%s", helpMessage);
            return;
        }

        //get color code
        int result = 0;

        for (int i = 0; i < 6; i++) {
            switch (args[i]) {
            case '0':
                result += 0x0;
                break;
            case '1':
                result += 0x1;
                break;
            case '2':
                result += 0x2;
                break;
            case '3':
                result += 0x3;
                break;
            case '4':
                result += 0x4;
                break;
            case '5':
                result += 0x5;
                break;
            case '6':
                result += 0x6;
                break;
            case '7':
                result += 0x7;
                break;
            case '8':
                result += 0x8;
                break;
            case '9':
                result += 0x9;
                break;
            case 'A':
                result += 0xA;
                break;
            case 'B':
                result += 0xB;
                break;
            case 'C':
                result += 0xC;
                break;
            case 'D':
                result += 0xD;
                break;
            case 'E':
                result += 0xE;
                break;
            case 'F':
                result += 0xF;
                break;
            case 'a':
                result += 0xA;
                break;
            case 'b':
                result += 0xB;
                break;
            case 'c':
                result += 0xC;
                break;
            case 'd': 
                result += 0xD;
                break;
            case 'e':
                result += 0xE;
                break;
            case 'f':
                result += 0xF;
                break;
            default:
                game::sendClientChat("§§cInvalid color code!\nyou need a 6 digits hex color code!\n§§b%s", helpMessage);
                return;
            }

            switch (i) {
            case 1:
                ClickguiColor::colors[colorId]->color.r = result / 255.f;
                result = 0;
                break;
            case 3:
                ClickguiColor::colors[colorId]->color.g = result / 255.f;
                result = 0;
                break;
            case 5:
                ClickguiColor::colors[colorId]->color.b = result / 255.f;
                result = 0;
                break;
            default:
                result *= 16;
                break;
            }
        }
            //save the color
            game::clickGui->Enable();
            game::clickGui->Disable();
            game::sendClientChat("Color %d changed!", colorId, result);
    }


};

