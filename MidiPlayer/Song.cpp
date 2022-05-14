//
//  Song.cpp
//  termSFML
//
//  Created by Valery Kovalev on 12.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "Song.hpp"


Song::Song(std::vector<SongLine*> songLines, int tempo, std::string title){
    _songLines = songLines;
    _tempo = tempo;
    _title = title;
    _volume = 1;
}

Song::Song(std::vector<SongLine*> songLines, int tempo){
    _songLines = songLines;
    _tempo = tempo;
    _title = "UNKNOWN";
    _volume = 1;
}

Song::Song(std::vector<SongLine*> songLines, int tempo, std::string title, double volume){
    if(volume<0 | volume>1){
        throw std::invalid_argument("The volume must be between 0 and 1");
    }
    _volume = volume;
    _songLines = songLines;
    _tempo = tempo;
    _title = title;
}

Song::Song(std::vector<SongLine*> songLines, int tempo, double volume){
    if(volume<0 | volume>1){
        throw std::invalid_argument("The volume must be between 0 and 1");
    }
    _volume = volume;
    _songLines = songLines;
    _tempo = tempo;
    _title = "UNKNOWN";
}

std::vector<SongLine*> Song::getLines(){
    return _songLines;
}

int Song::getTempo(){
    return _tempo;
}

std::string Song::getTitle(){
    return _title;
}

double Song::getVolume(){
    return _volume;
}

void Song::changeVolume(double value){
    if(value<0 | value>1){
        throw std::invalid_argument("The volume must be between 0 and 1");
    }
    _volume = value;
}
