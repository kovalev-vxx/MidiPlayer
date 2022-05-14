//
//  MidiParser.cpp
//  termSFML
//
//  Created by Valery Kovalev on 12.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "MidiParser.hpp"

MidiParser::MidiParser(std::string filePath){
    _midifile.read(filePath);
    _midifile.doTimeAnalysis();
    _midifile.linkNotePairs();
    _midifile.setMillisecondTicks();
}

std::vector<std::variant<Chord, Pause>> MidiParser::parser(){
    int tracks = _midifile.getTrackCount();
    if (!_midifile.status()) {
       std::cerr << "Error reading MIDI file" << std::endl;
    }
    
    int tempo;
    for (int i=0; i<_midifile[0].size(); i++) {
        if (_midifile[0][i].isTempo()){
            tempo = _midifile[0][i].getTempoBPM();
            std::cout << "TEMPO " << _midifile[0][i].getTempoBPM() << std::endl;
        }
    }
    std::cout << _midifile.getTPQ() << std::endl;
    std::cout << _midifile[1].back().tick << std::endl;
    int track = 1;
    int last_tick = 0;
    double last_second = 0;
    std::vector<std::variant<Chord, Pause>> chunks;
    for (int i=0; i<_midifile[track].size(); i++) {
        
        int tick = _midifile[track][i].tick;
        double seconds = _midifile[track][i].seconds;
        double duration = _midifile[track][i].getDurationInSeconds();
        int midiValue = (int)_midifile[track][i][1];
        bool isNoteOn = _midifile[track][i].isNoteOn();
        bool isNoteOff = _midifile[track][i].isNoteOff();
        
        
        if (last_tick!=tick & isNoteOn == true){
            double pause_duration = seconds-last_second;
            std::cout << "PAUSE HERE " << pause_duration << std::endl;
            chunks.emplace_back(Pause(calcTempo(pause_duration, tempo)));
        }
        
        if (last_tick!=tick & isNoteOff == true){
            std::cout << "NEW CHORD " << std::endl;
            chunks.emplace_back(Chord());
        }
        
    
        if (isNoteOff){
            std::cout << "OFF " << tick << " " << duration << '\t' << midiValue << std::endl;
            try {
                std::get<Chord>(chunks.back()).addNote(Note(midiValue));
                std::get<Chord>(chunks.back()).changeDuration(calcTempo(duration, 120));
            } catch (const std::bad_variant_access& ex) {
                continue;
            }
        }
        

        last_tick=tick;
        last_second=seconds;
    }
    for(int i=0; i<chunks.size(); i++){
        try {
          Chord c = std::get<Chord>(chunks[i]);
            std::cout << "CHORD " << c.getDuration() << std::endl;
            for (auto n:c.getNotes()){
                std::cout << n.getMidiValue() << std::endl;
            }
        } catch (const std::bad_variant_access& ex) {
            Pause p = std::get<Pause>(chunks[i]);
            std::cout << "PAUSE " << p.getDuration() << std::endl;
        }
        
    }
    return chunks;
}


double MidiParser::calcTempo(double seconds, int tempo){
    return seconds*tempo/60;
}


std::tuple<std::unordered_map<int, Chord>, std::unordered_map<int, Chord>> MidiParser::testParser(){
    std::cout << "PARSER" << std::endl;
    std::unordered_map<int, Chord> starts;
    std::unordered_map<int, Chord> ends;
    
    if (!_midifile.status()) {
       std::cerr << "Error reading MIDI file" << std::endl;
    }
    
    int tempo;
    for (int i=0; i<_midifile[0].size(); i++) {
        if (_midifile[0][i].isTempo()){
            tempo = _midifile[0][i].getTempoBPM();
            std::cout << "TEMPO " << _midifile[0][i].getTempoBPM() << std::endl;
        }
    }
    
    int track = 1;
    int last_tick = 0;
    double last_second = 0;
    for (int i=0; i<_midifile[track].size(); i++) {
        int tick = _midifile[track][i].tick;
        double seconds = _midifile[track][i].seconds;
        double duration = _midifile[track][i].getDurationInSeconds();
        int midiValue = (int)_midifile[track][i][1];
        bool isNoteOn = _midifile[track][i].isNoteOn();
        bool isNoteOff = _midifile[track][i].isNoteOff();
        
        if (isNoteOn){
            if (starts[seconds*1000].getDuration()){
                starts[seconds*1000].addNote(Note(midiValue));
            } else {
                starts[seconds*1000] = Chord();
                starts[seconds*1000].changeDuration(calcTempo(duration, tempo));
                starts[seconds*1000].addNote(Note(midiValue));
            }
        }
        
        if (isNoteOff){
            if (ends[seconds*1000].getDuration()){
                ends[seconds*1000].addNote(Note(midiValue));
            } else {
                ends[seconds*1000] = Chord();
                ends[seconds*1000].changeDuration(calcTempo(duration, tempo));
                ends[seconds*1000].addNote(Note(midiValue));
            }
        }
    }
    return std::make_tuple(starts, ends);
}
