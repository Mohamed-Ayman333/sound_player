#pragma once
#include <JuceHeader.h>
#include <functional>
#include <list>
#include <vector>
#include <map>



using namespace juce;

class playerAudio : public AudioAppComponent, public juce::ChangeBroadcaster {
    
   

public:
    int volume;
    AudioFormatManager formatManager;
    AudioThumbnailCache cache{ 5 };
    AudioThumbnail thumbnail{ 256, formatManager, cache };
    std::unique_ptr<juce::AudioFormatReader> reader;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    std::unique_ptr<juce::FileChooser> fileChooser;
    StringPairArray fileMetadata;
    String meta = "";
    /*std::vector<std::vector<File>>playlists;*/
    std::vector<File>playlist;

    
    
    playerAudio();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)override;
    void releaseResources()override;
    void load_track(std::function<void()> onComplete = {});
    void mute(Slider* slider);
    void setVolume(Slider* slider);
    void restart();
    void stop();
    void pauseAndPlay();
    void goToStart();
    void goToEnd();
    void forward();
    void backward();
    void setPosition(Slider* slider);
	void make_a_playlist();
	void add_to_playlist();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(playerAudio)
};