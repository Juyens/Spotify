#include "Song.h"
#include "Utils.h"

Song::Song(const std::string& name)
	: _name(name), _duration(0), _reproductions(0), _credits(new Credits()), _genres(new List<std::string>())
{
}

Song::Song(List<std::string>* genres, const std::string& name, std::uint32_t duration, std::uint64_t reproductions,
		   Credits* credits)
	: _genres(new List<std::string>()), _name(name), _duration(duration), _reproductions(reproductions), _credits(new Credits())
{
}

Song::~Song()
{
	delete _genres;
	delete _credits;
}

List<std::string>* Song::getGenres()
{
	return _genres;
}

void Song::setGenres(List<std::string>* genres)
{
	_genres = genres;
}

std::string Song::getName()
{
	return _name;
}

void Song::setName(const std::string& name)
{
	_name = name;
}

std::uint32_t Song::getDuration()
{
	return _duration;
}

void Song::setDuration(std::uint32_t duration)
{
	_duration = duration;
}

std::uint64_t Song::getReproductions()
{
	return _reproductions;
}

void Song::setReproductions(std::uint64_t reproductions)
{
	_reproductions = reproductions;
}

Credits* Song::getCredits()
{
	return _credits;
}

void Song::setCredits(Credits* credits)
{
	_credits = credits;
}

void Song::addGenre(const std::string& genre)
{
	_genres->addLast(genre);
}

void Song::printInfo()
{
    std::cout << "Mostrando informacion de la cancion..." << '\n';
    std::cout << "Nombre: " << _name << '\n';

    std::cout << "Generos: ";
    if (_genres->size() > 0)
    {
        for (uint i = 0; i < _genres->size(); ++i)
        {
            std::cout << _genres->getAtPosition(i);
            if (i != _genres->size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    else
    {
        std::cout << "No tiene generos asociados.";
    }
    std::cout << '\n';

    std::cout << "Duracion: " << _duration << "s" << '\n';

    std::cout << "Reproducciones: " << _reproductions << '\n';

    std::cout << "Discografica: " << _credits->getDiscography() << '\n';
    std::cout << "Autores: ";
    auto authors = _credits->getAuthor();
    for (uint i = 0; i < authors->size(); ++i)
    {
        std::cout << authors->getAtPosition(i);
        if (i != authors->size() - 1)
        {
            std::cout << ", ";
        }
    }

    PAUSE;
}
