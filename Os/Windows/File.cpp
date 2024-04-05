#include <OpenHome/Private/File.h>

namespace OpenHome {

IFile* IFile::Open(const TChar* aFilename, FileMode aFileMode)
{
    // check for names that came from file:// uris so may have the form /[drive]:/
    if (aFilename[0] == '/' && aFilename[1] != '\0' && aFilename[2] == ':') {
        aFilename++;
    }
    return new FileAnsi(aFilename, aFileMode);
}

} // namespace OpenHome
