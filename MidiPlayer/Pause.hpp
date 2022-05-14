//
//  Pause.hpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#ifndef Pause_hpp
#define Pause_hpp

#include <stdio.h>
#include "Note.hpp"
#include <iostream>
#include <vector>

class Pause{
    private:
        float _duration;
    public:
        Pause(double duration);
        bool isPause();
        double getDuration();
        std::vector<Note> getNotes();
};

#endif /* Pause_hpp */
