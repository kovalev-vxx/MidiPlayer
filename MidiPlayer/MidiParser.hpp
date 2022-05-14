//
//  MidiParser.hpp
//  termSFML
//
//  Created by Valery Kovalev on 12.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#ifndef MidiParser_hpp
#define MidiParser_hpp
#include "MidiFile.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Chord.hpp"
#include "Pause.hpp"
#include <unordered_map>
#include <map>
#include <tuple>

class MidiParser{
private:
    smf::MidiFile _midifile;
    
public:
    MidiParser(std::string filePath);
    std::vector<std::variant<Chord, Pause>> parser();
    static double calcTempo(double seconds, int tempo);
    std::tuple<std::unordered_map<int, Chord>, std::unordered_map<int, Chord>> testParser();
};

#endif /* MidiParser_hpp */
