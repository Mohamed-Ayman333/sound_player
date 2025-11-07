#include "PlayerAudio.h"
#include <algorithm>
#include <string>
#include <fileref.h>
#include <tag.h>

using namespace juce;

playerAudio::playerAudio() {
    formatManager.registerBasicFormats();
    volume = 50;

}

void playerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

// PlayerAudio.cpp

void playerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);

    
    if (readerSource != nullptr && !looping_on_song)
    {
        double trackLength = transportSource.getLengthInSeconds();
        double currentPosition = transportSource.getCurrentPosition();

        
        if (trackLength > 0.0 && currentPosition >= trackLength - 0.1)
        {
            
            playNextInPlaylist();

            
        }
    }
}
void playerAudio::releaseResources()
{
    transportSource.releaseResources();
}

void playerAudio::load_track(std::function<void()> onComplete)
{
    fileChooser = std::make_unique<juce::FileChooser>(
        "Select an audio file...",
        juce::File{},
        "*.wav;*.mp3");

    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this, onComplete](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();
            if (file.existsAsFile())
            {
                if (auto* rawReader = formatManager.createReaderFor(file))
                {
                    // stop and clear old sources
                    transportSource.stop();
                    transportSource.setSource(nullptr);
                    readerSource.reset();


                    reader.reset(rawReader);

                    {




                        const std::string pathUtf8 = file.getFullPathName().toStdString();
                        TagLib::FileRef f(pathUtf8.c_str());


                        if (!f.isNull() && f.tag())
                        {
                            meta.clear();

                            TagLib::Tag* t = f.tag();


                            if (t->title().length())   meta += "Title: " + String(t->title().toCString(true)) + "  ";
                            if (t->artist().length())  meta += "Artist: " + String(t->artist().toCString(true)) + "  ";
                            if (t->album().length())   meta += "Album: " + String(t->album().toCString(true)) + "  ";
                            if (t->year())             meta += "Year: " + String((int)t->year()) + "  ";
                            if (t->comment().length()) meta += "Comment: " + String(t->comment().toCString(true)) + "  ";
                            if (t->genre().length())   meta += "Genre: " + String(t->genre().toCString(true)) + "  ";

                        }
                        else
                        {
                            meta = file.getFileName();
                        }

                        String name = file.getFileName();

                        if (name.contains(".wav")) {
                            meta.clear();
                        }


                    }



                    readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader.get(), false);

                    // attach readerSource
                    transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
                    transportSource.start();

                    thumbnail.clear();
                    thumbnail.setSource(new juce::FileInputSource(file));

                    if (onComplete)
                        juce::MessageManager::callAsync(onComplete);
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
void playerAudio::forward() {
    transportSource.setPosition(std::min(transportSource.getCurrentPosition() + 10.0, transportSource.getLengthInSeconds()));
}
void playerAudio::backward() {
    transportSource.setPosition(std::max(transportSource.getCurrentPosition() - 10.0, 0.0));
}
void playerAudio::setPosition(Slider* slider) {
    transportSource.setPosition(slider->getValue());
}
void playerAudio::make_a_playlist() {

    fileChooser = std::make_unique<juce::FileChooser>(
        "Select audio files for playlist...",
        juce::File{},
        "*.wav;*.mp3");
    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,
        [this](const juce::FileChooser& fc)
        {
            std::vector<File>new_playlist;
            auto files = fc.getResults();
            for (auto& file : files) {

                if (file.existsAsFile()) {
                    new_playlist.push_back(file);
                }
            }
            if (!new_playlist.empty()) {

                playlist = new_playlist;
                playlist_index = 0;
                load_track_from_file(0);

                sendChangeMessage();
            }
        });
}
void playerAudio::add_to_playlist() {
    fileChooser = std::make_unique<juce::FileChooser>(
        "Select audio files to add to playlist...",
        juce::File{},
        "*.wav;*.mp3");
    fileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,
        [this](const juce::FileChooser& fc)
        {
            auto files = fc.getResults();
            for (auto& file : files) {
                if (file.existsAsFile()) {
                    playlist.push_back(file);
                }
            }
            sendChangeMessage();
        });
}
void playerAudio::load_track_from_file(int row) {
    if (row < 0 || row >= static_cast<int>(playlist.size()))
        return;
    playlist_index = row;
    File file = playlist[row];
    if (file.existsAsFile())
    {
        if (auto* rawReader = formatManager.createReaderFor(file))
        {
            // stop and clear old sources
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();
            reader.reset(rawReader);

            {




                const std::string pathUtf8 = file.getFullPathName().toStdString();
                TagLib::FileRef f(pathUtf8.c_str());


                if (!f.isNull() && f.tag())
                {
                    meta.clear();

                    TagLib::Tag* t = f.tag();


                    if (t->title().length())   meta += "Title: " + String(t->title().toCString(true)) + "  ";
                    if (t->artist().length())  meta += "Artist: " + String(t->artist().toCString(true)) + "  ";
                    if (t->album().length())   meta += "Album: " + String(t->album().toCString(true)) + "  ";
                    if (t->year())             meta += "Year: " + String((int)t->year()) + "  ";
                    if (t->comment().length()) meta += "Comment: " + String(t->comment().toCString(true)) + "  ";
                    if (t->genre().length())   meta += "Genre: " + String(t->genre().toCString(true)) + "  ";

                }
                else
                {
                    meta = file.getFileName();
                }

                String name = file.getFileName();

                if (name.contains(".wav")) {
                    meta.clear();
                }


            }



            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader.get(), false);

            transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
            transportSource.start();
            

            thumbnail.clear();
            thumbnail.setSource(new juce::FileInputSource(file));
            sendChangeMessage();

        }
    }
}
void playerAudio::playNextInPlaylist()
{
    if (playlist.empty())
        return;


    playlist_index++;
    if (playlist_index >= static_cast<int>(playlist.size()))
    {
        if (loopPlaylist)
            playlist_index = 0;
        else {
            

            return;
        }
        
    }

    load_track_from_file(playlist_index);
    {




        const std::string pathUtf8 = playlist[playlist_index].getFullPathName().toStdString();
        TagLib::FileRef f(pathUtf8.c_str());


        if (!f.isNull() && f.tag())
        {
            meta.clear();

            TagLib::Tag* t = f.tag();


            if (t->title().length())   meta += "Title: " + String(t->title().toCString(true)) + "  ";
            if (t->artist().length())  meta += "Artist: " + String(t->artist().toCString(true)) + "  ";
            if (t->album().length())   meta += "Album: " + String(t->album().toCString(true)) + "  ";
            if (t->year())             meta += "Year: " + String((int)t->year()) + "  ";
            if (t->comment().length()) meta += "Comment: " + String(t->comment().toCString(true)) + "  ";
            if (t->genre().length())   meta += "Genre: " + String(t->genre().toCString(true)) + "  ";
            //file_data.setText(meta, NotificationType::dontSendNotification);
        }
        else
        {
            meta = playlist[playlist_index].getFileName();
            //file_data.setText(P1.meta, NotificationType::dontSendNotification);
        }

        String name = playlist[playlist_index].getFileName();

        if (name.contains(".wav")) {
            meta.clear();
        }
        
        if (reader && meta.isEmpty())
        {
            meta.clear();
            auto& metadata = reader->metadataValues;
            
            auto keys = metadata.getAllKeys();
            auto vals = metadata.getAllValues();

            
            if (vals.size() >= 2)
            {
                meta += "Name : " + vals[1] + " Artest : " + vals[0];
            }
            else
            {
                
                meta = "File metadata not fully available.";
            }
        }
        

    }
}
void playerAudio::playPreviasInPlaylist()
{
    if (playlist.empty())
        return;

    playlist_index--;
    if (playlist_index < 0)
    {
        if (loopPlaylist)
            playlist_index = static_cast<int>(playlist.size()) - 1;
        else
            return;
    }
    load_track_from_file(playlist_index);
}
void playerAudio::speed(Slider* slider) {
    if (readerSource != nullptr) {
        double pos = transportSource.getCurrentPosition();
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate * slider->getValue());
        transportSource.setPosition(pos);
        transportSource.start();
        sendChangeMessage();

    }
}

