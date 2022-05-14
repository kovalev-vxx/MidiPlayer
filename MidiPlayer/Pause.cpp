//
//  Pause.cpp
//  termSFML
//
//  Created by Valery Kovalev on 11.05.2022.
//  Copyright © 2022 Valery Kovalev. All rights reserved.
//

#include "Pause.hpp"

Pause::Pause(double duration){
    _duration = duration;
}

double Pause::getDuration(){
    return _duration;
}

std::vector<Note> Pause::getNotes(){
    return std::vector<Note>();
};

bool Pause::isPause(){
    return true;
}
