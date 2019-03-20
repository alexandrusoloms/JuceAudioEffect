/*
  ==============================================================================

    SliderUtil.h
    Created: 20 Mar 2019 12:39:05pm
    Author:  mariussolomes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

template<class VAL_TYPE>
class SliderUtil{
public:

    explicit SliderUtil();
    ~SliderUtil();

    Slider* slider;
    Label label;
    VAL_TYPE value;

};

