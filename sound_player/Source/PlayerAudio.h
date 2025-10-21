#pragma once
#include <JuceHeader.h>
using namespace juce;

class playerAudio : public AudioAppComponent{
    
   

public:
    int volume;
    
    
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::FileChooser> fileChooser;
    playerAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)override;
    void releaseResources()override;
    void load_track();
    void mute(Slider* slider);
    void setVolume(Slider* slider);
    void restart();
    void stop();
    void loop();
    void pauseAndPlay();
    void goToStart();
    void goToEnd();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerAudio)
};