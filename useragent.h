#ifndef USERAGENT_H
#define USERAGENT_H

namespace miniweb {


class UserAgent {

public:

  QString ID () { return id; }
  QString UAString () { return uaString; }
  int     Wide () { return wide; }
  int     High () { return high; }
  
  void SetID (const QString i) { id = i; }
  void SetUAString (const QString ua) { uaString = ua; }
  void SetWide (const int w) { wide = w; }
  void SetHigh (const int h) { high = h; }
  
  bool Domify (QDomDocument & doc, QDomElement & el);
  
  bool ParseDom (QDomElement & el);
  
private:

  QString id;
  QString uaString;
  int     wide;
  int     high;
  
}

}



#endif
