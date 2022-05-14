//
//  Instrument.cpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "Instrument.hpp"

Instrument::Instrument(std::string dirWithSouns, int minMidiValue, int maxMidiValue){
    _note_list = {};
    _min_note_value = minMidiValue;
    _max_note_value = maxMidiValue;
    for (int i = _min_note_value; i < _max_note_value; i++){
        std::cout << "added "<< dirWithSouns+std::to_string(i)+".wav" << std::endl;
        _note_list.insert({i, dirWithSouns+std::to_string(i)+".wav"});
    }
}

Instrument::Instrument(){
}

std::map<int, std::string> Instrument::getNoteList(){
    return _note_list;
}

std::string Instrument::getSoundPathByValue(int midi_value){
    return _note_list[midi_value];
}

int Instrument::getMaxValue(){
    return _max_note_value;
}

int Instrument::getMinValue(){
    return _min_note_value;
}
