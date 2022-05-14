//
//  SongLine.hpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#ifndef SongLine_hpp
#define SongLine_hpp

#include <stdio.h>
#include "Chord.hpp"
#include <iostream>
#include <vector>
#include "Pause.hpp"
#include "synthesizer.hpp"

class SongLine{
private:
    std::vector<std::variant<Chord, Pause>> _chunks;
    double _duration;
    Synthesizer _synth;
    double _volume;
public:
    SongLine(std::vector<std::variant<Chord, Pause>> chunks, Instrument& instrument, double volume);
    SongLine(std::vector<std::variant<Chord, Pause>> chunks, Instrument& instrument);
    std::vector<std::variant<Chord, Pause>> getChunks();
    double getDuration();
    Synthesizer* getSynth();
    double getVolume();
    void changeVolume(double value);
};

#endif /* SongLine_hpp */
