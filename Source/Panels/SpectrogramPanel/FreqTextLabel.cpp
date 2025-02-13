/*
  ==============================================================================

    FreqTextLabel.cpp
    Created: 2 Dec 2020 7:53:08pm
    Author:  羽翼深蓝Wings

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FreqTextLabel.h"

//==============================================================================
FreqTextLabel::FreqTextLabel(VerticalLine &v) : verticalLine(v)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    mFrequency = -1;
    addAndMakeVisible(freqLabel);
    freqLabel.setEditable(true);
    setLookAndFeel(&flatButtonLnf);
}

FreqTextLabel::~FreqTextLabel()
{
    setLookAndFeel(nullptr);
}

void FreqTextLabel::paint (juce::Graphics& g)
{
    g.setColour (COLOUR1.withAlpha(0.2f));
    //g.setColour (juce::Colours::white);
    g.fillAll();
    g.setColour (COLOUR1);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    //    g.drawText (static_cast<juce::String>(mFrequency) + " Hz", getLocalBounds(),
    //                juce::Justification::centred, true);   // draw some placeholder text
    
    freqLabel.setBounds(0, 0, getWidth(), getHeight());
    freqLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    freqLabel.setColour(juce::Label::outlineColourId, COLOUR1);
    freqLabel.setColour(juce::Label::outlineWhenEditingColourId, COLOUR1);
    freqLabel.setColour(juce::Label::backgroundWhenEditingColourId, COLOUR7);

    freqLabel.setJustificationType (juce::Justification::centred);
    freqLabel.setFont (juce::Font (14.0f * mScale, juce::Font::plain));
    juce::String freqText;
    freqText = static_cast<juce::String>(mFrequency) + " Hz";
    if (!freqLabel.isBeingEdited())
    {
        freqLabel.setText(freqText, juce::dontSendNotification);
    }
    
    freqLabel.onTextChange = [this]
    {
        mFrequency = freqLabel.getText().getIntValue();
        verticalLine.setValue(mFrequency);
        // trigger silderValueChanged in FreqDividerGroup?
    };
}

void FreqTextLabel::resized()
{
    
}

void FreqTextLabel::setFreq(int freq)
{
    mFrequency = freq;
}

int FreqTextLabel::getFreq()
{
    return mFrequency;
}

void FreqTextLabel::setScale(float scale)
{
    mScale = scale;
}

bool FreqTextLabel::isMouseOverCustom()
{
    return isMouseOver() || freqLabel.isMouseOverOrDragging() || freqLabel.isBeingEdited();
}
