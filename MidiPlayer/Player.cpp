//
//  player.cpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "Player.hpp"

Player::Player(){
    _clock.restart();
    _time = _clock.getElapsedTime().asMilliseconds();
    _isPlaying = false;
}

void Player::resetTime(){
    _clock.restart();
}

void Player::play(){
    if (!isPlaying()){
        _clock.restart();
        _isPlaying = true;
    }
}

void Player::stop(){
    if (isPlaying()){
        _clock.restart();
        _isPlaying = false;
    }
}

bool Player::isPlaying(){
    return _isPlaying;
}

int Player::getTime(){
    _time = _clock.getElapsedTime().asMilliseconds();
    return _time;
}

float Player::calcChordDuration(float value, int tempo){
    return value*60/(float)tempo*1000;
}

void Player::playSongLine(SongLine* songLine, int tempo, double volume){
    int when_end = 0;
    if (_isPlaying){
        for(int i = 0; i < songLine->getChunks().size();i++){
            int when_start;
            try {
              Chord c = std::get<Chord>(songLine->getChunks().at(i));
                c.changeVolume(c.getVolume()*songLine->getVolume()*volume);
                when_end+=calcChordDuration(c.getDuration(), tempo);
                when_start=when_end-calcChordDuration(c.getDuration(), tempo);
                
                if (getTime()==when_start){
                    songLine->getSynth()->playOn(c);
                }
                
                if (getTime()==when_end){
                    songLine->getSynth()->playOff(c);
                }
            } catch (const std::bad_variant_access& ex) {
                Pause p = std::get<Pause>(songLine->getChunks().at(i));
                when_end+=calcChordDuration(p.getDuration(), tempo);
                when_start=when_end-calcChordDuration(p.getDuration(), tempo);
            }
        }
    } else{
        for(int i = 0; i < songLine->getChunks().size();i++){
            try {
              Chord c = std::get<Chord>(songLine->getChunks().at(i));
                songLine->getSynth()->playOff(c);
            } catch (const std::bad_variant_access& ex) {
                Pause p = std::get<Pause>(songLine->getChunks().at(i));
            }
        }
    }
}


void Player::playSong(Song& song){
    if (getTime()>calcChordDuration(song.getLines()[0]->getDuration(), song.getTempo())){
        _isPlaying = false;
    }
    for (int i = 0; i<song.getLines().size();i++){
        playSongLine(song.getLines()[i], song.getTempo(), song.getVolume());
    }
}


void Player::playTestSongLine(std::unordered_map<int, Chord> songLine, std::unordered_map<int, Chord> songLine2, Synthesizer &synth){
    Chord c1 = songLine[getTime()];
    
    if(c1.getDuration()){
        synth.playOn(c1);
        
    }
    std::thread t([&](){
        Chord c2 = songLine2[getTime()];
        if(c2.getDuration()){
            synth.playOff(c2);
        }
    });
    t.join();
}
