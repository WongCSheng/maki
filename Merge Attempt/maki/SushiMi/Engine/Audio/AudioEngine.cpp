/*!
@file    AudioEngine.cpp
@author	 Aurelia Chong

         Audio engine that manages all audio related functions
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "AudioEngine.h"

/*                                                                  Constructor
----------------------------------------------------------------------------- */
_audioManager::_audioManager(void)
{
    /*                                                            
    * Create the main system object.
    ----------------------------------------------------------------------------- */ 
    System_Create(&fmodSystem);

    /*
   *   Initialize FMOD.
   ----------------------------------------------------------------------------- */
    fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);

    /*
    *   Create the channel group
    ----------------------------------------------------------------------------- */
    fmodSystem->createChannelGroup("inGameSoundEffects", &channelGroup);

    /*
    *   Set music channel group
    ----------------------------------------------------------------------------- */
    channel->setChannelGroup(channelGroup);
    musicChannel->setChannelGroup(channelGroup);

    /*
    *   Set a callback on the channel.
    ----------------------------------------------------------------------------- */
    musicChannel->setCallback(&channelGroupCallback);

}

/*                                                                  Destructor
----------------------------------------------------------------------------- */
_audioManager::~_audioManager(void)
{
}

/*!				void _audioManager::PlayClip(string clipName)
@param			string clipName
@return none

                Plays music clip
*/
void _audioManager::PlayClip(string clipName)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = soundDatabase.find(clipName);
    if (search != soundDatabase.end())
        audioClip = search->second;

    // Play the sound.
    fmodSystem->playSound(audioClip, nullptr, false, &channel);
}

/*!				void _audioManager::PlayMusic(string musicTrack)
@param			string musicTrack
@return none

                Plays music track
*/
void _audioManager::PlayMusic(string musicTrack)
{
    // Create the sound.
    Sound* audioClip = 0;
    auto search = musicDatabase.find(musicTrack);
    if (search != musicDatabase.end())
        audioClip = search->second;

    // Play the music.
    musicChannel->stop();
    fmodSystem->playSound(audioClip, nullptr, false, &musicChannel);
}

/*!				void _audioManager::StopMusic(void)
@param			void
@return none

                Stop playing music
*/
void _audioManager::StopMusic(void)
{
    // stop play the sound.
    musicChannel->stop();
}

/*!				void _audioManager::SetAudioVolume(float volume)
@param			float volume
@return none

                Set volume for audios
*/
void _audioManager::SetAudioVolume(float volume)
{
    channel->setVolume(volume);
}

/*!				void _audioManager::SetMusicVolume(float volume)
@param			float volume
@return none

                Set volume for music channel
*/
void _audioManager::SetMusicVolume(float volume)
{
    musicChannel->setVolume(volume);
}

/*!				void _audioManager::Update()
@param			
@return none

               update music play
*/
void _audioManager::Update()
{
    fmodSystem->update();
}

/*!				void _audioManager::CleanPlaying()
@param
@return none

               clean up music play
*/
void _audioManager::CleanPlaying()
{
    // Clean up.
    map<string, Sound*>::iterator start;
    for (start = soundDatabase.begin(); start != soundDatabase.end(); start++)
        start->second->release();

    for (start = musicDatabase.begin(); start != musicDatabase.end(); start++)
        start->second->release();
    //channelGroup->release();
    fmodSystem->release();
}

/*!				void _audioManager::LoadSound(string name)
{
@param          string name
@return none

               Load sound into directory
*/
void _audioManager::LoadSound(string name)
{
    string pathString = "./Assets/Sound/" + name + '\0';
    char* pathName = new char[pathString.length() + 1];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* sound = 0;
    fmodSystem->createSound(pathName, FMOD_DEFAULT, nullptr, &sound);
    soundDatabase[name] = sound;
    delete[] pathName;
}

/*!				void _audioManager::LoadMusic(string name)
{
@param          string name
@return none

               Load music into directory
*/
void _audioManager::LoadMusic(string name)
{
    string pathString = "./Assets/Music/" + name + '\0';
    char* pathName = new char[pathString.length() + 1];
    copy(pathString.begin(), pathString.end(), pathName);
    Sound* music = 0;
    fmodSystem->createSound(pathName, FMOD_LOOP_NORMAL, nullptr, &music);
    musicDatabase[name] = music;
    delete[] pathName;
}

/*!				void _audioManager::UnloadSound(string name)
{
@param          string name
@return none

               Unload sound into directory
*/
void _audioManager::UnloadSound(string name)
{
    if (isActive && soundDatabase.find(name) != soundDatabase.end())
        soundDatabase[name]->release();
}

/*!				void _audioManager::UnloadMusic(string name)
{
@param          string name
@return none

               Unload music into directory
*/
void _audioManager::UnloadMusic(string name)
{
    if (isActive && musicDatabase.find(name) != musicDatabase.end())
        musicDatabase[name]->release();
}

/*!				void _audioManager::Free(void)
{
@param          
@return none

               Free memory space
*/
void _audioManager::Free(void)
{
    fmodSystem->release();
    isActive = false;
}

/*!				void _audioManager::GetSound(string name)
{
@param          string name
@return none

               get sound 
*/
Sound* _audioManager::GetSound(string name)
{
    auto search = soundDatabase.find(name);
    if (search != soundDatabase.end())
        return search->second;
    return NULL;
}

/*
   *   Instances
   ----------------------------------------------------------------------------- */
_audioManager& _audioManager::Instance(void)
{
    static _audioManager instance;
    return instance;
}

/*
   *   get channel
   ----------------------------------------------------------------------------- */
Channel* _audioManager::GetMusicChannel(void)
{
    return musicChannel;
}

FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
 void* commandData1, void* commandData2)
{
    if (controlType == FMOD_CHANNELCONTROL_CHANNEL 
        && AudioManager.GetMusicChannel() == (Channel*)channelControl 
        && callbackType == FMOD_CHANNELCONTROL_CALLBACK_END)
    {
        // music ended
    }

    return FMOD_OK;
}
