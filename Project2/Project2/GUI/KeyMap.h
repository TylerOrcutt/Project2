#ifndef __KEY_MAP_H_
#define __KEY_MAP_H_
#include <string>

static std::string getShiftKey(std::string key){
  if(key=="1"){
    return "!";
  }
  if(key=="2"){
    return "@";
  }
  if(key=="3"){
    return "#";
  }
  if(key=="4"){
    return "$";
  }
  if(key=="5"){
    return "%";
  }
  if(key=="6"){
    return "^";
  }
  if(key=="7"){
    return "&";
  }
  if(key=="8"){
    return "*";
  }
  if(key=="9"){
    return "(";
  }
  if(key=="0"){
    return ")";
  }
  if(key=="-"){
    return "_";
  }
  if(key=="="){
    return "+";
  }
  if(key=="`"){
    return "~";
  }
  if(key=="/"){
    return "?";
  }
  if(key==","){
    return "<";
  }
  if(key=="."){
    return ">";
  }
  if(key==";"){
    return ":";
  }
  if(key=="'"){
    return "\"";
  }
  if(key=="["){
    return "{";
  }
  if(key=="]"){
    return "}";
  }
  if(key=="\\"){
    return "|";
  }

  return "";
}

#endif
