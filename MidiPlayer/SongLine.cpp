//
//  SongLine.cpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "SongLine.hpp"

SongLine::SongLine(std::vector<std::variant<Chord, Pause>> chunks, Instrument& instrument, double volume){
    _synth = Synthesizer(instrument);
    _chunks = chunks;
    if(volume<0 | volume>1){
        throw std::invalid_argument("The volume must be between 0 and 1");
    }
    _volume = volume;
    _duration = 0;
    for(int i = 0; i < _chunks.size();i++){
        try {
          Chord c = std::get<Chord>(_chunks.at(i));
            _duration+=c.getDuration();
        }
        
        catch (const std::bad_variant_access& ex) {
            Pause p = std::get<Pause>(_chunks.at(i));
            _duration+=p.getDuration();
        }
    }
}

SongLine::SongLine(std::vector<std::variant<Chord, Pause>> chunks, Instrument& instrument){
    _synth = Synthesizer(instrument);
    _chunks = chunks;
    _volume = 1;
    _duration = 0;
    for(int i = 0; i < _chunks.size();i++){
        try {
          Chord c = std::get<Chord>(_chunks.at(i));
            _duration+=c.getDuration();

        }
        catch (const std::bad_variant_access& ex) {
            Pause p = std::get<Pause>(_chunks.at(i));
            _duration+=p.getDuration();
        }
    }
}

std::vector<std::variant<Chord, Pause>> SongLine::getChunks(){
    return _chunks;
}

double SongLine::getDuration(){
    return _duration;
}

Synthesizer* SongLine::getSynth(){
    return &_synth;
}

double SongLine::getVolume(){
    return _volume;
}

void SongLine::changeVolume(double value){
    if(value<0 | value>1){
        throw std::invalid_argument("The volume must be between 0 and 1");
    }
    _volume = value;
}
