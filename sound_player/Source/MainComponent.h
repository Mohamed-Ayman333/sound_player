#pragma once

#include <JuceHeader.h>
#include"PlayerAudio.h"
#include"PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    
    playerGUI g1;
    MainComponent();
    ~MainComponent() override;

    // Audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)override;
    void releaseResources()override;

    // GUI
    //screen color
    void paint(juce::Graphics& g) override;
    //button Size And Location
    void resized() override;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};