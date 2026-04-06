#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <IrrKlang/irrKlang.h>

#include <string>

// Simple Sound Manager, kinda thrown together

// Using very epic and awesome design patterns to make Nesty proud
class SoundManager {
public:
	static SoundManager& getInstance() {
		static SoundManager instance;
		return instance;
	}

	void clearSoundManager() {
		if (soundEngine_) {
			soundEngine_->removeAllSoundSources();
			std::cout << "SoundManager::clearSoundManager : soundEngine_ removed all its sound sources" << std::endl;
		}
		if (musicEngine_) {
			musicEngine_->removeAllSoundSources();
			std::cout << "SoundManager::clearSoundManager : musicEngine_ removed all its sound sources" << std::endl;
		}
	}

	void setMusicTrack(std::string soundFilepath) {
		musicEngine_->removeAllSoundSources();
		musicEngine_->play2D(soundFilepath.data(), true);
		std::cout << "SoundManager::setMusicTrack : Set music track to " << soundFilepath << std::endl;
		if (musicPauseFlag_) {
			std::cout << "SoundManager::setMusicTrack : Music is currently paused so new music track is queued till unpause " << std::endl;
			musicEngine_->setAllSoundsPaused(true);
		}
	}

	void playSound2D(std::string soundFilepath) {
		soundEngine_->play2D(soundFilepath.data(), false);
		std::cout << "SoundManager::playSound2D : Playing 2D sound " << soundFilepath << std::endl;
		if (soundPauseFlag_) {
			std::cout << "SoundManager::playSound2D : Sound is currently paused so new sound is queued till unpause " << std::endl;
			soundEngine_->setAllSoundsPaused(true);
		}
	}

	bool isSoundPauseFlagged() const { return soundPauseFlag_; }
	bool isMusicPauseFlagged() const { return musicPauseFlag_; }

	void pauseSounds() {
		if (!soundPauseFlag_) {
			soundPauseFlag_ = true;
			soundEngine_->setAllSoundsPaused(true);
			std::cout << "SoundManager::pauseSounds : Sounds are now paused " << std::endl;
		}
		else {
			return;
		}
	}

	void unpauseSounds() {
		if (soundPauseFlag_) {
			soundPauseFlag_ = false;
			soundEngine_->setAllSoundsPaused(false);
			std::cout << "SoundManager::unpauseSounds : Sounds are now unpaused " << std::endl;
		}
		else {
			return;
		}
	}

	void pauseMusic() {
		if (!musicPauseFlag_) {
			musicPauseFlag_ = true;
			musicEngine_->setAllSoundsPaused(true);
			std::cout << "SoundManager::pauseMusic : Music is now paused " << std::endl;
		}
		else {
			return;
		}
	}

	void unpauseMusic() {
		if (musicPauseFlag_) {
			musicPauseFlag_ = false;
			musicEngine_->setAllSoundsPaused(false);
			std::cout << "SoundManager::unpauseMusic : Music is now unpaused " << std::endl;
		}
		else {
			return;
		}
	}

	void pauseAll() {
		pauseSounds();
		pauseMusic();
	}

	void unpauseAll() {
		unpauseSounds();
		unpauseMusic();
	}

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(const SoundManager&&) = delete;
	SoundManager& operator=(const SoundManager&&) = delete;

private:
	SoundManager() {
		soundEngine_ = irrklang::createIrrKlangDevice();
		musicEngine_ = irrklang::createIrrKlangDevice();
	}

	~SoundManager() {
		if (soundEngine_) {
			soundEngine_->drop();
		}
		if (musicEngine_) {
			musicEngine_->drop();
		}
	}

	irrklang::ISoundEngine* soundEngine_;
	irrklang::ISoundEngine* musicEngine_;

	bool soundPauseFlag_ = false;
	bool musicPauseFlag_ = false;
};

#endif