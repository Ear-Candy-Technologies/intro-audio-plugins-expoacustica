/*
  ==============================================================================

    Gain.h
    Created: 27 Mar 2023 2:18:53pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
    Gain();
    ~Gain();
    
    void process (juce::AudioBuffer<float>& buffer, float gainValue);
};
