#pragma once
#include <JuceHeader.h>
#include <functional>
using namespace juce;

class playerAudio : public AudioAppComponent{
    
   

public:
    int volume;
    
    AudioFormatManager formatManager;
    AudioThumbnailCache cache{ 5 };
    AudioThumbnail thumbnail{ 256, formatManager, cache };
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    playerAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)override;
    void releaseResources()override;
    void load_track(std::function<void()> onComplete = {});
    void mute(Slider* slider);
    void setVolume(Slider* slider);
    void restart();
    void stop();
    void loop();
    void pauseAndPlay();
    void goToStart();
    void goToEnd();
    void forward();
    void backward();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerAudio)
};