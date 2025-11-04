#include<JuceHeader.h>
#include "PlayerGUI.h"
#include <algorithm>
#include <vector>
#include <string>


using namespace juce;


playerGUI::playerGUI(){
    
    addAndMakeVisible(file_data);
    file_data.setColour(Label::textColourId, Colours::white);
   
    //buttons
    
    loadButton.addListener(this);
    addAndMakeVisible(loadButton);
    
    restartButton.addListener(this);
    addAndMakeVisible(restartButton);

    stopButton.addListener(this);
    addAndMakeVisible(stopButton);

    mute.addListener(this);
    addAndMakeVisible(mute);

    pauseAndPlay.addListener(this);
    addAndMakeVisible(pauseAndPlay);

    goToStart.addListener(this);
    addAndMakeVisible(goToStart);

    goToEnd.addListener(this);
    addAndMakeVisible(goToEnd);

    loop.addListener(this);
    addAndMakeVisible(loop);

    forward.addListener(this);
    addAndMakeVisible(forward);

    backward.addListener(this);
    addAndMakeVisible(backward);

    playlists.addListener(this);
    addAndMakeVisible(playlists);

    make_a_playlist.addListener(this);
    addAndMakeVisible(make_a_playlist);

    add_to_playlist.addListener(this);
    addAndMakeVisible(add_to_playlist);

    back.addListener(this);
    addAndMakeVisible(back);

    next.addListener(this);
    addAndMakeVisible(next);

    

    // sliders
   
    volumeSlider.setRange(0, 100, 1);
    volumeSlider.setValue(50);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    

    positionSlider.setRange(0, 1 ,0.01);
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
        return juce::String::formatted("%03d:%02d:%02d",h, mins, secs);
    };
    //wave

    wave.addAndMakeVisible(posetion_marke_ptr);
    addAndMakeVisible(wave);
	
	file_data.setText("No File Loaded", NotificationType::dontSendNotification);

	//listbox
    play_list.setModel(&playlist_model);
    addAndMakeVisible(play_list);






	
    P1.addChangeListener(this);
    startTimer(1000/30);
}
//button Size And Location
void playerGUI::resized()
{
	file_data.setBounds(20, 10, getWidth() - 40, 30);
    //Button
    //r1
    loadButton.setBounds(20, 60, 100, 40);
    restartButton.setBounds(140, 60, 80, 40);
    stopButton.setBounds(240, 60, 80, 40);
    mute.setBounds(340, 60, 80, 40);
    //r2
    pauseAndPlay.setBounds(20, 180, 100, 40);
    goToStart.setBounds(140, 180, 80, 40);
    goToEnd.setBounds(240, 180, 80, 40);
    loop.setBounds(340, 180, 80, 40);
    //r3
    backward.setBounds(20, 300, 80, 40);
    forward.setBounds(140, 300, 80, 40);
    playlists.setBounds(240, 300, 80, 40);
	make_a_playlist.setBounds(340, 300, 80, 40);
    add_to_playlist.setBounds(440, 300, 80, 40);
    back.setBounds(540, 300, 80, 40);
    next.setBounds(640, 300, 80, 40);
    //sliders
    volumeSlider.setBounds(20, 140, getWidth() - 40, 30);
    positionSlider.setBounds(20, 480, getWidth() - 40, 30);
    //wave
    wave.setBounds(20, 380, getWidth() - 40, 60);
	wave.posetion_marke.setBounds(0, 0, 1, wave.getHeight());
   
	/*make_a_playlist.setBounds(20, playlists_panel.getTitleBarHeight(), 150, 25);*/
    
    //listbox
    play_list.setBounds(20,520,960,200);
	play_list.setRowHeight(20);
    

    
    


    
}
//screen color
void playerGUI::paint(Graphics& g)
{
    
    g.fillAll(juce::Colours::black);
    
    
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

            
            if (P1.reader&&P1.meta.isEmpty())
            {
                P1.meta.clear();
                auto& metadata = P1.reader->metadataValues;
                auto keys = metadata.getAllKeys();
                auto vals = metadata.getAllValues();
                
                   
                    P1.meta += "Name : " + vals[1] + " Artest : "+ vals[0];
                
            }
            

            file_data.setText(P1.meta, NotificationType::dontSendNotification);
			file_data.repaint();
        });

    }

    if (button == &restartButton)
    {
        //good for now
        P1.restart();
        
    }

    if (button == &stopButton)
    {
        //to be edeted
        P1.stop();
    }
    if (button == &mute) {
        P1.mute(&volumeSlider);

    }
    if (button == &pauseAndPlay) {
        P1.pauseAndPlay();

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

                this->menu_action(result,this);
            });


		

    }
    if (button == &forward) {
        P1.forward();

    }
    if (button == &backward) {
        P1.backward();

    }
    if (button == &playlists) {

		play_list.setVisible(!play_list.isVisible());
    }
    if (button == &make_a_playlist) {

        P1.make_a_playlist();
  
        for (auto& item : P1.playlist)
              playlist_model.items.push_back(item.getFileName());
        
		play_list.updateContent();

    }
    if (button == &add_to_playlist) {

        P1.add_to_playlist();
  
        for (auto& item : P1.playlist)
              playlist_model.items.push_back(item.getFileName());
        
		play_list.updateContent();

    }
    if (button == &back) {
        
		P1.playPreviasInPlaylist();
    }
    if (button == &next) {
        
        P1.playNextInPlaylist();
    }

}

void playerGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volumeSlider) {
        P1.setVolume(slider);
    }
    if (slider == &positionSlider) {
        P1.setPosition(slider);
    }
}

void playerGUI::timerCallback() {
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

    if (wasPlayingLastTick && !isPlayingNow && totalLen > 0.0)
    {

        if (currentPos < 0.2 || currentPos >= totalLen - 0.2)
        {
            P1.playNextInPlaylist();

            if (P1.reader)
            {
                const double len = P1.transportSource.getLengthInSeconds();
                positionSlider.setRange(0.0, len > 0.0 ? len : 1.0, 0.01);
                positionSlider.setValue(0.0);
                wave.looping_marker[0].position = 0.0;
                wave.looping_marker[1].position = len > 0.0 ? len : 1.0;
                wave.markers.clear();
                wave.repaint();
                file_data.setText(P1.meta, NotificationType::dontSendNotification);
            }
        }
    }

    wasPlayingLastTick = isPlayingNow;

    if (!markerLoopEnabled)
        return;

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

void playerGUI::changeListenerCallback(juce::ChangeBroadcaster* source) {
    if (source == &P1) {
        play_list.updateContent();
		play_list.repaint();
		
        play_list.repaintRow(0);
    }
}

void playerGUI::menu_action(int result, playerGUI* gui) {

    if (result == 1) {
        gui->P1.readerSource->setLooping(true);
        gui->markerLoopEnabled = false;
        
    }
    if (result == 2) {
        gui->P1.readerSource->setLooping(false);
        gui->markerLoopEnabled = true;
        
    }
    if (result == 3) {
        gui->P1.loopPlaylist = true;
        
    }
    if (result == 4) {
		gui->P1.readerSource->setLooping(false);
        gui->markerLoopEnabled = false;
        gui->P1.loopPlaylist = false;
	}
}

waver::waver(playerAudio* P1) {

    pPtr = P1;
    if (pPtr)
        pPtr->thumbnail.addChangeListener(this);

};

void waver::paint(Graphics& g) {
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::orange);

    if (pPtr != nullptr && pPtr->thumbnail.getNumChannels() > 0)
    {
        r = getLocalBounds();
        const double totalLength = pPtr->thumbnail.getTotalLength();
        pPtr->thumbnail.drawChannels(g, r, 0.0, totalLength > 0.0 ? totalLength : 1.0, 0.8);

        
        const double start = looping_marker[0].position;
        const double end   = looping_marker[1].position;
        if (totalLength > 0.0 && end > start)
        {
            const int x0 = (int) std::round((start / totalLength) * (double) r.getWidth());
            const int x1 = (int) std::round((end   / totalLength) * (double) r.getWidth());
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
    const double newPositionSeconds = (double) x / (double) w * total;

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

    MessageManager::callAsync([this] { repaint(); });
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
            if(position>=parentWaver->looping_marker[0].position&& position <= parentWaver->looping_marker[1].position)
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
            if(this->position== parentWaver->looping_marker[0].position)
				parentWaver->looping_marker[0].position = 0.0;
            if (this->position == parentWaver->looping_marker[1].position)
				parentWaver->looping_marker[1].position = parentWaver->pPtr->transportSource.getLengthInSeconds();
            
            parentWaver->removeChildComponent(this);

			parentWaver->repaint();
        }
    }
}

listModel::listModel(playerAudio* P1,playerGUI*gui) {
    pPtr = P1;
    guiptr = gui;
}

int listModel::getNumRows() {
    
        if (pPtr == nullptr)
            return 0;

        
        return pPtr->playlist.size();
    
}

void listModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else
        g.fillAll(juce::Colours::darkgrey);

    if (pPtr == nullptr || rowNumber < 0 || rowNumber >= pPtr->playlist.size())
        return;

    g.setColour(juce::Colours::white);
    juce::String fileName = pPtr->playlist[rowNumber].getFileNameWithoutExtension();

    // Draw centered vertically in the row
    g.drawText(fileName, 10, 0, width - 20, height, juce::Justification::centredLeft, true);
}

void listModel::listBoxItemClicked(int row, const MouseEvent& e) {
    if(row < 0 || row >= getNumRows())
		return;
    if (e.mods.isLeftButtonDown()) {
        if (pPtr) {
            pPtr->transportSource.setPosition(0.0);
            pPtr->load_track_from_file(row);
            pPtr->transportSource.start();


            guiptr->wave.repaint();

            const double len = pPtr->transportSource.getLengthInSeconds();
            guiptr->positionSlider.setRange(0.0, len > 0.0 ? len : 1.0, 0.01);
            guiptr->positionSlider.setValue(0.0);

            guiptr->wave.looping_marker[0].position = 0.0;
            guiptr->wave.looping_marker[1].position = len > 0.0 ? len : 1.0;


            if (pPtr->reader && pPtr->meta.isEmpty())
            {
                pPtr->meta.clear();
                auto& metadata = pPtr->reader->metadataValues;
                auto keys = metadata.getAllKeys();
                auto vals = metadata.getAllValues();


                pPtr->meta += "Name : " + vals[1] + " Artest : " + vals[0];

            }


            guiptr->file_data.setText(pPtr->meta, NotificationType::dontSendNotification);
            guiptr->file_data.repaint();
        }
    }
    if (e.mods.isRightButtonDown()) {
        PopupMenu menu;
        menu.addSeparator();
        menu.addItem(1, "play from here");
        menu.addItem(2, "Delete item");
        menu.showMenuAsync(juce::PopupMenu::Options(),
            [this, row](int result)
            {
                this->menu_action(result, row);
            });
    }
}

void listModel::menu_action(int option, int row)
{
    auto it = items.begin();
    std::advance(it, row);
    if (option == 1)
    {
        
    }
    if (option == 2)
    {
        items.erase(it);
    }
}

