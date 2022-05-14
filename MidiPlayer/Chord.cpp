//
//  chord.cpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "Chord.hpp"

Chord::Chord(std::vector<Note> notes, double duration, float volume){
    _notes = notes;
    _duration = duration;
    if(volume<0 | volume>100){
        throw std::invalid_argument("The volume must be between 0 and 100");
    }
    _volume = volume;
}

Chord::Chord(std::vector<Note> notes, double duration){
    _notes = std::move(notes);
    _duration = duration;
    _volume = 100;
}

Chord::Chord(){
    _notes = {};
    _duration = 0;
    _volume = 100;
}

std::vector<Note> Chord::getNotes(){
    return _notes;
}

double Chord::getDuration(){
    return _duration;
}

bool Chord::isPause(){
    return false;
}

void Chord::changeVolume(float value){
    if(value<0 | value>100){
        throw std::invalid_argument("The volume must be between 0 and 100");
    }
    _volume = value;
}

float Chord::getVolume(){
    return _volume;
}

void Chord::addNote(Note note){
    _notes.emplace_back(note);
}

void Chord::changeDuration(double duration){
    _duration = duration;
}
