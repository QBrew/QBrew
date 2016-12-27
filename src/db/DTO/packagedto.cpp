#include "packagedto.h"

namespace qbrew
{

QString PackageDTO::toString()
{
    QString result;
    result.append("Filename : " + filename_);
    result.append("Name : " + name_);
    result.append("\nVersion : " + version_);
    result.append("\nURL : " + url_);
    result.append("\nHomepage :" + homepage_);
    result.append("\nDesc : " + desc_ );
    result.append("\nInstalled : ");
    result.append(isInstalled_ ? "true" : "false");
    result.append("\nFavorite : ");
    result.append(isFavorite_ ? "true" : "false");
    return result;
}

}
