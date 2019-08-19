#include "Menu.hh"
#include <iostream>

using namespace std;

Menu::Menu (sf::String title, sf::String text, vector<string> options,
            vector<function<void()>> callbacks, sf::Font font, int titleSize,
            int textSize, int optionSize, int margin, int optionMargin)
:
    _font(font),
    _callbacks(callbacks),
    _cursor(Pong(optionSize / 2.0f, 0)),
    _selectedMenuItem(0),
    _titleSize(titleSize),
    _textSize(textSize),
    _optionSize(optionSize),
    _margin(margin),
    _optionMargin(optionMargin)
{
    // Set up the Text object for the menu title
    _title.setString(title);
    _title.setFont(_font);
    _title.setCharacterSize(_titleSize);
    // Set up the Text object for the menu text
    _text.setFont(_font);
    _text.setString(text);
    _text.setCharacterSize(_textSize);
    // Set up the Text object for the menu options
    for (auto optionText: options)
        _options.push_back(sf::Text(optionText, _font, _optionSize));
}


void Menu::show (sf::RenderWindow& window)
{    
    // Counter to hold the value of the current Y-axis offset at which we 
    // should draw the next element
    int currentY = _margin;

    // Position the menu title (centered horizontally, offset by the margin
    // vertically)
    _title.setPosition(window.getSize().x / 2.0f -
                          _title.getLocalBounds().width / 2.0f -
                          _titleSize / 10,
                      currentY);
    // Move the current Y-axis offset by the height of the title text plus the
    // margin
    currentY += _title.getLocalBounds().height + _margin;

    // Position the menu text (centered horizontally, offset by the previous
    // elements plus the margin)
    _text.setPosition(window.getSize().x / 2.0f -
                         _text.getLocalBounds().width / 2.0f -
                         _textSize / 10,
                     currentY);
    // Move the current Y-axis offset by the height of the menu text plus the
    // margin
    currentY += _text.getLocalBounds().height + _margin;

    // Position all the options using the same principle as before
    // The options are slightly offset to the right to allow for the cursor
    // to be placed to the left of them
    for (int i = 0; i < _options.size(); i++) {
        _options[i].setPosition(window.getSize().x / 2.0f,
                           currentY);
        // Move the current Y-axis offset by the height of the last option plus
        // the margin
        currentY += _options[i].getLocalBounds().height + _optionMargin;
    }

    // Position the cursor to the left of the first option
    _cursor.setPosition(window.getSize().x / 2.0f -
                            _cursor.getLocalBounds().width - _margin / 2.0f,
                        _options[0].getPosition().y +
                            _options[0].getLocalBounds().height / 2.0f);

    // Set up a polling loop
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // Close the window
                case sf::Event::Closed:
                    window.close();
                    break;

                // Keypress handling
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            // Handle moving the cursor up
                            moveCursorUp();
                            break;

                        case sf::Keyboard::Down:
                            // Handle moving the cursor down
                            moveCursorDown();
                            break;

                        case sf::Keyboard::Return:
                            // Trigger selected callback
                            _callbacks[_selectedMenuItem]();
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        // Clear the screen
        window.clear();
        // Draw all the elements
        window.draw(_title);
        window.draw(_text);
        window.draw(_cursor);
        for (int i = 0; i < _options.size(); i++)
            window.draw(_options[i]);

        // Display the screen
        window.display();
    }
}


void Menu::moveCursorUp ()
{
    // If we're on the first element
    if (_selectedMenuItem == 0) {
        // Set the counter to the last element
        _selectedMenuItem = _options.size() - 1;
        // Move the cursor next to the last element
        _cursor.setPosition(_cursor.getPosition().x,
                            _cursor.getPosition().y +
                                (_options.size() - 1) * _margin);
    } else {
        // Decrease the counter
        _selectedMenuItem--;
        // Move the cursor up by one spot
        _cursor.setPosition(_cursor.getPosition().x,
                            _cursor.getPosition().y - _margin);
    }
}

void Menu::moveCursorDown ()
{
    // If we're on the last element
    if (_selectedMenuItem == _options.size() - 1) {
        // Set the counter to the first element
        _selectedMenuItem = 0;
        // Move the cursor next to the first element
        _cursor.setPosition(_cursor.getPosition().x,
                            _cursor.getPosition().y -
                                (_options.size() - 1) * _margin);
    } else {
        // Increase the counter
        _selectedMenuItem++;
        // Move the cursor down by one spot
        _cursor.setPosition(_cursor.getPosition().x,
                            _cursor.getPosition().y + _margin);
    }
}

void Menu::setCallbacks(vector<function<void()>> callbacks)
{
    _callbacks = callbacks;
}
