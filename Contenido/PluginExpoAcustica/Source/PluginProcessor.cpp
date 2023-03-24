/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginExpoAcusticaAudioProcessor::PluginExpoAcusticaAudioProcessor()
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

PluginExpoAcusticaAudioProcessor::~PluginExpoAcusticaAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginExpoAcusticaAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("preGain", 1), "preGain", 0.0f, 2.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("distGain", 1), "distGain", 0.0f, 5.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("outGain", 1), "outGain", 0.0f, 2.0f, 1.0f));

    return parameters;
    
}

//==============================================================================
const juce::String PluginExpoAcusticaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginExpoAcusticaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginExpoAcusticaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginExpoAcusticaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginExpoAcusticaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginExpoAcusticaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginExpoAcusticaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginExpoAcusticaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PluginExpoAcusticaAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginExpoAcusticaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PluginExpoAcusticaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PluginExpoAcusticaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginExpoAcusticaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluginExpoAcusticaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float inGainValue = apvts.getRawParameterValue("preGain")->load();
    float outGainValue = apvts.getRawParameterValue("outGain")->load();
    float distortionValue = apvts.getRawParameterValue("distGain")->load();

    
    preGain.process(buffer, inGainValue);
    distortion.process(buffer, distortionValue);
    outGain.process(buffer, outGainValue);
}

//==============================================================================
bool PluginExpoAcusticaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginExpoAcusticaAudioProcessor::createEditor()
{
//    return new PluginExpoAcusticaAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void PluginExpoAcusticaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginExpoAcusticaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginExpoAcusticaAudioProcessor();
}
