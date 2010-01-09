#!/bin/sh
# 
# Build Script for miniweb
#

TARGET=miniweb
DOT_PRO_FILE=$TARGET.pro

QM=`which qmake`
QM4=`which qmake-qt4`

if [ -z $QM ] 
then
  RES3="0"
else
  RES3=`$QM -query QT_VERSION`
fi
if [ -z $QM4 ]
then
  RES4="0"
else
  RES4=`$QM4 -query QT_VERSION`
fi

MATCH3=`expr match $RES3 '4.'`
MATCH4=`expr match $RES4 '4.'`

QMAKE=qmake

if [ $MATCH3 -eq 2 ]
then
  QMAKE=$QM
else
  if [ $MATCH4 -eq 2 ]
  then
    QMAKE=$QM4
  else
    echo cannot find qmake for Qt4
    exit 1
  fi
fi

echo
echo Using $QMAKE
echo
echo Trying to build Makefile
echo

$QMAKE $DOT_PRO_FILE
OK=$?
if [ $OK -ne 0 ]
then
  echo Failed to build Makefile
  exit 1
fi

make clean
echo
echo Try to compile $TARGET
echo

make release

if [ -e $TARGET ] 
then
  echo
  echo successfully built $TARGET
  echo
  ls -l $TARGET
else
  echo 
  echo Could not build $TARGET
  echo
fi

