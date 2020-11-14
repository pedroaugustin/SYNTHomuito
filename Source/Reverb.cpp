/*
  ==============================================================================

    Reverb.cpp
    Created: 11 Nov 2020 3:16:46pm
    Author:  preod

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Reverb.h"

//==============================================================================
Reverb::Reverb(SynthoAudioProcessor& p): audioProcessor(p)
{
   
    setSize(300, 200);

    roomsizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    roomsizeSlider.setRange(0.1f, 1.0f);
    roomsizeSlider.setValue(0.6f);
    roomsizeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&roomsizeSlider);
    auto roomsizeAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "ROOMSIZE", roomsizeSlider);

    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dampingSlider.setRange(0.1f, 1.0f);
    dampingSlider.setValue(0.1f);
    dampingSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&dampingSlider);
    auto dampingeAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "DAMPING", dampingSlider);

    wetlevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    wetlevelSlider.setRange(0.1f, 1.0f);
    wetlevelSlider.setValue(0.2f);
    wetlevelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&wetlevelSlider);
    auto wetlevelAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "WETLEVEL", wetlevelSlider);

    drylevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drylevelSlider.setRange(0.1f, 1.0f);
    drylevelSlider.setValue(1.0f);
    drylevelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&drylevelSlider);
    auto drylevelAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "DRYLEVEL", drylevelSlider);

    widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    widthSlider.setRange(0.1f, 1.0f);
    widthSlider.setValue(0.1f);
    widthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 20.0, 10.0);
    addAndMakeVisible(&widthSlider);
    auto widthAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.apvts, "WIDTH", widthSlider);

    addAndMakeVisible(&freezemodeButton);
    auto freezemodeAttachment = new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.apvts, "FREEZEMODE", freezemodeButton);



}

Reverb::~Reverb()
{
}

void Reverb::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(-30, 10, getWidth(), 20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Reverb", titleArea, juce::Justification::centredTop);
    g.drawText("Room", 10, 30, 90, 60 , juce::Justification::centredBottom);
    g.drawText("Damping", 85, 30, 60, 60, juce::Justification::centredBottom);
    g.drawText("Wet", 145, 30, 60, 60, juce::Justification::centredBottom);
    g.drawText("Dry", 25, 105, 60, 60, juce::Justification::centredBottom);
    g.drawText("Width", 85, 105, 60, 60, juce::Justification::centredBottom);
    g.drawText("Freeze", 160, 100, 40, 40, juce::Justification::centredBottom);

    juce::Rectangle<float> area(25, 25, 190, 150);
    g.setColour(juce::Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void Reverb::resized()
{
    roomsizeSlider.setBounds(25, 25, 60, 60);
    dampingSlider.setBounds(85, 25, 60, 60);
    wetlevelSlider.setBounds(145, 25, 60, 60);
    drylevelSlider.setBounds(25, 100, 60, 60);
    widthSlider.setBounds(85, 100, 60, 60);
    freezemodeButton.setBounds(165, 100, 40, 40);

}

