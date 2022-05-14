
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "synthesizer.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "MidiFile.h"
#include "Player.hpp"
#include "Note.hpp"
#include "Chord.hpp"
#include "Instrument.hpp"
#include "SongLine.hpp"
#include "Pause.hpp"
#include "Song.hpp"
#include "MidiParser.hpp"
#include <unordered_map>


int main(int argc, char const** argv)
{
    
//    return 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(1001);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);
    
    
    
    
    sf::Clock clock;
    sf::Time time;

    Instrument piano = Instrument("Instruments/Piano/", 48, 83);
    Instrument guitar = Instrument("Instruments/GuitarSamples/", 52, 99);
    Instrument bass = Instrument("Instruments/BassGuitarSamples/", 40, 87);
    Synthesizer synth = Synthesizer(bass);
    

    
    Player player = Player();
    MidiParser parser = MidiParser("res/BOURREE-1.mid");
    std::unordered_map<int, Chord> start = std::move(std::get<0>(parser.testParser()));
    std::unordered_map<int, Chord> end = std::move(std::get<1>(parser.testParser()));
    

    // Start the game loop
    while (window.isOpen())
        
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if (player.isPlaying()){
                    player.stop();
                } else {
                    player.play();
                }
            }
        }
        

        if (player.isPlaying()){
            std::string title = "NOW PLAYING";
            player.playTestSongLine(start, end, synth);
            text.setString(title);
            
        } else {
            text.setString("Stopped");
        };
        
    
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}

