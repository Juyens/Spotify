#include "DataManager.h"
#include "Utils.h"
#include "Input.h"

void DataManager::loadDataFromFile()
{
    std::ifstream file(_fileName);
    if (!file.is_open())
    {
        std::cerr << "Warning: Unable to open the file " << _fileName << " for reading." << std::endl;
        return;
    }

    Artist* currentArtist = nullptr;
    Album* currentAlbum = nullptr;
    Song* currentSong = nullptr;
    Credits* currentCredits = nullptr;

    recursiveData(file, 0, currentArtist, currentAlbum, currentSong, currentCredits);
}

void DataManager::recursiveData(std::ifstream& file, int previous, Artist* currentArtist, Album* currentAlbum, Song* currentSong, Credits* currentCredits)
{
    std::string line;
    if (!getline(file, line))
    {
        if (previous == 2)
        {
            currentArtist->addAlbum(currentAlbum);
            _artist->addLast(currentArtist);
        }
        return;
    }

    if (line.empty())
    {
        recursiveData(file, previous, currentArtist, currentAlbum, currentSong, currentCredits);
        return;
    }

    int tabLevel = countTabs(line);

    if (tabLevel == 0) 
    {
        if (previous == 2)
        {
            currentArtist->addAlbum(currentAlbum);
            _artist->addLast(currentArtist);
        }

        std::string nameArtist = line.substr(line.find(":") + 2);
        currentArtist = new Artist();
        currentArtist->setName(nameArtist);
    }
    else if (tabLevel == 1) 
    {
        if (previous == 2) 
        {
            currentArtist->addAlbum(currentAlbum);
        }

        std::string nameAlbum = line.substr(line.find(":") + 2);
        currentAlbum = new Album();
        currentAlbum->setName(nameAlbum);
    }
    else if (tabLevel == 2) 
    {
        if (!currentSong)
            currentSong = new Song();

        if (!currentCredits)
            currentCredits = new Credits();

        if (line.find("Song") != std::string::npos)
        {
            std::string nameSong = line.substr(line.find(":") + 2);
            currentSong->setName(nameSong);
        }
        else if (line.find("Genres") != std::string::npos)
        {
            std::string genres = line.substr(line.find(":") + 2);
            auto genresList = split(genres, ',');
            currentSong->setGenres(genresList);
        }
        else if (line.find("Duration") != std::string::npos)
        {
            std::string durationStr = line.substr(line.find(":") + 2);
            std::uint32_t duration = std::stoi(durationStr);
            currentSong->setDuration(duration);
        }
        else if (line.find("Reproductions") != std::string::npos)
        {
            std::string reproductionsStr = line.substr(line.find(":") + 2);
            std::uint64_t reproductions = std::stoll(reproductionsStr);
            currentSong->setReproductions(reproductions);
        }
        else if (line.find("Discography") != std::string::npos)
        {
            std::string discography = line.substr(line.find(":") + 2);
            currentCredits->setDiscography(discography);
        }
        else if (line.find("Authors") != std::string::npos)
        {
            std::string authors = line.substr(line.find(":") + 2);
            auto authorsList = split(authors, ',');
            currentCredits->setAuthors(authorsList);
            currentSong->setCredits(currentCredits);
            currentAlbum->addSong(currentSong);

            currentSong = new Song();
            currentCredits = new Credits();
        }
    }

    recursiveData(file, tabLevel, currentArtist, currentAlbum, currentSong, currentCredits);
}

int DataManager::countTabs(const std::string& line)
{
	int count = 0;
	size_t pos = line.find('\t');
	while (pos != std::string::npos)
	{
		count++;
		pos = line.find('\t', pos + 1);
	}
	return count;
}

List<std::string>* DataManager::split(const std::string& input, char delimiter)
{
	List<std::string>* result = new List<std::string>();
	std::stringstream ss(input);
	std::string item;

	while (std::getline(ss, item, delimiter))
	{
		result->addLast(item);
	}

	return result;
}

// --------------------------------------- //

DataManager::DataManager()
    : _artist(new List<Artist*>())
{
    loadDataFromFile();
}

DataManager::~DataManager()
{
    for (uint i = 0; i < _artist->size(); ++i)
    {
        delete _artist->getAtPosition(i);
    }
    delete _artist;
}

Artist* DataManager::searchArtist()
{
    std::cout << "Iniciando busqueda de Artista..." << '\n';

    auto nameArtist = validatedInput<std::string>(
        "Ingrese el nombre del artista: ",
        "\n:: Nombre no valida, vuelva a intentarlo.\n\n"
    );

    std::string nameLower = toLower(nameArtist);
    Artist* artist = nullptr;

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* aux_artist = _artist->getAtPosition(i);
        if (toLower(aux_artist->getName()).find(nameLower) != std::string::npos)
        {
            artist = aux_artist;
        }
    }

    if (!artist)
    {
        MSG("\n:: No se encontraron coincidencias.");
        return nullptr;
    }

    MSG("\n:: Artista \"" + artist->getName() + "\" encontrado...");

    return artist;
}

Album* DataManager::searchAlbum()
{
    std::cout << "Iniciando busqueda de album..." << '\n';

    auto nameAlbum = validatedInput<std::string>(
        "Ingrese el nombre del album: ",
        "\n:: Nombre no valido, vuelva a intentarlo.\n\n"
    );

    std::string nameLower = toLower(nameAlbum);
    Album* album = nullptr;

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* aux_artist = _artist->getAtPosition(i);
        List<Album*>* albums = aux_artist->getAlbums();

        for (uint j = 0; j < albums->size(); ++j)
        {
            Album* aux_album = albums->getAtPosition(j);
            if (toLower(aux_album->getName()).find(nameLower) != std::string::npos)
            {
                album = aux_album;
                break;
            }
        }

        if (album)
        {
            break;
        }
    }

    if (!album)
    {
        MSG("\n:: No se encontraron coincidencias para el album.");
        return nullptr;
    }

    MSG("\n:: Album \"" + album->getName() + "\" encontrado...");
    return album;
}

Song* DataManager::searchSong()
{
    std::cout << "Iniciando busqueda de cancion..." << '\n';

    auto nameSong = validatedInput<std::string>(
        "Ingrese el nombre de la cancion: ",
        "\n:: Nombre no valido, vuelva a intentarlo.\n\n"
    );

    std::string nameLower = toLower(nameSong);
    Song* song = nullptr;

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* aux_artist = _artist->getAtPosition(i);
        List<Album*>* albums = aux_artist->getAlbums();

        for (uint j = 0; j < albums->size(); ++j)
        {
            Album* aux_album = albums->getAtPosition(j);
            List<Song*>* songs = aux_album->getSongs();

            for (uint k = 0; k < songs->size(); ++k)
            {
                Song* aux_song = songs->getAtPosition(k);
                if (toLower(aux_song->getName()).find(nameLower) != std::string::npos)
                {
                    song = aux_song;
                    break;
                }
            }

            if (song)
            {
                break;
            }
        }

        if (song)
        {
            break;
        }
    }

    if (!song)
    {
        MSG("\n:: No se encontraron coincidencias para la cancion.");
        return nullptr;
    }

    MSG("\n:: Cancion \"" + song->getName() + "\" encontrada...");
    return song;
}

List<Artist*>* DataManager::getArtists()
{
    return _artist;
}

void DataManager::printData()
{
	for (uint i = 0; i < _artist->size(); ++i)
	{
		auto artist = _artist->getAtPosition(i);
		std::cout << "Artist: " << artist->getName() << '\n';

		auto albums = artist->getAlbums();
		for (uint j = 0; j < albums->size(); ++j)
		{
			auto album = albums->getAtPosition(j);
			std::cout << "  Album: " << album->getName() << '\n';

			auto songs = album->getSongs();
			for (uint k = 0; k < songs->size(); ++k)
			{
				auto song = songs->getAtPosition(k);
				std::cout << "      Song: " << song->getName() << '\n';

				std::cout << "      Genres: ";
				auto genresSize = song->getGenres()->size();
				for (uint l = 0; l < genresSize; ++l)
				{
					auto genre = song->getGenres()->getAtPosition(l);
					std::cout << genre;

					if (l == genresSize - 1)
					{
						std::cout << '\n';
						break;
					}

					std::cout << ",";
				}

				std::cout << "      Duration: " << song->getDuration() << '\n';
				std::cout << "      Reproductions: " << song->getReproductions() << '\n';
				std::cout << "      Discography: " << song->getCredits()->getDiscography() << '\n';
                std::cout << "      Authors: ";

				auto authorsSize = song->getCredits()->getAuthor()->size();
				for (uint m = 0; m < authorsSize; ++m)
				{
					auto author = song->getCredits()->getAuthor()->getAtPosition(m);
					std::cout << author;

					if (m == authorsSize - 1)
					{
						std::cout << '\n';
						break;
					}

					std::cout << ",";
				}
			}
		}
	}
}

List<Song*>* DataManager::getSongsByArtist(const std::string& artistName)
{
    List<Song*>* allSongs = new List<Song*>();

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* artist = _artist->getAtPosition(i);
        if (toLower(artist->getName()).find(toLower(artistName)) != std::string::npos)
        {
            List<Album*>* albums = artist->getAlbums();
            for (uint j = 0; j < albums->size(); ++j)
            {
                Album* album = albums->getAtPosition(j);
                List<Song*>* songs = album->getSongs();
                for (uint k = 0; k < songs->size(); ++k)
                {
                    allSongs->addLast(songs->getAtPosition(k));
                }
            }
            return allSongs;
        }
    }

    std::cout << ":: No se encontraron canciones para el artista: " << artistName << std::endl;
    return nullptr;
}

List<Song*>* DataManager::getSongsByAlbum(const std::string& albumName)
{
    List<Song*>* allSongs = new List<Song*>();

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* artist = _artist->getAtPosition(i);

        List<Album*>* albums = artist->getAlbums();

        for (uint j = 0; j < albums->size(); ++j)
        {
            Album* album = albums->getAtPosition(j);

            if (toLower(album->getName()).find(toLower(albumName)) != std::string::npos)
            {
                List<Song*>* songs = album->getSongs();
                for (uint k = 0; k < songs->size(); ++k)
                {
                    allSongs->addLast(songs->getAtPosition(k));
                }
                return allSongs;
            }
        }
    }

    std::cout << ":: No se encontraron canciones en el álbum: " << albumName << std::endl;
    return nullptr;
}

List<Album*>* DataManager::getAllAlbums()
{
    List<Album*>* allAlbums = new List<Album*>();

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* artist = _artist->getAtPosition(i);
        List<Album*>* albums = artist->getAlbums();

        for (uint j = 0; j < albums->size(); ++j)
        {
            allAlbums->addLast(albums->getAtPosition(j));
        }
    }

    return allAlbums;
}

List<Song*>* DataManager::getAllSongs()
{
    List<Song*>* allSongs = new List<Song*>();

    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* artist = _artist->getAtPosition(i);
        List<Album*>* albums = artist->getAlbums();

        for (uint j = 0; j < albums->size(); ++j)
        {
            Album* album = albums->getAtPosition(j);
            List<Song*>* songs = album->getSongs();

            for (uint k = 0; k < songs->size(); ++k)
            {
                allSongs->addLast(songs->getAtPosition(k));
            }
        }
    }

    return allSongs;
}

List<Song*>* DataManager::getSongsSortedByDurationBubbleSort(bool ascending)
{
    List<Song*>* allSongs = getAllSongs();
    bool swapped;

    for (uint i = 0; i < allSongs->size() - 1; ++i)
    {
        swapped = false;

        for (uint j = 0; j < allSongs->size() - 1 - i; ++j)
        {
            Song* song1 = allSongs->getAtPosition(j);
            Song* song2 = allSongs->getAtPosition(j + 1);

            bool shouldSwap = false;
            if (!ascending)
            {
                shouldSwap = song1->getDuration() > song2->getDuration();
            }
            else
            {
                shouldSwap = song1->getDuration() < song2->getDuration();
            }

            if (shouldSwap)
            {
                allSongs->swap(j, j + 1);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }

    return allSongs;
}

List<Song*>* DataManager::getSongsSortedByReproductions(bool ascending)
{
    List<Song*>* allSongs = getAllSongs();

    // Algoritmo de ordenamiento por selección (Selection Sort)
    for (uint i = 0; i < allSongs->size(); ++i)
    {
        for (uint j = i + 1; j < allSongs->size(); ++j)
        {
            Song* songI = allSongs->getAtPosition(i);
            Song* songJ = allSongs->getAtPosition(j);

            bool shouldSwap = false;
            if (!ascending)
            {
                shouldSwap = songI->getReproductions() > songJ->getReproductions();  // Mayor a menor
            }
            else
            {
                shouldSwap = songI->getReproductions() < songJ->getReproductions();  // Menor a mayor
            }

            if (shouldSwap)
            {
                allSongs->swap(i, j);
            }
        }
    }

    return allSongs;
}

Artist* DataManager::findArtistByName(const std::string& name)
{
    for (uint i = 0; i < _artist->size(); ++i)
    {
        Artist* artist = _artist->getAtPosition(i);
        if (toLower(artist->getName()) == toLower(name))
        {
            return artist;
        }
    }
    return nullptr;
}

Album* DataManager::findAlbumByName(const std::string& name)
{
    for (uint i = 0; i < _artist->size(); ++i)
    {
        List<Album*>* albums = _artist->getAtPosition(i)->getAlbums();
        for (uint j = 0; j < albums->size(); ++j)
        {
            Album* album = albums->getAtPosition(j);
            if (toLower(album->getName()) == toLower(name))
            {
                return album;
            }
        }
    }
    return nullptr;
}

Song* DataManager::findSongByName(const std::string& name)
{
    for (uint i = 0; i < _artist->size(); ++i)
    {
        List<Album*>* albums = _artist->getAtPosition(i)->getAlbums();
        for (uint j = 0; j < albums->size(); ++j)
        {
            List<Song*>* songs = albums->getAtPosition(j)->getSongs();
            for (uint k = 0; k < songs->size(); ++k)
            {
                Song* song = songs->getAtPosition(k);
                if (toLower(song->getName()) == toLower(name))
                {
                    return song;
                }
            }
        }
    }
    return nullptr;
}

std::map<std::string, List<Song*>*> DataManager::getSongsGroupedByGenre()
{
    std::map<std::string, List<Song*>*> grouped;
    List<Song*>* allSongs = getAllSongs();

    for (uint i = 0; i < allSongs->size(); ++i)
    {
        Song* song = allSongs->getAtPosition(i);
        List<std::string>* genres = song->getGenres();

        for (uint j = 0; j < genres->size(); ++j)
        {
            const std::string& genre = genres->getAtPosition(j);

            if (grouped.find(genre) == grouped.end())
            {
                grouped[genre] = new List<Song*>();
            }

            grouped[genre]->addLast(song);
        }
    }

    return grouped;
}
