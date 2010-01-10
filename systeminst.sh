#!/bin/sh

PROGRAM=miniweb

DEST=/usr/local/bin

install --strip $PROGRAM $DEST

ls -l $DEST/$PROGRAM
