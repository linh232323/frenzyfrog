#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^G:/Cocos2dx/cygwin_install/lib!/usr/lib!ig;s! G:/Cocos2dx/cygwin_install/lib! /usr/lib!ig;s!^G:/Cocos2dx/cygwin_install/bin!/usr/bin!ig;s! G:/Cocos2dx/cygwin_install/bin! /usr/bin!ig;s!^G:/Cocos2dx/cygwin_install/!/!ig;s! G:/Cocos2dx/cygwin_install/! /!ig;s!^G:!/cygdrive/g!ig;s! G:! /cygdrive/g!ig;s!^C:!/cygdrive/c!ig;s! C:! /cygdrive/c!ig;' $1.org > $1 && rm -f $1.org
fi
