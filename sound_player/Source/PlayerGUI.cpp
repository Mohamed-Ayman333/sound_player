#include<JuceHeader.h>
#include "PlayerGUI.h"
#include <algorithm>
#include <vector>
#include <string>
#include <random>


using namespace juce;


playerGUI::playerGUI() {

    addAndMakeVisible(file_data);
    file_data.setColour(Label::textColourId, Colours::white);

    //buttons

    loadButton.addListener(this);
    loadButton.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::load_png, BinaryData::load_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::load_png, BinaryData::load_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::load_png, BinaryData::load_pngSize), 1.0f, Colours::transparentBlack);

    addAndMakeVisible(loadButton);

    restartButton.addListener(this);
    restartButton.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::restart_png, BinaryData::restart_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::restart_png, BinaryData::restart_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::restart_png, BinaryData::restart_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(restartButton);

    stopButton.addListener(this);
    stopButton.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::stop_png, BinaryData::stop_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::stop_png, BinaryData::stop_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::stop_png, BinaryData::stop_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(stopButton);

    mute.addListener(this);
    mute.setToggleable(true);
    mute.setClickingTogglesState(true);
    mute.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(mute);

    pauseAndPlay.addListener(this);
    pauseAndPlay.setToggleable(true);
    pauseAndPlay.setClickingTogglesState(true);
    pauseAndPlay.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(pauseAndPlay);

    goToStart.addListener(this);
    goToStart.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::go_to_start_png, BinaryData::go_to_start_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::go_to_start_png, BinaryData::go_to_start_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::go_to_start_png, BinaryData::go_to_start_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(goToStart);

    goToEnd.addListener(this);
    goToEnd.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::go_to_end_png, BinaryData::go_to_end_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::go_to_end_png, BinaryData::go_to_end_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::go_to_end_png, BinaryData::go_to_end_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(goToEnd);

    loop.addListener(this);
    loop.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::looping_png, BinaryData::looping_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::looping_png, BinaryData::looping_pngSize), 1.0f, Colours::transparentBlack,
		ImageCache::getFromMemory(BinaryData::looping_png, BinaryData::looping_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(loop);

    forward.addListener(this);
    forward.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::f_png, BinaryData::f_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::f_png, BinaryData::f_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::f_png, BinaryData::f_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(forward);

    backward.addListener(this);
    backward.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::b_png, BinaryData::b_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::b_png, BinaryData::b_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::b_png, BinaryData::b_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(backward);

    playlists.addListener(this);
    playlists.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::playlist_png, BinaryData::playlist_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::playlist_png, BinaryData::playlist_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::playlist_png, BinaryData::playlist_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(playlists);

    make_a_playlist.addListener(this);
    make_a_playlist.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::plus_png, BinaryData::plus_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::plus_png, BinaryData::plus_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::plus_png, BinaryData::plus_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(make_a_playlist);

    add_to_playlist.addListener(this);
    add_to_playlist.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::add_to_playlist_png, BinaryData::add_to_playlist_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::add_to_playlist_png, BinaryData::add_to_playlist_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::add_to_playlist_png, BinaryData::add_to_playlist_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(add_to_playlist);

    back.addListener(this);
    back.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::back_png, BinaryData::back_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(back);

    next.addListener(this);
    next.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::next_png, BinaryData::next_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::next_png, BinaryData::next_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::next_png, BinaryData::next_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(next);

    markes.addListener(this);
    markes.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::marks_png, BinaryData::marks_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::marks_png, BinaryData::marks_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::marks_png, BinaryData::marks_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(markes);

    shuf.addListener(this);
    pauseAndPlay.setToggleable(true);
    pauseAndPlay.setClickingTogglesState(true);
    shuf.setImages(false, true, true,
        ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack,
        ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack);
    addAndMakeVisible(shuf);



    // sliders

    volumeSlider.setRange(0, 100, 1);
    volumeSlider.setValue(50);
    volumeSlider.addListener(this);
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(volumeSlider);

    speedSlider.setRange(0.1, 4, 0.1);
    speedSlider.setValue(1);
    speedSlider.addListener(this);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    addAndMakeVisible(speedSlider);


    positionSlider.setRange(0, 1, 0.01);
    positionSlider.setValue(P1.transportSource.getCurrentPosition());
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);
    setSize(1000, 1000);
    positionSlider.textFromValueFunction = [this](double value)
        {
            int s = (int)std::round(value);
            int h = s / 3600;
            int mins = (s % 3600) / 60;
            int secs = s % 60;
            return juce::String::formatted("%03d:%02d:%02d", h, mins, secs);
        };
    //wave

    wave.addAndMakeVisible(posetion_marke_ptr);
    addAndMakeVisible(wave);

    file_data.setText("No File Loaded", NotificationType::dontSendNotification);

    //listbox
    play_list.setModel(&playlist_model);
    addAndMakeVisible(play_list);
    play_list.setVisible(false);

    mark_list.setModel(&marklist_model);
    addAndMakeVisible(mark_list);
    mark_list.setVisible(false);






    P1.addChangeListener(this);
    startTimer(50);
}
//button Size And Location
void playerGUI::resized()
{
    file_data.setBounds(20, 10, getWidth() - 40, 30);
    //Button
    //r1
    loadButton.setBounds(20, 60, 60, 40);
    stopButton.setBounds(100, 60, 60, 40);
    goToStart.setBounds(180, 60, 60, 40);
    pauseAndPlay.setBounds(260, 60, 60, 40);
    goToEnd.setBounds(340, 60, 60, 40);
    shuf.setBounds(420, 60, 60, 40);

    //r2
    mute.setBounds(20, 260, 60, 40);
    loop.setBounds(100, 260, 60, 40);
    backward.setBounds(180, 260, 60, 40);
    forward.setBounds(260, 260, 60, 40);
    restartButton.setBounds(340, 260, 60, 40);
    //r3

    playlists.setBounds(20, 560, 60, 40);
    make_a_playlist.setBounds(100, 560, 60, 40);
    add_to_playlist.setBounds(180, 560, 60, 40);
    back.setBounds(260, 560, 60, 40);
    next.setBounds(340, 560, 60, 40);
    markes.setBounds(420, 560, 60, 40);
    //sliders
    positionSlider.setBounds(20, 210, getWidth() - 40, 30);
    volumeSlider.setBounds(getWidth() * 0.4, 320, 200, 200);
    speedSlider.setBounds(50, 320, 30, 200);
    //wave
    wave.setBounds(20, 130, getWidth() - 40, 60);
    wave.posetion_marke.setBounds(0, 0, 1, wave.getHeight());

    /*make_a_playlist.setBounds(20, playlists_panel.getTitleBarHeight(), 150, 25);*/

    //listbox
    play_list.setBounds(20, 620, getWidth() - 40, 200);
    play_list.setRowHeight(20);

    mark_list.setBounds(20, 620, getWidth() - 40, 200);
    mark_list.setRowHeight(20);







}
//screen color
void playerGUI::paint(Graphics& g)
{

    g.setFillType(juce::ColourGradient(juce::Colour::fromRGB(105, 117, 136), getWidth() * 0.5, getHeight() * 0.5, juce::Colour::fromRGB(40, 49, 62), 0, getHeight() - 100, true));
    g.fillAll();


}

void playerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        P1.load_track([this] {
            wave.repaint();

            const double len = P1.transportSource.getLengthInSeconds();
            positionSlider.setRange(0.0, len > 0.0 ? len : 1.0, 0.01);
            positionSlider.setValue(0.0);

            wave.looping_marker[0].position = 0.0;
            wave.looping_marker[1].position = len > 0.0 ? len : 1.0;
            wave.markers.clear();
            this->mark_list.updateContent();

            if (P1.reader && P1.meta.isEmpty())
            {
                P1.meta.clear();
                auto& metadata = P1.reader->metadataValues;
                auto keys = metadata.getAllKeys();
                auto vals = metadata.getAllValues();


                P1.meta += "Name : " + vals[1] + " Artest : " + vals[0];

            }


            file_data.setText(P1.meta, NotificationType::dontSendNotification);
            P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate * speedSlider.getValue());
            P1.transportSource.start();
            file_data.repaint();
            });
        


    }

    if (button == &restartButton)
    {
        //good for now
        P1.restart();
        P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate * speedSlider.getValue());
        P1.transportSource.start();

    }

    if (button == &stopButton)
    {
        //to be edeted
        P1.stop();
    }
    if (button == &mute) {
        P1.mute(&volumeSlider);
        bool isMuted = button->getToggleState();
        if (!isMuted) {

            mute.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack);
        }
        else {
            mute.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack);
        }

    }
    if (button == &pauseAndPlay) {
        P1.pauseAndPlay();
        bool isPlaying = button->getToggleState();
        if (!isPlaying) {
            pauseAndPlay.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack);

        }
        else {
            pauseAndPlay.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack);

        }


    }
    if (button == &goToStart) {
        P1.goToStart();

    }
    if (button == &goToEnd) {
        P1.goToEnd();

    }
    if (button == &loop) {

        PopupMenu loop_menu;
        loop_menu.addItem(1, "loop on song");
        loop_menu.addItem(2, "loop betwean markers");
        loop_menu.addItem(3, "loop on playlist");
        loop_menu.addItem(4, "stop looping");
        loop_menu.showMenuAsync(juce::PopupMenu::Options(),
            [this](int result)
            {

                this->menu_action(result, this);
            });




    }
    if (button == &forward) {
        P1.forward();

    }
    if (button == &backward) {
        P1.backward();

    }
    if (button == &playlists) {
		mark_list.setVisible(false);

        play_list.setVisible(!play_list.isVisible());
    }
    if (button == &make_a_playlist) {

        P1.make_a_playlist();

        

        play_list.updateContent();

    }
    if (button == &add_to_playlist) {

        P1.add_to_playlist();

        

        play_list.updateContent();

    }
    if (button == &back) {

        wave.looping_marker[0].position = 0.0;
        wave.looping_marker[1].position = wave.pPtr->transportSource.getLengthInSeconds();
        markerLoopEnabled = false;
        wave.markers.clear();
        P1.playPreviasInPlaylist();
        P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate* speedSlider.getValue());
        P1.transportSource.start();
        wave.repaint();

    }
    if (button == &next) {

        if (!isShuf) {
            wave.looping_marker[0].position = 0.0;
            wave.looping_marker[1].position = wave.pPtr->transportSource.getLengthInSeconds();
            markerLoopEnabled = false;
            wave.markers.clear();
            P1.playNextInPlaylist();
            P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate * speedSlider.getValue());
            P1.transportSource.start();
            wave.repaint();
        }
        else
        {
            wave.looping_marker[0].position = 0.0;
            wave.looping_marker[1].position = wave.pPtr->transportSource.getLengthInSeconds();
            markerLoopEnabled = false;
            wave.markers.clear();
            std::random_device rd;
            std::mt19937 gen(rd());
            int min_val = 0;
            int max_val = P1.playlist.size() - 1;
            std::uniform_int_distribution<> distrib(min_val, max_val);
            P1.load_track_from_file(distrib(gen));
            P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate* speedSlider.getValue());
            P1.transportSource.start();
            wave.repaint();
        }
    }
    if (button == &markes) {
        play_list.setVisible(false);
		mark_list.setVisible(!mark_list.isVisible());
	}
    if(button == &shuf) {
		isShuf = !isShuf;
        if (isShuf) {
            shuf.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::s_png, BinaryData::s_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::s_png, BinaryData::s_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::s_png, BinaryData::s_pngSize), 1.0f, Colours::transparentBlack);
        }
        else {
            shuf.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::ns_png, BinaryData::ns_pngSize), 1.0f, Colours::transparentBlack);
        }
        
	}

}

void playerGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider) {
        P1.setVolume(slider);
        if (slider->getValue() == 0.0) {

            mute.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::mute_png, BinaryData::mute_pngSize), 1.0f, Colours::transparentBlack);
        }
        else {
            mute.setImages(false, true, true,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack,
                ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize), 1.0f, Colours::transparentBlack);
        }
    }
    if (slider == &positionSlider) {
        P1.setPosition(slider);
    }
    if (slider == &speedSlider) {
        P1.speed(slider);
    }
}

void playerGUI::timerCallback() {

    if (!P1.transportSource.isPlaying()) {
        pauseAndPlay.setToggleState(true, juce::dontSendNotification);
        pauseAndPlay.setImages(false, true, true,
            ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize), 1.0f, Colours::transparentBlack);
        pauseAndPlay.repaint();
    }
    else {
        pauseAndPlay.setToggleState(false, juce::dontSendNotification);
        pauseAndPlay.setImages(false, true, true,
            ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack,
            ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize), 1.0f, Colours::transparentBlack);
        pauseAndPlay.repaint();
    }


    positionSlider.setValue(P1.transportSource.getCurrentPosition(), dontSendNotification);

    const int w = wave.getWidth();
    const double length = P1.transportSource.getLengthInSeconds();

    if (w > 0 && length > 0.0)
    {
        int x = (int)std::round((P1.transportSource.getCurrentPosition() / length) * (double)w);
        x = jlimit(0, w - 1, x);
        posetion_marke_ptr->setBounds(x, 0, 2, wave.getHeight());
        posetion_marke_ptr->repaint();
    }


    bool isPlayingNow = P1.transportSource.isPlaying();
    double currentPos = P1.transportSource.getCurrentPosition();
    double totalLen = P1.transportSource.getLengthInSeconds();

    if (!markerLoopEnabled)
        return;
    else {
        const double pos = P1.transportSource.getCurrentPosition();
        const double loopStart = wave.looping_marker[0].position;
        const double loopEnd = wave.looping_marker[1].position;

        const double eps = 1e-6;
        if (loopEnd > loopStart + eps && pos >= loopEnd - eps)
        {
            P1.transportSource.setPosition(loopStart);
            P1.transportSource.start();
        }
        if (loopEnd > loopStart + eps && pos <= loopStart - eps)
        {
            P1.transportSource.setPosition(loopStart);
            P1.transportSource.start();
        }
    }
    if (wasPlayingLastTick && !isPlayingNow && totalLen > 0.0)
    {

        if (currentPos < 0.2 || currentPos >= totalLen - 0.2)
        {
            if (!isShuf) {
                P1.playNextInPlaylist();
            }
            else
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                int min_val = 0;
                int max_val = P1.playlist.size() - 1;
                std::uniform_int_distribution<> distrib(min_val, max_val);
                P1.load_track_from_file(distrib(gen));
            }
            if (P1.reader)
            {
                const double len = P1.transportSource.getLengthInSeconds();
                positionSlider.setRange(0.0, len > 0.0 ? len : 1.0, 0.01);
                positionSlider.setValue(0.0);
                wave.markers.clear();
                wave.looping_marker[0].position = 0.0;
                wave.looping_marker[1].position = len > 0.0 ? len : 1.0;
                wave.repaint();
                P1.transportSource.setSource(P1.readerSource.get(), 0, nullptr, P1.reader->sampleRate * speedSlider.getValue());
                P1.transportSource.start();
                file_data.setText(P1.meta, NotificationType::dontSendNotification);
            }
        }
    }

    wasPlayingLastTick = isPlayingNow;





}

void playerGUI::changeListenerCallback(juce::ChangeBroadcaster* source) {
    if (source == &P1) {
        play_list.updateContent();
        play_list.repaint();

        wave.repaint();
    }
}

void playerGUI::menu_action(int result, playerGUI* gui) {

    if (result == 1) {
        gui->P1.readerSource->setLooping(true);
        gui->markerLoopEnabled = false;
        gui->P1.looping_on_song = true;
        wave.repaint();

    }
    if (result == 2) {
        gui->P1.readerSource->setLooping(false);
        gui->markerLoopEnabled = true;
        gui->P1.looping_on_song = false;
        wave.repaint();

    }
    if (result == 3) {
        gui->P1.loopPlaylist = true;
        gui->P1.readerSource->setLooping(false);
        gui->markerLoopEnabled = false;
        gui->P1.looping_on_song = false;
    }
    if (result == 4) {
        gui->P1.readerSource->setLooping(false);
        gui->markerLoopEnabled = false;
        gui->P1.loopPlaylist = false;
        gui->P1.looping_on_song = false;
        wave.repaint();
    }
}

waver::waver(playerAudio* P1, playerGUI* gui) {

    pPtr = P1;
    if (pPtr)
        pPtr->thumbnail.addChangeListener(this);
    guiptr = gui;

}

void waver::paint(Graphics& g) {
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::orange);

    if (pPtr != nullptr && pPtr->thumbnail.getNumChannels() > 0)
    {
        r = getLocalBounds();
        const double totalLength = pPtr->thumbnail.getTotalLength();
        pPtr->thumbnail.drawChannels(g, r, 0.0, totalLength > 0.0 ? totalLength : 1.0, 0.8);


        const double start = looping_marker[0].position;
        const double end = looping_marker[1].position;
        if (totalLength > 0.0 && end > start && guiptr->markerLoopEnabled == true)
        {
            const int x0 = (int)std::round((start / totalLength) * (double)r.getWidth());
            const int x1 = (int)std::round((end / totalLength) * (double)r.getWidth());


            const int width = jmax(1, x1 - x0);
            g.setColour(juce::Colours::green.withAlpha(0.25f));
            g.fillRect(r.getX() + x0, r.getY(), width, r.getHeight());
            g.setColour(juce::Colours::green);
            g.drawRect(r.getX() + x0, r.getY(), width, r.getHeight(), 1);

        }
    }


}

void waver::mouseDown(const MouseEvent& event)
{
    if (pPtr == nullptr)
        return;

    const int w = getWidth();
    if (w <= 0)
        return;

    const double total = pPtr->thumbnail.getTotalLength();
    if (total <= 0.0)
        return;

    const int x = jlimit(0, w - 1, event.getPosition().x);
    const double newPositionSeconds = (double)x / (double)w * total;
    if (event.mods.isLeftButtonDown()) {
        pPtr->transportSource.setPosition(newPositionSeconds);


        if (auto* parentGui = dynamic_cast<playerGUI*>(getParentComponent()))
        {

            posetion_marke.setBounds(x - 2, 0, 5, getHeight());
            posetion_marke.repaint();
        }
    }
    if (event.mods.isRightButtonDown()) {

        std::make_unique<marker>(newPositionSeconds);
        markers.push_back(std::make_unique<marker>(newPositionSeconds));
        this->addAndMakeVisible(&*(markers.back()));
        markers.back()->setBounds(jlimit(0, getWidth() - 1, x - 1), 0, 5, getHeight());
		guiptr->mark_list.updateContent();

    }
    repaint();
}

void waver::mouseDrag(const MouseEvent& event)
{

    if (pPtr == nullptr)
        return;

    const int w = getWidth();
    if (w <= 0)
        return;

    const double total = pPtr->thumbnail.getTotalLength();
    if (total <= 0.0)
        return;

    int x = event.getPosition().x;
    x = jlimit(0, w - 1, x);
    const double newPositionSeconds = (double)x / (double)w * total;

    pPtr->transportSource.setPosition(newPositionSeconds);
    pPtr->transportSource.start();

    if (auto* parentGui = dynamic_cast<playerGUI*>(getParentComponent()))
    {

        parentGui->posetion_marke_ptr->setBounds(x - 2, 0, 5, getHeight());
        parentGui->posetion_marke_ptr->repaint();
    }
    repaint();
}


void waver::changeListenerCallback(ChangeBroadcaster* source)
{
    MessageManager::callAsync([this] {

        if (pPtr && pPtr->reader)
        {
            const double len = pPtr->transportSource.getLengthInSeconds();


            if (looping_marker[1].position == 0.0 || looping_marker[1].position == pPtr->transportSource.getLengthInSeconds())
            {
                looping_marker[0].position = 0.0;
                looping_marker[1].position = len > 0.0 ? len : 1.0;
            }
        }

        repaint();
        });
}

waver::~waver()
{
    if (pPtr)
        pPtr->thumbnail.removeChangeListener(this);
}

marker::marker(double pos) {

    position = pos;
}

void marker::paint(Graphics& g) {
    g.fillAll(juce::Colours::red);
}

void marker::mouseDown(const MouseEvent& event)
{
    if (event.mods.isLeftButtonDown()) {
        waver* parentWaver = dynamic_cast<waver*>(getParentComponent());
        if (parentWaver && parentWaver->pPtr) {
            parentWaver->pPtr->transportSource.setPosition(position);
        }
    }
    if (event.mods.isRightButtonDown()) {
        auto* parentWaver = dynamic_cast<waver*>(getParentComponent());
        if (this != &(parentWaver->posetion_marke)) {
            PopupMenu menu;
            menu.addSeparator();
            menu.addItem(1, "Make it a looping start");
            menu.addItem(2, "Make it a looping end");
            menu.addItem(3, "remove from looping");
            menu.addItem(4, "Delete Marker");

            menu.showMenuAsync(juce::PopupMenu::Options(),
                [this](int result)
                {

                    this->menu_action(result, dynamic_cast<waver*>(getParentComponent()));
                });


        }

    }

}

void marker::menu_action(int option, waver* parentWaver)
{
    if (option == 1)
    {
        if (parentWaver && parentWaver->pPtr)
        {
            if (position >= parentWaver->looping_marker[0].position && position <= parentWaver->looping_marker[1].position)
                parentWaver->looping_marker[0].position = position;

            parentWaver->repaint();

        }
    }
    if (option == 2)
    {
        if (parentWaver && parentWaver->pPtr)
        {
            if (position >= parentWaver->looping_marker[0].position && position <= parentWaver->looping_marker[1].position)
                parentWaver->looping_marker[1].position = position;


            parentWaver->repaint();

        }
    }
    if (option == 3)
    {
        if (parentWaver && parentWaver->pPtr)
        {
            if (this->position == parentWaver->looping_marker[0].position)
                parentWaver->looping_marker[0].position = 0.0;
            if (this->position == parentWaver->looping_marker[1].position)
                parentWaver->looping_marker[1].position = parentWaver->pPtr->transportSource.getLengthInSeconds();
            parentWaver->repaint();
        }
    }

    if (option == 4)
    {
        if (parentWaver)
        {
            if (this->position == parentWaver->looping_marker[0].position)
                parentWaver->looping_marker[0].position = 0.0;
            if (this->position == parentWaver->looping_marker[1].position)
                parentWaver->looping_marker[1].position = parentWaver->pPtr->transportSource.getLengthInSeconds();

            parentWaver->removeChildComponent(this);
            parentWaver->markers.erase(std::remove_if(parentWaver->markers.begin(), parentWaver->markers.end(),
				[this](const std::unique_ptr<marker>& m) { return m.get() == this; }), parentWaver->markers.end());
			parentWaver->guiptr->mark_list.updateContent();
            parentWaver->repaint();
        }
    }
}

playlistModel::playlistModel(playerAudio* P1, playerGUI* gui) {
    pPtr = P1;
    guiptr = gui;
}

int playlistModel::getNumRows() {

    if (pPtr == nullptr)
        return 0;


    return pPtr->playlist.size();

}

void playlistModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else
        g.fillAll(juce::Colours::darkgrey);

    if (pPtr == nullptr || rowNumber < 0 || rowNumber >= pPtr->playlist.size())
        return;

    g.setColour(juce::Colours::white);
    juce::String fileName = pPtr->playlist[rowNumber].getFileNameWithoutExtension();

    
    g.drawText(fileName, 10, 0, width - 20, height, juce::Justification::centredLeft, true);
}

void playlistModel::listBoxItemClicked(int row, const MouseEvent& e) {
    if (row < 0 || row >= getNumRows())
        return;
    if (e.mods.isLeftButtonDown()) {
        if (pPtr) {
            pPtr->transportSource.setPosition(0.0);
            pPtr->load_track_from_file(row);
            pPtr->transportSource.start();

            guiptr->wave.looping_marker[0].position = 0.0;
            guiptr->wave.looping_marker[1].position = guiptr->wave.pPtr->transportSource.getLengthInSeconds();
            guiptr->markerLoopEnabled = false;
            guiptr->wave.markers.clear();


            const double len = pPtr->transportSource.getLengthInSeconds();
            guiptr->positionSlider.setRange(0.0, len > 0.0 ? len : 1.0, 0.01);
            guiptr->positionSlider.setValue(0.0);




            if (pPtr->reader && pPtr->meta.isEmpty())
            {
                pPtr->meta.clear();
                auto& metadata = pPtr->reader->metadataValues;
                auto keys = metadata.getAllKeys();
                auto vals = metadata.getAllValues();


                pPtr->meta += "Name : " + vals[1] + " Artest : " + vals[0];

            }


            guiptr->file_data.setText(pPtr->meta, NotificationType::dontSendNotification);
            pPtr->transportSource.setSource(pPtr->readerSource.get(), 0, nullptr, pPtr->reader->sampleRate * guiptr->speedSlider.getValue());
            pPtr->transportSource.start();
            guiptr->file_data.repaint();
        }
    }
    if (e.mods.isRightButtonDown()) {
        if (row < 0 || row >= static_cast<int>(pPtr->playlist.size())) return;

        pPtr->playlist.erase(pPtr->playlist.begin() + row);
		guiptr->play_list.updateContent();
    }
}

marklistModel::marklistModel(playerAudio* P1, playerGUI* gui) {
	pPtr = P1;
	guiptr = gui;
}

int marklistModel::getNumRows() {
    if (pPtr == nullptr)
        return 0;
    return guiptr->wave.markers.size();
}

void marklistModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else
        g.fillAll(juce::Colours::darkgrey);
    if (pPtr == nullptr || rowNumber < 0 || rowNumber >= guiptr->wave.markers.size())
        return;
    g.setColour(juce::Colours::white);
	
    int s = (int)std::round(guiptr->wave.markers[rowNumber]->position);
    int h = s / 3600;
    int mins = (s % 3600) / 60;
    int secs = s % 60;
    juce::String markPos = juce::String::formatted("Marker at : % 03d: % 02d : % 02d", h,mins,secs);
    
    g.drawText(markPos, 10, 0, width - 20, height, juce::Justification::centredLeft, true);
}

void marklistModel::listBoxItemClicked(int row, const MouseEvent& e) {
    if (row < 0 || row >= getNumRows())
        return;
    if (e.mods.isLeftButtonDown()) {
        if (pPtr) {
            pPtr->transportSource.setPosition(guiptr->wave.markers[row]->position);
            pPtr->transportSource.start();
        }
    }
    if (e.mods.isRightButtonDown()) {
        PopupMenu menu;
        menu.addSeparator();
        menu.addItem(1, "Make it a looping start");
        menu.addItem(2, "Make it a looping end");
        menu.addItem(3, "remove from looping");
        menu.addItem(4, "Delete Marker");
        menu.showMenuAsync(juce::PopupMenu::Options(),
            [this, row](int result)
            {
                this->menu_action(result, row);
            });
    }
}

void marklistModel::menu_action(int option, int row)
{
    if (option == 1)
    {
        if (pPtr && guiptr)
        {
            if (guiptr->wave.markers[row]->position >= guiptr->wave.looping_marker[0].position && guiptr->wave.markers[row]->position <= guiptr->wave.looping_marker[1].position)
                guiptr->wave.looping_marker[0].position = guiptr->wave.markers[row]->position;
            guiptr->wave.repaint();
        }
    }
    if (option == 2)
    {
        if (pPtr && guiptr)
        {
            if (guiptr->wave.markers[row]->position >= guiptr->wave.looping_marker[0].position && guiptr->wave.markers[row]->position <= guiptr->wave.looping_marker[1].position)
				guiptr->wave.looping_marker[1].position = guiptr->wave.markers[row]->position;
            guiptr->wave.repaint();
        }
	}
    if (option == 3)
    {
        if (pPtr && guiptr)
        {
            if (guiptr->wave.markers[row]->position == guiptr->wave.looping_marker[0].position)
                guiptr->wave.looping_marker[0].position = 0.0;
            if (guiptr->wave.markers[row]->position == guiptr->wave.looping_marker[1].position)
                guiptr->wave.looping_marker[1].position = pPtr->transportSource.getLengthInSeconds();
            guiptr->wave.repaint();
        }
    }
    if (option == 4)
    {
        if (pPtr && guiptr)
        {
            if (guiptr->wave.markers[row]->position == guiptr->wave.looping_marker[0].position)
                guiptr->wave.looping_marker[0].position = 0.0;
            if (guiptr->wave.markers[row]->position == guiptr->wave.looping_marker[1].position)
                guiptr->wave.looping_marker[1].position = pPtr->transportSource.getLengthInSeconds();
            guiptr->wave.removeChildComponent(guiptr->wave.markers[row].get());
            guiptr->wave.markers.erase(guiptr->wave.markers.begin() + row);
            guiptr->wave.repaint();
			guiptr->mark_list.updateContent();
        }
	}
}
