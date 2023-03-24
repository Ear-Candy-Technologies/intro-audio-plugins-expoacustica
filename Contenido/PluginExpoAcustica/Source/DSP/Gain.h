/*
  ==============================================================================

    Gain.h
    Created: 23 Mar 2023 7:59:31pm
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
    
    void process (juce::AudioBuffer<float>& inBuffer, float gainValue);
    
};

