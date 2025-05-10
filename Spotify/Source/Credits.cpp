#include "Credits.h"

Credits::Credits()
	: _authors(new List<std::string>())
{
}

Credits::Credits(List<std::string>* authors, const std::string& discography)
	: _authors(new List<std::string>()), _discography(discography)
{

}

Credits::~Credits()
{
	delete _authors;
}

List<std::string>* Credits::getAuthor()
{
	return _authors;
}

void Credits::setAuthors(List<std::string>* authors)
{
	_authors = authors;
}

std::string Credits::getDiscography()
{
	return _discography;
}

void Credits::setDiscography(const std::string& discography)
{
	_discography = discography;
}

void Credits::addAuthor(const std::string& author)
{
	_authors->addLast(author);
}
