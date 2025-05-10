#pragma once

#include "Credits.h"
#include "List.h"
#include "Input.h"

#include <string>
#include <iostream>

class Song
{
private:
	List<std::string>* _genres;
	std::string _name;
	std::uint32_t _duration;
	std::uint64_t _reproductions;
	Credits* _credits;

public:
	Song(const std::string& name = "unnamed");
	Song(List<std::string>* genres, const std::string& name, std::uint32_t duration,
		 std::uint64_t reproductions, Credits* credits);

	~Song();

	List<std::string>* getGenres();
	void setGenres(List<std::string>* genres);

	std::string getName();
	void setName(const std::string& name);

	std::uint32_t getDuration();
	void setDuration(std::uint32_t duration);

	std::uint64_t getReproductions();
	void setReproductions(std::uint64_t reproductions);

	Credits* getCredits();
	void setCredits(Credits* credits);

	void addGenre(const std::string& genre);

	void printInfo();
};