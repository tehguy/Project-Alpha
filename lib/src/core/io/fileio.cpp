/*
    CPPAdventures
    Copyright (C) 2017  TehGuy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <include/core/io/fileio.hpp>

FileIO::FileIO() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

bool FileIO::openFile(std::string filePath, std::ofstream *stream) {
    stream->open(filePath);
    return stream->is_open();
}

bool FileIO::openFile(std::string filePath, std::ifstream *stream) {
    stream->open(filePath);
    return stream->is_open();
}

void FileIO::closeFile(std::ofstream *stream) {
    stream->close();
}

void FileIO::closeFile(std::ifstream *stream) {
    stream->close();
}
