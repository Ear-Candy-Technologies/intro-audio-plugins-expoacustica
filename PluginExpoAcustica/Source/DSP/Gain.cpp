/*
  ==============================================================================

    Gain.cpp
    Created: 23 Mar 2023 7:59:31pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain() {};
Gain::~Gain() {};

void Gain::process(juce::AudioBuffer<float> &inBuffer, float gainValue)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            auto inSample = inBuffer.getSample (channel, i);
            float outSample = inSample * gainValue;
            inBuffer.setSample(channel, i, outSample);
        }
    }
}
