/*
  ==============================================================================

    Oscillator.cpp
    Created: 5 Nov 2020 10:57:48am
    Author:  preod

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthoAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(200, 200);
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.setSelectedId(2);
    oscMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscMenu);

    osc2Menu.addItem("None", 1);
    osc2Menu.addItem("Sine", 2);
    osc2Menu.addItem("Saw", 3);
    osc2Menu.addItem("Square", 4);
    osc2Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc2Menu);

    osc2Level.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    osc2Level.setRange(0.0f, 1.0f);
    osc2Level.setValue(1.0f);
    osc2Level.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    osc2Level.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&osc2Level);
    auto osc2LevelAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "OSC2LEVEL", osc2Level);



   auto waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.apvts, "WAVETYPE", oscMenu);
   auto wave2Selection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.apvts, "WAVETYPE2", osc2Menu);


    

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.drawText("Oscillators", titleArea, juce::Justification::centredTop);
    g.drawText("Oscillator 1", 0, 30, getWidth(), 20, juce::Justification::centredTop);
    g.drawText("Oscillator 2", 0, 80, getWidth(), 20, juce::Justification::centredTop);
    g.drawText("Osc2 Level", 0, 130, getWidth(), 20, juce::Justification::centredTop);

    juce::Rectangle<float> area(25, 25, 150, 150);
    g.setColour(juce::Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    oscMenu.setBounds(50, 50, 100, 20);
    osc2Menu.setBounds(50,100,100,20);
    osc2Level.setBounds(50, 140, 100, 20);


}


void Oscillator::comboBoxChanged(juce::ComboBox* box) 
{

}
