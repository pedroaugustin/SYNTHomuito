/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SynthoAudioProcessor  : public juce::AudioProcessor
    
{
public:
    //==============================================================================
    SynthoAudioProcessor();
    ~SynthoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================

    void setReverbSampleRate(double sampleRate);
    void setReverbParams(std::atomic<float>* roomSize, std::atomic<float>* damping, std::atomic<float>* wetLevel, std::atomic<float>* dryLevel, std::atomic<float>* width, std::atomic<float>* freezeMode);
    void updateFilter();
    void updateVoices();

    juce::AudioProcessorValueTreeState apvts;
    float sliderValue; 
    string sliderID;
     

private:
    juce::Synthesiser mySynth; 
    SynthVoice* myVoice;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    double lastSampleRate;
    juce::Reverb reverb;
    juce::Reverb::Parameters reverbParams;
    

    juce::dsp::ProcessorDuplicator<juce::dsp::StateVariableFilter::Filter<float>, juce::dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthoAudioProcessor)
};
