/**
 * @file Menu.hh
 * @author Dimitri Kokkonis ([\@kokkonisd](https://github.com/kokkonisd))
 * @date 17 Aug 2019
 * @brief The generic Menu class for the Pong game.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "Pong.hh"

using std::string;
using std::vector;
using std::function;


class Menu {

    public:
        /**
         * @brief Constructor method of the Menu class.
         * 
         * This method constructs a new Menu object. It sets up all its
         * variables based on the arguments that were passed, and then
         * initializes the sf::Text objects with the corresponding values (font
         * size, font family and text).
         *
         * @param[in]  title         The title of the menu.
         * @param[in]  text          The text (body) of the menu.
         * @param[in]  options       The options of the menu.
         * @param[in]  callbacks     The callbacks associated to the options.
         * @param[in]  font          The font family of the text of the menu.
         * @param[in]  titleSize     The menu's title size.
         * @param[in]  textSize      The menu's text text size.
         * @param[in]  optionSize    The menu's option size.
         * @param[in]  margin        The size of the margin to be put between
         *                           the three sections of the menu (title,
         *                           text and options).
         * @param[in]  optionMargin  The size of the option margin to be put
         *                           between the menu's options.
         */
        Menu (sf::String title, sf::String text, vector<string> options,
              vector<function<void()>> callbacks, sf::Font font,
              int titleSize = 50, int textSize = 35, int optionSize = 40,
              int margin = 50, int optionMargin = 20);
        /**
         * @brief Shows the menu in a given window and handles the callbacks
         *        based on the menu option that the user has selected.
         *
         * @param      window  The window for the menu to be drawn in
         */
        void show(sf::RenderWindow& window);


    private:
        /**
         * @brief Handles moving the cursor up (with wrapping functionality
         * once it reaches the top).
         */
        void moveCursorUp ();
        /**
         * @brief Handles moving the cursor down (with wrapping functionality
         * once it reaches the bottom).
         */
        void moveCursorDown ();

        /** The menu's font. */
        sf::Font _font;
        /** The menu title's Text object. */
        sf::Text _title;
        /** The menu text's Text object. */
        sf::Text _text;
        /** The menu options' Text objects. */
        vector<sf::Text> _options;
        /** The callbacks associated to the menu options. */
        vector<function<void()>> _callbacks;
        /** The cursor (which is just a Pong object in this case). */
        Pong _cursor;
        /** The currently selected menu item index. */
        int _selectedMenuItem;
        /** The size of the menu's title. */
        int _titleSize;
        /** The size of the menu's text (body). */
        int _textSize;
        /** The size of the menu's options. */
        int _optionSize;
        /** The margin to be put inbetween the three menu sections (title, text
         * and options). */
        int _margin;
        /** The option margin to be put inbetween the menu options. */
        int _optionMargin;

};
