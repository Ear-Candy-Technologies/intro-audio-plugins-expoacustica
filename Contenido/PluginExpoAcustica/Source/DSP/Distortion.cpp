/*
  ==============================================================================

    Distortion.cpp
    Created: 23 Mar 2023 8:13:38pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Distortion.h"
Distortion::Distortion() {};
Distortion::~Distortion() {};

void Distortion::process(juce::AudioBuffer<float> &inBuffer, float distortionValue)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            auto inSample = inBuffer.getSample (channel, i);
            // Soft Clip Algorithm
            float gainSample = distortionValue * inSample;
            float outSample =  gainSample - (powf(gainSample, 3.0f) / 3.0f) ;
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

