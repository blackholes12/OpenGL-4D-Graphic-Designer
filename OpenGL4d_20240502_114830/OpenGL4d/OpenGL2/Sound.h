#pragma once
//#include<SFML/Audio.hpp>
//#include<iostream>
class Sound
{
private:
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
public:
	Sound(const char* fileName)
	{
		if (!this->soundBuffer.loadFromFile(fileName))
		{
			std::cout << "ERROR::SOUND.H::SOUND_INIT_FAILED" << "\n";
		}
		sf::Listener::setPosition((float)0.0f, (float)0.0f, (float)0.0f);
		this->sound.setPosition(0.0f, 0.0f, 0.0f);
		this->sound.setBuffer(this->soundBuffer);
		this->sound.setMinDistance(5.0f);
		this->sound.setAttenuation(0.5f);
		this->sound.setLoop(false);
	}
	void play(float distance,float volume)
	{
		float distance2 = glm::max(distance/5.f, 1.f);
		this->sound.setVolume(volume / distance2);
		this->sound.play();
	}
	void set_volume(float volume)
	{
		this->sound.setVolume(volume);
	}
	void set_pitch(float volume)
	{
		this->sound.setPitch(volume);
	}
	~Sound(){}
};

class Music
{
private:
public:
	sf::Music music;
	Music(const char* fileName)
	{
		if (!this->music.openFromFile(fileName))
		{
			std::cout << "ERROR::SOUND.H::MUSIC_INIT_FAILED" << "\n";
		}
	}
	void play()
	{
		this->music.play();
	}
	void stop()
	{
		if (this->music.getStatus() != 0)
		{
			this->music.stop();
		}
	}
	void set_volume(float volume)
	{
		this->music.setVolume(volume);
	}
	void set_pitch(float volume)
	{
		this->music.setPitch(volume);
	}
	~Music(){}
};

static void switch_musics(std::vector<Music*> musics)
{
	bool isStop=true;
	for (Music* i : musics)
	{
		if (i->music.getStatus() != 0)
		{
			isStop = false;
		}
	}
	if (isStop)
	{
		musics[rand() % musics.size()]->play();
	}
}
