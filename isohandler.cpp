#include <iostream>
#include <archive.h>
#include <archive_entry.h>
#include <filesystem>

void extractIso(const std::string &isoPath) {
    struct archive *a = archive_read_new();
    struct archive_entry *entry;
    
    if (archive_read_open_filename(a, isoPath.c_str(), 10240) != ARCHIVE_OK) {
        std::cerr << "Error: Could not open ISO file." << std::endl;
        archive_read_free(a);
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *entryName = archive_entry_pathname(entry);
        std::cout << "Extracting: " << entryName << std::endl;
        archive_read_data_skip(a);
    }

    archive_read_free(a);
}
