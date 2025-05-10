#pragma once

#include "List.h"

#include <string>

class Credits
{
private:
	List<std::string>* _authors;
	std::string _discography;

public:
	Credits();
	Credits(List<std::string>* authors, const std::string& discography);
	~Credits();

	List<std::string>* getAuthor();
	void setAuthors(List<std::string>* authors);

	std::string getDiscography();
	void setDiscography(const std::string& discography);

	void addAuthor(const std::string& author);
};