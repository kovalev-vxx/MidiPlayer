//
//  synthesizer.cpp
//  termSFML
//
//  Created by Valery Kovalev on 02.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "synthesizer.hpp"


std::vector<sf::Sound> Synthesizer::get_sounds(){
    return _sounds;
}


Synthesizer::Synthesizer(Instrument& instrument){
    std::cout << "SYNTH" << std::endl;
    _maxMidiValue = instrument.getMaxValue();
    _minMidiValue = instrument.getMinValue();
    for (int i = 0; i<instrument.getMaxValue()-instrument.getMinValue();i++){
        _soundBuffers.emplace_back(sf::SoundBuffer());
        _soundBuffers[i].loadFromFile(instrument.getNoteList()[i+instrument.getMinValue()]);
    }

    for (int i = 0; i < _soundBuffers.size(); i++){
        _sounds.emplace_back(sf::Sound());
        _sounds[i].setBuffer(_soundBuffers[i]);
    }
}

void Synthesizer::playOn(Chord chord){
    for (int i = 0; i<chord.getNotes().size();i++){
        try {
            if (_sounds.at(chord.getNotes().at(i).getMidiValue()-_minMidiValue).getStatus()!=2){
                _sounds.at(chord.getNotes().at(i).getMidiValue()-_minMidiValue).setVolume(chord.getVolume());
                _sounds.at(chord.getNotes().at(i).getMidiValue()-_minMidiValue).play();
            }
        } catch (const std::out_of_range& e){
            std::cout << "Note with value " << chord.getNotes().at(i).getMidiValue() << " not found" << std::endl;
        }
    }
}

void Synthesizer::playOff(Chord chord){
    for (int i = 0; i<chord.getNotes().size();i++){
        try {
            if (_sounds.at(chord.getNotes().at(i).getMidiValue()-_minMidiValue).getStatus()!=0){
                _sounds.at(chord.getNotes().at(i).getMidiValue()-_minMidiValue).stop();
            }
        } catch (const std::out_of_range& e){
            std::cout << "Note with value " << chord.getNotes().at(i).getMidiValue() << " not found" << std::endl;
        }
    }
}

Synthesizer::Synthesizer(){
    std::cout << "EMPTY" << std::endl;
}
