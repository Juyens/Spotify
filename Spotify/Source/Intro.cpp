#include "Intro.h"

/*
                 ;
               :;;
              ;;;;;
              :;;;;;;
    :          ;;;;;;;;            :
   ;:          ;;;;;;;;;:          :;
  :;:           :;;;;;;;;          :;:
  :;;            ::;;;;;;:         ;;:
  :;;;             ;:;;;;:        ;;;:
   ;;;;             ;;;;;;       ;;;;
   :;;;;            ;;;;;      :;;;;:
    ;;;;;;:         ;;;;     :;;;;;;
     :;;;;;;;:     ;;;    :;;;;;;;:
       ;;;;;;;;;;;;;;;;;;;;;;;;;;
         :;;;;;;;;;;;;;;;;;;;;:
             :;;;;;;;;;;;;:
*/

const std::array<std::string, 16> LOGO_UPC =
{
    "                 ;",
    "               :;;",
    "              ;;;;;",
    "              :;;;;;;",
    "    :          ;;;;;;;;            :",
    "   ;:          ;;;;;;;;;:          :;",
    "  :;:           :;;;;;;;;          :;:",
    "  :;;            ::;;;;;;:         ;;:",
    "  :;;;             ;:;;;;:        ;;;:",
    "   ;;;;             ;;;;;;       ;;;;",
    "   :;;;;            ;;;;;      :;;;;:",
    "    ;;;;;;:         ;;;;     :;;;;;;",
    "     :;;;;;;;:     ;;;    :;;;;;;;:",
    "       ;;;;;;;;;;;;;;;;;;;;;;;;;;",
    "         :;;;;;;;;;;;;;;;;;;;;:",
    "             :;;;;;;;;;;;;:"
};

void Intro::drawBorder()
{
    auto consoleSize = Console::getSize();

    std::string horizontalLine(consoleSize.width - 2, char(196));
    std::string horTop = std::string(1, char(218)) + horizontalLine + std::string(1, char(191));
    std::string horButton = std::string(1, char(192)) + horizontalLine + std::string(1, char(217));

    Console::writeAt(0, 0, horTop, FG::White | BG::Black);
    Console::writeAt(0, consoleSize.height - 1, horButton, FG::White | BG::Black);

    for (int i = 1; i < consoleSize.height - 1; ++i)
    {
        Console::writeAt(0, i, std::string(1, char(179)), FG::White | BG::Black);
        Console::writeAt(consoleSize.width - 1, i, std::string(1, char(179)), FG::White | BG::Black);
    }
}

void Intro::drawLogo()
{
    auto consoleSize = Console::getSize();

    for (size_t i = 0; i < LOGO_UPC.size(); i++)
    {
        auto line = LOGO_UPC[i];
        int posX = (consoleSize.width - 38) / 2;

        Console::writeAt(posX, static_cast<int>(i) + 1, line, FG::Red | BG::Black);
    }
}

void Intro::drawMessage(int y, const std::string& msg, WORD attributes)
{
    auto consoleSize = Console::getSize();

    int posX = (consoleSize.width - static_cast<int>(msg.length())) / 2;
    Console::writeAt(posX, y, msg, attributes);
}

void Intro::showIntro(ConsoleSize size)
{
    auto consoleSize = Console::getSize();

    int alturaLogo = 5;
    int startY = (consoleSize.height - (alturaLogo + 8)) / 2;

    drawBorder();
    drawLogo();

    WORD tituloColor = FG::LightYellow | BG::Black;
    WORD grupoColor = FG::LightMagenta | BG::Black;
    WORD integrantesColor = FG::LightCyan | BG::Black;
    WORD anioColor = FG::LightGray | BG::Black;
    WORD profesorColor = FG::LightYellow | BG::Black;
    WORD proyectoColor = FG::LightGreen | BG::Black;

    drawMessage(startY + alturaLogo + 2, "Trabajo Parcial", tituloColor);
    drawMessage(startY + alturaLogo + 3, "Algoritmos y Estructura de Datos", tituloColor);

    drawMessage(startY + alturaLogo + 5, "Profesor", profesorColor);
    drawMessage(startY + alturaLogo + 6, "John Edward Arias Orihuela", profesorColor);

    drawMessage(startY + alturaLogo + 8, "Spotify - Consola", proyectoColor);
    drawMessage(startY + alturaLogo + 10, "Grupo 5", grupoColor);

    drawMessage(startY + alturaLogo + 12, "Integrantes", integrantesColor);
    drawMessage(startY + alturaLogo + 13, "Camargo Briceño, Joseph Julius (U20241D992)", integrantesColor);
    drawMessage(startY + alturaLogo + 14, "Flores Pinchi, José Fernando (U20241A290)", integrantesColor);
    drawMessage(startY + alturaLogo + 15, "Palma De Los Santos, Elynor Mikela (U20241A972)", integrantesColor);

    drawMessage(startY + alturaLogo + 18, "2025 - 01", anioColor);

    std::this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(3)));

    Console::clearScreen();
}
