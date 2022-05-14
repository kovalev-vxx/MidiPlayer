//
//  Instrument.hpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#ifndef Instrument_hpp
#define Instrument_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

class Instrument{
    private:
        int _max_note_value;
        int _min_note_value;
        std::map<int, std::string> _note_list;
    public:
        Instrument();
        Instrument(std::string dirWithSouns, int minMidiValue, int maxMidiValue);
        std::map<int, std::string> getNoteList();
        std::string getSoundPathByValue(int midi_value);
        int getMaxValue();
        int getMinValue();
};

#endif /* Instrument_hpp */
