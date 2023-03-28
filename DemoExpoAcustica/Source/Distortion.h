/*
  ==============================================================================

    Distortion.h
    Created: 27 Mar 2023 2:37:14pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distortion
{
public:
    Distortion();
    ~Distortion();
    
    void process (juce::AudioBuffer<float>& buffer, float distGainValue);
};
