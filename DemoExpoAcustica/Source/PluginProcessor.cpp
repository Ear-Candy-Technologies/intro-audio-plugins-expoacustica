/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DemoExpoAcusticaAudioProcessor::DemoExpoAcusticaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())

#endif
{
}

DemoExpoAcusticaAudioProcessor::~DemoExpoAcusticaAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout DemoExpoAcusticaAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("preGain", 1), "preGain", 0.0f, 2.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("distGain", 1), "distGain", 0.0f, 2.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("outGain", 1), "outGain", 0.0f, 2.0f, 1.0f));


    return parameters;
    
}

//==============================================================================
const juce::String DemoExpoAcusticaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DemoExpoAcusticaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DemoExpoAcusticaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DemoExpoAcusticaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DemoExpoAcusticaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DemoExpoAcusticaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DemoExpoAcusticaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DemoExpoAcusticaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DemoExpoAcusticaAudioProcessor::getProgramName (int index)
{
    return {};
}

void DemoExpoAcusticaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DemoExpoAcusticaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DemoExpoAcusticaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DemoExpoAcusticaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DemoExpoAcusticaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float inGainParameter = *apvts.getRawParameterValue("preGain");
    float inDistParameter = *apvts.getRawParameterValue("distGain");
    float inOutParameter = *apvts.getRawParameterValue("outGain");
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto inSample = buffer.getSample(channel, i);
            float outSample = inSample * inGainParameter;
            outSample = outSample * inDistParameter;
            outSample = outSample - (powf(outSample,3.0f)/3.0f);
            outSample = outSample * inOutParameter;
            
            buffer.setSample(channel, i, outSample);
            
        }
    }
}

//==============================================================================
bool DemoExpoAcusticaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DemoExpoAcusticaAudioProcessor::createEditor()
{
    // return new DemoExpoAcusticaAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void DemoExpoAcusticaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DemoExpoAcusticaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoExpoAcusticaAudioProcessor();
}
