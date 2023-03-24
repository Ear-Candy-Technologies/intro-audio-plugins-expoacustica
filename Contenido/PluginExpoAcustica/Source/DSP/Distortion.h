/*
  ==============================================================================

    Distortion.h
    Created: 23 Mar 2023 8:13:38pm
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
    void process (juce::AudioBuffer<float>& inBuffer, float distortionValue);
    
};
