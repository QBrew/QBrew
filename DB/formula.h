#ifndef FORMULA_H 
#define FORMULA_H 
 
#include <QString> 
 
namespace qbrew 
{ 
 
class formula 
{ 
 
  private: 
    const QString name_; 
    QString version_; 
  public: 
    inline formula(QString name, QString version); 
    inline QString name(); 
    inline QString version(); 
    inline void setVersion(QString version); 
}; 
 
formula::formula(QString name, QString version) : name_{name}, version_{version} 
{ 
} 
 
QString formula::name() 
{ 
    return name_; 
} 
 
QString formula::version() 
{ 
    return version_; 
} 
 
void formula::setVersion(QString version) 
{ 
    version_ = version; 
} 
 
} 
 
#endif // FORMULA_H 
