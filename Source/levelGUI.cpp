/*
  ==============================================================================

    levelGUI.cpp
    Created: 10 Nov 2020 2:08:37pm
    Author:  preod

  ==============================================================================
*/

#include <JuceHeader.h>
#include "levelGUI.h"

//==============================================================================
levelGUI::levelGUI(SynthoAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setValue(0.2f);
    levelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    levelSlider.setPopupDisplayEnabled(true, true, this);
    levelSlider.setSkewFactorFromMidPoint(0.25f);
    addAndMakeVisible(&levelSlider);
    auto levelAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "LEVEL", levelSlider);

    detuneSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider.setRange(0.0f, 3000.0f);
    detuneSlider.setValue(0.0f);
    detuneSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    detuneSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&detuneSlider);
    auto detuneAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "DETUNE", detuneSlider);

    voicesBox.addItem("1", 1);
    voicesBox.addItem("2", 2);
    voicesBox.addItem("3", 3);
    voicesBox.addItem("4", 4);
    voicesBox.addItem("5", 5);
    voicesBox.addItem("6", 6);
    voicesBox.addItem("7", 7);
    voicesBox.addItem("8", 8);
    voicesBox.addItem("9", 9);
    voicesBox.addItem("10", 10);
    voicesBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&voicesBox);
    auto voiceNum = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.apvts, "NUMVOICES", voicesBox);

}

levelGUI::~levelGUI()
{
}

void levelGUI::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.drawText("Controls", titleArea, juce::Justification::centredTop);
    g.drawText("Volume", 20, 55, 150, 150 , juce::Justification::centredTop);
    g.drawText("Voices", 20, 105, 150, 150, juce::Justification::centredTop);
    g.drawText("Detune", 50, 120, 80, 50, juce::Justification::centredRight);
    



    juce::Rectangle<float> area(25, 25, 150, 150);
    g.setColour(juce::Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void levelGUI::resized()
{

   levelSlider.setBounds(40, 40 , 120, 20);
   voicesBox.setBounds(55, 80, 80, 20);
   detuneSlider.setBounds(30, 115, 60, 60);

}
