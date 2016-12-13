#include "formuladto.h"

namespace qbrew
{

QString FormulaDTO::toString()
{
    QString result;
    result.append("Name : " + name_);
    result.append("\nURL : " + url_);
    result.append("\nHomepage :" + homepage_);
    result.append("\nDesc : " + desc_ );
    return result;
}

}
