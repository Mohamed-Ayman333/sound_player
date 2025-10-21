#include "PlayerAudio.h"


void playerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void playerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void playerAudio::releaseResources()
{
    transportSource.releaseResources();
}

playerAudio::playerAudio() {
    formatManager.registerBasicFormats();
    volume = 50;
    
}
void playerAudio::load_track() {
    juce::FileChooser chooser("Select audio files...",
        juce::File{},
        "*.wav;*.mp3");

    fileChooser = std::make_unique<juce::FileChooser>(
        "Select an audio file...",
        juce::File{},
        "*.wav;*.mp3");

    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            if (file.existsAsFile())
            {
                if (auto* reader = formatManager.createReaderFor(file))
                {
                    // ?? Disconnect old source first
                    transportSource.stop();
                    transportSource.setSource(nullptr);
                    readerSource.reset();

                    // Create new reader source
                    readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

                    // Attach safely
                    transportSource.setSource(readerSource.get(),
                        0,
                        nullptr,
                        reader->sampleRate);
                    transportSource.start();
                }
            }
        });
}
void playerAudio::setVolume(Slider* slider) {
   
    transportSource.setGain((float)slider->getValue());
    
    
}
void playerAudio::mute(Slider* slider) {
    if (slider->getValue() == 0) {
        transportSource.setGain(volume);
        slider->setValue(volume);
    }
    else {
        volume = slider->getValue();
        slider->setValue(0);
        setVolume(slider);
        
    }
  
}
void playerAudio::restart() {
    stop();
    transportSource.start();
}
void playerAudio::stop() {
    transportSource.stop();
    transportSource.setPosition(0.0);
}
void playerAudio::loop() {
    if (readerSource->isLooping()) {
        readerSource->setLooping(false);
    }
    else
    {
        readerSource->setLooping(true);
    }
}
void playerAudio::pauseAndPlay() {
    if (transportSource.isPlaying()) {
        transportSource.stop();
    }
    else {
        transportSource.start();
    }
}
void playerAudio::goToStart() {
    transportSource.setPosition(0);
}
void playerAudio::goToEnd() {
    transportSource.setPosition(transportSource.getTotalLength());
}
