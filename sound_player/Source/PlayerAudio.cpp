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
void playerAudio::mute(Slider* slider,int* volume) {
    if ((*slider).getValue()!=0)
    {
        
        (*slider).setValue(0);
       
    }
    else {
        (*slider).setValue(*volume);
        
    }
}

