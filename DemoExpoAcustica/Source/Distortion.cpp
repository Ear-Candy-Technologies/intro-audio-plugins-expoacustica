/*
  ==============================================================================

    Distortion.cpp
    Created: 27 Mar 2023 2:37:14pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion() {}
Distortion::~Distortion() {}


void Distortion::process (juce::AudioBuffer<float>& buffer, float distGainValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);
            
            //Algoritmo de distorsión Soft Clipping
            float gainSample = sample * distGainValue;
            float outSample = gainSample - (powf(gainSample, 3.0f) / 3.0f);
            
            buffer.setSample(channel, i, outSample);
        }
    }
}
