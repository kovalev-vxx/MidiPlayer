//
//  synthesizer.hpp
//  termSFML
//
//  Created by Valery Kovalev on 02.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#pragma once
#ifndef synthesizer_hpp
#define synthesizer_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "Note.hpp"
#include "Chord.hpp"
#include "Instrument.hpp"




class Synthesizer{
private:
    int _minMidiValue;
    int _maxMidiValue;
    std::vector<sf::SoundBuffer> _soundBuffers;
    std::vector<sf::Sound> _sounds;
    public:
    Synthesizer();
    Synthesizer(Instrument& instrument);
    std::vector<sf::Sound> get_sounds();
    void playOn(Chord chord);
    void playOff(Chord chord);
};


#endif /* synthesizer_hpp */
