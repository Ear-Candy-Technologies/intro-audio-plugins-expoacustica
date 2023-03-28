/*
  ==============================================================================

    Gain.cpp
    Created: 27 Mar 2023 2:18:53pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain() {}
Gain::~Gain() {}


void Gain::process(juce::AudioBuffer<float> &buffer, float gainValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);
            float outSample = gainValue * sample;
            buffer.setSample(channel, i, outSample);
            
        }
    }
}

