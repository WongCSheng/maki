/*!
@file    AudioEngine.cpp
@author	 Aurelia Chong

         Audio engine that manages all audio related functions
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "AudioEngine.h"
#include "../Factory/Factory.h"

namespace Core
{
    /*                                                                  Constructor
    ----------------------------------------------------------------------------- */
    _audioManager::_audioManager(void)
    {
        /*
        * Create the main system object.
        ----------------------------------------------------------------------------- */
        FMOD::System_Create(&fmodSystem);

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

    /*!				void _audioManager::PlaySFX(string clipName)
    @param			string clipName
    @return none

                    Plays music clip
    */
    void _audioManager::PlaySFX(std::string clipName)
    {
        // Create the sound.
        FMOD::Sound* audioClip = 0;
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
    void _audioManager::PlayMusic(std::string musicTrack)
    {
        // Create the sound.
        FMOD::Sound* audioClip = 0;
        auto search = musicDatabase.find(musicTrack);
        if (search != musicDatabase.end())
            audioClip = search->second;

        // Play the music.
        musicChannel->stop();
        fmodSystem->playSound(audioClip, nullptr, false, &musicChannel);
    }

    /*!				void _audioManager::PlayVoice(string voiceClip)
    @param			string voiceClip
    @return none

                    Plays voice
    */
    void _audioManager::PlayVoice(std::string voiceClip)
    {
        // Create the sound.
        FMOD::Sound* audioClip = 0;
        auto search = soundDatabase.find(voiceClip);
        if (search != soundDatabase.end())
            audioClip = search->second;

        // Play the sound.
        fmodSystem->playSound(audioClip, nullptr, false, &channel);
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

    /*!				void _audioManager::StopSFX(void)
    @param			void
    @return none

                    Stop playing Sound Effects
    */
    void _audioManager::StopSFX(void)
    {
        // stop play the sound.
        channel->stop();
    }

    /*!				void _audioManager::StopVoice(void)
    @param			void
    @return none

                    Stop playing Voices
    */
    void _audioManager::StopVoice(void)
    {
        // stop play the sound.
        channel->stop();
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
        FMOD::Sound* snd = nullptr;
        musicChannel->getCurrentSound(&snd);
        
        musicChannel->stop();
        musicChannel->setVolume(volume);
        fmodSystem->playSound(snd, nullptr, false, &musicChannel);
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
        std::map<std::string, FMOD::Sound*>::iterator start;
        for (start = soundDatabase.begin(); start != soundDatabase.end(); start++)
            start->second->release();

        for (start = musicDatabase.begin(); start != musicDatabase.end(); start++)
            start->second->release();
        //channelGroup->release();
        fmodSystem->release();
    }

    /*!				void _audioManager::LoadSFX(string name)
    {
    @param          string name
    @return none

                   Load sound into directory
    */
    void _audioManager::LoadSFX(std::string name)
    {        
        std::string pathString = "../Assets/Audio/SFX/" + name + '\0';
        char* pathName = new char[pathString.length() + 1];
        std::copy(pathString.begin(), pathString.end(), pathName);
        FMOD::Sound* sound = 0;
        fmodSystem->createSound(pathName, FMOD_DEFAULT, nullptr, &sound);
        soundDatabase[name] = sound;
        delete[] pathName;
    }

    /*!				void _audioManager::LoadVoice(string name)
    {
    @param          string name
    @return none

                   Load sound into directory
    */
    void _audioManager::LoadVoice(std::string name)
    {
        std::string pathString = "../Assets/Audio/Voice-over/" + name + '\0';
        char* pathName = new char[pathString.length() + 1];
        std::copy(pathString.begin(), pathString.end(), pathName);
        FMOD::Sound* sound = 0;
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
    void _audioManager::LoadMusic(std::string name)
    {
        std::string pathString = "../Assets/Audio/Music/" + name + '\0';
        char* pathName = new char[pathString.length() + 1];
        std::copy(pathString.begin(), pathString.end(), pathName);
        FMOD::Sound* music = 0;
        fmodSystem->createSound(pathName, FMOD_LOOP_NORMAL, nullptr, &music);
        musicDatabase[name] = music;
        delete[] pathName;
    }

    /*!				void _audioManager::UnLoadSFX(string name)
    {
    @param          string name
    @return none

                   Unload sound into directory
    */
    void _audioManager::UnLoadSFX(std::string name)
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
    void _audioManager::UnloadMusic(std::string name)
    {
        if (isActive && musicDatabase.find(name) != musicDatabase.end())
            musicDatabase[name]->release();
    }

    /*!				void _audioManager::UnloadVoice(string name)
    {
    @param          string name
    @return none

                   Unload voice into directory
    */
    void _audioManager::UnloadVoice(std::string name)
    {
        if (isActive && soundDatabase.find(name) != soundDatabase.end())
            soundDatabase[name]->release();
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
    FMOD::Sound* _audioManager::GetSound(std::string name)
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
    FMOD::Channel* _audioManager::GetMusicChannel(void)
    {
        return musicChannel;
    }

    FMOD_RESULT F_CALLBACK channelGroupCallback(FMOD_CHANNELCONTROL* channelControl,
        FMOD_CHANNELCONTROL_TYPE controlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType,
        void* commandData1, void* commandData2)
    {
        if (controlType == FMOD_CHANNELCONTROL_CHANNEL
            && AudioManager.GetMusicChannel() == (FMOD::Channel*)channelControl
            && callbackType == FMOD_CHANNELCONTROL_CALLBACK_END)
        {
            // music ended
        }

        commandData1;
        commandData2;

        return FMOD_OK;
    }
}