//
//  player.hpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SongLine.hpp"
#include "Instrument.hpp"
#include "synthesizer.hpp"
#include "Song.hpp"
#include "MidiFile.h"
#include <unordered_map>
#include <thread>
#include <map>

class Player{
private:
    sf::Clock _clock;
    int _time;
    bool _isPlaying;
public:
    Player();
    void resetTime();
    int getTime();
    void play();
    void stop();
    bool isPlaying();
    void playSongLine(SongLine* songLine, int tempo, double volume);
    void playSong(Song& song);
    static float calcChordDuration(float value, int tempo);
    void playTestSongLine(std::unordered_map<int, Chord> songLine, std::unordered_map<int, Chord> songLine2,  Synthesizer &synth);
};

#endif /* Player_hpp */
